#pragma once

#include "quickgui/components/element.h"

#include <memory>
#include <string>
#include <vector>

#include <imgui.h>

namespace QGUI
{
    enum class LayoutDirection
    {
        Vertical,
        Horizontal
    };

    class Frame : public Element
    {
    public:
        Frame(const std::string &title, LayoutDirection direction = LayoutDirection::Vertical, float weight = 1.0f)
            : Element(weight), m_title(title), m_layoutDirection(direction) {};

        void add_element(std::unique_ptr<Element> element) { m_elements.push_back(std::move(element)); }

        void render() override
        {
            ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;

            if (!ImGui::Begin(m_title.c_str(), nullptr, flags))
            {
                ImGui::End();
                return;
            }

            // Measure Element Positioning
            float total_weight = 0;
            float fixed_space = 0;
            int weighted_element_count = 0;
            const float spacing = ImGui::GetStyle().ItemSpacing.x; // Use style for consistent spacing

            for (const auto &el : m_elements)
            {
                if (el->getWeight() > 0)
                {
                    total_weight += el->getWeight();
                    weighted_element_count++;
                }
                else
                {
                    // This is a simplified measurement. A real-world scenario would
                    // use ImGui::CalcTextSize or similar to measure fixed-size elements.
                    // For now, we assume non-weighted elements take up a default space.
                    if (m_layoutDirection == LayoutDirection::Horizontal)
                    {
                        fixed_space += 50.0f; // Assume fixed elements are 50px wide
                    }
                    else
                    {
                        fixed_space += 24.0f; // Assume fixed elements are 24px high
                    }
                }
            }

            // --- 2. Allocation and Drawing Pass ---
            ImVec2 available_space = ImGui::GetContentRegionAvail();
            float primary_axis_space =
                (m_layoutDirection == LayoutDirection::Horizontal) ? available_space.x : available_space.y;

            float total_spacing = (m_elements.size() > 1) ? (spacing * (m_elements.size() - 1)) : 0;
            float space_for_weighted_elements = primary_axis_space - fixed_space - total_spacing;
            float space_per_weight = (total_weight > 0) ? (space_for_weighted_elements / total_weight) : 0;

            for (size_t i = 0; i < m_elements.size(); ++i)
            {
                const auto &el = m_elements[i];

                if (m_layoutDirection == LayoutDirection::Horizontal && i > 0)
                {
                    ImGui::SameLine();
                }

                float weight = el->getWeight();
                if (weight > 0)
                {
                    float element_primary_size = weight * space_per_weight;
                    ImVec2 child_size = (m_layoutDirection == LayoutDirection::Horizontal)
                                            ? ImVec2(element_primary_size, 0)  // Width is calculated, height is auto
                                            : ImVec2(0, element_primary_size); // Height is calculated, width is auto

                    // Use a child window to enforce the calculated size
                    std::string id = "child_" + std::to_string(i);
                    ImGui::BeginChild(id.c_str(), child_size, false, ImGuiWindowFlags_NoScrollbar);
                    el->render();
                    ImGui::EndChild();
                }
                else
                {
                    // Draw fixed-size elements directly
                    el->render();
                }
            }

            ImGui::End();
        }

    private:
        std::string m_title;
        LayoutDirection m_layoutDirection;
        std::vector<std::unique_ptr<Element>> m_elements;
    };

} // namespace QGUI
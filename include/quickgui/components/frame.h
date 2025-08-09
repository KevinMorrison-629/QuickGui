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
            : Element(title, weight), m_title(title), m_layoutDirection(direction) {};

        void add_element(std::shared_ptr<Element> element) { m_elements.push_back(std::move(element)); }

        void render(const float width, const float height) override
        {
            ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                                     ImGuiWindowFlags_NoScrollbar;

            if (!ImGui::BeginChild(m_title.c_str(), ImVec2(width, height), flags))
            {
                ImGui::EndChild();
                return;
            }

            // Measure Element Spacing
            float totalWeight = 0.0f;
            for (auto &elem : m_elements)
                totalWeight += elem->getWeight();

            // --- 2. Allocation and Drawing Pass ---
            if (m_layoutDirection == LayoutDirection::Horizontal)
            {
                for (size_t i = 0; i < m_elements.size(); i++)
                {
                    auto &elem = m_elements[i];
                    float childWidth = width * (elem->getWeight() / totalWeight);

                    ImGui::PushItemWidth(childWidth);
                    ImGui::BeginGroup();
                    elem->render(childWidth, height);
                    ImGui::EndGroup();
                    ImGui::PopItemWidth();
                    if (i != m_elements.size() - 1)
                    {
                        ImGui::SameLine();
                    }
                }
            }
            else
            {
                for (auto &elem : m_elements)
                {
                    float childHeight = height * (elem->getWeight() / totalWeight);
                    elem->render(width, childHeight);
                }
            }

            ImGui::EndChild();
        }

    private:
        std::string m_title;
        LayoutDirection m_layoutDirection;
        std::vector<std::shared_ptr<Element>> m_elements;
    };

} // namespace QGUI
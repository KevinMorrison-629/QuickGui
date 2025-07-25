#pragma once

#include "quickgui/components/element.h"

#include <memory>
#include <string>
#include <vector>

#include <imgui.h>

namespace QGUI
{
    class Frame : public Element
    {
    public:
        Frame(const std::string &title) : m_title(title) {}

        void add_element(std::unique_ptr<Element> element) { m_elements.push_back(std::move(element)); }

        void render() override
        {
            ImGui::Begin(m_title.c_str());
            for (const auto &element : m_elements)
            {
                element->render();
            }
            ImGui::End();
        }

    private:
        std::string m_title;
        std::vector<std::unique_ptr<Element>> m_elements;
    };

} // namespace QGUI
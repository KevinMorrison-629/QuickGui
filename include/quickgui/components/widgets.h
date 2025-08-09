#pragma once

#include "quickgui/components/element.h"

#include <functional>
#include <string>

namespace QGUI
{
    class Button : public Element
    {
    public:
        Button(const std::string &label = "##", const float weight = 1.0f, std::function<void()> on_click = nullptr)
            : Element(label, weight), m_label(label), m_onClick(on_click) {};

        void render(const float width, const float height) override
        {
            if (ImGui::Button(m_label.c_str(), ImVec2(-1, 0)))
            {
                if (m_onClick)
                {
                    m_onClick();
                }
            }
        }

    private:
        std::string m_label;
        std::function<void()> m_onClick;
    };

    class Text : public Element
    {
    public:
        Text(const std::string &label = "##", const std::string &text = "", float weight = 1.0f)
            : Element(label, weight), m_text(text)
        {
        }

        void render(const float width, const float height) override { ImGui::TextUnformatted(m_text.c_str()); }

    private:
        std::string m_text;
    };

    class Spacer : public Element
    {
    public:
        Spacer(float weight = 1.0f) : Element("##", weight) {}

        void render(const float width, const float height) override {
        } // Spacers do not draw anything themselves (only used for space calculation)
    };

} // namespace QGUI
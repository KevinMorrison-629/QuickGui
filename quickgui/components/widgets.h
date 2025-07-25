#pragma once

#include "quickgui/components/element.h"

#include <functional>
#include <string>

namespace QGUI
{
    class Button : public Element
    {
    public:
        Button(const std::string &label, std::function<void()> on_click = nullptr) : m_label(label), m_onClick(on_click) {}

        void render() override
        {
            if (ImGui::Button(m_label.c_str()))
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
        Text(const std::string &text) : m_text(text) {}

        void render() override { ImGui::TextUnformatted(m_text.c_str()); }

    private:
        std::string m_text;
    };

    class Checkbox : public Element
    {
    public:
        Checkbox(const std::string &label, bool *value) : m_label(label), m_value(value) {}

        void render() override
        {
            if (m_value)
            {
                ImGui::Checkbox(m_label.c_str(), m_value);
            }
        }

    private:
        std::string m_label;
        bool *m_value;
    };

} // namespace QGUI
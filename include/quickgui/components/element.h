#pragma once

#include <glad/glad.h>
/// @note glad MUST be included before GLFW
#include <GLFW/glfw3.h>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <string>

namespace QGUI
{
    class Element
    {
    public:
        Element(const std::string &name, const float weight = 0.0) : m_name(name), m_weight(weight) {}

        virtual ~Element() = default;

        virtual void render(const float width, const float height) = 0;

        float getWeight() const { return m_weight; }
        std::string getName() const { return m_name; }

    private:
        float m_weight;
        std::string m_name;
    };
} // namespace QGUI
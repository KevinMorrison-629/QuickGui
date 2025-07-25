#pragma once

#include <glad/glad.h>
/// @note glad MUST be included before GLFW
#include <GLFW/glfw3.h>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace QGUI
{
    class Element
    {
    public:
        virtual ~Element() = default;

        virtual void render() = 0;
    };
} // namespace QGUI
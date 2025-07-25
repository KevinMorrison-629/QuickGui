#pragma once

#include "quickgui/components/frame.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace QGUI
{
    class Window
    {
    public:
        Window(const std::string &title, const size_t width, const size_t height)
            : title_(title), width_(width), height_(height), glfw_window_(nullptr)
        {
            // Set GLFW window hints
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            // Create the GLFW window
            glfw_window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
            if (!glfw_window_)
            {
                throw std::runtime_error("Failed to create GLFW window");
            }
            glfwMakeContextCurrent(glfw_window_);
            glfwSwapInterval(1); // Enable vsync

            // Initialize GLAD
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                throw std::runtime_error("Failed to initialize GLAD");
            }

            // Setup ImGui
            setup_imgui();
        }

        ~Window() { cleanup(); }

        void add_frame(std::unique_ptr<Frame> frame) { frames_.push_back(std::move(frame)); }

        void run() { render_loop(); }

    private:
        void setup_imgui()
        {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO &io = ImGui::GetIO();
            (void)io;
            // NOTE: Docking and Viewport flags have been removed.
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

            // Setup Dear ImGui style
            ImGui::StyleColorsDark();

            // Setup Platform/Renderer backends
            ImGui_ImplGlfw_InitForOpenGL(glfw_window_, true);
            ImGui_ImplOpenGL3_Init("#version 330");
        }

        void render_loop()
        {
            while (!glfwWindowShouldClose(glfw_window_))
            {
                // Poll and handle events (inputs, window resize, etc.)
                glfwPollEvents();

                // Start the Dear ImGui frame
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                // Draw all the frames added to the window.
                // Without a dockspace, they will appear as independent floating windows.
                for (const auto &frame : frames_)
                {
                    if (frame)
                    {
                        frame->render();
                    }
                }

                // Rendering
                ImGui::Render();
                int display_w, display_h;
                glfwGetFramebufferSize(glfw_window_, &display_w, &display_h);
                glViewport(0, 0, display_w, display_h);
                glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
                glClear(GL_COLOR_BUFFER_BIT);
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

                // Swap buffers
                glfwSwapBuffers(glfw_window_);
            }
        }

        void cleanup()
        {
            // Cleanup ImGui
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();

            // Cleanup GLFW
            if (glfw_window_)
            {
                glfwDestroyWindow(glfw_window_);
            }
        }

    private:
        GLFWwindow *glfw_window_;
        std::vector<std::unique_ptr<Frame>> frames_;
        int width_;
        int height_;
        std::string title_;
    };

} // namespace QGUI
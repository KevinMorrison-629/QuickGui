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
            : m_title(title), m_width(width), m_height(height), m_glfw_window(nullptr)
        {
            // Set GLFW window hints
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            // Create the GLFW window
            m_glfw_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
            if (!m_glfw_window)
            {
                throw std::runtime_error("Failed to create GLFW window");
            }
            glfwMakeContextCurrent(m_glfw_window);
            glfwSwapInterval(1); // Enable vsync

            // Initialize GLAD
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                throw std::runtime_error("Failed to initialize GLAD");
            }

            // Setup ImGui
            setup_imgui();

            m_frame = std::make_unique<Frame>("Main Frame", QGUI::LayoutDirection::Horizontal, 1.0f);
        }

        ~Window() { cleanup(); }

        void add_element(std::shared_ptr<Element> elem) { m_frame->add_element(elem); }

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
            ImGui_ImplGlfw_InitForOpenGL(m_glfw_window, true);
            ImGui_ImplOpenGL3_Init("#version 330");

            ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
            ImGui::SetNextWindowSize(ImVec2(m_width, m_height), ImGuiCond_Once);
        }

        void render_loop()
        {
            while (!glfwWindowShouldClose(m_glfw_window))
            {
                // Poll and handle events (inputs, window resize, etc.)
                glfwPollEvents();

                // Start the Dear ImGui frame
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                                         ImGuiWindowFlags_NoScrollbar;

                ImGui::SetNextWindowPos(ImGui::GetMainViewport()->WorkPos);
                ImGui::SetNextWindowSize(ImGui::GetMainViewport()->WorkSize);
                // ImGui::SetNextWindowViewport(ImGui::GetMainViewport()->ID);

                ImGui::Begin(m_title.c_str(), nullptr, flags);
                ImVec2 size = ImGui::GetContentRegionAvail();
                m_frame->render(size.x, size.y);

                ImGui::End();

                // Rendering
                ImGui::Render();
                int display_w, display_h;
                glfwGetFramebufferSize(m_glfw_window, &display_w, &display_h);
                glViewport(0, 0, display_w, display_h);
                glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
                glClear(GL_COLOR_BUFFER_BIT);
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

                // Swap buffers
                glfwSwapBuffers(m_glfw_window);
            }
        }

        void cleanup()
        {
            // Cleanup ImGui
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();

            // Cleanup GLFW
            if (m_glfw_window)
            {
                glfwDestroyWindow(m_glfw_window);
            }
        }

    private:
        GLFWwindow *m_glfw_window;
        std::unique_ptr<Frame> m_frame;
        int m_width;
        int m_height;
        std::string m_title;
    };

} // namespace QGUI
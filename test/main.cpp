#include "quickgui/quickgui.h"
#include <iostream>

int main()
{
    // Initialize the library (starts GLFW)
    if (!QGUI::init())
    {
        return -1;
    }

    try
    {
        // Create the main application window
        QGUI::Window main_window("My First QuickGUI App", 1280, 720);

        // Create a frame (an ImGui window)
        auto my_frame = std::make_unique<QGUI::Frame>("Controls");

        // Add some text to the frame
        my_frame->add_element(std::make_unique<QGUI::Text>("Hello, QuickGUI!"));
        my_frame->add_element(std::make_unique<QGUI::Text>("This is a simple test."));

        // Add a button with a callback lambda
        my_frame->add_element(
            std::make_unique<QGUI::Button>("Click Me!", []() { std::cout << "Button was clicked!" << std::endl; }));

        // Add a checkbox
        static bool is_checked = false;
        my_frame->add_element(std::make_unique<QGUI::Checkbox>("Check this box", &is_checked));

        // Add the frame to the main window
        main_window.add_frame(std::move(my_frame));

        // Run the application's main loop
        main_window.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "An exception occurred: " << e.what() << std::endl;
        QGUI::shutdown();
        return -1;
    }

    // Clean up resources
    QGUI::shutdown();
    return 0;
}


// Include the core components of the QuickGUI library
#include "components/element.h"
#include "components/frame.h"
#include "components/widgets.h"
#include "components/window.h"

#include <iostream>
#include <string>

namespace QGUI
{
    /**
     * @brief Initializes the QuickGUI library.
     * This function must be called before creating any Window objects.
     * It initializes GLFW.
     * @return true if initialization is successful, false otherwise.
     */
    inline bool init()
    {
        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return false;
        }
        return true;
    }

    /**
     * @brief Terminates the QuickGUI library.
     * This function should be called at the end of the application
     * to clean up GLFW resources.
     */
    inline void shutdown() { glfwTerminate(); }
} // namespace QGUI
# CMakeLists.txt for the quickgui interface project.
# This version supports being used as a submodule and can build its own tests
# when run as a standalone project.
cmake_minimum_required(VERSION 3.20)

# --- Define Project Name ---
# Setting a variable for the project name makes the conditional check for
# standalone builds cleaner and more reliable.
set(PROJECT_NAME "QuickGui")

project(${PROJECT_NAME} VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# You can also check here and error out if it’s missing:
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  message(FATAL_ERROR "Please invoke CMake with -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

# --- Find Dependencies ---
find_package(imgui CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

# --- Define the Library/Interface Target ---
add_library(quickgui INTERFACE)

# --- Configure Include Directories ---
# Add the 'include' directory to the public include path.
# This allows both the library itself and any consumers to use #include "quickgui/quickgui.h"
target_include_directories(quickgui INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# --- Configure Linking ---
# Publicly link against imgui,glfw,glad so any consumer of this library
# also gets the necessary settings.
target_link_libraries(quickgui INTERFACE
    imgui::imgui
    glad::glad
    glfw
)

# --- Add the subdirectory for the test executable ---
# This conditional ensures that the 'test' subdirectory is only configured
# when this project is being built directly, not when it's included as a
# submodule in a larger project.
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "Building QuickGui as a standalone project. Including tests.")
    add_subdirectory(test)
endif()

# --- Optional but Recommended: Installation Rules ---
include(GNUInstallDirs)
install(TARGETS ${LIB_NAME}
    EXPORT quickgui-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
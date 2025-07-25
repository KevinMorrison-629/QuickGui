
add_library(quickgui INTERFACE)

target_include_directories(quickgui INTERFACE ${CMAKE_SOURCE_DIR})

find_package(imgui CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

target_link_libraries(quickgui INTERFACE
    imgui::imgui
    glad::glad
    glfw
)
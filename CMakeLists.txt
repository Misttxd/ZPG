cmake_minimum_required(VERSION 3.16)
project(ZPG LANGUAGES CXX)

file(GLOB ZPG_SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/Scene/*.cpp")
add_executable(ZPG ${ZPG_SOURCES}
        Include/Scene/FionaScene.hpp)

target_compile_features(ZPG PRIVATE cxx_std_20)

target_include_directories(ZPG PRIVATE
    Include
    Libraries/glad/include
    Libraries/glfw/include
    Libraries/glm
)
target_link_libraries(ZPG PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/glfw/lib-macos-arm64/libglfw3.a"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework QuartzCore"
)
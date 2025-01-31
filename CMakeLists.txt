cmake_minimum_required(VERSION 3.10)

project(
    opengl_samples
    VERSION 0.1.0
)
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/libs/stb_image)

link_directories(libs/glfw)

include_directories(libs/glad)
include_directories(libs/KHR)
include_directories(libs/imgui)
include_directories(libs/glfw)
include_directories(include)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(opengl_samples ${SOURCES})


target_link_libraries(opengl_samples PRIVATE stb_image)
find_package(OpenGL REQUIRED)
target_link_libraries(opengl_samples PRIVATE ${OPENGL_gl_LIBRARY})
target_link_libraries(opengl_samples PRIVATE glfw3)

file(COPY resources DESTINATION /)
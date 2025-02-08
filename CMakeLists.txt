cmake_minimum_required(VERSION 3.10)

project(
    opengl_samples
    VERSION 0.1.0
)
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

add_library(stb_image INTERFACE)
add_library(glm INTERFACE)
target_include_directories(stb_image INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/libs/stb_image)
target_include_directories(glm INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/libs/glm)

link_directories(
	libs/glfw
	libs/assimp
)


include_directories(libs/glad)
include_directories(libs/KHR)
include_directories(libs/imgui)
include_directories(libs/glfw)
include_directories(libs)
include_directories(include)


file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(opengl_samples ${SOURCES})


target_link_libraries(opengl_samples PRIVATE stb_image)
#find_package(OpenGL REQUIRED)
#target_link_libraries(opengl_samples PRIVATE ${OPENGL_gl_LIBRARY})
target_link_libraries(opengl_samples PRIVATE glfw3)
target_link_libraries(opengl_samples PRIVATE glm)


file(COPY resources DESTINATION /)

find_path(ASSIMP_INCLUDE_DIR assimp/mesh.h
    ${CMAKE_SOURCE_DIR}/libs
)

find_library(ASSIMP_LIBRARY assimp
    ${CMAKE_SOURCE_DIR}/libs/assimp
)

IF(ASSIMP_INCLUDE_DIR AND ASSIMP_LIBRARY)
	SET( ASSIMP_FOUND TRUE )
	SET( ASSIMP_LIBRARIES ${ASSIMP_LIBRARY} )
ENDIF(ASSIMP_INCLUDE_DIR AND ASSIMP_LIBRARY)
IF(ASSIMP_FOUND)
	IF(NOT ASSIMP_FIND_QUIETLY)
	MESSAGE(STATUS "Found ASSIMP: ${ASSIMP_LIBRARY}")
	ENDIF(NOT ASSIMP_FIND_QUIETLY)
ELSE(ASSIMP_FOUND)
	IF(ASSIMP_FIND_REQUIRED)
	MESSAGE(FATAL_ERROR "Could not find libASSIMP")
	ENDIF(ASSIMP_FIND_REQUIRED)
ENDIF(ASSIMP_FOUND)


target_link_libraries(opengl_samples PRIVATE assimp)
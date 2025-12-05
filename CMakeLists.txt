cmake_minimum_required(VERSION 3.10)

project(face-detector)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OpenGL_GL_PREFERENCE "GLVND")

find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
 
add_executable(fDetector 
main.cpp
textureConverter.cpp
GLFwindow.cpp
imguiRenderer.cpp
)

#target_include_directories(
#    ${OpenCV_INCLUDE_DIRS}
#    ${OPENGL_INCLUDE_DIR}
#    libs/glfw/include
#    libs/imgui
#)

target_link_libraries(fDetector PRIVATE
${OpenCV_LIBS}
${OPENGL_LIBRARIES}
#OpenGL::GL
glfw
GLEW::GLEW
imgui
)



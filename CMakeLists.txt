cmake_minimum_required(VERSION 3.10)

project(face-detector)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OpenGL_GL_PREFERENCE "GLVND")

find_package(OpenCV REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)


add_subdirectory(thirdparty/imgui)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(fDetector 
main.cpp
textureConverter.cpp
GLFwindow.cpp
imguiRenderer.cpp
app.cpp
)

target_link_directories(fDetector PRIVATE imgui)

target_link_libraries(fDetector PRIVATE
glfw
${OpenCV_LIBS}
${OPENGL_LIBRARIES}
OpenGL::GL
GLEW::GLEW
imgui
)



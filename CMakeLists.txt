cmake_minimum_required(VERSION 3.10)

project(face-detector)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(fDetector main.cpp)

target_link_libraries(fDetector PRIVATE
${OpenCV_LIBS}
OpenGL::GL
glfw
GLEW::GLEW
)



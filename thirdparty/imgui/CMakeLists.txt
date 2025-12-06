
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB IMGUI_SOURCES 
"*.cpp" 
"backend/*.cpp"
)

message("ImGui sources: ${IMGUI_SOURCES}")
add_library(imgui STATIC ${IMGUI_SOURCES})
 



target_include_directories(imgui PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/backend
)


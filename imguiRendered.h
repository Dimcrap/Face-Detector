#pragma once

#include "imgui.h"
#include <opencv4/opencv2/opencv.hpp>
#include "textureConverter.h"
#include "backend/imgui_impl_glfw.h" //imgui_impl_glfw.h"
#include "backend/imgui_impl_opengl3.h"

class ImguiRenderer{
    private:
        TextureConverter textureconverter;
        GLuint VideoTextureID;//=0;
        cv::Mat currentFrame;

    public:
        void init(GLFWwindow * window);
        void beginFrame();
        void renderVideoWindow(cv::VideoCapture & cap);
        void renderControls();
        void renderFrame(){ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());};
        void cleanup();
};

#pragma once

#include "imgui/imgui.h"
#include "backend/imgui_impl_glfw.h"
#include "backend/imgui_impl_opengl3.h"
#include "textureConverter.h"
#include <opencv2/opencv.hpp>

class ImguiRenderer{
    private:
        TextureConverter textureconverter;
        GLuint VideoTextureID;
        cv::Mat currentFrame;

    public:
        void init(GLFWwindow * window);
        void beginFrame();
        void renderVideoWindow(cv::VideoCapture & cap);
};

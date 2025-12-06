#include "imguiRendered.h"  
#include <opencv4/opencv2/opencv.hpp>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFwindow.h"

class App{

    private:
    GLFWWindow glfw_window;
    ImguiRenderer imguirenderer;
    cv::VideoCapture videoCap;
    bool isRunning;

    public:
        App():isRunning(true){};
        bool initialize();
        void run();
        void renderDebugWindow();
        void renderSettingWindow();
        void cleanup();

};
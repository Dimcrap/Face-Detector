#include "app.h"

bool App::initialize(){

    if(!glfw_window.init()){
        return false;
    }

    imguirenderer.init(glfw_window.getWindow());

    videoCap.open(0);
    if(!videoCap.isOpened()){
        std::cerr<<"could not open the webcam/camera\n";
        return false;
    }

    videoCap.set(cv::CAP_PROP_FRAME_WIDTH,640);
    videoCap.set(cv::CAP_PROP_FRAME_HEIGHT,480);
    videoCap.set(cv::CAP_PROP_FPS,30);

    return true;
};

void App::run(){
    while(!glfw_window.shouldClose() && isRunning){
        
       // glfw_window.setCurrWindow();

        imguirenderer.beginFrame();
        imguirenderer.renderVideoWindow(videoCap);
        imguirenderer.renderControls();
        //renderDebugWindow();
        //renderSettingWindow();

        imguirenderer.renderFrame();
        glfw_window.pollEvents();
        glfw_window.swapBuffers();

    }
};


void App::renderDebugWindow(){

};
void App::renderSettingWindow(){

};
void App::cleanup(){
    imguirenderer.cleanup();
    glfw_window.cleanup();
    videoCap.release();
};
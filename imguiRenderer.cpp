#include "imguiRendered.h"

void ImguiRenderer::init(GLFWwindow * window){
    IMGUI_CHECKVERSION();
    ImGuiIO & io =ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplGlfw_InitForOpenGL(window,true);
    ImGui_ImplOpenGL3_Init("#version 330");

    ImGui::StyleColorsDark();
}

void ImguiRenderer::beginFrame(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
};

void ImguiRenderer::renderVideoWindow(cv::VideoCapture & cap){
    cap>>currentFrame;
        if(currentFrame.empty()) return;

        if(VideoTextureID ==0){
            VideoTextureID = textureconverter.matToTexture(currentFrame);
        }else{
            textureconverter.updateTexture(VideoTextureID,currentFrame);
        }

        ImGui::Begin("Video Feed",nullptr,ImGuiWindowFlags_NoCollapse);
        
        ImVec2 windowSize =ImGui::GetContentRegionAvail();
        float aspectRatio =(float)currentFrame.cols/currentFrame.rows;

        ImVec2 imageSize;
        if(windowSize.x/aspectRatio<windowSize.y){
            imageSize =ImVec2(windowSize.x,windowSize.x/aspectRatio);
        }else{
            imageSize =ImVec2(windowSize.y* aspectRatio,windowSize.y);
       }

       ImGui::Image((void *)(intptr_t)VideoTextureID,imageSize,
                ImVec2(0,0),
                ImVec2(1,1),
                ImVec4(1,1,1,1),
                ImVec4(0,0,0,0));
       ImGui::End();
    
};
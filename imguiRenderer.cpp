#include "imguiRendered.h"

void ImguiRenderer::init(GLFWwindow * window){

    //VideoTextureID=0;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
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

         std::cout << "Frame size: " << currentFrame.cols << 
         "x" << currentFrame.rows << std::endl;

        if(VideoTextureID ==0){
            VideoTextureID = textureconverter.matToTexture(currentFrame);
              std::cout << "Created texture ID: " << VideoTextureID <<std::endl;
        }else{
            textureconverter.updateTexture(VideoTextureID,currentFrame);
            std::cout << "Updated texture ID: " << VideoTextureID << 
            std::endl;
        }
if (glIsTexture(VideoTextureID)) {
    std::cout << "Texture " << VideoTextureID << " is valid OpenGL texture" << std::endl;
} else {
    std::cout << "Texture " << VideoTextureID << " is INVALID!" << std::endl;
}

        GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cout << "OpenGL error: " << err << std::endl;
    }

        ImGui::Begin("Video Feed",nullptr,ImGuiWindowFlags_NoCollapse);
        
        ImVec2 windowSize =ImGui::GetContentRegionAvail();
        float aspectRatio =(float)currentFrame.cols/currentFrame.rows;
        
        
        ImVec2 imageSize;
        if(windowSize.x/aspectRatio > windowSize.y){
            imageSize =ImVec2(windowSize.y*aspectRatio,windowSize.y);
        }else{
            imageSize =ImVec2(windowSize.x,windowSize.x / aspectRatio);
        }
        
      // glBindTexture(GL_TEXTURE_2D,VideoTextureID);
       ImGui::Image((void *)(intptr_t)VideoTextureID,
                imageSize,
                ImVec2(0,0),
                ImVec2(1,1),
                ImVec4(1,1,1,1),
                ImVec4(0,0,0,0));
       ImGui::End();
    
};

void ImguiRenderer::renderControls(){
    ImGui::Begin("Controls");

    static float threshold = 0.5f;
    static bool enableFaceDetection =true;
    static int blurSize=5;

    ImGui::Text("OpenCV Controls");
    ImGui::Separator();

    ImGui::Checkbox("Enable Face Detectin",&enableFaceDetection);
    //ImGui::SliderFloat("Detection ThreshHold",&threshold,0.0f,1.0f);
    ImGui::SliderInt("Blur Size",&blurSize,1,15);

    if(ImGui::Button("Take Snapshot")){
        cv::imwrite("snapshot.png",currentFrame);
    }

    ImGui::SameLine();

    if(ImGui::Button("Reset Settings")){
        threshold=0.5f;
        blurSize=5;
    }

    ImGuiIO & io=ImGui::GetIO();
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
    1000.0f/io.Framerate,io.Framerate);

    ImGui::End();


}

void ImguiRenderer::cleanup(){
            textureconverter.deleteTexture(VideoTextureID);
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }
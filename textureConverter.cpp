#include "textureConverter.h"
#include <GLFW/glfw3.h>

GLuint TextureConverter::matToTexture(const cv::Mat & mat,GLenum minFilter,
    GLenum magFilter,GLenum wrapMode)
    {
        GLFWwindow* currentWindow = glfwGetCurrentContext();
    if (!currentWindow) {
        std::cerr << "CRITICAL ERROR: No OpenGL context is current!" << std::endl;
        return 0;
    }
     //std::cout << "matToTexture: Current window context: " << currentWindow << std::endl;
     if (!glGenTextures) {
        std::cerr << "CRITICAL ERROR: OpenGL functions not loaded!" << std::endl;
        std::cerr << "Make sure GLEW/GLAD is initialized before calling this!" << std::endl;
        return 0;
    }
     GLenum preErr = glGetError();
    if (preErr != GL_NO_ERROR) {
        std::cerr << "OpenGL error before starting: " << preErr << std::endl;
    }
        
        GLuint newTextureID;
        glGenTextures(1,&textureID);
         if(textureID ==0) {std::cerr<<"Could't create textureID error\n";return 0;}
          
        //std::cout << "Generated texture ID: " << textureID << std::endl;

        if (!glIsTexture(newTextureID)) {
            std::cout << "ERROR: glGenTextures gave invalid texture ID!" << std::endl;
           //return 0;
        }    

    glBindTexture(GL_TEXTURE_2D,textureID);

     GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "ERROR in glBindTexture: " << err << std::endl;
        glDeleteTextures(1, &textureID);  // Clean up
        //return 0;
    }


        glTexParameteri(GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER,minFilter);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,
        magFilter);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,
        wrapMode);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,
        wrapMode);

         if (mat.empty()) {
        std::cerr << "ERROR: Empty mat passed to matToTexture!" << std::endl;
        glDeleteTextures(1, &textureID);
        return 0;
        }
        cv::Mat displaymat=mat.clone();

        static int counter = 0;
    cv::imwrite("/tmp/debug_frame_" + std::to_string(counter++) + ".jpg", displaymat);
    
        GLenum inputFormat=GL_BGR;
        GLenum internalFormat= GL_RGB8;
        
        if(displaymat.channels()==1){
            inputFormat=GL_RED;
            internalFormat=GL_R8;
        }else if(displaymat.channels()==4){
            inputFormat=GL_BGRA;
            internalFormat =GL_RGBA8;
        }
 
        glTexImage2D(GL_TEXTURE_2D,0,internalFormat,displaymat.cols,
            displaymat.rows,0,inputFormat,GL_UNSIGNED_BYTE,displaymat.data);
        
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glBindTexture(GL_TEXTURE_2D,0);

        return textureID;
    };   


void TextureConverter::detectandDrawFace(cv::Mat &frame){
    cv::String face_cascade_name=cv::samples::findFile("/home/unred/opencv/data/"
        "haarcascades/haarcascade_frontalface_alt.xml");
    face_cascade.load(face_cascade_name);
    cv::Mat frame_gray;
    cv::cvtColor( frame, frame_gray, cv::COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    
    //-- Detect faces
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale( frame_gray, faces );
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        cv::Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( frame, center, cv::Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, cv::Scalar( 255, 0, 255 ), 4 );
        cv::Mat faceROI = frame_gray( faces[i] );
    }
}


void TextureConverter::updateTexture(GLuint textureID,
                             cv::Mat& mat)
{
    GLFWwindow* currentWindow = glfwGetCurrentContext();
    if (!currentWindow) {
        std::cout << "ERROR: No OpenGL context is current!" << std::endl;
        return;
    }
    //std::cout << "Current GLFW window: " << currentWindow << std::endl;
    

      if (mat.empty()) {
        std::cerr << "ERROR: Empty frame for texture update" << std::endl;
     
    }
           // cv::ellipse(mat,cv::Point(mat.cols/2, mat.rows/2),cv::Size(50,65),0,0,360,cv::Scalar(55, 243, 235),4);
            detectandDrawFace(mat);
    //while (glGetError() != GL_NO_ERROR);
     GLenum err1 = glGetError();
    if (err1 != GL_NO_ERROR) {
        std::cout << "opengl error before operation: " << err1 << std::endl;
        return;
    }
    glBindTexture(GL_TEXTURE_2D,textureID);
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cout << "glBindTexture error: " << err << std::endl;
        return;
    }


    GLenum format =(mat.channels() ==4) ?GL_BGRA:
                    (mat.channels() ==3) ? GL_BGR:GL_RED;
    
    glTexSubImage2D(GL_TEXTURE_2D,
    0,0,0, mat.cols,mat.rows,format,
    GL_UNSIGNED_BYTE,mat.data);

    glBindTexture(GL_TEXTURE_2D,0);
};
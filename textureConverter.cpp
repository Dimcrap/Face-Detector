#include "textureConverter.h"
#include <GLFW/glfw3.h>

GLuint TextureConverter::matToTexture(const cv::Mat & mat,GLenum minFilter,
    GLenum magFilter,GLenum wrapMode)
    {
        while (glGetError() != GL_NO_ERROR);

        glGenTextures(1,&textureID);
         if(textureID ==0) {std::cerr<<"textureID error\n";return 0;}
          
    std::cout << "Generated texture ID: " << textureID << std::endl;
    if (!glIsTexture(textureID)) {
        std::cout << "ERROR: glGenTextures gave invalid texture ID!" << std::endl;
        return 0;
    }    
    glBindTexture(GL_TEXTURE_2D,textureID);

        glTexParameteri(GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER,minFilter);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,
        magFilter);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,
        wrapMode);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,
        wrapMode);

        GLenum inputFormat=GL_BGR;
        GLenum internalFormat= GL_RGB8;
        
        if(mat.channels()==1){
            inputFormat=GL_RED;
            internalFormat=GL_R8;
        }else if(mat.channels()==4){
            inputFormat=GL_BGRA;
            internalFormat =GL_RGBA8;
        }

        glTexImage2D(GL_TEXTURE_2D,0,internalFormat,mat.cols,
            mat.rows,0,inputFormat,GL_UNSIGNED_BYTE,mat.data);
        
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glBindTexture(GL_TEXTURE_2D,0);

        return textureID;
    };   

void TextureConverter::updateTexture(GLuint textureID,
                            const cv::Mat& mat)
{
    GLFWwindow* currentWindow = glfwGetCurrentContext();
    if (!currentWindow) {
        std::cout << "ERROR: No OpenGL context is current!" << std::endl;
        return;
    }
    std::cout << "Current GLFW window: " << currentWindow << std::endl;
    

    while (glGetError() != GL_NO_ERROR);
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
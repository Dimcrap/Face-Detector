#include <GL/glew.h>
#pragma once
#include <opencv4/opencv2/opencv.hpp>
#include <iostream>

class TextureConverter{
    private:
        GLuint textureID;
        
        int width,height;

    public:
        GLuint matToTexture(const cv::Mat & mat,GLenum minFilter=GL_LINEAR,
                        GLenum magFilter=GL_LINEAR,GLenum wrapMode=GL_CLAMP_TO_EDGE);   
        void updateTexture(GLuint textureID,const cv::Mat& mat);
        void deleteTexture(GLuint textureID){glDeleteTextures(1,&textureID);}

};
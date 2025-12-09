#include <GL/glew.h>
#pragma once
#include <opencv4/opencv2/opencv.hpp>
#include <iostream>

class TextureConverter{
    private:
        GLuint textureID;
        bool texturecreated;
        int width,height;
        cv::CascadeClassifier face_cascade;

    public:
        TextureConverter():textureID(0),texturecreated(false){}
        GLuint matToTexture(const cv::Mat & mat,GLenum minFilter=GL_LINEAR,
                        GLenum magFilter=GL_LINEAR,GLenum wrapMode=GL_CLAMP_TO_EDGE);   
        void detectandDrawFace(cv::Mat &frame);
        void updateTexture(GLuint textureID,cv::Mat& mat);
        void deleteTexture(GLuint textureID){glDeleteTextures(1,&textureID);}

};
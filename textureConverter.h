#include <GL/glew.h>
#pragma once
#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include "faceDetector.h"

class TextureConverter{
    private:
        GLuint textureID;
        bool texturecreated;
        int width,height;
        faceDetector faceD;
        
        std::vector<cv::Rect> faces;
        std::chrono::steady_clock::time_point lastSubmissionTime;
        int64_t minSubmissionIntervalMs = 100;

    public:
        TextureConverter():textureID(0),texturecreated(false)
        ,faceD("/home/unred/opencv/data/haarcascades/haarcascade_frontalface_alt.xml")
        {

        }

        GLuint matToTexture(const cv::Mat & mat,GLenum minFilter=GL_LINEAR,
                        GLenum magFilter=GL_LINEAR,GLenum wrapMode=GL_CLAMP_TO_EDGE);   
        void DrawFace(std::vector<cv::Rect> & facesrects ,cv::Mat frame);
        void updateTexture(GLuint textureID,cv::Mat& mat);
        void deleteTexture(GLuint textureID){glDeleteTextures(1,&textureID);}

};
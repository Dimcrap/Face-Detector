#include "faceDetector.h"
#include <opencv2/core/utility.hpp>

void faceDetector::workerFunction(){
    while(running){
        cv::Mat frame;

        {
            if(inputQueue.empty()){
            std::unique_lock<std::mutex>lock(inputMutex);
            inputcv.wait_for(lock,std::chrono::milliseconds(100));
            if(inputQueue.empty()) continue;
        }

        frame=std::move(inputQueue.front());
        inputQueue.pop();
    }
        if(detectionEnabled){
            std::vector<cv::Rect>faces=detectFaces(frame);
           {
               std::lock_guard<std::mutex> lock(inputMutex);
               latestFaces=std::move(faces);
               hasNewResult=true;
            }
            //outputQueue.push(faces);
        }/*else{
            outputQueue.push(std::vector<cv::Rect>());
        }*/
    }
};

faceDetector::faceDetector(const std::string & cascadePath):face_cascade(){
   
    std::cout << "Loading cascade from: " << cascadePath << std::endl;
    
   static bool opencvInitialized = false;
    if (!opencvInitialized) {
        cv::theRNG();  // Force OpenCV init
        opencvInitialized = true;
    }
      if(!face_cascade.load(cascadePath)){
        throw std::runtime_error("failed to load cascadePath");
    };
   // prewarmCascade();
    worker=std::thread(&faceDetector::workerFunction,this);
};

faceDetector::~faceDetector(){
    running=false;
    inputcv.notify_one();
    if(worker.joinable())worker.join();
};

void faceDetector::setDetectionEnabled(bool enabled){
    detectionEnabled=enabled;
    if(!enabled){
        //std::vector<cv::Rect> dummy;
        //while(outputQueue.try_pop(dummy)){}
        latestFaces.clear();
    }
};


std::vector<cv::Rect> faceDetector::detectFaces(cv::Mat &frame){
    
    cv::Mat smallFrame;
    cv::resize(frame, smallFrame, cv::Size(320, 240));  // Downscale!

    cv::Mat frame_gray;
    cv::cvtColor( frame, frame_gray, cv::COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    std::vector<cv::Rect> faces;
    
    face_cascade.detectMultiScale( frame_gray,
         faces,1.1,3,0,cv::Size(40,40));
   /*
     float scaleX = static_cast<float>(frame.cols) / 320.0f;
     float scaleY = static_cast<float>(frame.rows) / 240.0f;
        
        for (auto& face : faces) {
            face.x = static_cast<int>(face.x * scaleX);
            face.y = static_cast<int>(face.y * scaleY);
            face.width = static_cast<int>(face.width * scaleX);
            face.height = static_cast<int>(face.height * scaleY);
        }*/

    return faces;

};

bool faceDetector::submitFrame(const cv::Mat& frame){
    std::lock_guard<std::mutex>lock(inputMutex);

    if(inputQueue.size()>=MAX_INPUT_QUEUE){
        return false;
    }


    inputQueue.push(frame.clone());
    inputcv.notify_one();
    return true;
}

bool faceDetector::getResults(std::vector<cv::Rect>&faces)
{
    std::lock_guard<std::mutex> lock(ouputMutex);
    if(!hasNewResult)return false;
    faces=latestFaces;
    hasNewResult=false;
    return true;
}
//getQueueSize() recommended 
void faceDetector::prewarmCascade() {
        // Create dummy images of various sizes
        std::vector<cv::Size> testSizes = {
            cv::Size(320, 240),   // Small
            cv::Size(640, 480),   // Medium  
            cv::Size(1280, 720)   // Large
        };
        
        for (const auto& size : testSizes) {
            cv::Mat dummyGray(size, CV_8UC1, cv::Scalar(128));
            cv::Mat dummyColor(size, CV_8UC3, cv::Scalar(128, 128, 128));
            
            std::vector<cv::Rect> dummyFaces;
            
            // Test on grayscale
            face_cascade.detectMultiScale(dummyGray, dummyFaces, 
                                    1.1, 2, 0, cv::Size(30, 30));
            
            // Test on color (converted internally)
            cv::cvtColor(dummyColor, dummyGray, cv::COLOR_BGR2GRAY);
            face_cascade.detectMultiScale(dummyGray, dummyFaces, 
                                    1.1, 2, 0, cv::Size(30, 30));
            
            std::cout << "Pre-warmed for size: " << size.width 
                      << "x" << size.height << std::endl;
        }
        
        // Force internal data structures to initialize
        for (int i = 0; i < 10; i++) {
            cv::Mat tiny(10, 10, CV_8UC1, cv::Scalar(100));
            std::vector<cv::Rect> faces;
            face_cascade.detectMultiScale(tiny, faces);
        }
    }
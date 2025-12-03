#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

void detectanddisplay(cv::Mat frame);

cv::CascadeClassifier face_cascade;




int main(int argc,const char ** argv){
    cv::CommandLineParser parser(argc,argv,
                        "{help h||}"
                        "{face_cascade|"
                        "/home/unred/opencv/data/haarcascades/haarcascade_frontalface_alt.xml"
                        "|Path to face cascade.}"
                        "{camera|0|Camera device number.}");
                    
        parser.about("\nThis program demonstrates using the"
            " cv::CascadeClassifier class to detect object Face in a Video stream.\n");
        parser.printMessage();

        cv::String face_cascade_name =cv::samples::findFile(parser.get<cv::String>("face_cascade"));
        
        if(!face_cascade.load(face_cascade_name) )
        {
            std::cout<<"--(!)Error loading face cascade\n";
            return -1;
        }


    int camera_device =parser.get<int>("camera");
    cv::VideoCapture cap;
    cap.open(camera_device);
    if(!cap.isOpened()){
        std::cerr<<"failed to load video capturing.\n could not access webcam";
        return -1;
    }else{
        std::cout<<"webcam opened successfully.";
    }

    cv::Mat frame;
    bool ret=cap.read(frame);

    while(cap.read(frame))
    {
        if(frame.empty()){
            std::cout<<"--(!) No captured frame --break!\n";
            break;
        }

        detectanddisplay(frame);
        
        if(cv::waitKey(10)==27){
            break;
        };
        //cv::destroyAllWindows();
    }

    //cap.release();
    return 0;

}

void detectanddisplay(cv::Mat frame){
    cv::Mat frame_gray;
    cv::cvtColor(frame,frame_gray,cv::COLOR_BGR2GRAY);
    cv::equalizeHist( frame_gray,frame_gray);

    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(frame,faces);

    for(size_t i=0;i<faces.size();i++)
    {
        cv::Point center(faces[i].x +faces[i].width/2,
                        faces[i].y+faces[i].height/2);
        cv::ellipse(frame,center,cv::Size(faces[i].width/2,faces[i].height/2),0,0,360,cv::Scalar(55, 243, 235),4);

        cv::Mat faceROI= frame_gray(faces[i]);

        
        

    }
    cv::imshow( "Capture Face detection",frame);

};
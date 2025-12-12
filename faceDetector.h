#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <queue>
#include <opencv2/opencv.hpp>

template <typename T> class ThreadSafeQueue{
private:
std::queue<T> m_queue;
std::mutex m_mutex;
std::condition_variable m_cond;
public:
void push (T item){
    std::unique_lock<std::mutex> lock(m_mutex);
    m_queue.push(item);
    m_cond.notify_all();
}
/*T take(){
    std::unique_lock<std::mutex> lock(m_mutex);

    m_cond.wait(lock,[this](){return !m_queue.empty});

    T item =m_queue.front();
    m_queue.pop();

    return item;
}*/
bool try_pop(T &item){
    std::unique_lock<std::mutex> lock(m_mutex);
    if(m_queue.empty()){
        return false;
    }
    item=std::move(m_queue.front());
    m_queue.pop();
    return true;
}
bool empty(){
    std::unique_lock<std::mutex> lock(m_mutex);
     if(m_queue.empty())return true;
     return false;
}
T front(){
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_queue.front();
}
void pop(){ 
        std::unique_lock<std::mutex> lock(m_mutex);
 m_queue.pop();}
int size(){
        std::unique_lock<std::mutex> lock(m_mutex);
 return m_queue.size();}
}; 

class faceDetector{
private:
    std::thread worker;
    std::atomic<bool> running{true};
    std::atomic<bool> detectionEnabled{true};
    //ThreadSafeQueue<cv::Mat>inputQueue;
    std::queue<cv::Mat> inputQueue;
    std::mutex inputMutex;
    std::condition_variable inputcv;
    const int MAX_INPUT_QUEUE=2;
    //ThreadSafeQueue<std::vector<cv::Rect>> outputQueue;
    std::vector <cv::Rect>latestFaces;
    std::mutex ouputMutex;
    bool hasNewResult=false;
    cv::CascadeClassifier face_cascade;
    void workerFunction();
    public: 
        faceDetector(const std::string & cascadePath);
        ~faceDetector();
        void setDetectionEnabled(bool enabled);
        std::vector<cv::Rect> detectFaces(cv::Mat &frame);
        bool submitFrame(const cv::Mat& frame);
        bool getResults(std::vector<cv::Rect>&faces);
        void prewarmCascade();
};
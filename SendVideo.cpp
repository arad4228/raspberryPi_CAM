#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;

int main(int argc, char** argv) 
{
    std::string strIPAddress(argv[1]);
    cv::VideoCapture cap(0); // 라즈베리 파이 카메라 모듈 열기

    if (!cap.isOpened()) {
        std::cerr << "Camera open failed." << std::endl;
        return -1;
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('H', '2', '6', '4'));

    // GStreamer 파이프라인
    std::string pipeline = "appsrc ! queue ! videoconvert ! x264enc ! rtph264pay ! udpsink host="+strIPAddress+" port=5000";
    cv::VideoWriter writer;
    writer.open(pipeline, 0, 30, cv::Size(640, 480), true);

    if (!writer.isOpened()) {
        std::cerr << "VideoWriter open failed." << std::endl;
        return -1;
    }

    while (true) 
    {
	cv::Mat frame;
	cap >> frame;
        
        if (frame.empty()) 
        {
            std::cerr << "Frame Empty" << std::endl;
            break;
        }
        // cv::imshow("test.avi", frame);
        writer << frame;
    }

    return 0;
}

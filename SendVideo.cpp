#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>

using namespace cv;

int main() 
{
    cv::VideoCapture cap(0); // 라즈베리 파이 카메라 모듈 열기

    if (!cap.isOpened()) {
        std::cerr << "Camera open failed." << std::endl;
        return -1;
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('H', '2', '6', '4'));
    std::string strTestkey = "012345678901234567890123456789012345678901234567890123456789";

    // GStreamer 파이프라인
    // Nomal
    // std::string pipeline = "appsrc ! queue ! videoconvert ! x264enc ! rtph264pay ! udpsink host=163.152.126.107 port=5000";
    
    // Enc
    std::string pipeline =
        "appsrc ! "
        "videoconvert ! "
        "video/x-raw, width=640, height=480, framerate=30/1, format=I420 ! "
        "x264enc tune=zerolatency ! "
        "rtph264pay ssrc=1356955624 ! "
        "srtpenc key=" + strTestkey + " ! queue ! udpsink sync=false host=163.152.126.107 port=5000";

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
        writer << frame;
    }

    return 0;
}

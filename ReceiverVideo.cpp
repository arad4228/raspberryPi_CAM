#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

int main() 
{
    // 30~50 bytes
    std::string strTestkey = "012345678901234567890123456789012345678901234567890123456789";

    // GStreamer 파이프라인을 통한 UDP 스트림 수신 설정
    // Nomal
    // std::string pipeline = "udpsrc port=5000 "
    //                       "! application/x-rtp, media=video, encoding-name=H264, payload=96"
    //                       "! queue ! rtph264depay ! h264parse ! avdec_h264 ! videoconvert ! appsink sync=false";

    // Enc
    std::string pipeline = 
        "udpsrc port=5000 ! "
        "application/x-srtp, media=video, clock-rate=90000, encoding-name=H264, payload=96, ssrc=(uint)1356955624, "
        "srtp-key=(buffer)" + strTestkey + ", "
        "srtp-cipher=aes-128-icm, srtp-auth=hmac-sha1-80 , srtcp-cipher=aes-128-icm, srtcp-auth=hmac-sha1-80 ! "
        "srtpdec ! rtph264depay !"
        "avdec_h264 ! videoconvert ! queue ! "
        "appsink sync=false";

    // VideoCapture 객체를 GStreamer 파이프라인을 사용하여 열기
    cv::VideoCapture cap(pipeline, cv::CAP_GSTREAMER);

    if (!cap.isOpened()) {
        std::cerr << "VideoCapture open failed." << std::endl;
        return -1;
    }
    std::cout << "연결 성공" << std::endl;
    cv::Mat frame;
    while (true) {
        // 프레임 캡처
        cap >> frame;
        if (frame.empty()) break;

        // 프레임 표시
        cv::imshow("Frame", frame);

        // 'ESC' 키가 눌리면 루프 종료
        if (cv::waitKey(1) == 27) break;
    }

    return 0;
}

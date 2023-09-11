#include <iostream>
#include <time.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(void)
{
    VideoCapture cap(0);
    VideoWriter videoWriter;

    if(!cap.isOpened())
    {
        std::cerr << "Cant Open Cam" << std::endl;
        return -1;
    }

    Mat videoFrame;

    float videoFPS = cap.get(cv::CAP_PROP_FPS);
	int videoWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH);
	int videoHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    
    std::cout << "Video Info" << std::endl;
	std::cout << "video FPS : " << videoFPS << std::endl;
	std::cout << "video width : " << videoWidth << std::endl;
	std::cout << "video height : " << videoHeight << std::endl;

    videoWriter.open("test.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 
		videoFPS , cv::Size(videoWidth, videoHeight), true);

    if (!videoWriter.isOpened())
	{
		std::cout << "Can't write video !!! check setting" << std::endl;
		return -1;
	}
    time_t start, end;
    start = time(NULL);

    while (true) {
		//VideoCapture로 부터 프래임을 받아온다
		cap >> videoFrame;

		//캡쳐 화면이 없는 경우는 Video의 끝인 경우
		if (videoFrame.empty()) {
			std::cout << "Video END" << std::endl;
		}

        // cv::imshow("test.avi", videoFrame);

		//받아온 Frame을 저장한다.
		videoWriter << videoFrame;
        
        if(waitKey(2) == 27)
        {
            videoWriter.release();
            break;
        }
            
        end = time(NULL);
        if(end - start >= 30)
        {
            std::cout << "Recording End" << std::endl;
		    videoWriter.release();
            break;
        }
	}
    return 0;
}

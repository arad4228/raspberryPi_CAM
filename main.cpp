#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;

int main(void)
{
    VideoCapture cap(0);
    if(!cap.isOpened())
    {
        std::cerr << "Cant Open Cam" << std::endl;
        return -1;
    }

    Mat img;

    while (1)
    {
        cap >> img;

        imshow("Cam img", img);

        if(waitKey(1) == 27)
            break;
    }
    return 0;
}
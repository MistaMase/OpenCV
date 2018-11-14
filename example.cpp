#include "opencv2/opencv.hpp"
#include <iostream>
#include <chrono>

using namespace cv;

int main(int, char**)
{
    VideoCapture cap(1); // open the default camera   
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    cap.set(CV_CAP_PROP_FPS, 60);
    Mat edges;
    namedWindow("edges",1);
    for(;;)
    {
	auto start = std::chrono::high_resolution_clock::now();
        Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, edges, COLOR_BGR2GRAY);
        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        Canny(edges, edges, 0, 30, 3);
        imshow("edges", edges);
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Time: " << elapsed.count()/1000.0 << "ms" << std::endl;
	std::cout << "Video Capture FPS " << cap.get(CV_CAP_PROP_FPS) << std::endl;
	if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <OpenNI.h>
#include "imagedeal.h"
#include "filedeal.h"
#include <time.h>
#include <Eigen/Dense>
using namespace std;
using namespace cv;
#include <thread>

void greeting() {       // 2.
    while(1)
	std::cout << "Hello multithread!" << std::endl;
    return;
}
using namespace Eigen;
int main(int argc, char * argv[])
{
//     cv::Mat color_image=cv::Mat(480,640,CV_8UC3);
        cv::Mat color_image=cv::Mat(480,640,CV_16UC1);

    namedWindow(WINDOW_NAME);
    setMouseCallback(WINDOW_NAME,on_MouseHandle,(void*)&color_image);
    AstralCam astralcam0;  

    if(astralcam0.Init())
    {
	cout<<"fail open camera"<<endl;
    }
    else{
	cout<<"success open camera"<<endl;
    }
    
    int a=astralcam0.run();
    waitKey(300);
    while(1)
    {	
	a=astralcam0.run();
	if(waitKey(10)==27)
	    break;
    }

    return 0;
}



#include <iostream>
#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>
#include "camera.h"
#include <time.h>
using namespace std;
using namespace cv;
int main(int argc, char **argv) {
    //D435 camera class
    camera cam;
    
    cam.start();
    while(1){
// 	clock_t t1 = clock();
// 	update image
	cam.showImage();
	if(waitKey(30)==27)
	    break;
// 	cout << (clock() - t1) * 1.0 /1000 << endl;
    }
    return 0;
}
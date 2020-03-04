#ifndef __CAMERA_H
#define __CAMERA_H
#include <iostream>
#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>

#define COLOR_IMG "color"
#define DEPTH_IMG "depth"
#define INFRARE_1_IMG "infrare1"
#define INFRARE_2_IMG "infrare2"


using namespace std;
using namespace cv;
class camera{
public:
    camera();
    void start(void);
    void showImage(void);
    ~camera();
private:
    rs2::pipeline pipe;
    rs2::config cfg;
    rs2::colorizer color_map;
    Mat color;
    Mat infrare1;
    Mat infrare2;
    Mat depth;

};

#endif
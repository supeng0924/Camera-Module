#ifndef IMAGEDEAL_H
#define IMAGEDEAL_H
#include <OpenNI.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#define WINDOW_NAME  "DisplayWindow"           //为窗口标题定义的宏
#define MINIOR
#define COLOR_PATH "color/"
#define DEPTH_PATH "depth/"
#define SIMPLING_PATH "img/"


#define USE_ASTRA_CAMERA
// #define USE_NORMAL_CAMERA
// #define USE_TWO_CAMERA
// #define ASTRA_COLOR_IMAGE

// 彩色图像相关宏定义
#define COLOR_IMAGE_GET
#define COLOR_IMAGE_SHOW

// 深度图像相关宏定义
#define DEPTH_IMAGE_GET
#define DEPTH_IMAGE_SHOW

// // 红外图像相关宏定义
// #define IR_IMAGE_GET
// #define IR_IMAGE_SHOW


using namespace cv;
class AstralCam{
public:
    AstralCam();
    int Init();
    int run();
    int ReadStreamFormatAndSet(void);
    void OutputFormatSet(void);
    void Setstreams(void);
    void GetFrame(void);
  
protected:
    openni::Device          device;
    openni::VideoStream     depth;
    openni::VideoStream     color;
    openni::VideoStream     ir;
    openni::VideoStream**   m_streams;
    cv::Mat depth_image;
    cv::Mat color_image;

    
    
};

// 鼠标回调函数
void on_MouseHandle(int event, int x, int y, int flags, void *param);
bool getSignal(void);
Point getPoint(void);
int getImageNum(void);

#endif


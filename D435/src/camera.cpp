#include "camera.h"
#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;
using namespace rs2;

// mouse callback funciton
void on_MouseHandle_up(int event, int x, int y, int flags, void *param);
Point draw_point_up;        
bool mouse_signal_up=false;  

camera::camera(){
    //enable relative video steaming
    cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);
    cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);
    cfg.enable_stream(RS2_STREAM_INFRARED,1, 640, 480, RS2_FORMAT_Y8, 30);
    cfg.enable_stream(RS2_STREAM_INFRARED,2, 640, 480, RS2_FORMAT_Y8, 30);
    //create window
    namedWindow(COLOR_IMG);moveWindow(COLOR_IMG,0,0);
    namedWindow(DEPTH_IMG);moveWindow(DEPTH_IMG,0,700);
    namedWindow(INFRARE_1_IMG);moveWindow(INFRARE_1_IMG,700,0);
    namedWindow(INFRARE_2_IMG);moveWindow(INFRARE_2_IMG,700,700);
}

void camera::start(void){
    //start pipe
    pipe.start(cfg);
    // define image size and channels
    color.create(Size(640, 480), CV_8UC3);
    infrare1.create(Size(640, 480), CV_8UC1);
    infrare2.create(Size(640, 480), CV_8UC1);
    depth.create(Size(640, 480), CV_8UC3);
    // set mouse callback function for debug
    setMouseCallback(COLOR_IMG,on_MouseHandle_up,(void*)&color);
}

void camera::showImage(void)
{
    rs2::frameset frames;
    // wait frames
    frames = pipe.wait_for_frames();
    // define align 
    rs2::align align_to_depth(RS2_STREAM_COLOR);
    // depth image aligh to color image(this may take a period of time)
    frames = align_to_depth.process(frames);
    if(frames.size()){
	rs2::frame color_frame = frames.get_color_frame();
	//rs2::frame depth_frame = frames.get_depth_frame();
	rs2::frame infrare1_frame = frames.get_infrared_frame(1);
	rs2::frame infrare2_frame = frames.get_infrared_frame(2);	
	rs2::frame depth_frame = color_map.process(frames.get_depth_frame()); 
	color.data=(uchar*)color_frame.get_data();
	infrare1.data=(uchar*)infrare1_frame.get_data();
	infrare2.data=(uchar*)infrare2_frame.get_data();
	depth.data=(uchar*)depth_frame.get_data();
// // 	Mat depth(Size(640, 480), CV_16UC1, (void*)dep.get_data(), Mat::AUTO_STEP);
	imshow(COLOR_IMG, color);
	imshow(DEPTH_IMG, depth);
	imshow(INFRARE_1_IMG, infrare1);
	imshow(INFRARE_2_IMG, infrare2);
    }

}


camera::~camera()
{
    cout<<"over"<<endl;
}
void on_MouseHandle_up(int event, int x, int y, int flags, void *param){
	switch( event)
	{
	    //mouse function
	    case EVENT_LBUTTONDOWN: 
	    {
		mouse_signal_up=true;
		draw_point_up.x=x;
		draw_point_up.y=y;
		cout<<x<<"\t"<<y<<endl;
	    }
		break;
	    default :
		break;
	}
}


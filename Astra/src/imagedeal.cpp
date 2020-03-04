#include <iostream>
#include <opencv2/opencv.hpp>
#include <OpenNI.h>
#include "imagedeal.h"
#include "filedeal.h"
using namespace cv;
Point draw_point;        // 扫描按下的键的坐标
bool mouse_signal=false;   // 扫描按下的键的标志

AstralCam::AstralCam()
{
    ;
}

int AstralCam::Init(void)
{
    openni::Status rc = openni::STATUS_OK;
 
    rc = openni::OpenNI::initialize();
    std::cout<<"After initialization: "<<openni::OpenNI::getExtendedError()<<std::endl;
    
    const char* deviceURI;
    openni::Array<openni::DeviceInfo> deviceList;
    openni::OpenNI::enumerateDevices(&deviceList);
    deviceURI = deviceList[0].getUri();
    cout<<deviceURI<<endl;
       
    rc = device.open(deviceURI);    
    if (rc != openni::STATUS_OK)
    {
	std::cout<<"Device open failed: "<<openni::OpenNI::getExtendedError()<<std::endl;
	openni::OpenNI::shutdown();
	return 1;
    }
    
  
#ifdef COLOR_IMAGE_GET
    rc = color.create(device, openni::SENSOR_COLOR);
    if (rc == openni::STATUS_OK)
    {
	rc = color.start();
	if (rc != openni::STATUS_OK)
	{
	    std::cout<<"Couldn't find color stream: "<<openni::OpenNI::getExtendedError()<<std::endl;
	    color.destroy();
	}
    }
    else
    {
	std::cout<<"Couldn't find color stream: "<<openni::OpenNI::getExtendedError()<<std::endl;
    }
#endif

#ifdef DEPTH_IMAGE_GET
    rc = depth.create(device, openni::SENSOR_DEPTH);
    if (rc == openni::STATUS_OK)
    {
	rc = depth.start();
	if (rc != openni::STATUS_OK)
	{
	    std::cout<<"Couldn't find depth stream: "<<openni::OpenNI::getExtendedError()<<std::endl;
	    depth.destroy();
	}
    }
    else
    {
	std::cout<<"Couldn't find depth stream: "<<openni::OpenNI::getExtendedError()<<std::endl;
    }
#endif

#ifdef IR_IMAGE_GET
    rc = ir.create(device, openni::SENSOR_IR);
    if (rc == openni::STATUS_OK)
    {
	rc = ir.start();
	if (rc != openni::STATUS_OK)
	{
	    std::cout<<"Couldn't find ir stream: "<<openni::OpenNI::getExtendedError()<<std::endl;
	    ir.destroy();
	}
    }
    else
    {
	std::cout<<"Couldn't find ir stream: "<<openni::OpenNI::getExtendedError()<<std::endl;
    }
#endif

// 获取支持的数据流格式,并设置   
    if(ReadStreamFormatAndSet())
    {
	return 2;
    }
    

    std::cout<<"pass"<<std::endl;
    OutputFormatSet();
    Setstreams();
#ifdef DEPTH_IMAGE_GET
    depth_image=Mat(Size(640,480), CV_16UC1);
#endif
    
#ifdef COLOR_IMAGE_GET
    color_image=Mat(Size(640,480), CV_8UC3);
#endif    
    
    return 0;
}

static int image_number=18;
int AstralCam::run()
{
    openni::Status rc = openni::STATUS_OK;
    int changedIndex;	
    rc = openni::OpenNI::waitForAnyStream(m_streams, getImageNum(), &changedIndex,2000);
    if (rc != openni::STATUS_OK)
    {
	std::cout<<"Wait failed "<<std::endl;
	return -1;
    }
    GetFrame();
    

//     cv::Mat dep_image=cv::Mat(480,640,CV_16UC1);
//     cv::Mat dep_image_c2=cv::Mat::zeros(480,640,CV_8UC3);
//     
//     
// 	int max_vla=0;
// 	const openni::DepthPixel* pDepthRow = (const openni::DepthPixel*)m_irFrame.getData();
// 	for(int row=0;row<480;row++)
// 	{
// 	  unsigned short *data=dep_image.ptr<unsigned short>(row);
// 	  unsigned char *data_c2=dep_image_c2.ptr<unsigned char>(row);
// #ifdef MINIOR
// 	  for(int col=639;col>=0;col--)
// #else
// 	  for(int col=0;col<640;col++)
// #endif
// 	  {
// 	     unsigned short dep_data_temp=(*pDepthRow);
// 
// 	     data[col]=dep_data_temp;
// 	     int col_temp=3*col+1;
// 	     data_c2[col_temp]=dep_data_temp;col_temp++;
// 	     data_c2[col_temp]=dep_data_temp>>8;
// 	     pDepthRow++;
// 	  }
// 	}
// #ifdef SHOW_IMAGE
// // 	cv::imshow(WINDOW_NAME,color_image);
// 	cv::imshow(WINDOW_NAME,dep_image);
// 	cv::imshow("dep_image_c2",dep_image_c2);
// #endif
// 	
//     
// 	
// 	
// 	
// 	
// //     string img_num_str=Int_to_String(image_number);
// //     cv::imwrite(COLOR_PATH+img_num_str+".jpg",color_image);
// //     cv::imwrite(DEPTH_PATH+img_num_str+".png",dep_image);
// 	
// 	
// 	
// 	
// #ifdef SAMPLING_MODE		
//     if(mouse_signal)
//     {
// 	mouse_signal=false;
// 	
// // 	string img_num_str=Int_to_String(image_number);
// // 	cv::imwrite(SIMPLING_PATH+img_num_str+".jpg",color_image);
// // 	image_number++;
// 	
// // 	cout<<img_num_str<<endl;	
// // 	int xxx=draw_point.x*3;
// // 	std::cout<<(int)color_image.ptr<unsigned char>(draw_point.y)[xxx]<<"  "<<(int)color_image.ptr<unsigned char>(draw_point.y)[xxx+1]<<"  ";
// // 	std::cout<<(int)color_image.ptr<unsigned char>(draw_point.y)[xxx+2];
// 	std::cout<<"  "<<dep_image.ptr<unsigned short>(draw_point.y)[draw_point.x]<<std::endl;
//     }
//     
// #endif
// 
// 
// 
// 
// #ifdef IDENTIFICATION_MODE
//     string img_num_str=Int_to_String(image_number);
//     cv::imwrite(COLOR_PATH+img_num_str+".jpg",color_image);
//     cv::imwrite(DEPTH_PATH+img_num_str+".jpg",dep_image);
//       
//     vector<string> files=getFile(PATH_SCAN_COLOR);
// 
//     if(files.size()>10)
//     {
// 	Delete_file(COLOR_PATH,image_number-10);
// 	Delete_file(DEPTH_PATH,image_number-10);	
//     }
//     image_number++;
// #endif
    return 0;  
}


void AstralCam::GetFrame(void)
{
#ifdef IR_IMAGE_GET
    openni::VideoFrameRef m_irFrame;	
    ir.readFrame(&m_irFrame);
    if(!m_irFrame.isValid())
    {
	std::cout<<"get ir error"<<std::endl;
    }
//     else{
// 	std::cout<<"get ir ok"<<endl;
//     }
#endif

#ifdef DEPTH_IMAGE_GET
    openni::VideoFrameRef m_depFrame;	
    depth.readFrame(&m_depFrame);
    openni::DepthPixel* pDepthRow = (openni::DepthPixel*)m_depFrame.getData();
    depth_image.data=(unsigned char *)pDepthRow;
    imshow("depth",depth_image);
    
    
    if(!m_depFrame.isValid())
    {
	std::cout<<"get depth error"<<std::endl;
    }
//     else{
// 	std::cout<<"get depth ok"<<endl;
//     }
    
#endif

#ifdef COLOR_IMAGE_GET
    openni::VideoFrameRef m_colFrame;	
    color.readFrame(&m_colFrame);
    unsigned char * pColRow = (unsigned char*)m_colFrame.getData();
    color_image.data=pColRow;
    cvtColor(color_image,color_image,CV_BGR2RGB);
    imshow("color",color_image);
    if(!m_colFrame.isValid())
    {
	std::cout<<"get color error"<<std::endl;
    }
//     else{
// 	std::cout<<"get color ok"<<endl;
//     }
#endif
}

void AstralCam::Setstreams(void)
{
    int amount=getImageNum();
    int number=0;
    m_streams = new openni::VideoStream*[amount];
#ifdef IR_IMAGE_GET
    m_streams[number] = &ir;
    number++;
#endif
#ifdef DEPTH_IMAGE_GET
    m_streams[number] = &depth;
    number++;
#endif
#ifdef COLOR_IMAGE_GET
    m_streams[number] = &color;
    number++;
#endif
}

void AstralCam::OutputFormatSet(void)
{
   //     输出彩色和深度图像的分辨率和数据格式   
#ifdef IR_IMAGE_GET
    openni::VideoMode depVideoModeir=ir.getVideoMode();
    std::cout<<"ir  "<<depVideoModeir.getResolutionX()<<"   "<<depVideoModeir.getResolutionY()<<"   "<<depVideoModeir.getFps()<<"   "<<depVideoModeir.getPixelFormat()<<std::endl;
#endif
#ifdef DEPTH_IMAGE_GET
    openni::VideoMode depVideoModedep=depth.getVideoMode();
    std::cout<<"dep  "<<depVideoModedep.getResolutionX()<<"   "<<depVideoModedep.getResolutionY()<<"   "<<depVideoModedep.getFps()<<"   "<<depVideoModedep.getPixelFormat()<<std::endl;
#endif
#ifdef COLOR_IMAGE_GET
    openni::VideoMode depVideoModecolor=color.getVideoMode();
    std::cout<<"color  "<<depVideoModecolor.getResolutionX()<<"   "<<depVideoModecolor.getResolutionY()<<"   "<<depVideoModecolor.getFps()<<"   "<<depVideoModecolor.getPixelFormat()<<std::endl;
#endif
}


int AstralCam::ReadStreamFormatAndSet(void)
{
    openni::Status rc = openni::STATUS_OK;
#ifdef IR_IMAGE_GET
    const openni::Array<openni::VideoMode>& getir=ir.getSensorInfo().getSupportedVideoModes();
//     cout<<getir.getSize()<<endl;
//     for(int i=0;i<getir.getSize();i++)
//     {
// 	cout<<i<<"  "<<getir[i].getResolutionX()<<"  "<<getir[i].getResolutionY()<<"  "<<getir[i].getPixelFormat()<<endl;
//     }
    rc =ir.setVideoMode(getir[4]);   
    // // //     设置数据流格式
    if(rc == openni::STATUS_OK)
	cout<<"success"<<endl;
    else
	cout<<"faile change"<<endl;
    if (!ir.isValid())
    {
	    std::cout<<"No valid ir streams. Exiting: "<<openni::OpenNI::getExtendedError()<<std::endl;
	    openni::OpenNI::shutdown();
	    return 2;
    }
#endif
#ifdef DEPTH_IMAGE_GET
    const openni::Array<openni::VideoMode>& getdep=depth.getSensorInfo().getSupportedVideoModes();
//     cout<<getdep.getSize()<<endl;
//     for(int i=0;i<getdep.getSize();i++)
//     {
// 	cout<<i<<"  "<<getdep[i].getResolutionX()<<"  "<<getdep[i].getResolutionY()<<"  "<<getdep[i].getPixelFormat()<<endl;
//     }
    // // //     设置数据流格式
    rc =depth.setVideoMode(getdep[5]);   
    if(rc == openni::STATUS_OK)
	cout<<"success"<<endl;
    else
	cout<<"faile change"<<endl;
    if (!depth.isValid())
    {
	    std::cout<<"No valid depth streams. Exiting: "<<openni::OpenNI::getExtendedError()<<std::endl;
	    openni::OpenNI::shutdown();
	    return 2;
    }
#endif
#ifdef COLOR_IMAGE_GET
    const openni::Array<openni::VideoMode>& getcol=color.getSensorInfo().getSupportedVideoModes();
//     cout<<getcol.getSize()<<endl;
//     for(int i=0;i<getcol.getSize();i++)
//     {
// 	cout<<i<<"  "<<getcol[i].getResolutionX()<<"  "<<getcol[i].getResolutionY()<<"  "<<getcol[i].getPixelFormat()<<endl;
//     }
    // // //     设置数据流格式
    rc =color.setVideoMode(getcol[9]);   
    if(rc == openni::STATUS_OK)
	cout<<"success"<<endl;
    else
	cout<<"faile change"<<endl;
    if(!color.isValid())
    {
	    std::cout<<"No valid depth streams. Exiting: "<<openni::OpenNI::getExtendedError()<<std::endl;
	    openni::OpenNI::shutdown();
	    return 2;
    }
#endif  
    return 0; 
}


// 鼠标回调函数
void on_MouseHandle(int event, int x, int y, int flags, void *param){
	switch( event)
	{
	    //鼠标移动消息
	    case EVENT_LBUTTONDOWN: 
	    {
		mouse_signal=true;
		draw_point.x=x;
		draw_point.y=y;
	    }
		break;
	    default :
		break;
	}
}
bool getSignal(void)
{
    return mouse_signal;
}
Point getPoint(void)
{
    return draw_point;
}

int getImageNum(void)
{
    int number=0;   
#ifdef IR_IMAGE_GET
    number++;
#endif
#ifdef DEPTH_IMAGE_GET
    number++;
#endif
#ifdef COLOR_IMAGE_GET
    number++;
#endif
    return number;
}

# D435

D435相机 Demo，包括：获取彩色，配准后深度图，左红外，右红外 四幅图像

D435摄像头github详细资料链接[link](https://github.com/IntelRealSense/librealsense),  

Ubuntu安装链接[link](https://github.com/IntelRealSense/librealsense/blob/master/doc/installation.md)   

程序中包括深度图像向彩色配准操作，视平台不同，对齐操作时间可能不同，如果将对齐操作屏蔽，处理时间会大大缩短。程序中调用opencv进行图像显示，所以需要安装opencv。
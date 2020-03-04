#include <opencv2\opencv.hpp>
#include <iostream>
#include <chrono>
#include "app.h"
#include "image.h"
#include "counttime.h"

using namespace std::chrono;
typedef steady_clock Clock;

#undef main  //#undef cancel the preprocessor definition from the previous program
int main(int, char**)
{
	cv::namedWindow("chuangkou");//just to use to get waitkey

	App app;
	app.Init();
	image frame;
	//timing variable   unit is ms
	Times timing(MILLISECOND_TYPE);
	while (true)
	{		
		if (app.Update() == true)
		{
			//image update
			frame.image_init(app.GetColorImage());
			
			//foreach algorithm
			std::cout << "foreach al   ";
			timing.start();
			frame.ForeachAl();
			timing.end();

			//pointer access algorithm 
			std::cout << "pointal  ";
			timing.start();
			frame.PointAl();
			timing.end();
		}
		else
		{
			//image do not update
			app.PrintTest();
		}
		if (cv::waitKey(30) == 27)
			break;

		
			
	}

	//clean up
	app.Shutdown();

	return 0;
}




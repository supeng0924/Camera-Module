#include "image.h"
#include <opencv2\opencv.hpp>
#include <iostream>
void image::image_init(cv::Mat& input_im)
{
	cv::resize(input_im, image_res, cv::Size(), 0.5, 0.5);
	cv::imshow("image_res", image_res);
}
void image::ForeachAl(void)
{
	image_res.forEach<Pixel>(Operator());	
}
void image::PointAl(void)
{
	for (int i = 0; i < image_res.rows; i++)
	{
		uchar *data = image_res.ptr<uchar>(i);
		for (int j = 0; j < image_res.cols; j++)
		{
			int jj = j * 3;
			if (pow(double(data[jj]) / 10, 2.5) > 100)
			{
				data[jj] = 255;
				data[jj + 1] = 255;
				data[jj + 2] = 255;
			}
			else
			{
				data[jj] = 0;
				data[jj + 1] = 0;
				data[jj + 2] = 0;
			}
		}
	}
}
void complicatedThreshold(Pixel &pixel)
{
	if (pow(double(pixel.x) / 10, 2.5) > 100)
	{
		pixel.x = 255;
		pixel.y = 255;
		pixel.z = 255;
	}
	else
	{
		pixel.x = 0;
		pixel.y = 0;
		pixel.z = 0;
	}
}


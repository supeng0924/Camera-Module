#include <opencv2\opencv.hpp>
typedef cv::Point3_<uchar>  Pixel;
class image {
public:
	void image_init(cv::Mat&);
	void ImageResize(void);
	void SetScale(void);
	void ForeachAl(void);
	void PointAl(void);
private:
	cv::Mat image_res;
};
void complicatedThreshold(Pixel &pixel);
struct Operator
{
	void operator ()(Pixel &pixel, const int * position) const
	{
		//perform a simple threshold operation
		complicatedThreshold(pixel);
	}
};

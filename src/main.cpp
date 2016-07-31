#include <opencv2/opencv.hpp>

int main(int argc, char** argv)
{
	cv::VideoCapture cap;

	cap.open("test.avi");
	return 0;
}
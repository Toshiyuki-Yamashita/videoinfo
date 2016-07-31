#include <opencv2/opencv.hpp>

int main(int argc, char** argv)
{
	char* input = NULL;
	if (argc > 1)
	{
		input = argv[1];
	}
	cv::VideoCapture cap;

	if (input == NULL)
	{
		return -1;
	}
	cap.open(input);

	int frames = static_cast<int>(cap.get(CV_CAP_PROP_FRAME_COUNT));

	fprintf(stdout, "%ld\n", frames);

	return 0;
}
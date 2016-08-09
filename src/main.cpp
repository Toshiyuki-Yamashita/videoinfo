#include <windows.h>
#include <Shlwapi.h>
#include <opencv2/opencv.hpp>
#include <Vfw.h>
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "vfw32.lib")
#define BSIZE 4096

int videoinfo(int argc, char** argv)
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

struct videowriter;
typedef int (writefunc)(videowriter* w, cv::Mat& img, double fps, cv::Size size);

struct videowriter
{
	writefunc* write;
	const char* filename;
	int fourcc;
	int count;
	cv::VideoWriter w;
};

static int writeframe(videowriter* w, cv::Mat& img, double fps, cv::Size size)
{
	w->w.write(img);
	w->count++;
	return 0;
}

static int writestart(videowriter* w, cv::Mat& img, double fps, cv::Size size)
{
	w->w.open(w->filename, w->fourcc, fps, size);
	w->write = &writeframe;
	return w->write(w, img, fps, size);
}

static int videowriter_init(videowriter* w, const char* filename, int fourcc)
{
	w->filename = filename;
	w->fourcc = fourcc;
	w->write = &writestart;
	w->count = 0;
	return 0;
}
int videocat(int argc, char** argv)
{
	AVIFileInit();
	videowriter w;
	videowriter_init(&w, "output.avi", CV_FOURCC('D', 'I', 'B', ' '));
	int count = 0;
	for (int i = 0; i < argc; i++)
	{
		cv::VideoCapture cap;
		cv::Size size;
		cap.open(argv[i+1]);
		double fps = cap.get(CV_CAP_PROP_FPS);
		size.width = static_cast<int>(cap.get(CV_CAP_PROP_FRAME_WIDTH));
		size.height = static_cast<int>(cap.get(CV_CAP_PROP_FRAME_HEIGHT));
		cv::Mat img;
		while (cap.grab())
		{ 
			cap.retrieve(img);
			w.write(&w, img, fps, size);
		}
	}
	AVIFileExit();
	fprintf(stdout, "%d frames wrote", w.count);
	return 0;
}

int main(int argc, char** argv)
{
	TCHAR name[BSIZE];

	GetModuleFileName(NULL, name, BSIZE);
	LPSTR n = PathFindFileName(name);

	if (strcmp(n, "videoinfo.exe") == 0)
	{
		return videoinfo(argc, argv);
	}

	if (strcmp(n, "videocat.exe") == 0)
	{
		return videocat(argc, argv);
	}

	return 0;
}
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

extern "C" {
#include <WinSock2.h>
#include <ws2tcpip.h>
}
#include <windows.h>
#include <Shlwapi.h>
#include <opencv2/opencv.hpp>
#include "bzlib.h"
#include <Vfw.h>
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "vfw32.lib")
#pragma comment(lib, "Ws2_32.lib")
#define BSIZE 4096

#define IMAGESIZE (1280*960)

int senddata(int sock, void* data, size_t size)
{
	char* p = static_cast<char*>(data);
	do {
		int l = send(sock, p, size, 0);
		if (l < 0) return -1;
		p += l;
		size -= l;
	} while (size > 0);
	return 0;
}

int recvdata(int sock, void* data, size_t size)
{
	char* p = static_cast<char*>(data);
	do {
		int l = recv(sock, p , size, 0);
		if (l < 0) return -1;
		p += l;
		size -= l;
	} while (size > 0);
	return 0;
}

int connectsrv(const char* server, const char* port)
{
	struct addrinfo *results = NULL;
	struct addrinfo *addrptr = NULL;
	struct addrinfo hints = { 0 };
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_family = AF_UNSPEC;

	getaddrinfo(
		server,//ローカルホストを指定します
		port,
		&hints,
		&results
	);

	int sock = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

	while (connect(sock, results->ai_addr, results->ai_addrlen) != 0)
	{
		fprintf(stderr, "retrying... %s:%s\n", server, port);
		Sleep(100);
	};
	fprintf(stderr, "connected %s:%s\n", server, port);

	cv::namedWindow("test");
	static char src[IMAGESIZE];
	static char buff[IMAGESIZE];
	char fname[4096];

	LARGE_INTEGER freq;
	LARGE_INTEGER time;
	::QueryPerformanceFrequency(&freq);
	::QueryPerformanceCounter(&time);
	while (true)
	{
		struct 
		{
			int size;
			int serial;
		} head = { 0 };
		int cmd = 0;
		//senddata(sock, &cmd, sizeof(cmd));
		if (recvdata(sock, &head, sizeof(head)) < 0)
		{
			Sleep(66);
			continue;
		}
		recvdata(sock, src, head.size);
		LARGE_INTEGER now1;
		::QueryPerformanceCounter(&now1);
		unsigned int blen = IMAGESIZE;
		BZ2_bzBuffToBuffDecompress(buff, &blen, src, head.size, 0, 0);
		cv::Mat img(960, 1280, CV_8UC1, buff);
		_snprintf(fname, 4096, "image-%d.png", head.serial);
		cv::imwrite(fname, img);
		//cv::imshow("test", img);
		//cv::waitKey(1);
		LARGE_INTEGER now;
		::QueryPerformanceCounter(&now);
		fprintf(stdout, "serial: %d size: %d %lf %lf\n", head.serial, head.size, (double)(now.QuadPart - time.QuadPart)/freq.QuadPart, (double)(now1.QuadPart - time.QuadPart) / freq.QuadPart);
		time = now;
	}


	freeaddrinfo(results);
	return 0;
}


int main(int argc, char** argv)
{
	WSADATA wsaData = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	char* target = argv[1];
	char* port = argv[2];

	if (argc < 3)
	{
		return -1;
	}


	connectsrv(target, port);

	WSACleanup();
	return 0;
}
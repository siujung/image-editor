#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <Windows.h>

using namespace std;
using namespace cv;

class Video
{
private:
	VideoCapture cap;
	Mat srcFrame;
	Mat dstFrame;
	int width = cap.get(CAP_PROP_FRAME_WIDTH);
	int height = cap.get(CAP_PROP_FRAME_HEIGHT);

	int fourcc = VideoWriter::fourcc('M', 'J', 'P', 'G');
	double fps = 25.0;
	string filename = "./outcpp.avi";
	VideoWriter vw= VideoWriter(filename, fourcc, fps, Size(width, height));
public:
	Video(String srcPath);
	Video();
	~Video();

	static void write();
	void setSrc(Mat newFrame);
	void setDst(Mat newFrame);
	Mat getDst();
	Mat getSrc();
	VideoCapture getCap();
	int lighten(int intensity);
	int changeContrast(int contrast);
	int rotate(int angle);
	int blur(int value);
	int gaussian(int value);
};
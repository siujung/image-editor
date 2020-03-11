#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <Windows.h>

using namespace std;
using namespace cv;

class Image
{
private:
	vector<Mat> srcMats;
	Mat srcMat;
	Mat dstMat;

public:
	Image(String srcPath);
	Image();
	~Image();

	int canny(int threshold);
	int lighten(int intensity);
	int panorama(Stitcher::Mode mode = Stitcher::PANORAMA);
	int resize(int size);
	Mat getDstMat();
};

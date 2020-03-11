#include "Video.h"

using namespace std;
using namespace cv;

Video::Video(){}

Video::Video(String path)
{	
	cap.open(path);
	
	if (!cap.isOpened()) {
		cout << "Error opening video stream or file" << endl;
	}
	
	
}

Video::~Video ()
{
	cap.release();
}

void  Video::write() {
		//flip(dstFrame, dstFrame, 1);
		//vw.write(dstFrame);
}

void Video::setSrc(Mat newFrame) {
	srcFrame=newFrame;
}

void Video::setDst(Mat newFrame) {
	dstFrame = newFrame;
}

Mat Video::getSrc() {
	return srcFrame;
}

Mat Video::getDst() {
	return dstFrame;
}

VideoCapture Video::getCap() {
	return cap;
}

int Video::lighten(int intensity) {
	dstFrame = Mat::zeros(srcFrame.size(), srcFrame.type());
	srcFrame.Mat::convertTo(dstFrame, CV_8U, 1, (double)intensity - 100);

	if (NULL != dstFrame.data)
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}

int Video::changeContrast(int contrast) {
	dstFrame = Mat::zeros(srcFrame.size(), srcFrame.type());
	srcFrame.Mat::convertTo(dstFrame, -1, contrast/100, 0);
	if (NULL != dstFrame.data)
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}

int Video::rotate(int angle) {
	Point2f center(srcFrame.cols / 2, srcFrame.rows / 2);
	Mat M = getRotationMatrix2D(center, angle, 1);
	warpAffine(srcFrame, dstFrame, M, srcFrame.size());
	if (NULL != dstFrame.data)
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}

int Video::blur(int value) {
	cv::blur(srcFrame, dstFrame, Size(value, value), Point(-1, -1), BORDER_DEFAULT);
	if (NULL != dstFrame.data)
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}

int Video::gaussian(int value) {
	GaussianBlur(srcFrame, dstFrame, Size(value, value), 0, 0, BORDER_DEFAULT);
	if (nullptr != dstFrame.data)
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}
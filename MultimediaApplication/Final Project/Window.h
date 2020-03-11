#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include "Image.h"

using namespace std;
using namespace cv;


class Window
{
private:
	String nameWindow;
	Image srcImage;

public:
	Window(Image image, string name);
	Window();
	~Window();

	void create();

	void show();
	static void lightenCallback(int intensity, void *data);
	static void resizeCallback(int size, void *data);
	void settrackbar(int function);
};
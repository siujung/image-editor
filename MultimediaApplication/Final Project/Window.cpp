#include "Window.h"
#include"Image.h"
using namespace std;
using namespace cv;

Window::Window(Image image, string name)
{
	srcImage = image;
	nameWindow = name;
}

Window::Window() {}


Window::~Window()
{
	destroyWindow(nameWindow);
}

void Window::create()
{
	namedWindow(nameWindow);
}

void Window::show()
{
	imshow(nameWindow, srcImage.getDstMat());
}

void Window::lightenCallback(int intensity, void *data)
{
	Window* p = (Window*)data;
	p->srcImage.lighten(intensity);
	//srcImage.lighten(intensity);
}

void Window::resizeCallback(int size, void* data)
{
	if (size < 1)
		size = 1;
	Window* p = (Window*)data;
	p->srcImage.resize(size);
	//srcImage.resize(size);
}

void Window::settrackbar(int function)
{
	switch (function)
	{
	case(1):
		{
			int pos = 50;
			namedWindow("trackbar");
			createTrackbar("trackbar resize", "trackbar", &pos, 100, resizeCallback, this);
			while (true)
			{
				imshow(nameWindow, srcImage.getDstMat());
				if (char c = waitKey(10) == 27)
					break;
			}
			break;
		}
	case(2):
		{
			int pos = 50;
			namedWindow("trackbar");
			createTrackbar("trackbar lighten", "trackbar", &pos, 100, lightenCallback, this);
			while (true)
			{
				imshow(nameWindow, srcImage.getDstMat());
				if (char c = waitKey(10) == 27)
					break;
			}
			break;
		}
	}
}




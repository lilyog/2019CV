#include<cstdio>
#include<cstdlib>
#include<cmath>
# include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main()
{
	// read image 
	Mat img = imread("lena.bmp", CV_8UC1);
	Mat shrink;
	
	resize(img,shrink, Size(img.cols / 2, img.rows / 2), 0, 0, INTER_LINEAR); //shrink to half
	
	// show image
	imshow("shrink", shrink);

	// write image 
	imwrite("shrink.jpg", shrink);

	waitKey(0);
	return 0;
}

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
	Mat rotate;
	
	Point2f pc(img.cols / 2., img.rows / 2.);  //center of image
	Mat r = getRotationMatrix2D(pc, -45, 1.0); //get rotation matrix along pc
	warpAffine(img,rotate,r,img.size());


	// show image
	imshow("rotate", rotate);

	// write image 
	imwrite("rotate.jpg", rotate);

	waitKey(0);
	return 0;
}

#include<cstdio>
#include<cstdlib>
#include<cmath>
# include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main()
{
	// read image 
	Mat img = imread("lena.bmp", CV_8UC1);

	// sample code : Lomo Effect
	int center_i = img.rows / 2;
	int center_j = img.cols / 2;
	double max_dist = sqrt(center_i*center_i + center_j*center_j);
	int tmp;

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols/2; j++)
		{
			tmp = img.at<uchar>(i, j);
			img.at<uchar>(i, j) = img.at<uchar>(i,img.cols-j-1);
			img.at<uchar>(i, img.cols - j - 1) = tmp;
		}
	}
	// show image
	imshow("right-side-left", img);

	// write image 
	imwrite("right-side-left.jpg", img);

	waitKey(0);
	return 0;
}

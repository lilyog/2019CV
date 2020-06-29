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

	for (int i = 0; i < img.rows/2; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			tmp = img.at<uchar>(i, j);
			img.at<uchar>(i, j) = img.at<uchar>(img.rows - i - 1,j);
			img.at<uchar>(img.rows - i - 1, j) = tmp;
		}
	}
	// show image
	imshow("upside-down", img);

	// write image 
	imwrite("upside-downLena.jpg", img);

	waitKey(0);
	return 0;
}

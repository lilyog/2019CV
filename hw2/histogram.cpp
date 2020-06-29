#include<cstdio>
#include<cstdlib>
#include<cmath>
# include <iostream>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main()
{
	int num[256] = { 0 };   

	// read image 
	Mat img = imread("lena.bmp", CV_8UC1);

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			for (int k = 0; k < 256; k++)
			{
				if (k == img.at<uchar>(i, j))
				{
					num[k]++;
					break;
				}
			}
		}
	}

	fstream file;
	file.open("histogram.txt", ios::out | ios::trunc);  //write data for gnuplot to draw histogram
	for (int i = 0; i < 256; i++)
	{
		file << i << " " << num[i] << "\n";
	}


	// show image
//	imshow("binary", img);

	// write image 
//	imwrite("binary.jpg", img);

	waitKey(0);
	return 0;
}
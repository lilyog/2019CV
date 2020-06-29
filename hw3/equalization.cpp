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
	int num[256] = { 0 }, cdf[256] = { 0 };
	double pixels=0;
	// read image 
	Mat img = imread("lena.bmp", CV_8UC1);

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			pixels++;                          //count pixels
			for (int k = 0; k < 256; k++)
			{
				if (k == img.at<uchar>(i, j))  //num[] is the 0-255 each appearing times
				{
					num[k]++;
					break;
				}
			}
		}
	}
	
	for (int i = 0; i < 256; i++)     //count cdf
	{
		for (int j = 0; j <= i; j++)
		{
			cdf[i] += num[j];
		}
	}
	
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			img.at<uchar>(i, j) = round(255*cdf[img.at<uchar>(i, j)]/pixels) ;			//histogram equalization 
		}
	}

	for (int i = 0; i < img.rows; i++)        //histogram after equalization 
	{
		for (int j = 0; j < img.cols; j++)
		{
			for (int k = 0; k < 256; k++)
			{
				if (k == img.at<uchar>(i, j))  //num[] is the 0-255 each appearing times
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
	imshow("equalization", img);

	// write image 
	imwrite("equalization.jpg", img);
	waitKey(0);

	return 0;
}

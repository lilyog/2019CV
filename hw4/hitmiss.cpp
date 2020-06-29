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
	Mat img = imread("lena.bmp", CV_8UC1);    //thresholding

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			if (img.at<uchar>(i, j) >= 128)
			{
				img.at<uchar>(i, j) = 255;
			}
			else
				img.at<uchar>(i, j) = 0;
		}
	}
	Mat dil = img.clone();
	int flag;
	for (int i = 0; i < img.rows; i++)          //use octagon kernel to erosion
	{
		for (int j = 0; j < img.cols; j++)
		{
			if (img.at<uchar>(i, j) == 255)    //erosion to white pixel
			{
				flag = 0;

				if (i > 0 && j - 1 > 0 && i < img.rows && j - 1 < img.cols)
				{
					if (img.at<uchar>(i, j - 1) == 255)
					{
						flag++;
					}
				}

				if (i + 1 > 0 && j > 0 && i + 1 < img.rows && j < img.cols)
				{
					if (img.at<uchar>(i + 1, j) == 255)
					{
						flag++;
					}
				}
				
				if (i - 1 > 0 && j > 0 && i - 1 < img.rows && j < img.cols)
				{
					if (img.at<uchar>(i - 1, j) == 0)
					{
						flag++;
					}
				}

				if (i - 1 > 0 && j + 1 > 0 && i - 1 < img.rows && j + 1 < img.cols)
				{
					if (img.at<uchar>(i - 1, j + 1) == 0)
					{
						flag++;
					}
				}

				if (i > 0 && j + 1 > 0 && i < img.rows && j + 1 < img.cols)
				{
					if (img.at<uchar>(i, j + 1) == 0)
					{
						flag++;
					}
				}

				if (flag == 5)
				{
					dil.at<uchar>(i, j) = 255;
				}
				else if (flag != 5)
				{
					dil.at<uchar>(i, j) = 0;
				}
			}
		}
	}


	// show image
	imshow("hitmiss", dil);

	// write image 
	imwrite("hitmiss.jpg", dil);

	waitKey(0);
	return 0;
}
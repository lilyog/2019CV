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
				
				if (i - 2 > 0 && j - 1 > 0 && i - 2 < img.rows && j - 1 < img.cols)    //check octagon's 20 parts are white or not
				{                                                                      //if 20 parts are all white,then i,j is white 
					if (img.at<uchar>(i - 2, j - 1) == 255)
					{
						flag++;
					}
				}
				if (i - 2 > 0 && j > 0 && i - 2 < img.rows && j < img.cols)
				{
					if (img.at<uchar>(i - 2, j) == 255)
					{
						flag++;
					}
				}
				if (i - 2 > 0 && j + 1 > 0 && i - 2 < img.rows && j + 1 < img.cols)
				{
					if (img.at<uchar>(i - 2, j + 1) == 255)
					{
						flag++;
					}
				}
				if (i - 1 > 0 && j - 2 > 0 && i - 1 < img.rows && j - 2 < img.cols)
				{
					if (img.at<uchar>(i - 1, j - 2) == 255)
					{
						flag++;
					}
				}
				if (i - 1 > 0 && j - 1 > 0 && i - 1 < img.rows && j - 1 < img.cols)
				{
					if (img.at<uchar>(i - 1, j - 1) == 255)
					{
						flag++;
					}
				}
				if (i - 1 > 0 && j > 0 && i - 1 < img.rows && j < img.cols)
				{
					if (img.at<uchar>(i - 1, j)== 255)
					{
						flag++;
					}
				}
				if (i - 1 > 0 && j + 1 > 0 && i - 1 < img.rows && j + 1 < img.cols)
				{
					if (img.at<uchar>(i - 1, j + 1) == 255)
					{
						flag++;
					}
				}
				if (i - 1 > 0 && j + 2 > 0 && i - 1 < img.rows && j + 2 < img.cols)
				{
					if (img.at<uchar>(i - 1, j + 2) == 255)
					{
						flag++;
					}
				}
				if (i > 0 && j - 2 > 0 && i < img.rows && j - 2 < img.cols)
				{
					if (img.at<uchar>(i , j - 2) == 255)
					{
						flag++;
					}
				}
				if (i > 0 && j - 1 > 0 && i < img.rows && j - 1 < img.cols)
				{
					if (img.at<uchar>(i, j - 1) == 255)
					{
						flag++;
					}
				}
				if (i > 0 && j + 1 > 0 && i < img.rows && j + 1 < img.cols)
				{
					if (img.at<uchar>(i, j + 1) == 255)
					{
						flag++;
					}
				}
				if (i > 0 && j + 2 > 0 && i < img.rows && j + 2 < img.cols)
				{
					if (img.at<uchar>(i, j + 2) == 255)
					{
						flag++;
					}
				}
				if (i + 1 > 0 && j - 2 > 0 && i + 1 < img.rows && j - 2 < img.cols)
				{
					if (img.at<uchar>(i + 1, j - 2) == 255)
					{
						flag++;
					}
				}
				if (i + 1 > 0 && j - 1 > 0 && i + 1 < img.rows && j - 1 < img.cols)
				{
					if (img.at<uchar>(i + 1, j - 1) == 255)
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
				if (i + 1 > 0 && j + 1 > 0 && i + 1 < img.rows && j + 1 < img.cols)
				{
					if (img.at<uchar>(i + 1, j + 1) == 255)
					{
						flag++;
					}
				}
				if (i + 1 > 0 && j + 2 > 0 && i + 1 < img.rows && j + 2 < img.cols)
				{
					if (img.at<uchar>(i + 1, j + 2) == 255)
					{
						flag++;
					}
				}
				if (i + 2 > 0 && j - 1 > 0 && i + 2 < img.rows && j - 1 < img.cols)
				{
					if (img.at<uchar>(i + 2, j - 1) == 255)
					{
						flag++;
					}
				}
				if (i + 2 > 0 && j > 0 && i + 2 < img.rows && j < img.cols)
				{
					if (img.at<uchar>(i + 2, j) == 255)
					{
						flag++;
					}
				}
				if (i + 2 > 0 && j + 1 > 0 && i + 2 < img.rows && j + 1 < img.cols)
				{
					if (img.at<uchar>(i + 2, j + 1) == 255)
					{
						flag++;
					}
				}
				
				if (flag == 20)
				{
					dil.at<uchar>(i, j) = 255;
				}
				else if (flag != 20)
				{
					dil.at<uchar>(i, j) = 0;
				}
			}
		}
	}


	// show image
	imshow("erosion", dil);

	// write image 
	imwrite("erosion.jpg", dil);

	waitKey(0);
	return 0;
}
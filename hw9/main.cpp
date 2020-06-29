#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<ctime>
# include <iostream>
#include <random>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

Mat robert(Mat s,int thr)
{
	Mat pad,edge;
	s.copyTo(edge);
	copyMakeBorder(s, pad, 0, 1, 0, 1, BORDER_REPLICATE);
	int r1, r2;
	for (int i = 0; i < s.rows; i++)
	{
		for (int j = 0; j < s.cols; j++)
		{
			r1 = -pad.at<uchar>(i, j) + pad.at<uchar>(i + 1, j + 1);
			r2 = pad.at<uchar>(i + 1, j) - pad.at<uchar>(i, j + 1);
			if (sqrt(r1 * r1 + r2 * r2) > thr)
			{
				edge.at<uchar>(i, j) = 0;
			}
			else
				edge.at<uchar>(i, j) = 255;
		}
	}

	return edge;
}
Mat prewitt(Mat s, int thr)
{
	Mat pad, edge;
	s.copyTo(edge);
	copyMakeBorder(s, pad, 1, 1, 1, 1, BORDER_REPLICATE);
	int r1, r2;
	for (int i = 0; i < s.rows; i++)
	{
		for (int j = 0; j < s.cols; j++)
		{
			r1 = pad.at<uchar>(i + 1, j - 1) + pad.at<uchar>(i + 1, j) + pad.at<uchar>(i + 1, j + 1) - pad.at<uchar>(i - 1, j - 1) - pad.at<uchar>(i - 1, j) - pad.at<uchar>(i - 1, j + 1);
			r2 = pad.at<uchar>(i - 1, j + 1) + pad.at<uchar>(i, j + 1) + pad.at<uchar>(i + 1, j + 1) - pad.at<uchar>(i - 1, j - 1) - pad.at<uchar>(i, j - 1) - pad.at<uchar>(i + 1, j - 1);
			if (sqrt(r1 * r1 + r2 * r2) > thr)
			{
				edge.at<uchar>(i, j) = 0;
			}
			else
				edge.at<uchar>(i, j) = 255;
		}
	}

	return edge;
}
Mat kirschCompass(Mat s, int thr)
{
	Mat pad, edge;
	s.copyTo(edge);
	copyMakeBorder(s, pad, 1, 1, 1, 1, BORDER_REPLICATE);
	int k[8],max;
	
	for (int i = 0; i < s.rows; i++)
	{
		for (int j = 0; j < s.cols; j++)
		{
			
			k[0] = -3 * pad.at<uchar>(i, j) - 3 * pad.at<uchar>(i, j + 1) + 5 * pad.at<uchar>(i, j + 2) - 3 * pad.at<uchar>(i + 1, j) \
				+5 * pad.at<uchar>(i + 1, j + 2) - 3 * pad.at<uchar>(i + 2, j) - 3 * pad.at<uchar>(i + 2, j + 1) + 5 * pad.at<uchar>(i + 2, j + 2);
			k[1] = -3 * pad.at<uchar>(i, j) + 5 * pad.at<uchar>(i, j + 1) + 5 * pad.at<uchar>(i, j + 2)  -3 * pad.at<uchar>(i + 1, j) \
				+5 * pad.at<uchar>(i + 1, j + 2)  -3 * pad.at<uchar>(i + 2, j)  -3 * pad.at<uchar>(i + 2, j + 1)  -3 * pad.at<uchar>(i + 2, j + 2);
			k[2] = 5 * pad.at<uchar>(i, j) + 5 * pad.at<uchar>(i, j + 1) + 5 * pad.at<uchar>(i, j + 2) - 3 * pad.at<uchar>(i + 1, j) \
				-3 * pad.at<uchar>(i + 1, j + 2) - 3 * pad.at<uchar>(i + 2, j) - 3 * pad.at<uchar>(i + 2, j + 1) - 3 * pad.at<uchar>(i + 2, j + 2);
			k[3] = 5 * pad.at<uchar>(i, j) + 5 * pad.at<uchar>(i, j + 1) - 3 * pad.at<uchar>(i, j + 2) + 5 * pad.at<uchar>(i + 1, j) \
				-3 * pad.at<uchar>(i + 1, j + 2) - 3 * pad.at<uchar>(i + 2, j) - 3 * pad.at<uchar>(i + 2, j + 1) - 3 * pad.at<uchar>(i + 2, j + 2);
			k[4] = 5 * pad.at<uchar>(i, j) - 3 * pad.at<uchar>(i, j + 1) - 3 * pad.at<uchar>(i, j + 2) + 5 * pad.at<uchar>(i + 1, j) \
				-3 * pad.at<uchar>(i + 1, j + 2) + 5 * pad.at<uchar>(i + 2, j) - 3 * pad.at<uchar>(i + 2, j + 1) - 3 * pad.at<uchar>(i + 2, j + 2);
			k[5] = -3 * pad.at<uchar>(i, j)  -3 * pad.at<uchar>(i, j + 1)  -3 * pad.at<uchar>(i, j + 2) + 5 * pad.at<uchar>(i + 1, j) \
				-3 * pad.at<uchar>(i + 1, j + 2) + 5 * pad.at<uchar>(i + 2, j) + 5 * pad.at<uchar>(i + 2, j + 1)  -3 * pad.at<uchar>(i + 2, j + 2);
			k[6] = -3 * pad.at<uchar>(i, j) - 3 * pad.at<uchar>(i, j + 1) - 3 * pad.at<uchar>(i, j + 2) - 3 * pad.at<uchar>(i + 1, j) \
				-3 * pad.at<uchar>(i + 1, j + 2) + 5 * pad.at<uchar>(i + 2, j) + 5 * pad.at<uchar>(i + 2, j + 1) + 5 * pad.at<uchar>(i + 2, j + 2);
			k[7] = -3 * pad.at<uchar>(i, j)  -3 * pad.at<uchar>(i, j + 1)  -3 * pad.at<uchar>(i, j + 2)  -3 * pad.at<uchar>(i + 1, j) \
				+5 * pad.at<uchar>(i + 1, j + 2)  -3 * pad.at<uchar>(i + 2, j) + 5 * pad.at<uchar>(i + 2, j + 1) + 5 * pad.at<uchar>(i + 2, j + 2);
			
			max = k[0];
			for (int r = 0; r < 8; r++)
			{
				if (k[r] > max)
				{
					max = k[r];
				}
			}
			
			if (max > thr)
			{
				edge.at<uchar>(i, j) = 0;
			}
			else
				edge.at<uchar>(i, j) = 255;
		}
	}

	return edge;
}
Mat robinsonCompass(Mat s, int thr)
{
	Mat pad, edge;
	s.copyTo(edge);
	copyMakeBorder(s, pad, 1, 1, 1, 1, BORDER_REPLICATE);
	int k[8], max;

	for (int i = 0; i < s.rows; i++)
	{
		for (int j = 0; j < s.cols; j++)
		{

			k[0] = -pad.at<uchar>(i, j) + pad.at<uchar>(i, j + 2) - 2 * pad.at<uchar>(i + 1, j) \
				+ 2 * pad.at<uchar>(i + 1, j + 2) - pad.at<uchar>(i + 2, j) + pad.at<uchar>(i + 2, j + 2);
			k[1] = pad.at<uchar>(i, j + 1) + 2 * pad.at<uchar>(i, j + 2) - pad.at<uchar>(i + 1, j) \
				+ pad.at<uchar>(i + 1, j + 2) - 2 * pad.at<uchar>(i + 2, j) - pad.at<uchar>(i + 2, j + 1);
			k[2] = pad.at<uchar>(i, j) + 2 * pad.at<uchar>(i, j + 1) + pad.at<uchar>(i, j + 2) \
				- pad.at<uchar>(i + 2, j) - 2 * pad.at<uchar>(i + 2, j + 1) - pad.at<uchar>(i + 2, j + 2);
			k[3] = 2 * pad.at<uchar>(i, j) + pad.at<uchar>(i, j + 1) + pad.at<uchar>(i + 1, j) \
				- pad.at<uchar>(i + 1, j + 2) - pad.at<uchar>(i + 2, j + 1) - 2 * pad.at<uchar>(i + 2, j + 2);
			k[4] = pad.at<uchar>(i, j) - pad.at<uchar>(i, j + 2) + 2 * pad.at<uchar>(i + 1, j) \
				- 2 * pad.at<uchar>(i + 1, j + 2) + pad.at<uchar>(i + 2, j) - pad.at<uchar>(i + 2, j + 2);
			k[5] = -pad.at<uchar>(i, j + 1) - 2 * pad.at<uchar>(i, j + 2) + pad.at<uchar>(i + 1, j) \
				- pad.at<uchar>(i + 1, j + 2) + 2 * pad.at<uchar>(i + 2, j) + pad.at<uchar>(i + 2, j + 1);
			k[6] = -pad.at<uchar>(i, j) - 2 * pad.at<uchar>(i, j + 1) - pad.at<uchar>(i, j + 2) \
				+ pad.at<uchar>(i + 2, j) + 2 * pad.at<uchar>(i + 2, j + 1) + pad.at<uchar>(i + 2, j + 2);
			k[7] = -2 * pad.at<uchar>(i, j) - pad.at<uchar>(i, j + 1) - pad.at<uchar>(i + 1, j) \
				+ pad.at<uchar>(i + 1, j + 2) + pad.at<uchar>(i + 2, j + 1) + 2 * pad.at<uchar>(i + 2, j + 2);

			max = k[0];
			for (int r = 0; r < 8; r++)
			{
				if (k[r] > max)
				{
					max = k[r];
				}
			}

			if (max > thr)
			{
				edge.at<uchar>(i, j) = 0;
			}
			else
				edge.at<uchar>(i, j) = 255;
		}
	}

	return edge;
}
Mat babu(Mat s, int thr)
{
	Mat pad, edge;
	s.copyTo(edge);
	copyMakeBorder(s, pad, 2, 2, 2, 2, BORDER_REPLICATE);
	int k[6], max;

	for (int i = 0; i < s.rows; i++)
	{
		for (int j = 0; j < s.cols; j++)
		{

			k[0] = 100 * pad.at<uchar>(i, j) + 100 * pad.at<uchar>(i, j + 1) + 100 * pad.at<uchar>(i, j + 2) + 100 * pad.at<uchar>(i, j + 3) + 100 * pad.at<uchar>(i, j + 4) \
				+ 100 * pad.at<uchar>(i + 1, j) + 100 * pad.at<uchar>(i + 1, j + 1) + 100 * pad.at<uchar>(i + 1, j + 2) + 100 * pad.at<uchar>(i + 1, j + 3) + 100 * pad.at<uchar>(i + 1, j + 4)\
				+ 0 * pad.at<uchar>(i + 2, j) + 0 * pad.at<uchar>(i + 2, j + 1) + 0 * pad.at<uchar>(i + 2, j + 2) + 0 * pad.at<uchar>(i + 2, j + 3) + 0 * pad.at<uchar>(i + 2, j + 4)\
				- 100 * pad.at<uchar>(i + 3, j) - 100 * pad.at<uchar>(i + 3, j + 1) - 100 * pad.at<uchar>(i + 3, j + 2) - 100 * pad.at<uchar>(i + 3, j + 3) - 100 * pad.at<uchar>(i + 3, j + 4)\
				- 100 * pad.at<uchar>(i + 4, j) - 100 * pad.at<uchar>(i + 4, j + 1) - 100 * pad.at<uchar>(i + 4, j + 2) - 100 * pad.at<uchar>(i + 4, j + 3) - 100 * pad.at<uchar>(i + 4, j + 4);
			
			k[1] = 100 * pad.at<uchar>(i, j) + 100 * pad.at<uchar>(i, j + 1) + 100 * pad.at<uchar>(i, j + 2) + 100 * pad.at<uchar>(i, j + 3) + 100 * pad.at<uchar>(i, j + 4) \
				+ 100 * pad.at<uchar>(i + 1, j) + 100 * pad.at<uchar>(i + 1, j + 1) + 100 * pad.at<uchar>(i + 1, j + 2) + 78 * pad.at<uchar>(i + 1, j + 3) - 32 * pad.at<uchar>(i + 1, j + 4)\
				+ 100 * pad.at<uchar>(i + 2, j) + 92 * pad.at<uchar>(i + 2, j + 1) + 0 * pad.at<uchar>(i + 2, j + 2) - 92 * pad.at<uchar>(i + 2, j + 3) - 100 * pad.at<uchar>(i + 2, j + 4)\
				+ 32 * pad.at<uchar>(i + 3, j) - 78 * pad.at<uchar>(i + 3, j + 1) - 100 * pad.at<uchar>(i + 3, j + 2) - 100 * pad.at<uchar>(i + 3, j + 3) - 100 * pad.at<uchar>(i + 3, j + 4)\
				- 100 * pad.at<uchar>(i + 4, j) - 100 * pad.at<uchar>(i + 4, j + 1) - 100 * pad.at<uchar>(i + 4, j + 2) - 100 * pad.at<uchar>(i + 4, j + 3) - 100 * pad.at<uchar>(i + 4, j + 4);
			
			k[2] = 100 * pad.at<uchar>(i, j) + 100 * pad.at<uchar>(i, j + 1) + 100 * pad.at<uchar>(i, j + 2) + 32 * pad.at<uchar>(i, j + 3) - 100 * pad.at<uchar>(i, j + 4) \
				+ 100 * pad.at<uchar>(i + 1, j) + 100 * pad.at<uchar>(i + 1, j + 1) + 92 * pad.at<uchar>(i + 1, j + 2) - 78 * pad.at<uchar>(i + 1, j + 3) - 100 * pad.at<uchar>(i + 1, j + 4)\
				+ 100 * pad.at<uchar>(i + 2, j) + 100 * pad.at<uchar>(i + 2, j + 1) + 0 * pad.at<uchar>(i + 2, j + 2) - 100 * pad.at<uchar>(i + 2, j + 3) - 100 * pad.at<uchar>(i + 2, j + 4)\
				+ 100 * pad.at<uchar>(i + 3, j) + 78 * pad.at<uchar>(i + 3, j + 1) - 92 * pad.at<uchar>(i + 3, j + 2) - 100 * pad.at<uchar>(i + 3, j + 3) - 100 * pad.at<uchar>(i + 3, j + 4)\
				+ 100 * pad.at<uchar>(i + 4, j) - 32 * pad.at<uchar>(i + 4, j + 1) - 100 * pad.at<uchar>(i + 4, j + 2) - 100 * pad.at<uchar>(i + 4, j + 3) - 100 * pad.at<uchar>(i + 4, j + 4);
			
			k[3] = -100 * pad.at<uchar>(i, j) - 100 * pad.at<uchar>(i, j + 1) + 0 * pad.at<uchar>(i, j + 2) + 100 * pad.at<uchar>(i, j + 3) + 100 * pad.at<uchar>(i, j + 4) \
				- 100 * pad.at<uchar>(i + 1, j) - 100 * pad.at<uchar>(i + 1, j + 1) + 0 * pad.at<uchar>(i + 1, j + 2) + 100 * pad.at<uchar>(i + 1, j + 3) + 100 * pad.at<uchar>(i + 1, j + 4)\
				- 100 * pad.at<uchar>(i + 2, j) - 100 * pad.at<uchar>(i + 2, j + 1) + 0 * pad.at<uchar>(i + 2, j + 2) + 100 * pad.at<uchar>(i + 2, j + 3) + 100 * pad.at<uchar>(i + 2, j + 4)\
				- 100 * pad.at<uchar>(i + 3, j) - 100 * pad.at<uchar>(i + 3, j + 1) - 0 * pad.at<uchar>(i + 3, j + 2) + 100 * pad.at<uchar>(i + 3, j + 3) + 100 * pad.at<uchar>(i + 3, j + 4)\
				- 100 * pad.at<uchar>(i + 4, j) - 100 * pad.at<uchar>(i + 4, j + 1) - 0 * pad.at<uchar>(i + 4, j + 2) + 100 * pad.at<uchar>(i + 4, j + 3) + 100 * pad.at<uchar>(i + 4, j + 4);
			
			k[4] = -100 * pad.at<uchar>(i, j) + 32 * pad.at<uchar>(i, j + 1) + 100 * pad.at<uchar>(i, j + 2) + 100 * pad.at<uchar>(i, j + 3) + 100 * pad.at<uchar>(i, j + 4) \
				- 100 * pad.at<uchar>(i + 1, j) - 78 * pad.at<uchar>(i + 1, j + 1) + 92 * pad.at<uchar>(i + 1, j + 2) + 100 * pad.at<uchar>(i + 1, j + 3) + 100 * pad.at<uchar>(i + 1, j + 4)\
				- 100 * pad.at<uchar>(i + 2, j) - 100 * pad.at<uchar>(i + 2, j + 1) + 0 * pad.at<uchar>(i + 2, j + 2) + 100 * pad.at<uchar>(i + 2, j + 3) + 100 * pad.at<uchar>(i + 2, j + 4)\
				- 100 * pad.at<uchar>(i + 3, j) - 100 * pad.at<uchar>(i + 3, j + 1) - 92 * pad.at<uchar>(i + 3, j + 2) + 78 * pad.at<uchar>(i + 3, j + 3) + 100 * pad.at<uchar>(i + 3, j + 4)\
				- 100 * pad.at<uchar>(i + 4, j) - 100 * pad.at<uchar>(i + 4, j + 1) - 100 * pad.at<uchar>(i + 4, j + 2) - 32 * pad.at<uchar>(i + 4, j + 3) + 100 * pad.at<uchar>(i + 4, j + 4);

			k[5] = 100 * pad.at<uchar>(i, j) + 100 * pad.at<uchar>(i, j + 1) + 100 * pad.at<uchar>(i, j + 2) + 100 * pad.at<uchar>(i, j + 3) + 100 * pad.at<uchar>(i, j + 4) \
				- 32 * pad.at<uchar>(i + 1, j) + 78 * pad.at<uchar>(i + 1, j + 1) + 100 * pad.at<uchar>(i + 1, j + 2) + 100 * pad.at<uchar>(i + 1, j + 3) + 100 * pad.at<uchar>(i + 1, j + 4)\
				- 100 * pad.at<uchar>(i + 2, j) - 92 * pad.at<uchar>(i + 2, j + 1) + 0 * pad.at<uchar>(i + 2, j + 2) + 92 * pad.at<uchar>(i + 2, j + 3) + 100 * pad.at<uchar>(i + 2, j + 4)\
				- 100 * pad.at<uchar>(i + 3, j) - 100 * pad.at<uchar>(i + 3, j + 1) - 100 * pad.at<uchar>(i + 3, j + 2) - 78 * pad.at<uchar>(i + 3, j + 3) + 32 * pad.at<uchar>(i + 3, j + 4)\
				- 100 * pad.at<uchar>(i + 4, j) - 100 * pad.at<uchar>(i + 4, j + 1) - 100 * pad.at<uchar>(i + 4, j + 2) - 100 * pad.at<uchar>(i + 4, j + 3) - 100 * pad.at<uchar>(i + 4, j + 4);
			

			max = k[0];
			for (int r = 0; r < 6; r++)
			{
				if (k[r] > max)
				{
					max = k[r];
				}
			}

			if (max > thr)
			{
				edge.at<uchar>(i, j) = 0;
			}
			else
				edge.at<uchar>(i, j) = 255;
		}
	}

	return edge;
}
Mat sobel(Mat s, int thr)
{
	Mat pad, edge;
	s.copyTo(edge);
	copyMakeBorder(s, pad, 1, 1, 1, 1, BORDER_REPLICATE);
	int r1, r2;
	for (int i = 0; i < s.rows; i++)
	{
		for (int j = 0; j < s.cols; j++)
		{
			r1 = pad.at<uchar>(i + 1, j - 1) + 2 * pad.at<uchar>(i + 1, j) + pad.at<uchar>(i + 1, j + 1) - pad.at<uchar>(i - 1, j - 1) - 2 * pad.at<uchar>(i - 1, j) - pad.at<uchar>(i - 1, j + 1);
			r2 = pad.at<uchar>(i - 1, j + 1) + 2 * pad.at<uchar>(i, j + 1) + pad.at<uchar>(i + 1, j + 1) - pad.at<uchar>(i - 1, j - 1) - 2 * pad.at<uchar>(i, j - 1) - pad.at<uchar>(i + 1, j - 1);
			if (sqrt(r1 * r1 + r2 * r2) > thr)
			{
				edge.at<uchar>(i, j) = 0;
			}
			else
				edge.at<uchar>(i, j) = 255;
		}
	}

	return edge;
}
Mat freiandchen(Mat s, int thr)
{
	Mat pad, edge;
	s.copyTo(edge);
	copyMakeBorder(s, pad, 1, 1, 1, 1, BORDER_REPLICATE);
	double r1, r2;
	double two = sqrt(2);
	for (int i = 0; i < s.rows; i++)
	{
		for (int j = 0; j < s.cols; j++)
		{
			r1 = pad.at<uchar>(i + 1, j - 1) + two * pad.at<uchar>(i + 1, j) + pad.at<uchar>(i + 1, j + 1) - pad.at<uchar>(i - 1, j - 1) - two * pad.at<uchar>(i - 1, j) - pad.at<uchar>(i - 1, j + 1);
			r2 = pad.at<uchar>(i - 1, j + 1) + two * pad.at<uchar>(i, j + 1) + pad.at<uchar>(i + 1, j + 1) - pad.at<uchar>(i - 1, j - 1) - two * pad.at<uchar>(i, j - 1) - pad.at<uchar>(i + 1, j - 1);
			if (sqrt(r1 * r1 + r2 * r2) > thr)
			{
				edge.at<uchar>(i, j) = 0;
			}
			else
				edge.at<uchar>(i, j) = 255;
		}
	}

	return edge;
}
int main()
{
	// read image 
	Mat s = imread("lena.bmp", CV_8UC1);
	Mat rob,pre,sob,fc,kirsch,robin,bab;
	
	rob = robert(s, 30);
	imshow("robert", rob);
	imwrite("robert.jpg", rob);

	pre = prewitt(s, 24);
	imshow("prewitt", pre);
	imwrite("prewitt.jpg", pre);

	sob = sobel(s, 38);
	imshow("sobel", sob);
	imwrite("sobel.jpg", sob);

	fc = freiandchen(s, 30);
	imshow("freiandchen", fc);
	imwrite("freiandchen.jpg", fc);

	kirsch = kirschCompass(s, 135);
	imshow("kirsch", kirsch);
	imwrite("kirsch.jpg", kirsch);

	robin = robinsonCompass(s, 43);
	imshow("robin", robin);
	imwrite("robin.jpg", robin);

	bab= babu(s, 12500);
	imshow("bab", bab);
	imwrite("bab.jpg", bab);
	
	waitKey(0);
	return 0;
}
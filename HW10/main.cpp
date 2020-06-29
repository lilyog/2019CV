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

Mat lap1(Mat s, int thr)
{
	Mat pad, edge,la;
	s.copyTo(edge);
	copyMakeBorder(s, pad, 1, 1, 1, 1, BORDER_REPLICATE);
	int pix;
	s.copyTo(la);
	for (int i = 0; i < s.rows; i++)
	{
		for (int j = 0; j < s.cols; j++)
		{
			pix = pad.at<uchar>(i, j + 1) + pad.at<uchar>(i + 1, j) - 4 * pad.at<uchar>(i + 1, j + 1) + pad.at<uchar>(i + 1, j + 2) + pad.at<uchar>(i + 2, j + 1);
			
			if (pix >= thr)
			{
				la.at<uchar>(i, j) = 3;
			}
			else if (pix <= -thr)
			{
				la.at<uchar>(i, j) = 2;
			}
			else
				la.at<uchar>(i, j) = 1;
		}
	}
	copyMakeBorder(la, la, 1, 1, 1, 1, BORDER_REPLICATE);
	
	for (int i = 0; i < s.rows; i++)
	{
		for (int j = 0; j < s.cols; j++)
		{
			if (la.at<uchar>(i + 1, j + 1) == 3)
			{
				if (la.at<uchar>(i, j) == 2 || la.at<uchar>(i, j + 1) == 2 || la.at<uchar>(i, j + 2) == 2 || la.at<uchar>(i + 1, j) == 2 || la.at<uchar>(i + 1, j + 2) == 2\
					|| la.at<uchar>(i + 2, j) == 2 || la.at<uchar>(i + 2, j + 1) == 2 || la.at<uchar>(i + 2, j + 2) == 2)
				{
					edge.at<uchar>(i, j) = 0;
				}
				else
					edge.at<uchar>(i, j) = 255;
			}
			else
				edge.at<uchar>(i, j) = 255;
		}
	}
	
	return edge;
}
Mat lap2(Mat s, int thr)
{
	Mat pad, edge, la;
	s.copyTo(edge);
	copyMakeBorder(s, pad, 1, 1, 1, 1, BORDER_REPLICATE);
	float pix;
	s.copyTo(la);
	for (int i = 0; i < s.rows; i++)
	{
		for (int j = 0; j < s.cols; j++)
		{
			pix = pad.at<uchar>(i, j) + pad.at<uchar>(i, j + 1) + pad.at<uchar>(i, j + 2)\
				+ pad.at<uchar>(i + 1, j) - 8 * pad.at<uchar>(i + 1, j + 1) + pad.at<uchar>(i + 1, j + 2)\
				+ pad.at<uchar>(i + 2, j) + pad.at<uchar>(i + 2, j + 1) + pad.at<uchar>(i + 2, j + 2);
			pix /= 3;
			if (pix >= thr)
			{
				la.at<uchar>(i, j) = 3;
			}
			else if (pix <= -thr)
			{
				la.at<uchar>(i, j) = 2;
			}
			else
				la.at<uchar>(i, j) = 1;
		}
	}
	copyMakeBorder(la, la, 1, 1, 1, 1, BORDER_REPLICATE);

	for (int i = 0; i < s.rows; i++)
	{
		for (int j = 0; j < s.cols; j++)
		{
			if (la.at<uchar>(i + 1, j + 1) == 3)
			{
				if (la.at<uchar>(i, j) == 2 || la.at<uchar>(i, j + 1) == 2 || la.at<uchar>(i, j + 2) == 2 || la.at<uchar>(i + 1, j) == 2 || la.at<uchar>(i + 1, j + 2) == 2\
					|| la.at<uchar>(i + 2, j) == 2 || la.at<uchar>(i + 2, j + 1) == 2 || la.at<uchar>(i + 2, j + 2) == 2)
				{
					edge.at<uchar>(i, j) = 0;
				}
				else
					edge.at<uchar>(i, j) = 255;
			}
			else
				edge.at<uchar>(i, j) = 255;
		}
	}

	return edge;
}
Mat minlap(Mat s, int thr)
{
	Mat pad, edge, la;
	s.copyTo(edge);
	copyMakeBorder(s, pad, 1, 1, 1, 1, BORDER_REPLICATE);
	float pix;
	s.copyTo(la);
	for (int i = 0; i < s.rows; i++)
	{
		for (int j = 0; j < s.cols; j++)
		{
			pix = 2 * pad.at<uchar>(i, j) - pad.at<uchar>(i, j + 1) + 2 * pad.at<uchar>(i, j + 2)\
				- pad.at<uchar>(i + 1, j) - 4 * pad.at<uchar>(i + 1, j + 1) - pad.at<uchar>(i + 1, j + 2)\
				+ 2 * pad.at<uchar>(i + 2, j) - pad.at<uchar>(i + 2, j + 1) + 2 * pad.at<uchar>(i + 2, j + 2);
			pix /= 3;
			if (pix >= thr)
			{
				la.at<uchar>(i, j) = 3;
			}
			else if (pix <= -thr)
			{
				la.at<uchar>(i, j) = 2;
			}
			else
				la.at<uchar>(i, j) = 1;
		}
	}
	copyMakeBorder(la, la, 1, 1, 1, 1, BORDER_REPLICATE);

	for (int i = 0; i < s.rows; i++)
	{
		for (int j = 0; j < s.cols; j++)
		{
			if (la.at<uchar>(i + 1, j + 1) == 3)
			{
				if (la.at<uchar>(i, j) == 2 || la.at<uchar>(i, j + 1) == 2 || la.at<uchar>(i, j + 2) == 2 || la.at<uchar>(i + 1, j) == 2 || la.at<uchar>(i + 1, j + 2) == 2\
					|| la.at<uchar>(i + 2, j) == 2 || la.at<uchar>(i + 2, j + 1) == 2 || la.at<uchar>(i + 2, j + 2) == 2)
				{
					edge.at<uchar>(i, j) = 0;
				}
				else
					edge.at<uchar>(i, j) = 255;
			}
			else
				edge.at<uchar>(i, j) = 255;
		}
	}

	return edge;
}
Mat lapofgau(Mat s, int thr)
{
	Mat pad, edge, la;
	s.copyTo(edge);
	copyMakeBorder(s, pad, 5, 5, 5, 5, BORDER_REPLICATE);
	int pix,b;
	s.copyTo(la);
	
	for (int i = 0; i < s.rows; i++)
	{
		for (int j = 0; j < s.cols; j++)
		{
			pix = -pad.at<uchar>(i, j + 3) - pad.at<uchar>(i, j + 4) - 2 * pad.at<uchar>(i, j + 5) - pad.at<uchar>(i, j + 6) - pad.at<uchar>(i, j + 7)\
				- 2 * pad.at<uchar>(i + 1, j + 2) - 4 * pad.at<uchar>(i + 1, j + 3) - 8 * pad.at<uchar>(i + 1, j + 4) - 9 * pad.at<uchar>(i + 1, j + 5) - 8 * pad.at<uchar>(i + 1, j + 6) - 4 * pad.at<uchar>(i + 1, j + 7) - 2 * pad.at<uchar>(i + 1, j + 8)\
				- 2 * pad.at<uchar>(i + 2, j + 1) - 7 * pad.at<uchar>(i + 2, j + 2) - 15 * pad.at<uchar>(i + 2, j + 3) - 22 * pad.at<uchar>(i + 2, j + 4) - 23 * pad.at<uchar>(i + 2, j + 5) - 22 * pad.at<uchar>(i + 2, j + 6) - 15 * pad.at<uchar>(i + 2, j + 7) - 7 * pad.at<uchar>(i + 2, j + 8) - 2 * pad.at<uchar>(i + 2, j + 9)\
				- 1 * pad.at<uchar>(i + 3, j) - 4 * pad.at<uchar>(i + 3, j + 1) - 15 * pad.at<uchar>(i + 3, j + 2) - 24 * pad.at<uchar>(i + 3, j + 3) - 14 * pad.at<uchar>(i + 3, j + 4) - 1 * pad.at<uchar>(i + 3, j + 5) - 14 * pad.at<uchar>(i + 3, j + 6) - 24 * pad.at<uchar>(i + 3, j + 7) - 15 * pad.at<uchar>(i + 3, j + 8) - 4 * pad.at<uchar>(i + 3, j + 9) - 1 * pad.at<uchar>(i + 3, j + 10)\
				- 1 * pad.at<uchar>(i + 4, j) - 8 * pad.at<uchar>(i + 4, j + 1) - 22 * pad.at<uchar>(i + 4, j + 2) - 14 * pad.at<uchar>(i + 4, j + 3) + 52 * pad.at<uchar>(i + 4, j + 4) + 103 * pad.at<uchar>(i + 4, j + 5) + 52 * pad.at<uchar>(i + 4, j + 6) - 14 * pad.at<uchar>(i + 4, j + 7) - 22 * pad.at<uchar>(i + 4, j + 8) - 8 * pad.at<uchar>(i + 4, j + 9) - 1 * pad.at<uchar>(i + 4, j + 10)\
				- 2 * pad.at<uchar>(i + 5, j) - 9 * pad.at<uchar>(i + 5, j + 1) - 23 * pad.at<uchar>(i + 5, j + 2) - 1 * pad.at<uchar>(i + 5, j + 3) + 103 * pad.at<uchar>(i + 5, j + 4) + 178 * pad.at<uchar>(i + 5, j + 5) + 103 * pad.at<uchar>(i + 5, j + 6) - 1 * pad.at<uchar>(i + 5, j + 7) - 23 * pad.at<uchar>(i + 5, j + 8) - 9 * pad.at<uchar>(i + 5, j + 9) - 2 * pad.at<uchar>(i + 5, j + 10)\
				- 1 * pad.at<uchar>(i + 6, j) - 8 * pad.at<uchar>(i + 6, j + 1) - 22 * pad.at<uchar>(i + 6, j + 2) - 14 * pad.at<uchar>(i + 6, j + 3) + 52 * pad.at<uchar>(i + 6, j + 4) + 103 * pad.at<uchar>(i + 6, j + 5) + 52 * pad.at<uchar>(i + 6, j + 6) - 14 * pad.at<uchar>(i + 6, j + 7) - 22 * pad.at<uchar>(i + 6, j + 8) - 8 * pad.at<uchar>(i + 6, j + 9) - 1 * pad.at<uchar>(i + 6, j + 10)\
				- 1 * pad.at<uchar>(i + 7, j) - 4 * pad.at<uchar>(i + 7, j + 1) - 15 * pad.at<uchar>(i + 7, j + 2) - 24 * pad.at<uchar>(i + 7, j + 3) - 14 * pad.at<uchar>(i + 7, j + 4) - 1 * pad.at<uchar>(i + 7, j + 5) - 14 * pad.at<uchar>(i + 7, j + 6) - 24 * pad.at<uchar>(i + 7, j + 7) - 15 * pad.at<uchar>(i + 7, j + 8) - 4 * pad.at<uchar>(i + 7, j + 9) - 1 * pad.at<uchar>(i + 7, j + 10)\
				- 2 * pad.at<uchar>(i + 8, j + 1) - 7 * pad.at<uchar>(i + 8, j + 2) - 15 * pad.at<uchar>(i + 8, j + 3) - 22 * pad.at<uchar>(i + 8, j + 4) - 23 * pad.at<uchar>(i + 8, j + 5) - 22 * pad.at<uchar>(i + 8, j + 6) - 15 * pad.at<uchar>(i + 8, j + 7) - 7 * pad.at<uchar>(i + 8, j + 8) - 2 * pad.at<uchar>(i + 8, j + 9)\
				- 2 * pad.at<uchar>(i + 9, j + 2) - 4 * pad.at<uchar>(i + 1, j + 3) - 8 * pad.at<uchar>(i + 9, j + 4) - 9 * pad.at<uchar>(i + 9, j + 5) - 8 * pad.at<uchar>(i + 9, j + 6) - 4 * pad.at<uchar>(i + 9, j + 7) - 2 * pad.at<uchar>(i + 9, j + 8)\
				- pad.at<uchar>(i + 10, j + 3) - pad.at<uchar>(i + 10, j + 4) - 2 * pad.at<uchar>(i + 10, j + 5) - pad.at<uchar>(i + 10, j + 6) - pad.at<uchar>(i + 10, j + 7);
			
			if (pix >= thr)
			{
				la.at<uchar>(i, j) = 3;
			}
			else if (pix <= -thr)
			{
				la.at<uchar>(i, j) = 2;
			}
			else
				la.at<uchar>(i, j) = 1;
		}
	}
	copyMakeBorder(la, la, 5, 5, 5, 5, BORDER_REPLICATE);
	
	for (int i = 0; i < s.rows; i++)
	{
		for (int j = 0; j < s.cols; j++)
		{
			edge.at<uchar>(i, j) = 255;
			if (la.at<uchar>(i + 5, j + 5) == 3)
			{
				for (int k = 0; k < 11; k++)
				{
					for (int l = 0; l < 11; l++)
					{
						if (la.at<uchar>(i + k, j + l) == 2)
							edge.at<uchar>(i, j) = 0;
					}
				}
			}
		}
	}
	return edge;
}
Mat diffofgau(Mat s, int thr)
{
	Mat pad, edge, la;
	s.copyTo(edge);
	copyMakeBorder(s, pad, 5, 5, 5, 5, BORDER_REPLICATE);
	int pix=0,b;
	s.copyTo(la);
	for (int i = 0; i < s.rows; i++)
	{
		for (int j = 0; j < s.cols; j++)
		{
			pix = -1 * pad.at<uchar>(i, j) - 3 * pad.at<uchar>(i, j + 1) - 4 * pad.at<uchar>(i, j + 2) - 6 * pad.at<uchar>(i, j + 3) - 7 * pad.at<uchar>(i, j + 4) - 8 * pad.at<uchar>(i, j + 5) - 7 * pad.at<uchar>(i, j + 6) - 6 * pad.at<uchar>(i, j + 7) - 4 * pad.at<uchar>(i, j + 8) - 3 * pad.at<uchar>(i, j + 9) - 1 * pad.at<uchar>(i, j + 10)\
				- 3 * pad.at<uchar>(i + 1, j) - 5 * pad.at<uchar>(i + 1, j + 1) - 8 * pad.at<uchar>(i + 1, j + 2) - 11 * pad.at<uchar>(i + 1, j + 3) - 13 * pad.at<uchar>(i + 1, j + 4) - 13 * pad.at<uchar>(i + 1, j + 5) - 13 * pad.at<uchar>(i + 1, j + 6) - 11 * pad.at<uchar>(i + 1, j + 7) - 8 * pad.at<uchar>(i + 1, j + 8) - 5 * pad.at<uchar>(i + 1, j + 9) - 3 * pad.at<uchar>(i + 1, j + 10)\
				- 4 * pad.at<uchar>(i + 2, j) - 8 * pad.at<uchar>(i + 2, j + 1) - 12 * pad.at<uchar>(i + 2, j + 2) - 16 * pad.at<uchar>(i + 2, j + 3) - 17 * pad.at<uchar>(i + 2, j + 4) - 17 * pad.at<uchar>(i + 2, j + 5) - 17 * pad.at<uchar>(i + 2, j + 6) - 16 * pad.at<uchar>(i + 2, j + 7) - 12 * pad.at<uchar>(i + 2, j + 8) - 8 * pad.at<uchar>(i + 2, j + 9) - 4 * pad.at<uchar>(i + 2, j + 10)\
				- 6 * pad.at<uchar>(i + 3, j) - 11 * pad.at<uchar>(i + 3, j + 1) - 16 * pad.at<uchar>(i + 3, j + 2) - 16 * pad.at<uchar>(i + 3, j + 3) - 0 * pad.at<uchar>(i + 3, j + 4) + 15 * pad.at<uchar>(i + 3, j + 5) - 0 * pad.at<uchar>(i + 3, j + 6) - 16 * pad.at<uchar>(i + 3, j + 7) - 16 * pad.at<uchar>(i + 3, j + 8) - 11 * pad.at<uchar>(i + 3, j + 9) - 6 * pad.at<uchar>(i + 3, j + 10)\
				- 7 * pad.at<uchar>(i + 4, j) - 13 * pad.at<uchar>(i + 4, j + 1) - 17 * pad.at<uchar>(i + 4, j + 2) - 0 * pad.at<uchar>(i + 4, j + 3) + 85 * pad.at<uchar>(i + 4, j + 4) + 160 * pad.at<uchar>(i + 4, j + 5) + 85 * pad.at<uchar>(i + 4, j + 6) - 0 * pad.at<uchar>(i + 4, j + 7) - 17 * pad.at<uchar>(i + 4, j + 8) - 13 * pad.at<uchar>(i + 4, j + 9) - 7 * pad.at<uchar>(i + 4, j + 10)\
				- 8 * pad.at<uchar>(i + 5, j) - 13 * pad.at<uchar>(i + 5, j + 1) - 17 * pad.at<uchar>(i + 5, j + 2) + 15 * pad.at<uchar>(i + 5, j + 3) + 160 * pad.at<uchar>(i + 5, j + 4) + 283 * pad.at<uchar>(i + 5, j + 5) + 160 * pad.at<uchar>(i + 5, j + 6) + 15 * pad.at<uchar>(i + 5, j + 7) - 17 * pad.at<uchar>(i + 5, j + 8) - 13 * pad.at<uchar>(i + 5, j + 9) - 8 * pad.at<uchar>(i + 5, j + 10)\
				- 7 * pad.at<uchar>(i + 6, j) - 13 * pad.at<uchar>(i + 6, j + 1) - 17 * pad.at<uchar>(i + 6, j + 2) - 0 * pad.at<uchar>(i + 6, j + 3) + 85 * pad.at<uchar>(i + 6, j + 4) + 160 * pad.at<uchar>(i + 6, j + 5) + 85 * pad.at<uchar>(i + 6, j + 6) - 0 * pad.at<uchar>(i + 6, j + 7) - 17 * pad.at<uchar>(i + 6, j + 8) - 13 * pad.at<uchar>(i + 6, j + 9) - 7 * pad.at<uchar>(i + 6, j + 10)\
				- 6 * pad.at<uchar>(i + 7, j) - 11 * pad.at<uchar>(i + 7, j + 1) - 16 * pad.at<uchar>(i + 7, j + 2) - 16 * pad.at<uchar>(i + 7, j + 3) - 0 * pad.at<uchar>(i + 7, j + 4) + 15 * pad.at<uchar>(i + 7, j + 5) - 0 * pad.at<uchar>(i + 7, j + 6) - 16 * pad.at<uchar>(i + 7, j + 7) - 16 * pad.at<uchar>(i + 7, j + 8) - 11 * pad.at<uchar>(i + 7, j + 9) - 6 * pad.at<uchar>(i + 7, j + 10)\
				- 4 * pad.at<uchar>(i + 8, j) - 8 * pad.at<uchar>(i + 8, j + 1) - 12 * pad.at<uchar>(i + 8, j + 2) - 16 * pad.at<uchar>(i + 8, j + 3) - 17 * pad.at<uchar>(i + 8, j + 4) - 17 * pad.at<uchar>(i + 8, j + 5) - 17 * pad.at<uchar>(i + 8, j + 6) - 16 * pad.at<uchar>(i + 8, j + 7) - 12 * pad.at<uchar>(i + 8, j + 8) - 8 * pad.at<uchar>(i + 8, j + 9) - 4 * pad.at<uchar>(i + 8, j + 10)\
				- 3 * pad.at<uchar>(i + 9, j) - 5 * pad.at<uchar>(i + 9, j + 1) - 8 * pad.at<uchar>(i + 9, j + 2) - 11 * pad.at<uchar>(i + 9, j + 3) - 13 * pad.at<uchar>(i + 9, j + 4) - 13 * pad.at<uchar>(i + 9, j + 5) - 13 * pad.at<uchar>(i + 9, j + 6) - 11 * pad.at<uchar>(i + 9, j + 7) - 8 * pad.at<uchar>(i + 9, j + 8) - 5 * pad.at<uchar>(i + 9, j + 9) - 3 * pad.at<uchar>(i + 9, j + 10)\
				- 1 * pad.at<uchar>(i + 10, j) - 3 * pad.at<uchar>(i + 10, j + 1) - 4 * pad.at<uchar>(i + 10, j + 2) - 6 * pad.at<uchar>(i + 10, j + 3) - 7 * pad.at<uchar>(i + 10, j + 4) - 8 * pad.at<uchar>(i + 10, j + 5) - 7 * pad.at<uchar>(i + 10, j + 6) - 6 * pad.at<uchar>(i + 10, j + 7) - 4 * pad.at<uchar>(i + 10, j + 8) - 3 * pad.at<uchar>(i + 10, j + 9) - 1 * pad.at<uchar>(i + 10, j + 10);

			if (pix >= thr)
			{
				la.at<uchar>(i, j) = 3;
			}
			else if (pix <= -thr)
			{
				la.at<uchar>(i, j) = 2;
			}
			else
				la.at<uchar>(i, j) = 1;
			b = la.at<uchar>(i, j);
		//	cout << b << endl;
		}
	}

	copyMakeBorder(la, la, 5, 5, 5, 5, BORDER_REPLICATE);
	for (int i = 0; i < s.rows; i++)
	{
		for (int j = 0; j < s.cols; j++)
		{
			edge.at<uchar>(i, j) = 255;
			if (la.at<uchar>(i + 5, j + 5) == 3)
			{
				for (int k = 0; k < 11; k++)
				{
					for (int l = 0; l < 11; l++)
					{
						if (la.at<uchar>(i + k, j + l) == 2)
							edge.at<uchar>(i, j) = 0;
					}
				}
			}
		}
	}
	return edge;
}
int main()
{
	// read image 
	Mat s = imread("lena.bmp", CV_8UC1);
	Mat la1,la2,mla,log,dog;
	
	la1 = lap1(s, 15);
	imshow("laplace1", la1);
	imwrite("laplace1.jpg", la1);
	
	la2 = lap2(s, 15);
	imshow("laplace2", la2);
	imwrite("laplace2.jpg", la2);
	
	mla = minlap(s, 20);
	imshow("minimum-variance Laplacian", mla);
	imwrite("minimum-variance Laplacian.jpg", mla);
	
	log = lapofgau(s, 3000);
	imshow("Laplacian of Gaussian", log);
	imwrite("Laplacian of Gaussian.jpg", log);

	dog = diffofgau(s, 1);
	imshow("Difference of Gaussian", dog);
	imwrite("Difference of Gaussian.jpg", dog);
	
	waitKey(0);
	return 0;
}
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
	Mat dil = img.clone();
	int max;

	for (int i = 0; i < img.rows; i++)          //use octagon kernel to dilate
	{
		for (int j = 0; j < img.cols; j++)      //find the kernel's max gray scale and give to i,j
		{
			max = 0;
			if (i - 2 > 0 && j - 1 > 0 && i - 2 < img.rows && j - 1 < img.cols)
			{
				if (max < img.at<uchar>(i - 2, j - 1))
				{
					max = img.at<uchar>(i - 2, j - 1);
				}
			}
			if (i - 2 > 0 && j > 0 && i - 2 < img.rows && j < img.cols)
			{
				if (max < img.at<uchar>(i - 2, j))
				{
					max = img.at<uchar>(i - 2, j);
				}
			}
			if (i - 2 > 0 && j + 1 > 0 && i - 2 < img.rows && j + 1 < img.cols)
			{
				if (max < img.at<uchar>(i - 2, j + 1))
				{
					max = img.at<uchar>(i - 2, j + 1);
				}
			}
			if (i - 1 > 0 && j - 2 > 0 && i - 1 < img.rows && j - 2 < img.cols)
			{
				if (max < img.at<uchar>(i - 1, j - 2))
				{
					max = img.at<uchar>(i - 1, j - 2);
				}
			}
			if (i - 1 > 0 && j - 1 > 0 && i - 1 < img.rows && j - 1 < img.cols)
			{
				if (max < img.at<uchar>(i - 1, j - 1))
				{
					max = img.at<uchar>(i - 1, j - 1);
				}
			}
			if (i - 1 > 0 && j > 0 && i - 1 < img.rows && j < img.cols)
			{
				if (max < img.at<uchar>(i - 1, j))
				{
					max = img.at<uchar>(i - 1, j);
				}
			}
			if (i - 1 > 0 && j + 1 > 0 && i - 1 < img.rows && j + 1 < img.cols)
			{
				if (max < img.at<uchar>(i - 1, j + 1))
				{
					max = img.at<uchar>(i - 1, j + 1);
				}
			}
			if (i - 1 > 0 && j + 2 > 0 && i - 1 < img.rows && j + 2 < img.cols)
			{
				if (max < img.at<uchar>(i - 1, j + 2))
				{
					max = img.at<uchar>(i - 1, j + 2);
				}
			}
			if (i > 0 && j - 2 > 0 && i < img.rows && j - 2 < img.cols)
			{
				if (max < img.at<uchar>(i, j - 2))
				{
					max = img.at<uchar>(i, j - 2);
				}
			}
			if (i > 0 && j - 1 > 0 && i < img.rows && j - 1 < img.cols)
			{
				if (max < img.at<uchar>(i, j - 1))
				{
					max = img.at<uchar>(i, j - 1);
				}
			}
			if (i > 0 && j + 1 > 0 && i < img.rows && j + 1 < img.cols)
			{
				if (max < img.at<uchar>(i, j + 1))
				{
					max = img.at<uchar>(i, j + 1);
				}
			}
			if (i > 0 && j + 2 > 0 && i < img.rows && j + 2 < img.cols)
			{
				if (max < img.at<uchar>(i, j + 2))
				{
					max = img.at<uchar>(i, j + 2);
				}
			}
			if (i + 1 > 0 && j - 2 > 0 && i + 1 < img.rows && j - 2 < img.cols)
			{
				if (max < img.at<uchar>(i + 1, j - 2))
				{
					max = img.at<uchar>(i + 1, j - 2);
				}
			}
			if (i + 1 > 0 && j - 1 > 0 && i + 1 < img.rows && j - 1 < img.cols)
			{
				if (max < img.at<uchar>(i + 1, j - 1))
				{
					max = img.at<uchar>(i + 1, j - 1);
				}
			}
			if (i + 1 > 0 && j > 0 && i + 1 < img.rows && j < img.cols)
			{
				if (max < img.at<uchar>(i + 1, j))
				{
					max = img.at<uchar>(i + 1, j);
				}
			}
			if (i + 1 > 0 && j + 1 > 0 && i + 1 < img.rows && j + 1 < img.cols)
			{
				if (max < img.at<uchar>(i + 1, j + 1))
				{
					max = img.at<uchar>(i + 1, j + 1);
				}
			}
			if (i + 1 > 0 && j + 2 > 0 && i + 1 < img.rows && j + 2 < img.cols)
			{
				if (max < img.at<uchar>(i + 1, j + 2))
				{
					max = img.at<uchar>(i + 1, j + 2);
				}
			}
			if (i + 2 > 0 && j - 1 > 0 && i + 2 < img.rows && j - 1 < img.cols)
			{
				if (max < img.at<uchar>(i + 2, j - 1))
				{
					max = img.at<uchar>(i + 2, j - 1);
				}
			}
			if (i + 2 > 0 && j > 0 && i + 2 < img.rows && j < img.cols)
			{
				if (max < img.at<uchar>(i + 2, j))
				{
					max = img.at<uchar>(i + 2, j);
				}
			}
			if (i + 2 > 0 && j + 1 > 0 && i + 2 < img.rows && j + 1 < img.cols)
			{
				if (max < img.at<uchar>(i + 2, j + 1))
				{
					max = img.at<uchar>(i + 2, j + 1);
				}
			}

			if (max > img.at<uchar>(i, j))
			{
				dil.at<uchar>(i, j) = max;
			}

		}
	}

	Mat ero = dil.clone();
	int min;

	for (int i = 0; i < img.rows; i++)          //use octagon kernel to dilate
	{
		for (int j = 0; j < img.cols; j++)      //find the kernel's min gray scale and give to i,j
		{
			min = 255;
			if (i - 2 > 0 && j - 1 > 0 && i - 2 < img.rows && j - 1 < img.cols)
			{
				if (min > dil.at<uchar>(i - 2, j - 1))
				{
					min = dil.at<uchar>(i - 2, j - 1);
				}
			}
			if (i - 2 > 0 && j > 0 && i - 2 < img.rows && j < img.cols)
			{
				if (min > dil.at<uchar>(i - 2, j))
				{
					min = dil.at<uchar>(i - 2, j);
				}
			}
			if (i - 2 > 0 && j + 1 > 0 && i - 2 < img.rows && j + 1 < img.cols)
			{
				if (min > dil.at<uchar>(i - 2, j + 1))
				{
					min = dil.at<uchar>(i - 2, j + 1);
				}
			}
			if (i - 1 > 0 && j - 2 > 0 && i - 1 < img.rows && j - 2 < img.cols)
			{
				if (min > dil.at<uchar>(i - 1, j - 2))
				{
					min = dil.at<uchar>(i - 1, j - 2);
				}
			}
			if (i - 1 > 0 && j - 1 > 0 && i - 1 < img.rows && j - 1 < img.cols)
			{
				if (min > dil.at<uchar>(i - 1, j - 1))
				{
					min = dil.at<uchar>(i - 1, j - 1);
				}
			}
			if (i - 1 > 0 && j > 0 && i - 1 < img.rows && j < img.cols)
			{
				if (min > dil.at<uchar>(i - 1, j))
				{
					min = dil.at<uchar>(i - 1, j);
				}
			}
			if (i - 1 > 0 && j + 1 > 0 && i - 1 < img.rows && j + 1 < img.cols)
			{
				if (min > dil.at<uchar>(i - 1, j + 1))
				{
					min = dil.at<uchar>(i - 1, j + 1);
				}
			}
			if (i - 1 > 0 && j + 2 > 0 && i - 1 < img.rows && j + 2 < img.cols)
			{
				if (min > dil.at<uchar>(i - 1, j + 2))
				{
					min = dil.at<uchar>(i - 1, j + 2);
				}
			}
			if (i > 0 && j - 2 > 0 && i < img.rows && j - 2 < img.cols)
			{
				if (min > dil.at<uchar>(i, j - 2))
				{
					min = dil.at<uchar>(i, j - 2);
				}
			}
			if (i > 0 && j - 1 > 0 && i < img.rows && j - 1 < img.cols)
			{
				if (min > dil.at<uchar>(i, j - 1))
				{
					min = dil.at<uchar>(i, j - 1);
				}
			}
			if (i > 0 && j + 1 > 0 && i < img.rows && j + 1 < img.cols)
			{
				if (min > dil.at<uchar>(i, j + 1))
				{
					min = dil.at<uchar>(i, j + 1);
				}
			}
			if (i > 0 && j + 2 > 0 && i < img.rows && j + 2 < img.cols)
			{
				if (min > dil.at<uchar>(i, j + 2))
				{
					min = dil.at<uchar>(i, j + 2);
				}
			}
			if (i + 1 > 0 && j - 2 > 0 && i + 1 < img.rows && j - 2 < img.cols)
			{
				if (min > dil.at<uchar>(i + 1, j - 2))
				{
					min = dil.at<uchar>(i + 1, j - 2);
				}
			}
			if (i + 1 > 0 && j - 1 > 0 && i + 1 < img.rows && j - 1 < img.cols)
			{
				if (min > dil.at<uchar>(i + 1, j - 1))
				{
					min = dil.at<uchar>(i + 1, j - 1);
				}
			}
			if (i + 1 > 0 && j > 0 && i + 1 < img.rows && j < img.cols)
			{
				if (min > dil.at<uchar>(i + 1, j))
				{
					min = dil.at<uchar>(i + 1, j);
				}
			}
			if (i + 1 > 0 && j + 1 > 0 && i + 1 < img.rows && j + 1 < img.cols)
			{
				if (min > dil.at<uchar>(i + 1, j + 1))
				{
					min = dil.at<uchar>(i + 1, j + 1);
				}
			}
			if (i + 1 > 0 && j + 2 > 0 && i + 1 < img.rows && j + 2 < img.cols)
			{
				if (min > dil.at<uchar>(i + 1, j + 2))
				{
					min = dil.at<uchar>(i + 1, j + 2);
				}
			}
			if (i + 2 > 0 && j - 1 > 0 && i + 2 < img.rows && j - 1 < img.cols)
			{
				if (min > dil.at<uchar>(i + 2, j - 1))
				{
					min = dil.at<uchar>(i + 2, j - 1);
				}
			}
			if (i + 2 > 0 && j > 0 && i + 2 < img.rows && j < img.cols)
			{
				if (min > dil.at<uchar>(i + 2, j))
				{
					min = dil.at<uchar>(i + 2, j);
				}
			}
			if (i + 2 > 0 && j + 1 > 0 && i + 2 < img.rows && j + 1 < img.cols)
			{
				if (min > dil.at<uchar>(i + 2, j + 1))
				{
					min = dil.at<uchar>(i + 2, j + 1);
				}
			}

			if (min < dil.at<uchar>(i, j))
			{
				ero.at<uchar>(i, j) = min;
			}

		}
	}

	// show image
	imshow("closing", ero);

	// write image 
	imwrite("closing.jpg", ero);

	waitKey(0);
	return 0;
}
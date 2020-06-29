#include<cstdio>
#include<cstdlib>
#include<cmath>
# include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int yokoinum(int i, int j, int mat[64][64])
{
	int q, r;
	q = r = 0;

	if (mat[i][j] == 255)
	{
		if (j + 1 < 64)
		{
			if (mat[i][j + 1] == 255)
			{
				if (i - 1 >= 0)
				{
					if (mat[i - 1][j] == 255)
					{
						if (mat[i - 1][j + 1] == 255)
						{
							r++;
						}
						else
							q++;
					}
					else
						q++;
				}
				else
					q++;
			}
		}

		if (i - 1 >= 0)
		{
			if (mat[i - 1][j] == 255)
			{
				if (j - 1 >= 0)
				{
					if (mat[i][j - 1] == 255)
					{
						if (mat[i - 1][j - 1] == 255)
						{
							r++;
						}
						else
							q++;
					}
					else
						q++;
				}
				else
					q++;
			}
		}

		if (j - 1 >= 0)
		{
			if (mat[i][j - 1] == 255)
			{
				if (i + 1 < 64)
				{
					if (mat[i + 1][j] == 255)
					{
						if (mat[i + 1][j - 1] == 255)
						{
							r++;
						}
						else
							q++;
					}
					else
						q++;
				}
				else
					q++;
			}
		}

		if (i + 1 < 64)
		{
			if (mat[i + 1][j] == 255)
			{
				if (j + 1 < 64)
				{
					if (mat[i][j + 1] == 255)
					{
						if (mat[i + 1][j + 1] == 255)
						{
							r++;
						}
						else
							q++;
					}
					else
						q++;
				}
				else
					q++;
			}
		}
	}
	else
		return 0;

	if (r == 4)
		return 5;
	else
		return q;
}

int main()
{
	// read image 
	Mat img = imread("lena.bmp", CV_8UC1);
	int dsample[64][64], yokoi[64][64],mark[64][64],neicnt;

	for (int i = 0; i < img.rows; i++)         //thresholding
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

	for (int i = 0; i < 64; i++)         //downsampling
	{
		for (int j = 0; j < 64; j++)
		{
			dsample[i][j] = img.at<uchar>(i * 8, j * 8);
		}
	}

	for (int i = 0; i < 64; i++)        //call yokoi()
	{
		for (int j = 0; j < 64; j++)
		{
			yokoi[i][j] = yokoinum(i, j, dsample);
		}
	}
	int change,itr = 0;
	while (1)
	{
		change = 0;
		for (int i = 0; i < 64; i++)        
		{
			for (int j = 0; j < 64; j++)
			{
				mark[i][j] = 0;
			}
		}

		for (int i = 0; i < 64; i++)       //mark pixel
		{
			for (int j = 0; j < 64; j++)
			{
				neicnt = 0;
				if (yokoi[i][j] == 1)
				{
					if (j + 1 < 64)
					{
						if (yokoi[i][j + 1] == 1)
						{
							neicnt++;
						}
					}

					if (i - 1 >= 0)
					{
						if (yokoi[i - 1][j] == 1)
						{
							neicnt++;
						}
					}

					if (j - 1 >= 0)
					{
						if (yokoi[i][j - 1] == 1)
						{
							neicnt++;
						}
					}

					if (i + 1 < 64)
					{
						if (yokoi[i + 1][j] == 1)
						{
							neicnt++;
						}
					}
					if (neicnt > 0)
						mark[i][j] = 1;
				}
			}
		}

		for (int i = 0; i < 64; i++)               //elimate
		{
			for (int j = 0; j < 64; j++)
			{
				if (mark[i][j] == 1)
				{
					if (yokoinum(i, j, dsample) == 1)
					{
						dsample[i][j] = 0;
						change = 1;
					}
				}
			}
		}

		for (int i = 0; i < 64; i++)        //call yokoi()
		{
			for (int j = 0; j < 64; j++)
			{
				yokoi[i][j] = yokoinum(i, j, dsample);
			}
		}
		
		itr++;
		if (change == 0)
			break;
	}

	Mat thin(64, 64, CV_8UC1);

	for (int i = 0; i < 64; i++)        
	{
		for (int j = 0; j < 64; j++)
		{
			thin.at<uchar>(i, j) = dsample[i][j];
		}
	}
	resize(thin, thin, Size(), 5, 5, INTER_LINEAR);
	imshow("thin", thin);
	imwrite("thin.jpg", thin);
	waitKey(0);

	return 0;
}
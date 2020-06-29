#include<cstdio>
#include<cstdlib>
#include<cmath>
# include <iostream>

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
	int dsample[64][64], yokoi[64][64];

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





	for (int i = 0; i < 64; i++)         //print yokoi
	{
		for (int j = 0; j < 64; j++)
		{
			if (yokoi[i][j] != 0)
			{
				cout << yokoi[i][j];
			}
			else
				cout << " ";
		}
		cout << endl;
	}


	system("pause");
	return 0;
}
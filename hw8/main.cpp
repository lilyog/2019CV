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

double snr(Mat s, Mat n)
{
	double** normals;
	int p;
	normals = new double* [s.rows];
	for (p = 0; p < s.cols; p++)
		normals[p] = new double[s.cols];

	double max = 0, min = 255;

	for (int i = 0; i < s.rows; i++)             //normalize  source image
	{
		for (int j = 0; j < s.cols; j++)
		{
			if (s.at<uchar>(i, j) > max)
			{
				max = s.at<uchar>(i, j);
			}
			if (s.at<uchar>(i, j) < min)
			{
				min = s.at<uchar>(i, j);
			}
		}
	}

	for (int i = 0; i < s.rows; i++)
	{
		for (int j = 0; j < s.cols; j++)
		{
			normals[i][j] = (s.at<uchar>(i, j) - min) / (max - min);
		}
	}
	
	double u = 0;

	for (int i = 0; i < s.rows; i++)
	{
		for (int j = 0; j < s.cols; j++)
		{
			u += normals[i][j];
		}
	}
	u = u / (s.rows * s.cols);

	double vs = 0;
	for (int i = 0; i < s.rows; i++)
	{
		for (int j = 0; j < s.cols; j++)
		{
			vs += pow(normals[i][j] - u, 2);
		}
	}
	vs = vs / (s.rows * s.cols);

/////////////////////////////////////////////////////////
	double** normaln;

	normaln = new double* [n.rows];
	for (p = 0; p < n.cols; p++)
		normaln[p] = new double[n.cols];

	max = 0, min = 255;

	for (int i = 0; i < n.rows; i++)             //normalize  noise image
	{
		for (int j = 0; j < n.cols; j++)
		{
			if (n.at<uchar>(i, j) > max)
			{
				max = n.at<uchar>(i, j);
			}
			if (n.at<uchar>(i, j) < min)
			{
				min = n.at<uchar>(i, j);
			}
		}
	}
	
	for (int i = 0; i < n.rows; i++)
	{
		for (int j = 0; j < n.cols; j++)
		{
			normaln[i][j] = (n.at<uchar>(i, j) - min) / (max - min);
		}
	}
	
	double un = 0;

	for (int i = 0; i < n.rows; i++)
	{
		for (int j = 0; j < n.cols; j++)
		{
			un += normaln[i][j] - normals[i][j];
		}
	}
	
	un = un / (n.rows * n.cols);
	
	double vn = 0;
	for (int i = 0; i < n.rows; i++)
	{
		for (int j = 0; j < n.cols; j++)
		{
			vn += pow(normaln[i][j] - normals[i][j] - un, 2);
		}
	}
	vn = vn / (n.rows * n.cols);
	
	double snr;
	snr = 20 * (log10(sqrt(vs) / sqrt(vn)));

	return snr;
}
Mat gaunoise(Mat s,int amp)
{
	random_device rd;
	mt19937 generator(rd());
	normal_distribution<> norm(0.0, 1.0);
	Mat n;
	s.copyTo(n);
	int no,pi;
	int c = 0;
	for (int i = 0; i < s.rows; i++)
	{
		for (int j = 0; j < s.cols; j++)
		{
			no = n.at<uchar>(i, j)+int(amp * (norm(generator)));
			if (no > 255)
				no = 255;
			n.at<uchar>(i, j) = no;		
		}
	}
	return n;
}
Mat box3(Mat n)
{
	Mat bor,clean;
	n.copyTo(clean);
	copyMakeBorder(n, bor, 1, 1, 1, 1, BORDER_REFLECT);
	for (int i = 0; i < n.rows; i++)
	{
		for (int j = 0; j < n.cols; j++)
		{
			clean.at<uchar>(i, j) = (bor.at<uchar>(i, j) + bor.at<uchar>(i, j + 1) + bor.at<uchar>(i, j + 2)\
				+ bor.at<uchar>(i + 1, j) + bor.at<uchar>(i + 1, j + 1) + bor.at<uchar>(i + 1, j + 2)\
				+ bor.at<uchar>(i + 2, j) + bor.at<uchar>(i + 2, j + 1) + bor.at<uchar>(i + 2, j + 2))/9;
		}
	}
	return clean;
}
Mat box5(Mat n)
{
	Mat bor, clean;
	n.copyTo(clean);
	copyMakeBorder(n, bor, 2, 2, 2, 2, BORDER_REFLECT);
	for (int i = 0; i < n.rows; i++)
	{
		for (int j = 0; j < n.cols; j++)
		{
			clean.at<uchar>(i, j) = (bor.at<uchar>(i, j) + bor.at<uchar>(i, j + 1) + bor.at<uchar>(i, j + 2) + bor.at<uchar>(i, j + 3) + bor.at<uchar>(i, j + 4)\
				+ bor.at<uchar>(i + 1, j) + bor.at<uchar>(i + 1, j + 1) + bor.at<uchar>(i + 1, j + 2) + bor.at<uchar>(i + 1, j + 3) + bor.at<uchar>(i + 1, j + 4)\
				+ bor.at<uchar>(i + 2, j) + bor.at<uchar>(i + 2, j + 1) + bor.at<uchar>(i + 2, j + 2) + bor.at<uchar>(i + 2, j + 3) + bor.at<uchar>(i + 2, j + 4)\
				+ bor.at<uchar>(i + 3, j) + bor.at<uchar>(i + 3, j + 1) + bor.at<uchar>(i + 3, j + 2) + bor.at<uchar>(i + 3, j + 3) + bor.at<uchar>(i + 3, j + 4)\
				+ bor.at<uchar>(i + 4, j) + bor.at<uchar>(i + 4, j + 1) + bor.at<uchar>(i + 4, j + 2) + bor.at<uchar>(i + 4, j + 3) + bor.at<uchar>(i + 4, j + 4)) / 25;
		}
	}
	return clean;
}
Mat med3(Mat n)
{
	Mat bor, clean;
	double fil[9],tmp;
	n.copyTo(clean);
	copyMakeBorder(n, bor, 1, 1, 1, 1, BORDER_REFLECT);
	for (int i = 0; i < n.rows; i++)
	{
		for (int j = 0; j < n.cols; j++)
		{
			fil[0] = bor.at<uchar>(i, j);
			fil[1] = bor.at<uchar>(i, j + 1);
			fil[2] = bor.at<uchar>(i, j + 2);
			fil[3] = bor.at<uchar>(i + 1, j);
			fil[4] = bor.at<uchar>(i + 1, j + 1);
			fil[5] = bor.at<uchar>(i + 1, j + 2);
			fil[6] = bor.at<uchar>(i + 2, j);
			fil[7] = bor.at<uchar>(i + 2, j + 1);
			fil[8] = bor.at<uchar>(i + 2, j + 2);
			
			for (int k = 0; k < 9; k++)
			{
				for (int l = 0; l < 8; l++)
				{
					if (fil[l] > fil[l + 1])
					{
						tmp = fil[l + 1];
						fil[l + 1]=fil[l];
						fil[l] = tmp;
					}
				}
			}
			clean.at<uchar>(i, j) = fil[4];
		}
	}
	return clean;
}
Mat med5(Mat n)
{
	Mat bor, clean;
	double fil[25], tmp;
	n.copyTo(clean);
	copyMakeBorder(n, bor, 2, 2, 2, 2, BORDER_REFLECT);
	for (int i = 0; i < n.rows; i++)
	{
		for (int j = 0; j < n.cols; j++)
		{
			fil[0] = bor.at<uchar>(i, j);
			fil[1] = bor.at<uchar>(i, j + 1);
			fil[2] = bor.at<uchar>(i, j + 2);
			fil[3] = bor.at<uchar>(i, j + 3);
			fil[4] = bor.at<uchar>(i, j + 4);
			fil[5] = bor.at<uchar>(i + 1, j);
			fil[6] = bor.at<uchar>(i + 1, j + 1);
			fil[7] = bor.at<uchar>(i + 1, j + 2);
			fil[8] = bor.at<uchar>(i + 1, j + 3);
			fil[9] = bor.at<uchar>(i + 1, j + 4);
			fil[10] = bor.at<uchar>(i + 2, j);
			fil[11] = bor.at<uchar>(i + 2, j + 1);
			fil[12] = bor.at<uchar>(i + 2, j + 2);
			fil[13] = bor.at<uchar>(i + 2, j + 3);
			fil[14] = bor.at<uchar>(i + 2, j + 4);
			fil[15] = bor.at<uchar>(i + 3, j);
			fil[16] = bor.at<uchar>(i + 3, j + 1);
			fil[17] = bor.at<uchar>(i + 3, j + 2);
			fil[18] = bor.at<uchar>(i + 3, j + 3);
			fil[19] = bor.at<uchar>(i + 3, j + 4);
			fil[20] = bor.at<uchar>(i + 4, j);
			fil[21] = bor.at<uchar>(i + 4, j + 1);
			fil[22] = bor.at<uchar>(i + 4, j + 2);
			fil[23] = bor.at<uchar>(i + 4, j + 3);
			fil[24] = bor.at<uchar>(i + 4, j + 4);

			for (int k = 0; k < 25; k++)
			{
				for (int l = 0; l < 24; l++)
				{
					if (fil[l] > fil[l + 1])
					{
						tmp = fil[l + 1];
						fil[l + 1] = fil[l];
						fil[l] = tmp;
					}
				}
			}
			clean.at<uchar>(i, j) = fil[12];
		}
	}
	return clean;
}
Mat open(Mat img)
{
	Mat ero;
	img.copyTo(ero);
	double min;

	for (int i = 0; i < img.rows; i++)          //use octagon kernel to dilate
	{
		for (int j = 0; j < img.cols; j++)      //find the kernel's min gray scale and give to i,j
		{
			min = 255;
			if (i - 2 > 0 && j - 1 > 0 && i - 2 < img.rows && j - 1 < img.cols)
			{
				if (min > img.at<uchar>(i - 2, j - 1))
				{
					min = img.at<uchar>(i - 2, j - 1);
				}
			}
			if (i - 2 > 0 && j > 0 && i - 2 < img.rows && j < img.cols)
			{
				if (min > img.at<uchar>(i - 2, j))
				{
					min = img.at<uchar>(i - 2, j);
				}
			}
			if (i - 2 > 0 && j + 1 > 0 && i - 2 < img.rows && j + 1 < img.cols)
			{
				if (min > img.at<uchar>(i - 2, j + 1))
				{
					min = img.at<uchar>(i - 2, j + 1);
				}
			}
			if (i - 1 > 0 && j - 2 > 0 && i - 1 < img.rows && j - 2 < img.cols)
			{
				if (min > img.at<uchar>(i - 1, j - 2))
				{
					min = img.at<uchar>(i - 1, j - 2);
				}
			}
			if (i - 1 > 0 && j - 1 > 0 && i - 1 < img.rows && j - 1 < img.cols)
			{
				if (min > img.at<uchar>(i - 1, j - 1))
				{
					min = img.at<uchar>(i - 1, j - 1);
				}
			}
			if (i - 1 > 0 && j > 0 && i - 1 < img.rows && j < img.cols)
			{
				if (min > img.at<uchar>(i - 1, j))
				{
					min = img.at<uchar>(i - 1, j);
				}
			}
			if (i - 1 > 0 && j + 1 > 0 && i - 1 < img.rows && j + 1 < img.cols)
			{
				if (min > img.at<uchar>(i - 1, j + 1))
				{
					min = img.at<uchar>(i - 1, j + 1);
				}
			}
			if (i - 1 > 0 && j + 2 > 0 && i - 1 < img.rows && j + 2 < img.cols)
			{
				if (min > img.at<uchar>(i - 1, j + 2))
				{
					min = img.at<uchar>(i - 1, j + 2);
				}
			}
			if (i > 0 && j - 2 > 0 && i < img.rows && j - 2 < img.cols)
			{
				if (min > img.at<uchar>(i, j - 2))
				{
					min = img.at<uchar>(i, j - 2);
				}
			}
			if (i > 0 && j - 1 > 0 && i < img.rows && j - 1 < img.cols)
			{
				if (min > img.at<uchar>(i, j - 1))
				{
					min = img.at<uchar>(i, j - 1);
				}
			}
			if (i > 0 && j + 1 > 0 && i < img.rows && j + 1 < img.cols)
			{
				if (min > img.at<uchar>(i, j + 1))
				{
					min = img.at<uchar>(i, j + 1);
				}
			}
			if (i > 0 && j + 2 > 0 && i < img.rows && j + 2 < img.cols)
			{
				if (min > img.at<uchar>(i, j + 2))
				{
					min = img.at<uchar>(i, j + 2);
				}
			}
			if (i + 1 > 0 && j - 2 > 0 && i + 1 < img.rows && j - 2 < img.cols)
			{
				if (min > img.at<uchar>(i + 1, j - 2))
				{
					min = img.at<uchar>(i + 1, j - 2);
				}
			}
			if (i + 1 > 0 && j - 1 > 0 && i + 1 < img.rows && j - 1 < img.cols)
			{
				if (min > img.at<uchar>(i + 1, j - 1))
				{
					min = img.at<uchar>(i + 1, j - 1);
				}
			}
			if (i + 1 > 0 && j > 0 && i + 1 < img.rows && j < img.cols)
			{
				if (min > img.at<uchar>(i + 1, j))
				{
					min = img.at<uchar>(i + 1, j);
				}
			}
			if (i + 1 > 0 && j + 1 > 0 && i + 1 < img.rows && j + 1 < img.cols)
			{
				if (min > img.at<uchar>(i + 1, j + 1))
				{
					min = img.at<uchar>(i + 1, j + 1);
				}
			}
			if (i + 1 > 0 && j + 2 > 0 && i + 1 < img.rows && j + 2 < img.cols)
			{
				if (min > img.at<uchar>(i + 1, j + 2))
				{
					min = img.at<uchar>(i + 1, j + 2);
				}
			}
			if (i + 2 > 0 && j - 1 > 0 && i + 2 < img.rows && j - 1 < img.cols)
			{
				if (min > img.at<uchar>(i + 2, j - 1))
				{
					min = img.at<uchar>(i + 2, j - 1);
				}
			}
			if (i + 2 > 0 && j > 0 && i + 2 < img.rows && j < img.cols)
			{
				if (min > img.at<uchar>(i + 2, j))
				{
					min = img.at<uchar>(i + 2, j);
				}
			}
			if (i + 2 > 0 && j + 1 > 0 && i + 2 < img.rows && j + 1 < img.cols)
			{
				if (min > img.at<uchar>(i + 2, j + 1))
				{
					min = img.at<uchar>(i + 2, j + 1);
				}
			}

			if (min < img.at<uchar>(i, j))
			{
				ero.at<uchar>(i, j) = min;
			}

		}
	}
	
	Mat dil;
	ero.copyTo(dil);
	double max;

	for (int i = 0; i < img.rows; i++)          //use octagon kernel to dilate
	{
		for (int j = 0; j < img.cols; j++)      //find the kernel's max gray scale and give to i,j
		{
			max = 0;
			if (i - 2 > 0 && j - 1 > 0 && i - 2 < img.rows && j - 1 < img.cols)
			{
				if (max < ero.at<uchar>(i - 2, j - 1))
				{
					max = ero.at<uchar>(i - 2, j - 1);
				}
			}
			if (i - 2 > 0 && j > 0 && i - 2 < img.rows && j < img.cols)
			{
				if (max < ero.at<uchar>(i - 2, j))
				{
					max = ero.at<uchar>(i - 2, j);
				}
			}
			if (i - 2 > 0 && j + 1 > 0 && i - 2 < img.rows && j + 1 < img.cols)
			{
				if (max < ero.at<uchar>(i - 2, j + 1))
				{
					max = ero.at<uchar>(i - 2, j + 1);
				}
			}
			if (i - 1 > 0 && j - 2 > 0 && i - 1 < img.rows && j - 2 < img.cols)
			{
				if (max < ero.at<uchar>(i - 1, j - 2))
				{
					max = ero.at<uchar>(i - 1, j - 2);
				}
			}
			if (i - 1 > 0 && j - 1 > 0 && i - 1 < img.rows && j - 1 < img.cols)
			{
				if (max < ero.at<uchar>(i - 1, j - 1))
				{
					max = ero.at<uchar>(i - 1, j - 1);
				}
			}
			if (i - 1 > 0 && j > 0 && i - 1 < img.rows && j < img.cols)
			{
				if (max < ero.at<uchar>(i - 1, j))
				{
					max = ero.at<uchar>(i - 1, j);
				}
			}
			if (i - 1 > 0 && j + 1 > 0 && i - 1 < img.rows && j + 1 < img.cols)
			{
				if (max < ero.at<uchar>(i - 1, j + 1))
				{
					max = ero.at<uchar>(i - 1, j + 1);
				}
			}
			if (i - 1 > 0 && j + 2 > 0 && i - 1 < img.rows && j + 2 < img.cols)
			{
				if (max < ero.at<uchar>(i - 1, j + 2))
				{
					max = ero.at<uchar>(i - 1, j + 2);
				}
			}
			if (i > 0 && j - 2 > 0 && i < img.rows && j - 2 < img.cols)
			{
				if (max < ero.at<uchar>(i, j - 2))
				{
					max = ero.at<uchar>(i, j - 2);
				}
			}
			if (i > 0 && j - 1 > 0 && i < img.rows && j - 1 < img.cols)
			{
				if (max < ero.at<uchar>(i, j - 1))
				{
					max = ero.at<uchar>(i, j - 1);
				}
			}
			if (i > 0 && j + 1 > 0 && i < img.rows && j + 1 < img.cols)
			{
				if (max < ero.at<uchar>(i, j + 1))
				{
					max = ero.at<uchar>(i, j + 1);
				}
			}
			if (i > 0 && j + 2 > 0 && i < img.rows && j + 2 < img.cols)
			{
				if (max < ero.at<uchar>(i, j + 2))
				{
					max = ero.at<uchar>(i, j + 2);
				}
			}
			if (i + 1 > 0 && j - 2 > 0 && i + 1 < img.rows && j - 2 < img.cols)
			{
				if (max < ero.at<uchar>(i + 1, j - 2))
				{
					max = ero.at<uchar>(i + 1, j - 2);
				}
			}
			if (i + 1 > 0 && j - 1 > 0 && i + 1 < img.rows && j - 1 < img.cols)
			{
				if (max < ero.at<uchar>(i + 1, j - 1))
				{
					max = ero.at<uchar>(i + 1, j - 1);
				}
			}
			if (i + 1 > 0 && j > 0 && i + 1 < img.rows && j < img.cols)
			{
				if (max < ero.at<uchar>(i + 1, j))
				{
					max = ero.at<uchar>(i + 1, j);
				}
			}
			if (i + 1 > 0 && j + 1 > 0 && i + 1 < img.rows && j + 1 < img.cols)
			{
				if (max < ero.at<uchar>(i + 1, j + 1))
				{
					max = ero.at<uchar>(i + 1, j + 1);
				}
			}
			if (i + 1 > 0 && j + 2 > 0 && i + 1 < img.rows && j + 2 < img.cols)
			{
				if (max < ero.at<uchar>(i + 1, j + 2))
				{
					max = ero.at<uchar>(i + 1, j + 2);
				}
			}
			if (i + 2 > 0 && j - 1 > 0 && i + 2 < img.rows && j - 1 < img.cols)
			{
				if (max < ero.at<uchar>(i + 2, j - 1))
				{
					max = ero.at<uchar>(i + 2, j - 1);
				}
			}
			if (i + 2 > 0 && j > 0 && i + 2 < img.rows && j < img.cols)
			{
				if (max < ero.at<uchar>(i + 2, j))
				{
					max = ero.at<uchar>(i + 2, j);
				}
			}
			if (i + 2 > 0 && j + 1 > 0 && i + 2 < img.rows && j + 1 < img.cols)
			{
				if (max < ero.at<uchar>(i + 2, j + 1))
				{
					max = ero.at<uchar>(i + 2, j + 1);
				}
			}

			if (max > ero.at<uchar>(i, j))
			{
				dil.at<uchar>(i, j) = max;
			}

		}
	}
	return dil;
}
Mat close(Mat img)
{
	Mat dil;
	img.copyTo(dil);
	double max;

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

	Mat ero;
	dil.copyTo(ero);
	double min;

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
	return ero;
}
Mat saltpepper(Mat s, double thr)
{
	//srand(time(NULL));
	random_device rd;
	mt19937 generator(rd());
	uniform_real_distribution<double> distribution(0.0, 1.0);
	double ran;
	Mat n;
	s.copyTo(n);
	for (int i = 0; i < s.rows; i++)
	{
		for (int j = 0; j < s.cols; j++)
		{
			ran = distribution(generator);
			if (ran < thr)
				n.at<uchar>(i, j) = 0;
			else if (ran > (1 - thr))
				n.at<uchar>(i, j) = 255;
			else
				n.at<uchar>(i, j) = s.at<uchar>(i, j);
		}
	}
	return n;
}
int main()
{
	// read image 
	Mat s = imread("lena.bmp", CV_8UC1);
	Mat gau10, gau10box3, gau10box5, gau10med3, gau10med5, gau10opcl, gau10clop,\
		gau30, gau30box3, gau30box5, gau30med3, gau30med5, gau30opcl, gau30clop,\
		salt005,salt005box3,salt005box5,salt005med3,salt005med5,salt005opcl,salt005clop,\
		salt01, salt01box3, salt01box5, salt01med3, salt01med5, salt01opcl, salt01clop;
	

	gau10 = gaunoise(s, 10);                                //Gaussian with amptitude 10
	gau10box3 = box3(gau10);
	gau10box5 = box5(gau10);
	gau10med3 = med3(gau10);
	gau10med5 = med5(gau10);
	gau10opcl = close(open(gau10));
	gau10clop = open(close(gau10));
	cout << "Gaussian with amptitude 10:" << endl;
	cout << "Gaussian noise snr:" << snr(s, gau10) << endl;
	imshow("gau10", gau10);
	imwrite("gau10.jpg", gau10);
	cout << "box 3x3 snr:" << snr(s, gau10box3) << endl;
	imshow("gau10box3", gau10box3);
	imwrite("gau10box3.jpg", gau10box3);
	cout << "box 5x5 snr:" << snr(s, gau10box5) << endl;
	imshow("gau10box5", gau10box5);
	imwrite("gau10box5.jpg", gau10box5);
	cout << "median 3x3 snr:" << snr(s, gau10med3) << endl;
	imshow("gau10med3", gau10med3);
	imwrite("gau10med3.jpg", gau10med3);
	cout << "median 5x5 snr:" << snr(s, gau10med5) << endl;
	imshow("gau10med5", gau10med5);
	imwrite("gau10med5.jpg", gau10med5);
	cout << "opening then closing snr:" << snr(s, gau10opcl) << endl;
	imshow("gau10opcl", gau10opcl);
	imwrite("gau10opcl.jpg", gau10opcl);
	cout << "closinging then opening snr:" << snr(s, gau10clop) << endl;
	imshow("gau10clop", gau10clop);
	imwrite("gau10clop.jpg", gau10clop);

	cout << endl;
	
	gau30 = gaunoise(s, 30);
	gau30box3 = box3(gau30);
	gau30box5 = box5(gau30);
	gau30med3 = med3(gau30);
	gau30med5 = med5(gau30);
	gau30opcl = close(open(gau30));
	gau30clop = open(close(gau30));
	cout << "Gaussian with amptitude 30:" << endl;          //Gaussian with amptitude 30
	cout << "Gaussian noise snr:" << snr(s, gau30) << endl;
	imshow("gau30", gau30);
	imwrite("gau30.jpg", gau30);
	cout << "box 3x3 snr:" << snr(s, gau30box3) << endl;
	imshow("gau30box3", gau30box3);
	imwrite("gau30box3.jpg", gau30box3);
	cout << "box 5x5 snr:" << snr(s, gau30box5) << endl;
	imshow("gau30box5", gau30box5);
	imwrite("gau30box5.jpg", gau30box5);
	cout << "median 3x3 snr:" << snr(s, gau30med3) << endl;
	imshow("gau30med3", gau30med3);
	imwrite("gau30med3.jpg", gau30med3);
	cout << "median 5x5 snr:" << snr(s, gau30med5) << endl;
	imshow("gau30med5", gau30med5);
	imwrite("gau30med5.jpg", gau30med5);
	cout << "opening then closing snr:" << snr(s, gau30opcl) << endl;
	imshow("gau30opcl", gau30opcl);
	imwrite("gau30opcl.jpg", gau30opcl);
	cout << "closinging then opening snr:" << snr(s, gau30clop) << endl;
	imshow("gau30clop", gau30clop);
	imwrite("gau30clop.jpg", gau30clop);

	cout << endl;

	salt005 = saltpepper(s, 0.05);                                //salt & pepper with threshold 0.05
	salt005box3 = box3(salt005);
	salt005box5 = box5(salt005);
	salt005med3 = med3(salt005);
	salt005med5 = med5(salt005);
	salt005opcl = close(open(salt005));
	salt005clop = open(close(salt005));
	cout << "salt & pepper with threshold 0.05:" << endl;
	cout << "salt & pepper snr:" << snr(s, salt005) << endl;
	imshow("salt005", salt005);
	imwrite("salt005.jpg", salt005);
	
	cout << "box 3x3 snr:" << snr(s, salt005box3) << endl;
	imshow("salt005box3", salt005box3);
	imwrite("salt005box3.jpg", salt005box3);
	cout << "box 5x5 snr:" << snr(s, salt005box5) << endl;
	imshow("salt005box5", salt005box5);
	imwrite("salt005box5.jpg", salt005box5);
	cout << "median 3x3 snr:" << snr(s, salt005med3) << endl;
	imshow("salt005med3", salt005med3);
	imwrite("salt005med3.jpg", salt005med3);
	cout << "median 5x5 snr:" << snr(s, salt005med5) << endl;
	imshow("salt005med5", salt005med5);
	imwrite("salt005med5.jpg", salt005med5);
	cout << "opening then closing snr:" << snr(s, salt005opcl) << endl;
	imshow("salt005opcl", salt005opcl);
	imwrite("salt005opcl.jpg", salt005opcl);
	cout << "closinging then opening snr:" << snr(s, salt005clop) << endl;
	imshow("salt005clop", salt005clop);
	imwrite("salt005clop.jpg", salt005clop);

	cout << endl;

	salt01 = saltpepper(s, 0.1);                                //salt & pepper with threshold 0.1
	salt01box3 = box3(salt01);
	salt01box5 = box5(salt01);
	salt01med3 = med3(salt01);
	salt01med5 = med5(salt01);
	salt01opcl = close(open(salt01));
	salt01clop = open(close(salt01));
	cout << "salt & pepper with threshold 0.1:" << endl;
	cout << "salt & pepper snr:" << snr(s, salt01) << endl;
	imshow("salt01", salt01);
	imwrite("salt01.jpg", salt01);

	cout << "box 3x3 snr:" << snr(s, salt01box3) << endl;
	imshow("salt005box3", salt01box3);
	imwrite("salt01box3.jpg", salt01box3);
	cout << "box 5x5 snr:" << snr(s, salt01box5) << endl;
	imshow("salt01box5", salt01box5);
	imwrite("salt01box5.jpg", salt01box5);
	cout << "median 3x3 snr:" << snr(s, salt01med3) << endl;
	imshow("salt01med3", salt01med3);
	imwrite("salt01med3.jpg", salt01med3);
	cout << "median 5x5 snr:" << snr(s, salt01med5) << endl;
	imshow("salt01med5", salt01med5);
	imwrite("salt01med5.jpg", salt01med5);
	cout << "opening then closing snr:" << snr(s, salt01opcl) << endl;
	imshow("salt01opcl", salt01opcl);
	imwrite("salt01opcl.jpg", salt01opcl);
	cout << "closinging then opening snr:" << snr(s, salt01clop) << endl;
	imshow("salt01clop", salt01clop);
	imwrite("salt01clop.jpg", salt01clop);
	waitKey(0);
	return 0;
}
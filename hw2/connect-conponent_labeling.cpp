#include<cstdio>
#include<cstdlib>
#include<cmath>
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp> 

using namespace cv;
using namespace std;

int main()
{
	// read image 
	Mat img = imread("lena.bmp",CV_8UC1);
	
	for (int i = 0; i < img.rows; i++)         //thresholding at 128
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
	
	int **label ;                        //dynamic allocate label 2d array
	label = new int* [img.rows];
	for (int i = 0; i < img.rows; i++)
	{
		label[i] = new int[img.cols];
	}

	for (int i = 0; i < img.rows; i++)  //initialize
	{
		for (int j = 0; j < img.cols; j++)
		{
			label[i][j] = 0;
		}
	}
	
	int idx,maxidx;
	idx = 1; 
	maxidx = 1;                         //idx is label's number
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			if (img.at<uchar>(i, j) == 255)  //white
			{
				if (i == 0 && j == 0)
				{
					label[i][j] = idx;
					maxidx = idx;
					idx++;
				}
				if (i == 0 && j != 0)        //the first row
				{
					if (img.at<uchar>(i, j - 1) == 0) //left is black
					{
						label[i][j] = idx;
						maxidx = idx;
						idx++;
					}
					else                              //left is white
					{
						label[i][j] = label[i][j - 1];
					}
				}
				if (i != 0 && j == 0)         //the first col
				{
					if (img.at<uchar>(i - 1, j) == 0) //up is black
					{
						label[i][j] = idx;
						maxidx = idx;
						idx++;
					}
					else                              //up is white
					{
						label[i][j] = label[i - 1][j];
					}
				}
				if (i != 0 && j != 0)
				{
					if ((img.at<uchar>(i - 1, j) == 0) && (img.at<uchar>(i, j - 1) == 0)) //up left both are black
					{
						label[i][j] = idx;
						maxidx = idx;
						idx++;
					}
					else if ((img.at<uchar>(i - 1, j) == 255) && (img.at<uchar>(i, j - 1) == 0))//up is white left is black
					{
						label[i][j] = label[i - 1][j];
					}
					else if ((img.at<uchar>(i - 1, j) == 0) && (img.at<uchar>(i, j - 1) == 255))//left is white up is black
					{
						label[i][j] = label[i][j - 1];
					}
					else // up left both are white
					{
						if (label[i - 1][j] < label[i][j - 1])
						{                                                            
							label[i][j] = label[i - 1][j];
							for (int a=0 ;a < img.rows; a++)             //change the label to both same
							{
								for (int b=0; b < img.cols; b++)
								{
									if (label[a][b] == label[i][j - 1])
									{
										label[a][b] = label[i - 1][j];
									}
								}
							}
						}
						else if (label[i - 1][j] > label[i][j - 1])
						{
							//label[i - 1][j] = label[i][j - 1];
							label[i][j] = label[i][j - 1];
							for (int a = 0; a < img.rows; a++)           //change the label to both same
							{
								for (int b = 0; b < img.cols; b++)
								{
									if (label[a][b] == label[i - 1][j])
									{
										label[a][b] = label[i][j - 1];
									}
								}
							}
						}
						else                                            //up left two lebels are same
						{
							label[i][j] = label[i][j - 1];
						}
					}
				}
			}
		}
	}
	
	int pixel;
	int area = 0;
	int n, e, w, s, xtotal, ytotal;                            //record the component's boundary
	int first;
	Point p1, p2;
	Point2d centroid;
	
	Mat imgc;                                 
	cvtColor(img, imgc, COLOR_GRAY2BGR);       //change to bgr color space to draw rectengle and mark
	
	for (int i = 1; i <= maxidx; i++)          //find component over 500 pixel
	{
		pixel = 0;
		first = 0;
		xtotal = ytotal = 0;
		for (int j = 0; j < img.rows; j++)
		{
			for (int k = 0; k < img.cols; k++)
			{
				if (label[j][k] == i)        
				{
					if (first == 0)          //the first pixel of component
					{
						n = s = j;
						w = e = k;
						first = 1;
					}
					if (j > s)              //record boundary's coordinate
					{
						s = j;
					}
					if (k > e)
					{
						e = k;
					}
					if (k < w)
					{
						w = k;
					}
					xtotal += k;
					ytotal += j;
					pixel++;
				}
			}
		}
		
		if (pixel >= 500)            //component over 500 pixel
		{
			p1.x = w;
			p1.y = n;
			p2.x = e;
			p2.y = s;
			rectangle(imgc, p1, p2, Scalar(255, 0, 0), 2);  //plot the component's boundary


			centroid.x = xtotal / pixel;
			centroid.y = ytotal / pixel;
			circle(imgc, centroid, 7, Scalar(0, 0, 255), 2);//plot the component's centroid
		}

	}

	

	// show image
	imshow("ConnectComponetLabeling", imgc);
	// write image 
	imwrite("ConnectComponetLabeling.jpg", imgc);
//	system("pause");
	waitKey(0);
	return 0;
}
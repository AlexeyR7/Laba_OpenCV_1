// LabaOpenCV.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <stdio.h>
#include <windows.h>
#include <windowsx.h>

#include <opencv2/opencv.hpp>

#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/types_c.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <opencv2/core.hpp>
#include <opencv2/video.hpp>
#include <opencv2/videoio.hpp>

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/video/video.hpp>
#include <opencv2/opencv.hpp>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2\opencv.hpp>


using namespace std;
using namespace cv;
int key_value[6][11];
void keyboard();
Vec2i cross(Vec4i v1, Vec4i v2);


int main()
{
	int max_buffer = 0, i, j = 0, k = 0, pen_pixels = 0, loc = 0, loc1 = 0, counter, init = 0, real = 0;
	int max_buffer1 = 0;
	int tip_x = 0, tip_y = 0, last_x = 0, last_y = 0, frame = 0;
	int clk = 0;
	int countP = 0;
	int clk_stat = 0;
	int keyboardX0 = 200, keyboardX1 = 400, keyboardY0 = 200, keyboardY1 = 400;
	int keyboardXcount = 4, keyboardYcount = 5;
	int keyboardDX = (keyboardX1 - keyboardX0) / keyboardXcount, keyboardDY = (keyboardY1 - keyboardY0) / keyboardYcount;
	char c;
	int pen_pixelsL = 0;
	int cntST1 = 0, cntST2 = 0;
	int findKeyboard = 0;
	int clickPOS_X = 0, clickPOS_Y = 0;
	int clickMAS_X = 0, clickMAS_Y = 0;

	IplImage* im_ttt;

	HWND stealth;
	CvLineIterator iterator;
	CvLineIterator iterator1;
	CvLineIterator iterator2;
	CvCapture* capture = cvCreateCameraCapture(CV_CAP_ANY);

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			key_value[i][j] = 0x23;
		}
	}




	cvNamedWindow("Video", CV_WINDOW_AUTOSIZE);

	cvNamedWindow("Video_im_bw", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Video_SQ", CV_WINDOW_AUTOSIZE);

	keyboard();
	AllocConsole();
	stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(stealth, 1);
	findKeyboard = 0;
	while (1)
	{
		IplImage* im_rgbOrig = cvQueryFrame(capture);
		IplImage* im_rgb = cvCloneImage(im_rgbOrig);
		IplImage* im_gray = cvCreateImage(cvGetSize(im_rgb), IPL_DEPTH_8U, 1);
		IplImage* im_bw = cvCreateImage(cvGetSize(im_gray), IPL_DEPTH_8U, 1);
		IplImage* im_ttt = cvCreateImage(cvGetSize(im_gray), IPL_DEPTH_8U, 1);
		if (!im_rgb)
		{
			printf("Camera not found.Check your camera connection");
			break;
		}
		cvWaitKey(20);
		frame = frame + 1;
		tip_x = -10;
		tip_y = -10;
		//findKeyboard = 0;
		cvCvtColor(im_rgb, im_gray, CV_RGB2GRAY);
		cvThreshold(im_gray, im_bw, 128, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
		cvLine(im_rgb, cvPoint(keyboardX0, keyboardY0), cvPoint(keyboardX1, keyboardY0), CV_RGB(255, 0, 0), 4, 8, 0);
		cvLine(im_rgb, cvPoint(keyboardX0, keyboardY0), cvPoint(keyboardX0, keyboardY1), CV_RGB(255, 0, 0), 4, 8, 0);
		cvLine(im_rgb, cvPoint(keyboardX1, keyboardY0), cvPoint(keyboardX1, keyboardY1), CV_RGB(255, 0, 0), 4, 8, 0);

		for (i = 0; i <= keyboardXcount; i++)
		{
			cvLine(im_rgb, cvPoint((i * keyboardDX) + keyboardX0, keyboardY0), cvPoint((i * keyboardDX) + keyboardX0, keyboardY1), CV_RGB(255, 0, 0), 1, 8, 0);
		}
		for (i = 0; i <= keyboardYcount; i++)
		{
			cvLine(im_rgb, cvPoint(keyboardX0, (i * keyboardDY) + keyboardY0), cvPoint(keyboardX1, (i * keyboardDY) + keyboardY0), CV_RGB(255, 0, 0), 1, 8, 0);
		}
		int lastPrclk_X = -10, lastPrclk_Y = -10;
		int lastPrclk_X1 = -10, lastPrclk_Y1 = -10;
		pen_pixelsL = 0;
		for (k = keyboardY0; k < keyboardY1 - 10; k++)
		{
			pen_pixels = 0;
			counter = 0;
			init = 0;
			max_buffer = cvInitLineIterator(im_bw, cvPoint(keyboardX0, k), cvPoint(keyboardX1, k), &iterator, 8, 0);
			max_buffer1 = cvInitLineIterator(im_bw, cvPoint(keyboardX0, k + 3), cvPoint(keyboardX1, k + 3), &iterator1, 8, 0);
			max_buffer1 = cvInitLineIterator(im_bw, cvPoint(keyboardX0, k + 7), cvPoint(keyboardX1, k + 7), &iterator2, 8, 0);
			for (j = 0; j < max_buffer - 5; j++)
			{
				if ((iterator.ptr[j] == 0 && iterator1.ptr[j] == 0 && iterator2.ptr[j] == 0) &&
					(iterator.ptr[j + 3] == 0 && iterator1.ptr[j + 3] == 0 && iterator2.ptr[j + 3] == 0) &&
					(iterator.ptr[j + 5] == 0 && iterator1.ptr[j + 5] == 0 && iterator2.ptr[j + 5] == 0))
				{
					//cvCircle(im_rgb, cvPoint(j+ keyboardX0, k), 1, CV_RGB(0, j%255, 255), 2, 8, 0);
					loc1 = j + keyboardX0;
					if (abs(loc1 - loc) < 2)
					{
						if (counter == 0)
						{
							init = loc1 - 1;
							counter++;
						}
						pen_pixels = pen_pixels + 1;
					}
				}
				loc = loc1;
				//CV_NEXT_LINE_POINT(iterator);
			}
			if (pen_pixels > 30 && pen_pixels < 100)
			{
				//cvCircle(im_rgb, cvPoint(tip_x, k), 1, CV_RGB(0, 255, 0), 2, 8, 0);
				if ((abs(init - tip_x) < 10))
				{
					countP++;
					//cvCircle(im_rgb, cvPoint(tip_x, k), 10, CV_RGB(255, 0, 0), 2, 8, 0);
				}
				else
				{
					if (countP > 0)
					{
						lastPrclk_X1 = lastPrclk_X;
						lastPrclk_Y1 = lastPrclk_Y;
						lastPrclk_X = tip_x;
						lastPrclk_Y = tip_y;
						//cvCircle(im_rgb, cvPoint(lastPrclk_X, lastPrclk_Y), 10, CV_RGB(255, 255, 0), 2, 8, 0);
					}
					countP = 0;
				}
				tip_x = init;
				tip_y = k;
				findKeyboard = 1;
			}

		}
		lastPrclk_X1 = lastPrclk_X;
		lastPrclk_Y1 = lastPrclk_Y;
		lastPrclk_X = tip_x;
		lastPrclk_Y = tip_y;
		cvCircle(im_rgb, cvPoint(lastPrclk_X, lastPrclk_Y), 10, CV_RGB(255, 255, 0), 2, 8, 0);
		cvCircle(im_rgb, cvPoint(lastPrclk_X1, lastPrclk_Y1), 10, CV_RGB(0, 255, 255), 2, 8, 0);

		int tipT_x = 0, tipT_y = 0;
		pen_pixelsL = 0;
		//////////////////////////
		for (k = keyboardY0; k < keyboardY1; k++)
		{
			pen_pixels = 0;
			counter = 0;
			init = 0;
			max_buffer = cvInitLineIterator(im_bw, cvPoint(keyboardX0, k), cvPoint(keyboardX1, k), &iterator, 8, 1);
			max_buffer1 = cvInitLineIterator(im_bw, cvPoint(keyboardX0, k + 3), cvPoint(keyboardX1, k + 3), &iterator1, 8, 1);
			max_buffer1 = cvInitLineIterator(im_bw, cvPoint(keyboardX0, k + 7), cvPoint(keyboardX1, k + 7), &iterator2, 8, 1);
			for (j = 0; j < max_buffer - 5; j++)
			{
				if ((iterator.ptr[j] == 0 && iterator1.ptr[j] == 0 && iterator2.ptr[j] == 0) &&
					(iterator.ptr[j + 3] == 0 && iterator1.ptr[j + 3] == 0 && iterator2.ptr[j + 3] == 0) &&
					(iterator.ptr[j + 5] == 0 && iterator1.ptr[j + 5] == 0 && iterator2.ptr[j + 5] == 0))
				{
					loc1 = j + keyboardX0;
					if (abs(loc1 - loc) < 2)
					{
						if (counter == 0)
						{
							init = loc1 - 1;
							counter++;
						}
						pen_pixels = pen_pixels + 1;
					}
				}
				loc = loc1;
			}
			if (pen_pixels > 30 && pen_pixels < 100)
			{
				cvCircle(im_rgb, cvPoint(tip_x, k), 1, CV_RGB(0, 255, 255), 2, 8, 0);
				tipT_x = init;
				tipT_y = k;
				findKeyboard = 2;
			}

		}


		//cvCircle(im_rgb, cvPoint(tip_x, tip_y), 10, CV_RGB(0, 0, 255), 2, 8, 0);
		//cvCircle(im_rgb, cvPoint(tipT_x, tipT_y), 10, CV_RGB(0, 255, 0), 2, 8, 0);
		clickPOS_X = (tip_x + tipT_x) / 2;
		clickPOS_Y = (tip_y + tipT_y) / 2;
		//cvCircle(im_rgb, cvPoint(clickPOS_X, clickPOS_Y), 10, CV_RGB(0, 55, 0), 2, 8, 0);

		clickMAS_X = (clickPOS_X - keyboardX0) / keyboardDX;
		clickMAS_Y = (clickPOS_Y - keyboardY0) / keyboardDY;

		switch (clk_stat)
		{
		case 0:
		{
			cntST2 = 0;
			if (((lastPrclk_X1 != -10) && (lastPrclk_Y1 != -10)) &&
				(tip_x >= keyboardX0) && (tip_x <= keyboardX1) &&
				(tip_y >= keyboardY0) && (tip_y <= keyboardY1) &&
				(tipT_x >= keyboardX0) && (tipT_x <= keyboardX1) &&
				(tipT_y >= keyboardY0) && (tipT_y <= keyboardY1)
				)
			{
				if (cntST1 > 5) {
					clk_stat = 1; cntST1 = 0;
				}
				else
				{
					cntST1++;
				}

			}
			break;
		}
		case 1:
		{
			cntST1 = 0;
			if (!((tip_x >= keyboardX0) && (tip_x <= keyboardX1) &&
				(tip_y >= keyboardY0) && (tip_y <= keyboardY1) &&
				(tipT_x >= keyboardX0) && (tipT_x <= keyboardX1) &&
				(tipT_y >= keyboardY0) && (tipT_y <= keyboardY1)
				))
			{
				clk_stat = 0;
			}
			if ((lastPrclk_X1 == -10) && (lastPrclk_Y1 == -10)) {
				if (cntST2 > 3) {
					clk_stat = 2; cntST2 = 0;
				}
				else
				{
					cntST2++;
				}
			}
			break;
		}
		case 2:
		{
			printf_s("CLICK! %d %d\n", clickMAS_X, clickMAS_Y);
			cvCircle(im_rgb, cvPoint(clickPOS_X, clickPOS_Y), 10, CV_RGB(255, 255, 0), 2, 8, 0);
			clk_stat = 0;
			break;
		}
		case 3:
		{

			break;
		}

		default:
			clk_stat = 0;
			break;
		}
		if (findKeyboard == 10)
		{
			//Mat img = cvarrToMat(im_rgb);
			Mat dst, cdst, cdstP;

			// Loads an image
			Mat src = cvarrToMat(im_rgbOrig);
			// Check if image is loaded fine

			// Edge detection
			Canny(src, dst, 50, 200, 3);
			// Copy edges to the images that will display the results in BGR
			cvtColor(dst, cdst, COLOR_GRAY2BGR);
			cdstP = cdst.clone();
			// Standard Hough Line Transform
			vector<Vec2f> lines; // will hold the results of the detection
			HoughLines(dst, lines, 1, CV_PI / 180, 80, 50, 50); // runs the actual detection
			// Draw the lines
			vector<Vec4i> linesHORZ;
			vector<Vec4i> linesVERT;
			vector<Vec2i> PointsCross;
			for (size_t i = 0; i < lines.size(); i++)
			{
				float rho = lines[i][0], theta = lines[i][1];
				Point pt1, pt2;
				double a = cos(theta), b = sin(theta);
				double x0 = a * rho, y0 = b * rho;
				pt1.x = cvRound(x0 + 1000 * (-b));
				pt1.y = cvRound(y0 + 1000 * (a));
				pt2.x = cvRound(x0 - 1000 * (-b));
				pt2.y = cvRound(y0 - 1000 * (a));
				if (b > 0.7) linesHORZ.push_back(Vec4i(pt1.x, pt1.y, pt2.x, pt2.y));
				else linesVERT.push_back(Vec4i(pt1.x, pt1.y, pt2.x, pt2.y));

				if (b > 0.7)line(cdst, pt1, pt2, Scalar(0, 0, 255), 3, LINE_AA);
				else line(cdst, pt1, pt2, Scalar(0, 255, 0), 3, LINE_AA);
			}

			for (Vec4i lineHor : linesHORZ)
			{
				for (Vec4i lineVert : linesVERT)
				{
					PointsCross.push_back(cross(lineHor, lineVert));

				}

			}
			for (int i = 0; i < PointsCross.size(); i++)
			{
				if ((PointsCross[i][0] <= 0 || PointsCross[i][1] <= 0) ||
					(PointsCross[i][0] >= 700 || PointsCross[i][1] >= 700))
					PointsCross.erase(PointsCross.begin() + i);
			}
			if (PointsCross.size() < 5)continue;
			int sX = 0, sY = 0;
			for (Vec2i PointVH : PointsCross)
			{
				cvCircle(im_rgb, cvPoint(PointVH[0], PointVH[1]), 2, CV_RGB(255, 255, 0), 2, 8, 0);
				sX += PointVH[0];
				sY += PointVH[1];
			}
			sX /= PointsCross.size();
			sY /= PointsCross.size();
			cvCircle(im_rgb, cvPoint(sX, sY), 2, CV_RGB(50, 255, 0), 2, 8, 0);

			////
			/*
			Найти крайнии линии по горизонтали и ветрикали
			Отсчитать 4 и 5 линий
			Получить квадрад
			Проверить ресстояние между линиями



			*/
			////





			im_ttt = cvCloneImage(&(IplImage)cdst);


			findKeyboard = 0;
		}




		cvShowImage("Video", im_rgb);
		//cvShowImage("Video_im_gray", im_gray);
		cvShowImage("Video_im_bw", im_bw);
		cvShowImage("Video_SQ", im_ttt);
		c = cvWaitKey(1);
		if (c == 27)
			break;
		if (c == 'c')
			findKeyboard = 10;


	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("Video");
	//cvDestroyWindow("Video1");
}

Vec2i cross(Vec4i v1, Vec4i v2) //точки a и b концы первого отрезка  c и d второго
{
	Vec2i  r;
	r[0] = -10;
	r[1] = -10;
	try {
		r[0] = -((v1[0] * v1[3] - v1[2] * v1[1]) * (v2[2] - v2[0]) - (v2[0] * v2[3] - v2[2] * v2[1]) * (v1[2] - v1[0])) / ((v1[1] - v1[3]) * (v2[2] - v2[0]) - (v2[1] - v2[3]) * (v1[2] - v1[0]));
		if ((v2[2] - v2[0]) == 0) return r;
		r[1] = ((v2[1] - v2[3]) * (-r[0]) - (v2[0] * v2[3] - v2[2] * v2[1])) / (v2[2] - v2[0]);
	}
	catch (int a)
	{
	}
	return r;
}


void keyboard()
{

	key_value[0][1] = 0x40;
	key_value[0][2] = 0x2F;
	key_value[0][3] = 0x2A;
	key_value[0][4] = 0x2D;

	key_value[1][1] = 0x37;
	key_value[1][2] = 0x38;
	key_value[1][3] = 0x39;
	key_value[1][4] = 0x2B;

	key_value[2][1] = 0x34;
	key_value[2][2] = 0x35;
	key_value[2][3] = 0x36;
	key_value[2][4] = 0x2B;

	key_value[3][1] = 0x31;
	key_value[3][2] = 0x32;
	key_value[3][3] = 0x33;
	key_value[3][4] = 0x23;

	key_value[4][1] = 0x30;
	key_value[4][2] = 0x30;
	key_value[4][3] = 0x2C;
	key_value[4][4] = 0x23;
}



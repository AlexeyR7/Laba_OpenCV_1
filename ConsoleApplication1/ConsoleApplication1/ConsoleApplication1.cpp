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
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

Vec2i cross(Vec4i v1, Vec4i v2);
int PointInPoly(Point click);

int keyboardXcount = 4, keyboardYcount = 5;
int key_value[4][5] = { { 'N', '7','4','1','0' },{ '/','8','5','2','0'},{ '*','9','6','3','.'},{ '-','+','+','E', 'E' } };
Point Keyboard_LU;
Point Keyboard_LD;
Point Keyboard_RU;
Point Keyboard_RD;

int main()
{
	int max_buffer = 0, i, j = 0, k = 0, pen_pixels = 0, loc = 0, loc1 = 0, counter, init = 0, real = 0;
	int max_buffer1 = 0;
	int tip_x = 0, tip_y = 0, last_x = 0, last_y = 0, frame = 0;
	int clk = 0;
	int countP = 0;
	int clk_stat = 0;
	int keyboardX0 = 200, keyboardX1 = 400, keyboardY0 = 200, keyboardY1 = 400;
	
	//int keyboardDX = (keyboardX1 - keyboardX0) / keyboardXcount, keyboardDY = (keyboardY1 - keyboardY0) / keyboardYcount;
	char c;
	int pen_pixelsL = 0;
	int cntST1 = 0, cntST2 = 0;
	int findKeyboard = 0;
	int clickPOS_X = 0, clickPOS_Y = 0;
	int clickMAS_X = 0, clickMAS_Y = 0;
	printf_s("OpeCV keyboard\n");
	

	HWND stealth;
	CvLineIterator iterator;
	CvLineIterator iterator1;
	CvLineIterator iterator2;
	CvCapture* capture = cvCreateCameraCapture(CV_CAP_ANY);
	if (capture == NULL)
	{
		printf("Camera not found.Check your camera connection");
		return 0;
	}

	//cvNamedWindow("Video", CV_WINDOW_AUTOSIZE);
	//cvNamedWindow("Video_im_gray", CV_WINDOW_AUTOSIZE);
	//cvNamedWindow("Video_im_bw", CV_WINDOW_AUTOSIZE);
	//cvNamedWindow("Video_SQ", CV_WINDOW_AUTOSIZE);
	/*
	keyboard();
	AllocConsole();
	stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(stealth, 1);
	findKeyboard = 0;
	*/
	IplImage* im_rgbOrig;
	IplImage* im_rgb;
	IplImage* im_gray;
	IplImage* im_bw;
	Mat outq, inq;
	im_rgb = cvQueryFrame(capture);
	//im_rgbOrig = cvLoadImage("123.jpg", 1);
	//im_rgb = cvCloneImage(im_rgbOrig);
	im_gray = cvCreateImage(cvGetSize(im_rgb), IPL_DEPTH_8U, 1);
	im_bw = cvCreateImage(cvGetSize(im_gray), IPL_DEPTH_8U, 1);
	int tres = 140;
	while (1)
	{
		if (capture == NULL)continue;

		im_rgbOrig = cvQueryFrame(capture);
		//im_rgb = cvLoadImage("123.jpg", 1);

		if (!im_rgb)
		{
			printf("Camera not found.Check your camera connection");
			break;
		}
		im_rgb = cvCloneImage(im_rgbOrig);
		im_gray = cvCreateImage(cvGetSize(im_rgb), IPL_DEPTH_8U, 1);
		im_bw = cvCreateImage(cvGetSize(im_gray), IPL_DEPTH_8U, 1);
		//im_ttt = cvCreateImage(cvGetSize(im_gray), IPL_DEPTH_8U, 1);

		cvWaitKey(20);
		frame = frame + 1;
		tip_x = -10;
		tip_y = -10;
		//findKeyboard = 0;
		cvCvtColor(im_rgb, im_gray, CV_RGB2GRAY);
		cvThreshold(im_gray, im_bw, tres, 255, CV_THRESH_BINARY);// | CV_THRESH_OTSU);
		
		cvLine(im_rgb, Keyboard_LU, Keyboard_RU, CV_RGB(255, 255, 0), 1, 8, 0);
		cvLine(im_rgb, Keyboard_LD, Keyboard_RD, CV_RGB(255, 255, 0), 1, 8, 0);
		cvLine(im_rgb, Keyboard_LU, Keyboard_LD, CV_RGB(255, 255, 0), 1, 8, 0);
		cvLine(im_rgb, Keyboard_RU, Keyboard_RD, CV_RGB(255, 255, 0), 1, 8, 0);

		//cvLine(im_rgb, cvPoint(keyboardX0, keyboardY0), cvPoint(keyboardX1, keyboardY0), CV_RGB(255, 255, 0), 4, 8, 0);
		//cvLine(im_rgb, cvPoint(keyboardX1, keyboardY0), cvPoint(keyboardX1, keyboardY1), CV_RGB(255, 255, 0), 4, 8, 0);
		//cvLine(im_rgb, cvPoint(keyboardX1, keyboardY1), cvPoint(keyboardX0, keyboardY1), CV_RGB(255, 255, 0), 4, 8, 0);
		//cvLine(im_rgb, cvPoint(keyboardX0, keyboardY1), cvPoint(keyboardX0, keyboardY0), CV_RGB(255, 255, 0), 4, 8, 0);

		/*for (i = 0; i <= keyboardXcount; i++)
		{
			cvLine(im_rgb, cvPoint((i * keyboardDX) + Keyboard_LU, keyboardY0), cvPoint((i * keyboardDX) + keyboardX0, keyboardY1), CV_RGB(255, 20, 0), 1, 8, 0);
		}*/

		float keyboardDyL = (Keyboard_LD.y - Keyboard_LU.y) / keyboardYcount;
		float keyboardDyR = (Keyboard_RD.y - Keyboard_RU.y) / keyboardYcount;
		float keyboardDdxL = (Keyboard_LD.x - Keyboard_LU.x) / keyboardYcount;
		float keyboardDdxR = (Keyboard_RD.x - Keyboard_RU.x) / keyboardYcount;

		float keyboardDxU = (Keyboard_RU.x - Keyboard_LU.x) / keyboardXcount;
		float keyboardDxD = (Keyboard_RD.x - Keyboard_LD.x) / keyboardXcount;
		float keyboardDdyU = (Keyboard_RU.y - Keyboard_LU.y) / keyboardXcount;
		float keyboardDdyD = (Keyboard_RD.y - Keyboard_LD.y) / keyboardXcount;


		for (i = 1; i < keyboardYcount; i++)
		{
			//cvLine(im_rgb, cvPoint((i * keyboardDdxL) + Keyboard_LU.x, (i * keyboardDyL) + Keyboard_LU.y), cvPoint((i * keyboardDdxR) + Keyboard_RU.x, (i * keyboardDyR) + Keyboard_RU.y), CV_RGB(255, 20, 0), 1, 8, 0);
		}
		
		for (i = 1; i < keyboardXcount; i++)
		{
			//cvLine(im_rgb, cvPoint((i * keyboardDxU) + Keyboard_LU.x, (i * keyboardDdyU) + Keyboard_LU.y), cvPoint((i * keyboardDxD) + Keyboard_LD.x, (i * keyboardDdyD) + Keyboard_LD.y), CV_RGB(255, 20, 0), 1, 8, 0);
		}
		int numX = 3;
		int numY = 0;		
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
			if (pen_pixels > 10 && pen_pixels < 100)
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
				//findKeyboard = 1;
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
				//cvCircle(im_rgb, cvPoint(tip_x, k), 1, CV_RGB(255, 255, 255), 2, 8, 0);
				tipT_x = init;
				tipT_y = k;
				//findKeyboard = 2;
			}

		}

		//cvCircle(im_rgb, cvPoint(tip_x, tip_y), 10, CV_RGB(0, 0, 255), 2, 8, 0);
		//cvCircle(im_rgb, cvPoint(tipT_x, tipT_y), 10, CV_RGB(0, 255, 0), 2, 8, 0);
		clickPOS_X = (tip_x + tipT_x) / 2;
		clickPOS_Y = (tip_y + tipT_y) / 2;
		//cvCircle(im_rgb, cvPoint(clickPOS_X, clickPOS_Y), 10, CV_RGB(0, 55, 0), 3, 8, 0);

		//clickMAS_X = (clickPOS_X - keyboardX0) / keyboardDX;
		//clickMAS_Y = (clickPOS_Y - keyboardY0) / keyboardDY;

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
				if (cntST2 > 2) {
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
			PointInPoly(cvPoint(clickPOS_X, clickPOS_Y));
			cvCircle(im_rgb, cvPoint(clickPOS_X, clickPOS_Y), 10, CV_RGB(255, 255, 255), 3, 8, 0);
			if ((clickMAS_X >= 0) && (clickMAS_X < 4) && (clickMAS_Y >= 0) && (clickMAS_Y < 5))
			{
				//keybd_event(key_value[3-clickMAS_X][4-clickMAS_Y], 0x45, 0, 0);
				//printf_s("CLICK! %d %d   %c\n", clickMAS_X, clickMAS_Y, (char)key_value[clickMAS_X][clickMAS_Y]);
				//PointInPoly(cvPoint(i, j));
				//cvCircle(im_rgb, cvPoint(clickPOS_X, clickPOS_Y), 10, CV_RGB(255, 255, 255), 3, 8, 0);
			}
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
		
		Mat dst, cdst, cdstP;
		if (findKeyboard == 0)
		{/*
			//Mat img = cvarrToMat(im_rgb);
			

			// Loads an image
			Mat src = cvarrToMat(im_rgbOrig);
			// Check if image is loaded fine

			// Edge detection
			Canny(src, dst, 50, 150, 5);
			// Copy edges to the images that will display the results in BGR
			cvtColor(dst, cdst, COLOR_GRAY2BGR);
			cdstP = cdst.clone();
			// Standard Hough Line Transform

			*/
			Mat img = cvarrToMat(im_rgbOrig);
			Mat gray, canny, RBGimg;

			//cvtColor(img, gray, CV_BGR2GRAY);
			gray = cvarrToMat(im_gray);
			Canny(gray, canny, 100, 200, 3);
			//imshow("canny", canny); 
			//imwrite("canny.jpg", canny);

			vector<Vec4i> lines;
			// Требуется изображение в оттенках серого, контейнер Vec4i
			HoughLinesP(canny, lines, 1, CV_PI / 180, 10, 20, 10);

			//printf("lines.size() %d \n", lines.size());
			// Draw the lines
			vector<Vec4i> linesHORZ;
			vector<Vec4i> linesVERT;
			vector<Vec2i> PointsCross;

			vector<int> linesHORZ_n;
			vector<int> linesVERT_n;
			for (size_t i = 0; i < lines.size(); i++)
			{
				float b=2;
				int dx = (lines[i][2] - lines[i][0]);

				if (dx != 0)
				{
					b = (lines[i][3] - lines[i][1]) / (dx);
				}

				Point pt1(lines[i][0], lines[i][1]);
				Point pt2(lines[i][2], lines[i][3]);


				if ((b > 1)|| (b < -1))cvLine(im_rgb, pt1, pt2, CV_RGB(0, 255, 0), 1, 8, 0);
				else  cvLine(im_rgb, pt1, pt2, CV_RGB(0, 0, 255), 1, 8, 0);

				if ((b > 1) || (b < -1))linesHORZ.push_back(lines[i]);
				else linesVERT.push_back(lines[i]);

			}
			int i = 0;


			for (Vec4i lineHor : linesHORZ)
			{
				for (Vec4i lineVert : linesVERT)
				{
					PointsCross.push_back(cross(lineHor, lineVert));
				}
			}

			for (Vec2i PointVH : PointsCross)cvCircle(im_rgb, cvPoint(PointVH[0], PointVH[1]), 2, CV_RGB(255, 255, 0), 2, 8, 0);
			

			int hN = 0;
			int cN = 0;

			int windowHeight = 15; //px
			int currLinesCount = 0;
			vector <int> lineCountMap;

			int maxY = 0, minY=1000;
			int maxX = 0, minX = 1000;


			Keyboard_LU.x = 1000;
			Keyboard_LD.x = 1000;
			Keyboard_RU.x = 0;
			Keyboard_RD.x = 0;


			for (Vec2i PCross : PointsCross)
			{
				//if ((lineH > maxY) && (lineH < cvGetSize(im_rgb).height - 100)) maxY = lineH;
				if (PCross[1] > maxY) maxY = PCross[1];
				if ((PCross[1] < minY) && (PCross[1] > 50)) minY = PCross[1];

				if ((PCross[0] > maxX) && (PCross[0] < cvGetSize(im_rgb).width - 50)) maxX = PCross[0];
				if ((PCross[0] < minX) && (PCross[0] > 50)) minX = PCross[0];
			}

			for (Vec2i PCross : PointsCross)
			{
				if ( (PCross[0] > 50) && (PCross[0] < cvGetSize(im_rgb).width - 50) && (PCross[1] > 50) && (PCross[1] < cvGetSize(im_rgb).height - 50))
				{
					if (PCross[1] <= minY + 50)
					{
						if (PCross[0] < Keyboard_LU.x)Keyboard_LU = PCross;
						if (PCross[0] > Keyboard_RU.x)Keyboard_RU = PCross;
					}
					if (PCross[1] >= maxY - 50)
					{
						if (PCross[0] < Keyboard_LD.x)Keyboard_LD = PCross;
						if (PCross[0] > Keyboard_RD.x)Keyboard_RD = PCross;
					}
				}
			}

			cvCircle(im_rgb, Keyboard_LU, 2, CV_RGB(255, 0, 0), 2, 8, 0);
			cvCircle(im_rgb, Keyboard_RU, 2, CV_RGB(0, 255, 0), 2, 8, 0);
			cvCircle(im_rgb, Keyboard_LD, 2, CV_RGB(0, 0, 255), 2, 8, 0);
			cvCircle(im_rgb, Keyboard_RD, 2, CV_RGB(150, 150, 250), 2, 8, 0);


			/*
			cvCircle(im_bw, cvPoint(minX, maxY), 2, CV_RGB(0, 150,250), 2, 8, 0);
			cvCircle(im_bw, cvPoint(minX, minY), 2, CV_RGB(0, 150, 250), 2, 8, 0);
			cvCircle(im_bw, cvPoint(maxX, maxY), 2, CV_RGB(0, 150, 250), 2, 8, 0);
			cvCircle(im_bw, cvPoint(maxX, maxY), 2, CV_RGB(0, 150, 250), 2, 8, 0);
			*/
			keyboardX0 = minX-50, keyboardX1 = maxX+50, keyboardY0 = minY-50, keyboardY1 = maxY+50;
			
			findKeyboard = 1;

		}
		
		inq = cvarrToMat(im_rgb);
		rotate(inq, outq, 1);
		imshow("Video", outq);
		//cvShowImage("Video", im_rgb);
		//cvShowImage("Video_im_gray", im_gray);
		//cvShowImage("Video_im_bw", im_bw);
		//cvShowImage("Video_SQ", im_ttt);

		c = cvWaitKey(1);
		if (c == 27)
			break;
		if (c == 'c')
		{
			findKeyboard = 0;
			//printf("findKeyboard = 0; \n", tres);
		}
		if (c == 'w')
		{
			tres += 5;
			printf("tres = %d \n", tres);
		}
		if (c == 's')
		{
			tres -= 5;
			printf("tres = %d \n", tres);
		}


	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("Video");
	//cvDestroyWindow("Video1");
}

Vec2i cross(Vec2i LU, Vec2i RU, Vec2i LD, Vec2i RD, int cX, int cY) {
	Vec2i  r;
	return r;
}


Vec2i cross(Vec4i v1, Vec4i v2) {
	float x1 = v1[0];float y1 = v1[1]; float x2 = v1[2]; float y2 = v1[3]; 
	float x3 = v2[0]; float y3 = v2[1]; float x4 = v2[2]; float y4 = v2[3];
	float n;
	int dx = 5; int dy = 5;
	Vec2i  r;
	r[0] = 0;
	r[1] = 0;

	if (y2 - y1 != 0) {  // a(y)
		float q = (x2 - x1) / (y1 - y2);
		float sn = (x3 - x4) + (y3 - y4) * q; if (!sn) { return 0; }  // c(x) + c(y)*q
		float fn = (x3 - x1) + (y3 - y1) * q;   // b(x) + b(y)*q
		n = fn / sn;
	}
	else {
		if (!(y3 - y4)) { return r; }  // b(y)
		n = (y3 - y1) / (y3 - y4);   // c(y)/b(y)
	}
	r[0] = x3 + (x4 - x3) * n;  // x3 + (-b(x))*n
	r[1] = y3 + (y4 - y3) * n;  // y3 +(-b(y))*n

	if (!((r[0] > x1 - dx) && (r[0] < x2 + dx) || (r[0] > x2 - dx) && (r[0] < x1 + dx))) { r[0] = 0; r[1] = 0;}
	if(!((r[1] > y1 - dy) && (r[1] < y2 + dy) || (r[1] > y2 - dy) && (r[1] < y1 + dy))) { r[0] = 0; r[1] = 0; }

	return r;
}


int PointInPoly(Point click)
{
	float keyboardDyL = (Keyboard_LD.y - Keyboard_LU.y) / keyboardYcount;
	float keyboardDyR = (Keyboard_RD.y - Keyboard_RU.y) / keyboardYcount;
	float keyboardDdxL = (Keyboard_LD.x - Keyboard_LU.x) / keyboardYcount;
	float keyboardDdxR = (Keyboard_RD.x - Keyboard_RU.x) / keyboardYcount;

	float keyboardDxU = (Keyboard_RU.x - Keyboard_LU.x) / keyboardXcount;
	float keyboardDxD = (Keyboard_RD.x - Keyboard_LD.x) / keyboardXcount;
	float keyboardDdyU = (Keyboard_RU.y - Keyboard_LU.y) / keyboardXcount;
	float keyboardDdyD = (Keyboard_RD.y - Keyboard_LD.y) / keyboardXcount;
	int numX = 1;
	int numY = 2;
	//cvCircle(im_rgb, cvPoint(((numY + 0) * keyboardDdxL) + ((numX + 0) * keyboardDxU) + Keyboard_LU.x, ((numY + 0) * keyboardDyL) + ((numX + 0) * keyboardDdyU) + Keyboard_LU.y), 2, CV_RGB(255, 0, 0), 2, 8, 0);
	//cvCircle(im_rgb, cvPoint(((numY + 0) * keyboardDdxL) + ((numX + 1) * keyboardDxU) + Keyboard_LU.x, ((numY + 0) * keyboardDyL) + ((numX + 1) * keyboardDdyU) + Keyboard_LU.y), 2, CV_RGB(255, 0, 0), 2, 8, 0);
	//cvCircle(im_rgb, cvPoint(((numY + 1) * keyboardDdxL) + ((numX + 1) * keyboardDxU) + Keyboard_LU.x, ((numY + 1) * keyboardDyL) + ((numX + 1) * keyboardDdyU) + Keyboard_LU.y), 2, CV_RGB(255, 0, 0), 2, 8, 0);
	//cvCircle(im_rgb, cvPoint(((numY + 1) * keyboardDdxL) + ((numX + 0) * keyboardDxU) + Keyboard_LU.x, ((numY + 1) * keyboardDyL) + ((numX + 0) * keyboardDdyU) + Keyboard_LU.y), 2, CV_RGB(255, 0, 0), 2, 8, 0);
	
	Vec2i h;
	h[1] = 1;
	Vec2i sq[4];

	for(int numX =0; numX < keyboardXcount; numX++)
		for (int numY = 0;  numY < keyboardYcount; numY++)
		{
			sq[0][0] = ((numY + 0) * keyboardDdxL) + ((numX + 0) * keyboardDxU) + Keyboard_LU.x;
			sq[0][1] = ((numY + 0) * keyboardDyL) + ((numX + 0) * keyboardDdyU) + Keyboard_LU.y;
			sq[1][0] = ((numY + 0) * keyboardDdxL) + ((numX + 1) * keyboardDxU) + Keyboard_LU.x;
			sq[1][1] = ((numY + 0) * keyboardDyL) + ((numX + 1) * keyboardDdyU) + Keyboard_LU.y;
			sq[2][0] = ((numY + 1) * keyboardDdxL) + ((numX + 1) * keyboardDxU) + Keyboard_LU.x;
			sq[2][1] = ((numY + 1) * keyboardDyL) + ((numX + 1) * keyboardDdyU) + Keyboard_LU.y;
			sq[3][0] = ((numY + 1) * keyboardDdxL) + ((numX + 0) * keyboardDxU) + Keyboard_LU.x;
			sq[3][1] = ((numY + 1) * keyboardDyL) + ((numX + 0) * keyboardDdyU) + Keyboard_LU.y;


			int b = 1, i;
			int n = 4;
			for (i = 0; i < n - 1; i++) {
				if ((click.y <= sq[i][1]) == (click.y > sq[i + 1][1])) {
					if ((click.x - sq[i][0]) <
						(click.y - sq[i][1]) * (sq[i + 1][0] - sq[i][0]) / (sq[i + 1][1] - sq[i][1])) b = !b;
				};
			};
			if ((click.y <= sq[n - 1][1]) == (click.y > sq[0][1])) {
				if ((click.x - sq[n - 1][0]) <
					(click.y - sq[n - 1][0]) * (sq[0][0] - sq[n - 1][0]) / (sq[0][1] - sq[n - 1][1])) b = !b;
			};

			//return !b;

			if (!b)
			{
				printf_s("CLICK!    %c\n",  (char)key_value[keyboardXcount -numX-1][keyboardYcount -numY-1]);
				keybd_event(key_value[keyboardXcount - numX - 1][keyboardYcount - numY - 1], 0x45, 0, 0);
				return 1;
			}
		}
};
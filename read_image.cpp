#include "stdafx.h"
#include "read_image.h"
#include "E:\opencv\opencv\build\include\opencv2\opencv.hpp"
#include "E:\opencv\opencv\build\include\opencv2\core\core.hpp"
#include "E:\opencv\opencv\build\include\opencv2\highgui\highgui.hpp"
#include "E:\opencv\opencv\build\include\opencv2\imgproc\imgproc.hpp"
#include <windows.h>
#include <iostream>

#include <stdlib.h>
#include <time.h>
#include <string>


using namespace cv;
using namespace std;

string get_current_time()
{
	struct tm t;   //tm结构指针
	time_t now;  //声明time_t类型变量
	time(&now);      //获取系统日期和时间
	localtime_s(&t, &now);   //获取当地日期和时间

	char szResult[20] = "\0";
	sprintf_s(szResult, 20, "%.4d-%.2d-%.2d-%.2d-%.2d-%.2d", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec); 

	return szResult;
}

void save_videoFile()
{
	string outputVideoPath = "F:\\图片采集\\video.mpeg"; // 文件的保存位置

	VideoCapture capture(1);//0打开的是自带的摄像头，1 打开外接的相机

	double rate = 30.0;//视频的帧率

	Size videoSize(640, 480);//设定只采集640*480的图片

	VideoWriter writer;
	writer.open(outputVideoPath, CAP_OPENCV_MJPEG, rate, videoSize);

	Mat frame;

	while (capture.isOpened())
	{
		capture >> frame;
		writer << frame;

		imshow("video", frame);

		if (waitKey(25) == 27)//键盘摁下esc退出播放
			break;
	}
	writer.release();
}

void Video_To_Image(string filename)
{
	cv::VideoCapture capture(filename);
	if (!capture.isOpened())
	{
		cout << "open video error";
	}
	int frame_number = capture.get(CAP_PROP_FRAME_COUNT);//总帧数  

	int num = 0;//统计帧数  
	cv::Mat img;
	string img_name;
	char image_name[100];

	string time;

	while (true)
	{
		time = get_current_time();//得到当前时间

		cv::Mat frame;
		//从视频中读取一帧  
		bool bSuccess = capture.read(frame);
		if (!bSuccess)
		{
			break;
		}

		sprintf_s(image_name, "%s%d%s%s", "F:\\图片采集\\pics\\", ++num, time.c_str(), ".jpg");
		img_name = image_name;
		imwrite(img_name, frame);//保存每一帧图片  

		if (num == frame_number)
			return ;
	}
}





int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	string folder_pics;//图片文件夹路径
	folder_pics = "F:\\图片采集\\pics\*.jpg";

	string folder_videos;//视频文件夹路径
	folder_videos = "F:\\图片采集\\*.mpeg";


	//每次保存之前，清空视频和图片文件
	system("del F:\\图片采集\\pics\\*.jpg");
	system("del F:\\图片采集\\*.mpeg");

	save_videoFile();//保存视频文件

	string local_FileName = "F:\\图片采集\\video.mpeg";

	Video_To_Image(local_FileName); //视频转图片  


	return 0;
}


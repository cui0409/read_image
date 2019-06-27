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
	struct tm t;   //tm�ṹָ��
	time_t now;  //����time_t���ͱ���
	time(&now);      //��ȡϵͳ���ں�ʱ��
	localtime_s(&t, &now);   //��ȡ�������ں�ʱ��

	char szResult[20] = "\0";
	sprintf_s(szResult, 20, "%.4d-%.2d-%.2d-%.2d-%.2d-%.2d", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec); 

	return szResult;
}

void save_videoFile()
{
	string outputVideoPath = "F:\\ͼƬ�ɼ�\\video.mpeg"; // �ļ��ı���λ��

	VideoCapture capture(1);//0�򿪵����Դ�������ͷ��1 ����ӵ����

	double rate = 30.0;//��Ƶ��֡��

	Size videoSize(640, 480);//�趨ֻ�ɼ�640*480��ͼƬ

	VideoWriter writer;
	writer.open(outputVideoPath, CAP_OPENCV_MJPEG, rate, videoSize);

	Mat frame;

	while (capture.isOpened())
	{
		capture >> frame;
		writer << frame;

		imshow("video", frame);

		if (waitKey(25) == 27)//��������esc�˳�����
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
	int frame_number = capture.get(CAP_PROP_FRAME_COUNT);//��֡��  

	int num = 0;//ͳ��֡��  
	cv::Mat img;
	string img_name;
	char image_name[100];

	string time;

	while (true)
	{
		time = get_current_time();//�õ���ǰʱ��

		cv::Mat frame;
		//����Ƶ�ж�ȡһ֡  
		bool bSuccess = capture.read(frame);
		if (!bSuccess)
		{
			break;
		}

		sprintf_s(image_name, "%s%d%s%s", "F:\\ͼƬ�ɼ�\\pics\\", ++num, time.c_str(), ".jpg");
		img_name = image_name;
		imwrite(img_name, frame);//����ÿһ֡ͼƬ  

		if (num == frame_number)
			return ;
	}
}





int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	string folder_pics;//ͼƬ�ļ���·��
	folder_pics = "F:\\ͼƬ�ɼ�\\pics\*.jpg";

	string folder_videos;//��Ƶ�ļ���·��
	folder_videos = "F:\\ͼƬ�ɼ�\\*.mpeg";


	//ÿ�α���֮ǰ�������Ƶ��ͼƬ�ļ�
	system("del F:\\ͼƬ�ɼ�\\pics\\*.jpg");
	system("del F:\\ͼƬ�ɼ�\\*.mpeg");

	save_videoFile();//������Ƶ�ļ�

	string local_FileName = "F:\\ͼƬ�ɼ�\\video.mpeg";

	Video_To_Image(local_FileName); //��ƵתͼƬ  


	return 0;
}


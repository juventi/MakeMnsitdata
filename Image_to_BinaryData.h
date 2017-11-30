#pragma once
#undef UNICODE
#ifndef IMAGE_TO_BINARYDATA_H_
#define IMAGE_TO_BINARYDATA_H_
#include <iostream>
#include <vector>

//#include <opencv2\opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#pragma comment( lib, "opencv_core330.lib" )  
#pragma comment( lib, "opencv_highgui330.lib" )
#pragma comment( lib, "opencv_imgcodecs330.lib")
#pragma comment( lib, "opencv_imgproc330.lib")
using namespace std;
using namespace cv;


class Image2BinaryData
{
public:
	int Height;
	int Width;
public:
	Image2BinaryData(int x, int y) :Height(x), Width(y) {} 
	~Image2BinaryData() {}

	void ReverseInt(ofstream &file, int i);
	vector<String> Image2BinaryData::getFileLists(string file_folder);		//获取文件夹下的图片名称
	string getFileName(string &filename);					//从文件的绝对路径当中得到文件名

	void ReadImage(string filefolder, vector<String> &img_Lists, vector<int> &img_Labels, vector<cv::Mat> &ImagesMat);
	void Image2BinaryFile(string filefolder, vector<cv::Mat> &ImagesMat, vector<int> & img_Labels);
	void Label2BinaryFile(string filefolder,vector<int> &img_Labels);
};





#endif // !IMAGE_TO_BINARYDATA_H_
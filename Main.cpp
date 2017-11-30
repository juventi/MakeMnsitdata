#include "Image_to_BinaryData.h"
#include <time.h>
#include <stdlib.h>

#pragma comment( lib, "opencv_core330.lib" )  
#pragma comment( lib, "opencv_highgui330.lib" )
#pragma comment( lib, "opencv_imgproc330.lib")
#pragma comment( lib, "opencv_imgcodecs330.lib")

#if 1

int main()
{
	Image2BinaryData IBD(32,32);											//设置图片大小(Height,Width)
	
	/*------------生成训练集文件--------------------------*/   //G:\Train_data\Train_ori
	printf("----------生成训练集文件-------------\n");  //D:\Chi_Charc\Train_ori   G:\IDcard\2222\2222
	string trainfilefolder = "G:/IDcard/2222/2222/";		//训练图片文件路径D:\\Chi_Charc\\Train_ori\\ D:\IdentityCard\自制样本\IDsamplesnn
	vector<String> trainfileLists = IBD.getFileLists(trainfilefolder);				//获得文件名列表

	const int train_size_list = trainfileLists.size();
	cout << "Images Number: " << train_size_list << endl;							//输出文件个数

	string trainimagebinfilepath = "G:\\train-images-idx3-ubyte";		//训练图片转换保存路径
	string trainlabelbinfilepath = "G:\\train-labels-idx1-ubyte";		//训练标签转换保存路径
	vector<cv::Mat> TrainImagesMat;															//用来存储训练图片像素值
	vector<int> train_image_labels(train_size_list);										//用来存储训练类标签列表
	IBD.ReadImage(trainfilefolder, trainfileLists, train_image_labels, TrainImagesMat);		//读取训练图片
	IBD.Image2BinaryFile(trainimagebinfilepath, TrainImagesMat, train_image_labels);		//训练图片转二进制文件
	IBD.Label2BinaryFile(trainlabelbinfilepath, train_image_labels);						//训练标签转二进制文件

	/*------------生成测试集文件--------------------------*/
	//printf("\n\n----------生成测试集文件-------------\n");
	//string testfilefolder = "C:\\Users\\lyf\\Desktop\\mnist\\test_images";		//测试图片文件路径
	//vector<string> testfileLists = IBD.getFileLists(testfilefolder);			//获得文件名列表
	//
	//const int test_size_list = testfileLists.size();
	//cout << "Images Number: " << test_size_list << endl;									//输出文件个数
	//string testimagebinfilepath = "C:\\Users\\lyf\\Desktop\\t10k-images-idx3-ubyte";		//测试图片转换保存路径
	//string testlabelbinfilepath  = "C:\\Users\\lyf\\Desktop\\t10k-labels-idx1-ubyte";		//测试标签转换保存路径
	//vector<cv::Mat> TestImagesMat;															//用来存储测试图片像素值
	//vector<int> test_image_labels(test_size_list);											//用来存储测试类标签列表
	//IBD.ReadImage(testfilefolder, testfileLists, test_image_labels, TestImagesMat);			//读取测试图片
	//IBD.Image2BinaryFile(testimagebinfilepath, TestImagesMat, test_image_labels);			//测试图片转二进制文件
	//IBD.Label2BinaryFile(testlabelbinfilepath, test_image_labels);							//测试标签转二进制文件
	system("pause");
	return 0;
}


#endif


int GetFileNameWithExt(const char* szFilePath, char* szFileName, int nLen)
{
	memset(szFileName, 0, nLen);
	const char* p1 = strrchr(szFilePath, '\\');
	//const char* p2 = strrchr(szFilePath, '.');
	if (p1 == NULL)
	{
		return -1;
	}

	int nCount = strlen(szFilePath) - (p1 - szFilePath + 1);

	if (nCount > nLen - 1)
	{
		return -1;
	}

	memcpy(szFileName, p1 + 1, nCount);
	return 0;
}

int GetFileNameWithoutExt(const char* szFilePath, char* szFileName, int nLen)
{
	memset(szFileName, 0, nLen);
	const char* p1 = strrchr(szFilePath, '\\');
	const char* p2 = strrchr(szFilePath, '.');
	if (p1 == NULL || p2 == NULL || p1 > p2)
	{
		return -1;
	}

	int nCount = p2 - p1 - 1;
	if (nCount > nLen - 1)
	{
		return -1;
	}

	memcpy(szFileName, p1 + 1, nCount);
	return 0;

}

bool morethan(vector<Point> &vt1, vector<Point> &vt2)
{
	return boundingRect(vt1).x < boundingRect(vt2).x;
}

#if 0

string int2str(int val)
{
	char buf[64] = "";
	_snprintf(buf, sizeof(buf) - 1, "%d", val);
	return buf;
}

int str2int(const string &val)
{
	return atoi(val.c_str());
}


#endif
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
	Image2BinaryData IBD(32,32);											//����ͼƬ��С(Height,Width)
	
	/*------------����ѵ�����ļ�--------------------------*/   //G:\Train_data\Train_ori
	printf("----------����ѵ�����ļ�-------------\n");  //D:\Chi_Charc\Train_ori   G:\IDcard\2222\2222
	string trainfilefolder = "G:/IDcard/2222/2222/";		//ѵ��ͼƬ�ļ�·��D:\\Chi_Charc\\Train_ori\\ D:\IdentityCard\��������\IDsamplesnn
	vector<String> trainfileLists = IBD.getFileLists(trainfilefolder);				//����ļ����б�

	const int train_size_list = trainfileLists.size();
	cout << "Images Number: " << train_size_list << endl;							//����ļ�����

	string trainimagebinfilepath = "G:\\train-images-idx3-ubyte";		//ѵ��ͼƬת������·��
	string trainlabelbinfilepath = "G:\\train-labels-idx1-ubyte";		//ѵ����ǩת������·��
	vector<cv::Mat> TrainImagesMat;															//�����洢ѵ��ͼƬ����ֵ
	vector<int> train_image_labels(train_size_list);										//�����洢ѵ�����ǩ�б�
	IBD.ReadImage(trainfilefolder, trainfileLists, train_image_labels, TrainImagesMat);		//��ȡѵ��ͼƬ
	IBD.Image2BinaryFile(trainimagebinfilepath, TrainImagesMat, train_image_labels);		//ѵ��ͼƬת�������ļ�
	IBD.Label2BinaryFile(trainlabelbinfilepath, train_image_labels);						//ѵ����ǩת�������ļ�

	/*------------���ɲ��Լ��ļ�--------------------------*/
	//printf("\n\n----------���ɲ��Լ��ļ�-------------\n");
	//string testfilefolder = "C:\\Users\\lyf\\Desktop\\mnist\\test_images";		//����ͼƬ�ļ�·��
	//vector<string> testfileLists = IBD.getFileLists(testfilefolder);			//����ļ����б�
	//
	//const int test_size_list = testfileLists.size();
	//cout << "Images Number: " << test_size_list << endl;									//����ļ�����
	//string testimagebinfilepath = "C:\\Users\\lyf\\Desktop\\t10k-images-idx3-ubyte";		//����ͼƬת������·��
	//string testlabelbinfilepath  = "C:\\Users\\lyf\\Desktop\\t10k-labels-idx1-ubyte";		//���Ա�ǩת������·��
	//vector<cv::Mat> TestImagesMat;															//�����洢����ͼƬ����ֵ
	//vector<int> test_image_labels(test_size_list);											//�����洢�������ǩ�б�
	//IBD.ReadImage(testfilefolder, testfileLists, test_image_labels, TestImagesMat);			//��ȡ����ͼƬ
	//IBD.Image2BinaryFile(testimagebinfilepath, TestImagesMat, test_image_labels);			//����ͼƬת�������ļ�
	//IBD.Label2BinaryFile(testlabelbinfilepath, test_image_labels);							//���Ա�ǩת�������ļ�
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
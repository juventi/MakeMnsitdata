#include "Image_to_BinaryData.h"
//#include <atlfile.h>
//#include <cstdlib>
#include <fstream>
#include <algorithm>


#pragma comment( lib, "opencv_core330.lib" )  
#pragma comment( lib, "opencv_highgui330.lib" )
#pragma comment( lib, "opencv_imgproc330.lib")
#pragma comment( lib, "opencv_imgcodecs330.lib")


using namespace std;
using namespace cv;


int GetFileNameWithoutExt1(const char* szFilePath, char* szFileName, int nLen)
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

void Image2BinaryData::ReverseInt(ofstream &file, int i)
{
	uchar ch1 = (uchar)(i >> 24);
	uchar ch2 = (uchar)((i << 8) >> 24);
	uchar ch3 = (uchar)((i << 16) >> 24);
	uchar ch4 = (uchar)((i << 24) >> 24);
	file.write((char*)&ch1, sizeof(ch4));
	file.write((char*)&ch2, sizeof(ch3));
	file.write((char*)&ch3, sizeof(ch2));
	file.write((char*)&ch4, sizeof(ch1));
}

vector<String> Image2BinaryData::getFileLists(string file_folder)
{
	std::vector<cv::String> filenames;
	cv::String folder = file_folder;
	cv::glob(folder, filenames, false);

	return filenames;
}

/*
从文件的绝对路径当中得到文件名
例如："C:\\Users\\lyf\\Desktop\\test.txt"，返回"test.txt"
*/
string Image2BinaryData::getFileName(string & filename)
{
	/*
	param
	filename:		文件的绝对路径
	*/
	int iBeginIndex = filename.find_last_of("\\") + 1;
	int iEndIndex = filename.length();

	return filename.substr(iBeginIndex, iEndIndex - iBeginIndex);

	cout << "Done!" << endl;
}

void read_label_file(std::string label_file, std::vector<std::string>& vtstr)
{
	//cout << "here" << endl;
	std::string label;
	std::ifstream in(label_file);
	char line[20] = { 0 };
	while (in.getline(line, sizeof(line)))
	{
		std::stringstream word(line);
		word >> label; 
		//cout << label << endl;
		vtstr.push_back(label);
	}

	in.close();

	std::cout << "read numbers" << vtstr.size() << std::endl;
}


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

void Image2BinaryData::ReadImage(string filefolder, vector<String>& img_Lists, vector<int>& img_Labels, vector<cv::Mat> &ImagesMat)
{
	string labelfile = "use.txt";
	vector<string> vtstr;
	read_label_file(labelfile, vtstr);
	cout << vtstr.size() << endl;
	
	const int size_list = img_Lists.size();
	
	for (int i = 0; i < size_list; ++i) {
		string names = img_Lists[i];
		char filename[100];
		GetFileNameWithoutExt1(names.c_str(), filename, 100);
		string name(filename);
		string::size_type idx1 = name.find("_");
		string label = name.substr(0, idx1);

		//cout << label << endl;

		if (label == "x")
		{
			label = "10";
		}
		
		vector<string>::iterator result = find(vtstr.begin(), vtstr.end(), label);
		
		int num_label = distance(vtstr.begin(), result);

		//cout << "label:" << num_label << endl;

		//int num_label = atoi(label.c_str());
		
		//string curPath = filefolder + "\\" + img_Lists[i];
		//cout << curPath << endl;
		Mat image = imread(img_Lists[i], 0);
		ImagesMat.push_back(image);
		//char label = img_Lists[i][0];

		//imshow("src", image);
		//waitKey();
		
		img_Labels[i] = str2int(label);  //num_label;   // //  // ;str2int(label);
		
		//cout << "label:" << img_Labels[i] << endl;
		printf("%d\n",img_Labels[i]);
		//printf("正在读取图片，请稍等: %.2lf%%\r", i*100.0 / (size_list - 1));
	}
	printf("\n图片读取完毕!\n\n");
}

void Image2BinaryData::Image2BinaryFile(string filefolder, vector<cv::Mat>& ImagesMat, vector<int>& img_Labels)
{
	ofstream file(filefolder, ios::binary);
	int idx = filefolder.find_last_of("\\") + 1;


	string subName = filefolder.substr(idx);
	if (file.is_open()) {
		cout << subName << "文件创建成功." << endl;

		int magic_number = 2051;
		int number_of_images = img_Labels.size();
		int n_rows = Height;
		int n_cols = Width;
		ReverseInt(file, magic_number);
		ReverseInt(file, number_of_images);
		ReverseInt(file, n_rows);
		ReverseInt(file, n_cols);

		cout << "需要转换的图片数为:  " << ImagesMat.size() << endl;

		int nr = ImagesMat[0].rows;
		int nl = ImagesMat[0].cols*ImagesMat[0].channels();
		for (int i = 0; i < ImagesMat.size(); ++i) {

			for (int k = 0; k < nr; k++)
			{
				// 每一行图像的指针
				const uchar* inData = ImagesMat[i].ptr<uchar>(k);
				for (int l = 0; l < nl; l++)
				{
					uchar tmp = inData[l];
					file.write((char*)&tmp, sizeof(tmp));
				}
			}

			//for (int r = 0; r < n_rows; ++r) {
			//	for (int c = 0; c < n_cols; ++c) {
			//		//cout << "here" << endl;
			//		//imshow("src", ImagesMat[i]);
			//		//waitKey();
			//		uchar tmp = ImagesMat[i].at<uchar>(r, c);
			//		//cout << tmp << endl;

			//		file.write((char*)&tmp, sizeof(tmp));

			//		//cout << tmp << endl;
			//	}
			printf("图片正在转换，请稍等......%.2lf%%\r", i*100.0 / (ImagesMat.size() - 1));
		}
		printf("\n******转换完成!******\n\n");
	}
	else
		cout << subName << "文件创建失败." << endl << endl;
	if (file.is_open())
		file.close();
	return;
}

void Image2BinaryData::Label2BinaryFile(string filefolder, vector<int>& img_Labels)
{
	ofstream file(filefolder, ios::binary);
	int idx = filefolder.find_last_of("\\") + 1;
	string subName = filefolder.substr(idx);


	if (file.is_open()) {
		cout << subName << "文件创建成功." << endl;

		int magic_number = 2049;
		int number_of_images = img_Labels.size();
		ReverseInt(file, magic_number);
		ReverseInt(file, number_of_images);

		cout << "需要转换的标签数为: " << img_Labels.size() << endl;

		for (int i = 0; i < img_Labels.size(); ++i) {
			int tmp = (int)img_Labels[i];
			
			stringstream ss;
			ss << tmp;
			

			string s1 = ss.str();
			string tmp1;
			string tmp2;
			//cout << s1 << endl;
			//cout << s1.length() << endl;
			
			if (s1.length() > 2)
			{
				tmp1 = s1.substr(0, 2);
				tmp2 = s1.substr(2);
			}
			else
			{
				tmp1 = "0";
				tmp2 = s1;
			}
			
			
			stringstream ss1;
			ss1 << tmp1;
			int sv1;
			ss1 >> sv1;
			stringstream ss2;
			ss2 << tmp2;
			int sv2;
			ss2 >> sv2;
			
			//cout << tmp << ", " << sv1 << "," << sv2 << endl;

			char str1[10];
			itoa(sv1, str1, 10);

			char str2[10];
			itoa(sv2, str2, 10);

			char svv1 = sv1;
			char svv2 = sv2;
			char svv3 = s1.length();
			//cout << tmp << ", " << svv1 << "," << svv2 << endl;
			
			printf("%d, ", svv1);
			printf("%d, ", svv2);
			printf("%d, \n", svv3);

			file.write((char*)&svv1, sizeof(svv1));
			file.write((char*)&svv2, sizeof(svv2));
			file.write((char*)&svv3, sizeof(svv3));
			printf("标签正在转换，请稍等......%.2lf%%\r", i*100.0 / (img_Labels.size() - 1));
		}
		printf("\n******转换完成!******\n");
	}
	else
		cout << subName << "文件创建失败." << endl;
	if (file.is_open())
		file.close();
	return;
}


#include "xueming.h"

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#include "windows.h"

#include <iostream>
#include <cassert>
using namespace std;

int main(int argc, char** argv)
{
	WIN32_FIND_DATAA FileData;
	HANDLE hFind;

	hFind = FindFirstFileA((LPCSTR)"Imgs/*.jpg", &FileData);
	if (hFind == INVALID_HANDLE_VALUE) {
		printf("Invalid File Handle. GetLastError reports %d/n",
			GetLastError());
		return (0);
	}

	Saliency sal;
	vector<double> salmap(0);
	while (FindNextFileA(hFind, &FileData)) {
		cout << FileData.cFileName << endl;
		string name("Imgs/");
		name.append(FileData.cFileName);
		IplImage* img = cvLoadImage(name.c_str());
		if (!img) {
			cout << "failed to load image" << endl;
			break;
		}
		assert(img->nChannels == 3);

		vector<unsigned int >imgInput;
		vector<double> imgSal;
		//IplImage to vector
		for (int h = 0; h<img->height; h++) {
			unsigned char*p = (unsigned char*)img->imageData + h*img->widthStep;
			for (int w = 0; w<img->width; w++) {
				unsigned int t = 0;
				t += *p++;
				t <<= 8;
				t += *p++;
				t <<= 8;
				t += *p++;
				imgInput.push_back(t);
			}
		}
		sal.GetSaliencyMap(imgInput, img->width, img->height, imgSal);
		//vector to IplImage
		int index = 0;
		IplImage* imgout = cvCreateImage(cvGetSize(img), IPL_DEPTH_64F, 1);
		for (int h = 0; h<imgout->height; h++) {
			double*p = (double*)(imgout->imageData + h*imgout->widthStep);
			for (int w = 0; w<imgout->width; w++) {
				*p++ = imgSal[index++];
			}
		}

		name.append(".saliency.jpg");


		cvSaveImage(name.c_str(), imgout);
		cvReleaseImage(&img);
		cvReleaseImage(&imgout);
	}

	FindClose(&hFind);
	return 0;
}
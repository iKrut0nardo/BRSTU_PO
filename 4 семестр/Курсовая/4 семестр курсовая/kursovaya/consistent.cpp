#include <iostream>
#include <string>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <time.h>
#include <Windows.h>

using namespace std;
using namespace cv;

Mat ConvolutionOperationRobert(Mat& src);

int main(int argc, char** argv)
{
	system("color f0");
	string inputImageName;
	cout << "Enter the name of your input image:  ";
	cin >> inputImageName;

	string outputImageName;
	cout << "Enter the name of your output image:  ";
	cin >> outputImageName;
	unsigned int end_time = clock();
	Mat img = imread(inputImageName, IMREAD_GRAYSCALE);


	Mat output = ConvolutionOperationRobert(img);
	if (img.empty()) {
		cout << "Could not to read image: " << inputImageName << endl;
	}
	imwrite(outputImageName, output);
	cout << "Operation success! Time = " << end_time / 1000.0 << endl;
	cout << "File saved in project catalog" << endl;
	cout << "Whant to see the file?(Y/N)";
	char variant;
	cin >> variant;
	switch (variant) {
	case 'y':
		cout << "Open..." << endl;
		namedWindow(outputImageName, WINDOW_NORMAL);
		imshow(outputImageName, output);
		waitKey(0);
		break;
	case 'n':
		break;
	default:
		cout << "Invalid input" << endl;
		break;
	}
	return 0;
}
Mat ConvolutionOperationRobert(Mat& src)
{
	// Когда размер ядра 2x2, возьмите верхний левый угол в качестве источника
	Mat dst(src.rows, src.cols, src.type(), Scalar(0));
	if (src.channels() == 1)
		for (int i = 0; i < src.rows - 1; i++)
			for (int j = 0; j < src.cols - 1; j++)
				dst.at<uchar>(i, j) = abs(src.at<uchar>(i, j) - src.at<uchar>(i + 1, j + 1)) + abs(src.at<uchar>(i + 1, j) - src.at<uchar>(i, j + 1));

	return dst;
}



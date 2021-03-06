// histogram_comparison.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(int argc, char**argv)
{
	string source1 = "C:\\Users\\11235\\Pictures\\Camera Roll\\IMG_20170915_171544.jpg";
	string source2="C:\\Users\\11235\\Pictures\\Camera Roll\\IMG_20170915_171540.jpg";
	if (argc > 1) {
		source1 = argv[0];
		source2 = argv[1];
	}
	Mat src1 = imread(source1, IMREAD_COLOR);
	Mat src2 = imread(source2, IMREAD_COLOR);
	if (src1.empty() | src2.empty()) {
		return -1;
	}

	Mat g1, g2;
	cvtColor(src1, g1, COLOR_BGR2HSV);
	cvtColor(src2, g2, COLOR_BGR2HSV);

	//如果对量化设置为256，可以得到最高的匹配结果，但是如果往上加就不行了，往下减则会得到较小的匹配结果
	//关键还是在与cvtColor()所转化出来的色彩的量化，w是范围，h是幅值
	int hist_w = 256; int hist_h = 256; int hist_size[] = { hist_w,hist_h };
	//用来存储hist的图的大小
	float w[] = { 0,256 };float h[] = { 0,256 };
	const float* range[] = { w,h };

	MatND hist1,hist2;
	int channels[] = { 0,1 };
	calcHist(&g1, 1,channels, Mat(), hist1, 2,hist_size, range, true, false);
	//对其进行normalize，可以尽量防止不均匀？
	normalize(hist1, hist1, 0,1,NORM_MINMAX, -1, Mat());

	calcHist(&g2, 1, channels, Mat(), hist2, 2, hist_size, range, true, false);
	normalize(hist2, hist2, 0, 1, NORM_MINMAX, -1, Mat());

	double re=compareHist(hist1, hist2, 1);
	cout << re;
	system("pause");
	return 0;
}

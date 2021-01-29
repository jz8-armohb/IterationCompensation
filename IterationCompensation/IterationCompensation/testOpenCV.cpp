#include "declarations.h"


void testOpenCV() {
	Mat img = imread(".\\test_data\\test16.jpg");
	if (img.empty()) {
		cerr << "Failed to read the image.\n";
	}
	cvtColor(img, img, COLOR_BGR2GRAY);
	//img.convertTo(img, CV_64FC1);

	int height = img.rows;
	int width = img.cols;
	int ch = img.channels();
	cout << "channel: " << ch << endl;

	//for (int h = 0; h < height; h++) {
	//	uchar* currentRow = img.ptr<uchar>(h);
	//	uchar* flagRow = currentRow;

	//	for (int w = 0; w < width; w++) {
	//		double value = *currentRow;
	//		printf("%lf\t", value);
	//		currentRow++;
	//	}
	//}

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			double pixel = (double)img.at<uchar>(h, w);
			cout << pixel << "\t";
		}
		cout << endl;
	}

}
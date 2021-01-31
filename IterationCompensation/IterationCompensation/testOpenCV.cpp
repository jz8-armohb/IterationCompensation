#include "declarations.h"


void testOpenCV() {
	Mat img = imread(".\\calibration_img_cam\\IMG_0008.jpg");
	if (img.empty()) {
		cerr << "Failed to read the image.\n";
	}
	cvtColor(img, img, COLOR_BGR2GRAY);

	int height = img.rows;
	int width = img.cols;
	int ch = img.channels();
	cout << "channel: " << ch << endl;


	for (int h = 0; h < 1; h++) {
		for (int w = 0; w < 10; w++) {
			uchar pixel = img.at<uchar>(h, w);
			cout << (int)pixel << "\t";
		}
		cout << endl;
	}

}
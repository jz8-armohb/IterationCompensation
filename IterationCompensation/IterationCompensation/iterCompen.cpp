#include "declarations.h"


//void iterComepn(string dirP, string dirC, string dirPC, 
//	string filenameCam, string filenamePrj,
//	string filenameCorPC, int numCompen, double lambda) {
void iterComepn(string dirP, string dirC, string dirPC,
	string filenameCam, string filenamePrj,
	string filenameCorPC, int numCompen, double lambda,
	double corPC[900][1440][2]) {

	/* Debug: check corPC */
	for (int i = 300; i < 900; i++) {
		for (int j = 480; j < 1440; j++) {
			if (abs(corPC[i][j][0]) >= 1.5e3 || abs(corPC[i][j][1]) >= 1.5e3) {
				printf("corPC[%d][%d][0] = %lf,\tcorPC[%d][%d][1] = %lf\n",
					i, j, corPC[i][j][0],
					i, j, corPC[i][j][1]);
			}
		}
	}

	
	Mat imPrj = imread(dirP + filenamePrj);
	Mat imCam = imread(dirC + filenameCam);
	//ifstream fileCorPC(dirPC + filenameCorPC, ios::in);
	//string lineCorPC;
	//double corPC[900][1440][2];
	//memset(corPC, 0, 900 * 1440 * 2);

	///* Read CSV */
	//cout << "\nReading CSV file...\n";
	//if (fileCorPC.is_open()) {
	//	int i = 0;
	//	
	//	while (getline(fileCorPC, lineCorPC)) {
	//		stringstream ss(lineCorPC);
	//		string sub;
	//		vector<string> subArray;

	//		while (getline(ss, sub, ',')) {
	//			subArray.push_back(sub);
	//		}

	//		for (size_t m = 0; m < subArray.size(); m++) {
	//			//cout << subArray[m] << "\t";
	//			if (m % 2 == 0) {	// Even
	//				corPC[i][int(m / 2)][0] = stod(subArray[m]);
	//			}
	//		}
	//		cout << endl;
	//		i++;
	//	}
	//} else {
	//	cerr << "Failed to open '" << filenameCorPC << "'.\n";
	//}
	////for (int i = 0; i < 1; i++) {	// Test
	////	for (int j = 0; j < 1440; j++) {
	////		cout << corPC[i][j][0] << "\t" << corPC[i][j][1] << "\t";
	////	}
	////	cout << endl;
	////}


	/* Geometric correction */
	cout << "\nCorrecting image...\n";
	Mat imCamTrans;		// Camera-captured image after geometric correction
	int numChannel = imCam.channels();
	switch (numChannel) {
	case 1: {
		imCamTrans = Mat::zeros(1200, 1920, CV_8UC1);
		for (int i = 300; i < 900; i++) {
			for (int j = 480; j < 1440; j++) {
				double temp[2];
				temp[0] = corPC[i][j][0];
				temp[1] = corPC[i][j][1];
				int ii = int(temp[0]);
				int jj = int(temp[1]);
				double u = temp[0] - ii;
				double v = temp[1] - jj;

				imCamTrans.at<uchar>(i, j) = uchar(
					(1 - u) * (1 - v) * imCam.at<uchar>(ii, jj)
					+ (1 - u) * v * imCam.at<uchar>(ii, jj + 1)
					+ u * (1 - v) * imCam.at<uchar>(ii + 1, jj)
					+ u * v * imCam.at<uchar>(ii + 1, jj + 1));
			}
		}

		break;
	}

	case 3: {
		imCamTrans = Mat::zeros(1200, 1920, CV_8UC3);
		for (int i = 300; i < 900; i++) {
			for (int j = 480; j < 1440; j++) {
				double temp[2];
				int ii = int(corPC[i][j][0]);
				int jj = int(corPC[i][j][1]);
				double u = corPC[i][j][0] - ii;
				double v = corPC[i][j][1] - jj;
				//printf("-----------------------------------------------\n");
				//printf("i = %d, j = %d\n", i, j);
				//printf("corPC[%d][%d][0] = %lf,\tcorPC[%d][%d][1] = %lf\n", 
				//	i, j, corPC[i][j][0], 
				//	i, j, corPC[i][j][1]);
				//printf("ii= %d,\tjj = %d,\tu = %lf,\tv = %lf\n", ii, jj, u, v);

				for (int ch = 0; ch < numChannel; ch++) {
					uchar i1 = imCam.at<Vec3b>(ii, jj)[ch];
					uchar i2 = imCam.at<Vec3b>(ii, jj + 1)[ch];
					uchar i3 = imCam.at<Vec3b>(ii + 1, jj)[ch];
					uchar i4 = imCam.at<Vec3b>(ii + 1, jj + 1)[ch];
					//printf("i1= %d,\ti2 = %d,\ti3 = %d,\ti4 = %d\n", (int)i1, (int)i2, (int)i3, (int)i4);

					imCamTrans.at<Vec3b>(i, j)[ch] = uchar(
						(1 - u) * (1 - v) * i1
						+ (1 - u) * v * i2
						+ u * (1 - v) * i3
						+ u * v * i4);
					//printf("imCamTrans.at<Vec3b>(%d, %d)[%d] = %d\n", i, j, ch, (int)imCamTrans.at<Vec3b>(i, j)[ch]);

					//imCamTrans.at<Vec3b>(i, j)[ch] = uchar(
					//	(1 - u) * (1 - v) * imCam.at<Vec3b>(ii, jj)[ch]
					//	+ (1 - u) * v * imCam.at<Vec3b>(ii, jj + 1)[ch]
					//	+ u * (1 - v) * imCam.at<Vec3b>(ii + 1, jj)[ch]
					//	+ u * v * imCam.at<Vec3b>(ii + 1, jj + 1)[ch]);
				}
			}
		}

		break;
	}

	default:
		break;
	}

	imshow("Geometric corrected image", imCamTrans);



}
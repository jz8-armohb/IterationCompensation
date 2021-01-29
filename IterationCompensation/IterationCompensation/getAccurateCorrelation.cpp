/********************************************************************************
*																				*
*   Description:		Get a more accurate projection model based on			*
*						structured light										*
*																				*
*	Parameters:																	*
*		imP:			Matrix array of the 8 original structured light images	*
*		imC:			Matrix array of the 8 captured structured light images	*
*		Mu:				Transformation matrix of the projection model			*
*		corPC:			Pre-defined array for correlation data					*
*		dirPC:			Directory of the coordinate correlation					*
*		filenameCorPC:	Filename of the coordinate correlation of the			*
*						projector-camera system									*
*																				*
*********************************************************************************
*																				*
*   Written and developed by Lipi NIU & Songzhi ZHENG.							*
*   Copyright © 2021 Lipi NIU & Songzhi ZHENG. All rights reserved.				*
*																				*
********************************************************************************/


#include "declarations.h"
#include <math.h>

void getAccurateCorrelation(Mat imP[], Mat imC[], Matrix3f Mu, double corPC[900][1440][2],
	string dirPC, string filenameCorPC) {
	double corP[900][1440][2], corC[1920][1920][2];
	//double corPC[900][1440][2];

	for (int i = 300; i < 900; i++) {
		for (int j = 480; j < 1440; j++) {
			//double imP0_ij = imP[0].ptr<uchar>(i)[j];
			//double imP1_ij = imP[1].ptr<uchar>(i)[j];
			//double imP2_ij = imP[2].ptr<uchar>(i)[j];
			//double imP3_ij = imP[3].ptr<uchar>(i)[j];
			//double imP4_ij = imP[4].ptr<uchar>(i)[j];
			//double imP5_ij = imP[5].ptr<uchar>(i)[j];
			//double imP6_ij = imP[6].ptr<uchar>(i)[j];
			//double imP7_ij = imP[7].ptr<uchar>(i)[j];
			double imP0_ij = (double)imP[0].at<uchar>(i, j);
			double imP1_ij = (double)imP[1].at<uchar>(i, j);
			double imP2_ij = (double)imP[2].at<uchar>(i, j);
			double imP3_ij = (double)imP[3].at<uchar>(i, j);
			double imP4_ij = (double)imP[4].at<uchar>(i, j);
			double imP5_ij = (double)imP[5].at<uchar>(i, j);
			double imP6_ij = (double)imP[6].at<uchar>(i, j);
			double imP7_ij = (double)imP[7].at<uchar>(i, j);


			double iTemp = atan((imP3_ij - imP1_ij) / (imP0_ij - imP2_ij));
			double jTemp = atan((imP7_ij - imP5_ij) / (imP4_ij - imP6_ij));

			corP[i][j][0] = iTemp;
			corP[i][j][1] = jTemp;
		}
	}

	for (int i = 0; i < 1280; i++) {
		for (int j = 0; j < 1920; j++) {
			//double imC0_ij = imC[0].ptr<uchar>(i)[j];
			//double imC1_ij = imC[1].ptr<uchar>(i)[j];
			//double imC2_ij = imC[2].ptr<uchar>(i)[j];
			//double imC3_ij = imC[3].ptr<uchar>(i)[j];
			//double imC4_ij = imC[4].ptr<uchar>(i)[j];
			//double imC5_ij = imC[5].ptr<uchar>(i)[j];
			//double imC6_ij = imC[6].ptr<uchar>(i)[j];
			//double imC7_ij = imC[7].ptr<uchar>(i)[j];
			double imC0_ij = (double)imC[0].at<uchar>(i, j);
			double imC1_ij = (double)imC[1].at<uchar>(i, j);
			double imC2_ij = (double)imC[2].at<uchar>(i, j);
			double imC3_ij = (double)imC[3].at<uchar>(i, j);
			double imC4_ij = (double)imC[4].at<uchar>(i, j);
			double imC5_ij = (double)imC[5].at<uchar>(i, j);
			double imC6_ij = (double)imC[6].at<uchar>(i, j);
			double imC7_ij = (double)imC[7].at<uchar>(i, j);


			double iTemp = atan((imC3_ij - imC1_ij) / (imC0_ij - imC2_ij));
			double jTemp = atan((imC7_ij - imC5_ij) / (imC4_ij - imC6_ij));

			corC[i][j][0] = iTemp;
			corC[i][j][1] = jTemp;
		}
	}

	//for (int i = 0; i < 1; i++) {
	//	for (int j = 0; j < 1920; j++) {
	//		cout << corC[i][j][0] << "\t" << corC[i][j][1] << endl;
	//	}
	//}

	for (int i = 300; i < 900; i++) {
		for (int j = 480; j < 1440; j++) {
			MatrixXf axis(3, 1);
			axis << j,
				i,
				1;
			MatrixXf temp(3, 1);
			temp = Mu * axis;

			double jja = temp(0, 0) / temp(2, 0);
			double iia = temp(1, 0) / temp(2, 0);
			int jj = int(jja + 0.5);
			int ii = int(iia + 0.5);

			double radPrj[2];
			radPrj[0] = corP[i][j][0];
			radPrj[1] = corP[i][j][1];

			//double t1[9][9], t2[9][9];
			//int count = 0;
			//for (int m = ii - 5; m < ii + 4; m++) {
			//	for (int n = jj - 5; n < jj + 4; n++) {
			//		t1[count] = corC[m][n][0];
			//		count++;
			//	}
			//}

			ArrayXXf t1(9, 9), t2(9, 9), tt(9, 9);
			for (int offset = -5; offset < 4; offset++) {
				t1.block(offset+5, 0, 1, t1.cols()) << 
					corC[ii + offset][jj - 5][0], corC[ii + offset][jj - 4][0], corC[ii + offset][jj - 3][0],
					corC[ii + offset][jj - 2][0], corC[ii + offset][jj - 1][0], corC[ii + offset][jj][0],
					corC[ii + offset][jj + 1][0], corC[ii + offset][jj + 2][0], corC[ii + offset][jj + 3][0];

				t2.block(offset + 5, 0, 1, t2.cols()) << 
					corC[ii + offset][jj - 5][1], corC[ii + offset][jj - 4][1], corC[ii + offset][jj - 3][1],
					corC[ii + offset][jj - 2][1], corC[ii + offset][jj - 1][1], corC[ii + offset][jj][1],
					corC[ii + offset][jj + 1][1], corC[ii + offset][jj + 2][1], corC[ii + offset][jj + 3][1];
			}

			tt = (t1 - radPrj[0]).abs() + (t2 - radPrj[1]).abs();
			//cout << "t1 = \n" << t1 << endl;	// Test
			//cout << "t2 = \n" << t2 << endl;
			//cout << "radPrj = \n" << radPrj[0] << ", " << radPrj[1] << endl;
			//cout << "tt = \n" << tt << endl;

			ArrayXXf::Index x, y;
			double ttMin = tt.minCoeff(&x, &y);
			ii = ii + x - 5;
			jj = jj + y - 5;
			ii = ii - (t1(x, y) - radPrj[0]) / 0.5236;
			jj = jj - (t2(x, y) - radPrj[1]) / 0.5236;

			corPC[i - 1][j - 1][0] = ii;
			corPC[i - 1][j - 1][1] = jj;
		}
	}


	ofstream fileCorPC(dirPC + filenameCorPC, ios::out);
	if (fileCorPC.is_open()) {
		for (int i = 0; i < 900; i++) {
			for (int j = 0; j < 1440; j++) {
				fileCorPC << corPC[i][j][0] << "," << corPC[i][j][1] << ",";
			}
			fileCorPC << endl;
		}
	}
	fileCorPC.close();

}
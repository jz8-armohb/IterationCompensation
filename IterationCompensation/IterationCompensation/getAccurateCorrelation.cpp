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
	double corP[900][1440][2], corC[1280][1920][2];
	//double corPC[900][1440][2];
	memset(corP, 0, 900 * 1440 * 2);
	memset(corC, 0, 1280 * 1920 * 2);
	memset(corPC, 0, 900 * 1440 * 2);

	/* Compute corP */
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

			corP[i][j][0] = atan((imP3_ij - imP1_ij) / (imP0_ij - imP2_ij));
			corP[i][j][1] = atan((imP7_ij - imP5_ij) / (imP4_ij - imP6_ij));
		}
	}

	for (int i = 302; i < 303; i++) {
		for (int j = 844; j < 847; j++) {
			printf("corP[%d][%d][0] = %d,\tcorP[%d][%d][1] = %d\n", i, j, corP[i][j][0], i, j, corP[i][j][1]);
		}
	}


	/* Compute corC */
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

			corC[i][j][0] = atan((imC3_ij - imC1_ij) / (imC0_ij - imC2_ij));
			corC[i][j][1] = atan((imC7_ij - imC5_ij) / (imC4_ij - imC6_ij));
		}
	}

	for (int i = 302; i < 303; i++) {
		for (int j = 844; j < 847; j++) {
			printf("corC[%d][%d][0] = %d,\tcorC[%d][%d][1] = %d\n", i, j, corC[i][j][0], i, j, corC[i][j][1]);
		}
	}


	/* Compute corPC */
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
			corPC[i][j][0] = ii - (t1(x, y) - radPrj[0]) / 0.5236;
			corPC[i][j][1] = jj - (t2(x, y) - radPrj[1]) / 0.5236;


			if ( corPC[i][j][0] >= 10000 || corPC[i][j][0] <= -10000 || 
				corPC[i][j][1] >= 10000 || corPC[i][j][1] <= -10000) {
				printf("-----------------------------------------------\n");
				printf("imP[0].at<uchar>(%d, %d) = %d,\timP[0].at<uchar>(%d, %d) = %lf\n",
					i, j, imP[0].at<uchar>(i, j),
					i, j, (double)imP[0].at<uchar>(i, j));
				printf("corP[%d][%d][0] = %lf,\tcorP[%d][%d][1] = %lf\n",
					i, j, corP[i][j][0],
					i, j, corP[i][j][1]);
				printf("imC[0].at<uchar>(%d, %d) = %d,\timC[0].at<uchar>(%d, %d) = %lf\n",
					i, j, imC[0].at<uchar>(i, j),
					i, j, (double)imC[0].at<uchar>(i, j));
				printf("corC[%d][%d][0] = %lf,\tcorC[%d][%d][1] = %lf\n",
					i, j, corC[i][j][0],
					i, j, corC[i][j][1]);
				printf("corPC[%d][%d][0] = %lf,\tcorPC[%d][%d][1] = %lf\n",
					i, j, corPC[i][j][0],
					i, j, corPC[i][j][1]);
			}



		}
	}

	for (int i = 302; i < 303; i++) {
		for (int j = 844; j < 847; j++) {
			printf("corPC[%d][%d][0] = %d,\tcorPC[%d][%d][1] = %d\n", i, j, corPC[i][j][0], i, j, corPC[i][j][1]);
		}
	}


	/* Write corPC into a CSV file */
	ofstream fileCorPC(dirPC + filenameCorPC, ios::out);
	if (fileCorPC.is_open()) {
		for (int i = 0; i < 900; i++) {
			for (int j = 0; j < 1440; j++) {
				fileCorPC << (double)corPC[i][j][0] << "," << (double)corPC[i][j][1] << ",";
			}
			fileCorPC << endl;
		}
	}
	fileCorPC.close();

}
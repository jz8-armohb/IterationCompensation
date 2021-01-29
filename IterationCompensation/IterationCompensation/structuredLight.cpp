/********************************************************************************
*																				*
*   Description:		Compute the radian of projector and camera coordinates	*
*																				*
*	Parameters:																	*
*		imP:			Matrix array of the 8 original structured light images	*
*		imC:			Matrix array of the 8 captured structured light images	*
*		corP:			Radian of the projector coordinates						*
*		corC:			Radian of the camera-captured coordinates				*
*																				*
*********************************************************************************
*																				*
*   Written and developed by Lipi NIU & Songzhi ZHENG.							*
*   Copyright © 2021 Lipi NIU & Songzhi ZHENG. All rights reserved.				*
*																				*
********************************************************************************/


#include "declarations.h"
#include <math.h>

void structuredLight(Mat imP[], Mat imC[], double corP[][1440][2], double corC[][1920][2]) {
	for (int i = 300; i < 900; i++) {
		for (int j = 480; j < 1440; j++) {
			double imP0_ij = imP[0].ptr<uchar>(i)[j];
			double imP1_ij = imP[1].ptr<uchar>(i)[j];
			double imP2_ij = imP[2].ptr<uchar>(i)[j];
			double imP3_ij = imP[3].ptr<uchar>(i)[j];
			double imP4_ij = imP[4].ptr<uchar>(i)[j];
			double imP5_ij = imP[5].ptr<uchar>(i)[j];
			double imP6_ij = imP[6].ptr<uchar>(i)[j];
			double imP7_ij = imP[7].ptr<uchar>(i)[j];

			double iTemp = atan((imP3_ij - imP1_ij) / (imP0_ij - imP2_ij));
			double jTemp = atan((imP7_ij - imP5_ij) / (imP4_ij - imP6_ij));

			corP[i][j][0] = iTemp;
			corP[i][j][1] = jTemp;
		}
	}

	for (int i = 0; i < 1280; i++) {
		for (int j = 0; j < 1920; j++) {
			double imC0_ij = imC[0].ptr<uchar>(i)[j];
			double imC1_ij = imC[1].ptr<uchar>(i)[j];
			double imC2_ij = imC[2].ptr<uchar>(i)[j];
			double imC3_ij = imC[3].ptr<uchar>(i)[j];
			double imC4_ij = imC[4].ptr<uchar>(i)[j];
			double imC5_ij = imC[5].ptr<uchar>(i)[j];
			double imC6_ij = imC[6].ptr<uchar>(i)[j];
			double imC7_ij = imC[7].ptr<uchar>(i)[j];

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
}
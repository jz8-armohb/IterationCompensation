/********************************************************************************
*																				*
*   Description:		Get the correlation between the coordinates of the		*
*						projector and the camera								*
*																				*
*	Parameters:																	*
*		dirP:			Directory of the input calibration images				*
*		dirC:			Directory of the captured calibration images			*
*		dirPC:			Directory of the coordinate correlation					*
*																				*
*********************************************************************************
*																				*
*   Written and developed by Lipi NIU & Songzhi ZHENG.							*
*   Copyright © 2021 Lipi NIU & Songzhi ZHENG. All rights reserved.				*
*																				*
********************************************************************************/


#include "declarations.h"

void getCoordCorrelation(string dirP, string dirC, string dirPC) {
	/****************************************************************************
	*	Read images																*
	****************************************************************************/
	string fnameP_board = "im_board.jpg";
	Mat imP_board = imread(dirP + fnameP_board);		// Checkerboard image (projector input)
	imOpenIndicator(imP_board, fnameP_board);
	//imshow("Calibration image input (checkerboard)", imP_board);

	Mat imP[8];		// 8 structured light images (projector input)
	string fnameSuffixP_sin = "im_sin";
	for (int i = 0; i < 8; i++) {
		char fnameIdxP_sin[2];
		sprintf(fnameIdxP_sin, "%d", i + 1);
		imP[i] = imread(dirP + fnameSuffixP_sin + fnameIdxP_sin + ".jpg");
		imOpenIndicator(imP[i], fnameSuffixP_sin + fnameIdxP_sin + ".jpg");
		cvtColor(imP[i], imP[i], COLOR_BGR2GRAY);
		//imP[i].convertTo(imP[i], CV_64FC1);		// Convert to double
		//imshow("Calibration image input (structured light " + (string)fnameIdxP_sin + ")", imP[i]);
	}


	string fnameC_board = "IMG_0001.JPG";
	Mat imC_board = imread(dirC + fnameC_board);		// Checkerboard image captured by camera
	imOpenIndicator(imC_board, fnameC_board);
	//imshow("Calibration image captured (checkerboard)", imC_board);

	Mat imC[8];		// 8 structured light images captured by camera
	string fnameSuffixC_sin = "IMG_";
	for (int i = 0; i < 8; i++) {
		char fnameIdxC_sin[5];
		sprintf(fnameIdxC_sin, "%04d", i + 1);		// %04d: pad the width with leading zeros to keep the integer 4 digits wide
		imC[i] = imread(dirC + fnameSuffixC_sin + fnameIdxC_sin + ".JPG");
		imOpenIndicator(imC[i], fnameSuffixC_sin + fnameIdxC_sin + ".JPG");
		cvtColor(imC[i], imC[i], COLOR_BGR2GRAY);
		//imC[i].convertTo(imC[i], CV_64FC1);		// Convert to double
		//imshow("Calibration image captured (structured light " + (string)fnameIdxC_sin + ")", imP[i]);
	}


	/****************************************************************************
	*	Detect corners of checkerboard images									*
	****************************************************************************/
	vector<Point2f> cornerIn;		// Corner points of the input (original checkerboard) image
	vector<Point2f> cornerOut;		// Corner points of the output (camera-captured checkerboard) image
	Size boardSize;
	boardSize.width = 8;
	boardSize.height = 5;

	cornerIn = getCheckerboardCorner(imP_board, boardSize, 
		dirP, addSuffix(fnameP_board, ".jpg", "_corner", ".jpg"), 
		dirPC, addSuffix(fnameP_board, ".jpg", "_coord", ".csv"));

	cornerOut = getCheckerboardCorner(imC_board, boardSize,
		dirC, addSuffix(fnameC_board, ".JPG", "_corner", ".jpg"),
		dirPC, addSuffix(fnameC_board, ".JPG", "_coord", ".csv"));


	/****************************************************************************
	*	Compute the transformation matrix of the projection model				*
	****************************************************************************/
	Matrix3f matTrans;
	matTrans = getTransMatrix(cornerIn, cornerOut, "SVD");


	/****************************************************************************
	*	Compute a more accurate model											*
	****************************************************************************/
	double corPC[900][1440][2];
	getAccurateCorrelation(imP, imC, matTrans, corPC, dirP, "prj_cam_correlation.csv");
}
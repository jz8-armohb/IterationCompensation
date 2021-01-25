/********************************************************************************
*																				*
*   Description:		Get the coordinate relations between the projector		*
*						and the camera											*
*																				*
*	Parameters:																	*
*		string dirP:	Directory of the input calibration images				*
*		string dirC:	Directory of the captured calibration images			*
*		string dirPC:	Directory of the coordinate relation					*
*																				*
*	Returns:			Void													*
*																				*
*********************************************************************************
*																				*
*   Written and developed by Songzhi ZHENG.										*
*   Copyright © 2021 Songzhi ZHENG. All rights reserved.						*
*																				*
********************************************************************************/


#include "declarations.h"


void getCoordRelation(string dirP, string dirC, string dirPC) {
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
		imP[i].convertTo(imP[i], CV_64FC3);		// Convert to double
		//imshow("Calibration image input (structured light " + (string)fnameIdxP_sin + ")", imP[i]);
		//imwrite(dirP + fnameSuffixP_sin + fnameIdxP_sin + " (CV_64FC3).jpg", imP[i]);
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
		imC[i].convertTo(imC[i], CV_64FC3);		// Convert to double
		//imshow("Calibration image captured (structured light " + (string)fnameIdxC_sin + ")", imP[i]);
	}


	/****************************************************************************
	*	Detect corners of checkerboard images									*
	****************************************************************************/
	Size boardSize, imSize;
	boardSize.width = 8;
	boardSize.height = 5;
	Mat imP_board_grey;
	vector<Point2f> cornerBuffer;
	cvtColor(imP_board, imP_board_grey, COLOR_BGR2GRAY);

	bool found = 0;
	found = findChessboardCornersSB(imP_board, boardSize, cornerBuffer, CALIB_CB_EXHAUSTIVE | CALIB_CB_ACCURACY);

	if (found) {
		drawChessboardCorners(imP_board, boardSize, Mat(cornerBuffer), found);
		ofstream filePCorner(dirPC + "im_board_coord.csv", ios::out);
		if (filePCorner.is_open()) {
			for (unsigned int i = 0; i < cornerBuffer.size(); i++) {
				float coordX = cornerBuffer.at(i).x;
				float coordY = cornerBuffer.at(i).y;
				filePCorner << coordX << "," << coordY << endl;		// Save coordinates to a .csv file
			}
		}
		filePCorner.close();
	}
	imshow("Checkerboard image with detected corners", imP_board);
	imwrite(dirP + "im_board_corner.jpg", imP_board);
	//waitKey(0);
}
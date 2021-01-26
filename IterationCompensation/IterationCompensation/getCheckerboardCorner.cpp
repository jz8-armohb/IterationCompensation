/********************************************************************************
*																				*
*   Description:			Detect the corners of a checkerboard image	 		*
*																				*
*	Parameters:																	*
*		Mat imBoard:			Matrix of the checkerboard image				*
*		Size boardSize:			Corner points along x and y axis				*
*		string dirImOut:		Saving directory of the corner-marked image		*
*		string fnImOut:			Filename of the corner-marked image				*
*		string dirCoorOut:		Saving directory of the file of cordinates		*
*		string fnCoorOut:		Filename of the CSV file of cordinates			*
*																				*
*	Returns:																	*
*		vector<Point2f> cornerBuffer:	Buffer of corner points					*
*																				*
*********************************************************************************
*																				*
*   Written and developed by Songzhi ZHENG.										*
*   Copyright © 2021 Songzhi ZHENG. All rights reserved.						*
*																				*
********************************************************************************/


#include "declarations.h"

vector<Point2f> getCheckerboardCorner(Mat imBoard, Size boardSize, 
	string dirImOut, string fnImOut, string dirCoordOut, string fnCoorOut) {

	Mat imP_board_grey;
	vector<Point2f> cornerBuffer;
	cvtColor(imBoard, imP_board_grey, COLOR_BGR2GRAY);

	bool found = 0;
	found = findChessboardCornersSB(imBoard, boardSize, cornerBuffer, CALIB_CB_EXHAUSTIVE | CALIB_CB_ACCURACY);

	if (found) {
		drawChessboardCorners(imBoard, boardSize, Mat(cornerBuffer), found);
		ofstream filePCorner(dirCoordOut + fnCoorOut, ios::out);
		if (filePCorner.is_open()) {
			for (unsigned int i = 0; i < cornerBuffer.size(); i++) {
				float coordX = cornerBuffer.at(i).x;
				float coordY = cornerBuffer.at(i).y;
				filePCorner << coordX << "," << coordY << endl;		// Save coordinates to CSV file
			}
		}
		filePCorner.close();
	}
	//imshow(fnImOut, imBoard);
	imwrite(dirImOut + fnImOut, imBoard);

	return cornerBuffer;
}
/********************************************************************************
*																				*
*   Description:		Compute the transformation matrix of the projection		*
*						model													*
*																				*
*	Parameters:																	*
*		coordIn:		Original coordinates									*
*		coordOut:		Coordinates after transformation						*
*		algorithm:		Supports the following 3 algorithms -					*
*						"SVD", "QR" and "Normal" (normal equation)				*
*																				*
*	Returns:																	*
*		matTrans:		Transformation matrix									*
*																				*
*********************************************************************************
*																				*
*   Written and developed by Songzhi ZHENG.										*
*   Copyright © 2021 Songzhi ZHENG. All rights reserved.						*
*																				*
********************************************************************************/


#include "declarations.h"

Matrix3f getTransMatrix(vector<Point2f> coordIn, vector<Point2f> coordOut, string algorithm) {
	int numCorner = coordIn.size();
	double xIn;
	double yIn;
	double xOut;
	double yOut;
	MatrixXf MM(2 * numCorner, 8);
	MatrixXf b(2 * numCorner, 1);
	VectorXf a(8);
	Matrix3f matTrans;


	for (int i = 0; i < numCorner; i++) {
		xIn = coordIn[i].x;
		yIn = coordIn[i].y;
		xOut = coordOut[i].x;
		yOut = coordOut[i].y;

		MM.block(2 * i, 0, 1, MM.cols()) << xIn, yIn, 1, 0, 0, 0, -xIn * xOut, -xOut * yIn;
		MM.block(2 * i + 1, 0, 1, MM.cols()) << 0, 0, 0, xIn, yIn, 1, -xIn * yOut, -yIn * yOut;

		b(2 * i, 0) = xOut;
		b(2 * i + 1, 0) = yOut;
	}


	if (algorithm == "SVD") {
		a = MM.bdcSvd(ComputeThinU | ComputeThinV).solve(b);
	} else if (algorithm == "QR") {
		a = MM.colPivHouseholderQr().solve(b);
	} else if (algorithm == "Normal") {
		a = (MM.transpose() * MM).ldlt().solve(MM.transpose() * b);
	}
	//cout << "a = \n" << a << endl;


	matTrans(0, 0) = a(0);
	matTrans(0, 1) = a(1);
	matTrans(0, 2) = a(2);
	matTrans(1, 0) = a(3);
	matTrans(1, 1) = a(4);
	matTrans(1, 2) = a(5);
	matTrans(2, 0) = a(6);
	matTrans(2, 1) = a(7);
	matTrans(2, 2) = 1;
	//cout << "matTrans =\n" << matTrans << endl;

	return matTrans;
}
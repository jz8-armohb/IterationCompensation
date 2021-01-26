﻿/********************************************************************************
*																				*
*   Description:		Declarations of functions and header files				*
*																				*
*********************************************************************************
*																				*
*   Written and developed by Lipi NIU & Songzhi ZHENG.							*
*   Copyright © 2021 Lipi NIU & Songzhi ZHENG. All rights reserved.				*
*																				*
********************************************************************************/


#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
#include <Eigen/SVD>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>
#include <fstream>
using namespace std;
using namespace cv;
using namespace Eigen;


/* Function declarations */
void getCoordRelation(string dirP, string dirC, string dirPC);
void imOpenIndicator(Mat img, string filename);
vector<Point2f> getCheckerboardCorner(Mat imBoard, Size boardSize,
	string dirImOut, string fnImOut, string dirCoordOut, string fnCoorOut);
string addSuffix(string filenameIn, string extPrev, string suffixNew, string extNew);
Matrix3f getTransMatrix(vector<Point2f> coordIn, vector<Point2f> coordOut);

void testEigen();
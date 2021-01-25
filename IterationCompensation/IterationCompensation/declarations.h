/********************************************************************************
*																				*
*   Description:		Declarations of functions and header files				*
*																				*																				*
*********************************************************************************
*																				*
*   Written and developed by Songzhi ZHENG.										*
*   Copyright © 2021 Songzhi ZHENG. All rights reserved.						*
*																				*
********************************************************************************/


#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
using namespace std;
using namespace cv;


/* Function declarations */
void getCoorRelation(string dirP, string dirC);
void imOpenIndicator(Mat img, string filename);
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
#include <iostream>
#include <fstream>
using namespace std;
using namespace cv;


/* Function declarations */
void getCoordRelation(string dirP, string dirC, string dirPC);
void imOpenIndicator(Mat img, string filename);
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


/// <summary>
///     Get the coordinate relations between the projector and the camera
/// </summary>
/// 
/// <param name = "dirP"> - Directory of the input calibration images</param>
/// <param name = "dirC"> - Directory of the captured calibration images</param>
/// <param name = "dirPC"> - Directory of the coordinate relation</param>
void getCoordRelation(string dirP, string dirC, string dirPC);


/// <summary>
///     Print indication of reading status of images
/// </summary>
/// <param name = "img"> - The matrix with image data</param>
/// <param name = "filename"> - The filename of the imag</param>
void imOpenIndicator(Mat img, string filename);


/// <summary>
///     Detect the corners of a checkerboard image
/// </summary>
/// 
/// <param name = "imBoard"> - Matrix of the checkerboard image</param>
/// <param name = "boardSize"> - Corner points along x and y axis</param>
/// <param name = "dirImOut"> - Saving directory of the corner-marked image</param>
/// <param name = "fnImOut"> - Filename of the corner-marked image</param>
/// <param name = "dirCoorOut"> - Saving directory of the file of cordinates</param>
/// <param name = "fnCoorOut"> - Filename of the CSV file of cordinates</param>
/// 
/// <returns>Buffer of corner points</returns>
vector<Point2f> getCheckerboardCorner(Mat imBoard, Size boardSize,
	string dirImOut, string fnImOut, string dirCoordOut, string fnCoorOut);


/// <summary>
///     Insert a suffix between	the filename and the extension, with an option to change a new extension
/// </summary>
/// 
/// <param name = "filename"> - Input filename (including extension)</param>
/// <param name = "extPrev"> - Previous file extension (with ".")</param>
/// <param name = "suffixNew"> - Suffix of the new filename</param>
/// <param name = "exteNew"> - New file extension (with ".")</param>
/// 
/// <returns>Output filename</returns>
string addSuffix(string filenameIn, string extPrev, string suffixNew, string extNew);


/// <summary>
///     Compute the transformation matrix of the projection model
/// </summary>
/// 
/// <param name = "coordIn"> - Original coordinates</param>
/// <param name = "coordOut"> - Coordinates after transformation</param>
/// <param name = "algorithm"> - Supports the following 3 algorithms: "SVD", "QR" and "Normal" (normal equation)</param>
/// 
/// <returns>Transformation matrix</returns>
Matrix3f getTransMatrix(vector<Point2f> coordIn, vector<Point2f> coordOut, string algorithm);

void testEigen();
/********************************************************************************
*																				*
*   Description:		Get the coordinates relation between the projector		*
*						and the camera											*
*																				*
*	Parameters:																	*
*		string dirP:	Directory of the input calibration images				*
*		string dirC:	Directory of the captured calibration images			*
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


void getCoorRelation(string dirP, string dirC) {
	/* 读取图像 */
	string fname_checkerP = "im_checkerboard.jpg";
	Mat imP_checker = imread(dirP + fname_checkerP);		// 棋盘格图像（投影仪输入）
	imOpenIndicator(imP_checker, fname_checkerP);
	//imshow("Calibration image input (checkerboard)", imP_checker);

	Mat imP[8];		// 8张结构光图像（投影仪输入）
	string fnameSuffix_sinP = "im_sin";
	for (int i = 0; i < 8; i++) {
		char fnameIdx_sinP[2];
		sprintf(fnameIdx_sinP, "%d", i + 1);
		imP[i] = imread(dirP + fnameSuffix_sinP + fnameIdx_sinP + ".jpg");
		imOpenIndicator(imP[i], fnameSuffix_sinP + fnameIdx_sinP + ".jpg");
		imP[i].convertTo(imP[i], CV_64FC3);		// 转为浮点型
		//imshow("Calibration image input (structured light " + (string)fnameIdx_sinP + ")", imP[i]);
		//imwrite(dirP + fnameSuffix_sinP + fnameIdx_sinP + " (CV_64FC1).jpg", imP[i]);
	}

	string fname_checkerC = "IMG_0001.JPG";
	Mat imC_checker = imread(dirC + fname_checkerC);		// 棋盘格图像（相机采集）
	imOpenIndicator(imC_checker, fname_checkerC);
	//imshow("Calibration image captured (checkerboard)", imC_checker);

	Mat imC[8];		// 8张结构光图像（相机采集）
	string fnameSuffix_sinC = "IMG_";
	for (int i = 0; i < 8; i++) {
		char fnameIdx_sinC[5];
		sprintf(fnameIdx_sinC, "%04d", i + 1);		// %04d表示将整型数补0至4位
		imC[i] = imread(dirC + fnameSuffix_sinC + fnameIdx_sinC + ".JPG");
		imOpenIndicator(imC[i], fnameSuffix_sinC + fnameIdx_sinC + ".JPG");
		imC[i].convertTo(imC[i], CV_64FC3);		// 转为浮点型
		//imshow("Calibration image captured (structured light " + (string)fnameIdx_sinC + ")", imP[i]);
	}


}
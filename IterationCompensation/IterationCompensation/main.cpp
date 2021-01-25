﻿/********************************************************************************
*																				*
*   Description:			Main function										*
*																				*
*	Parameters:																	*
*		int argc:			The number of command line arguments 				*
*		string filename:	The array of command line arguments					*
*																				*
*	Returns:				Exit code											*
*																				*
*********************************************************************************
*																				*
*   Written and developed by Songzhi ZHENG.										*
*   Copyright © 2021 Songzhi ZHENG. All rights reserved.						*
*																				*
********************************************************************************/


#include "declarations.h"

int main(int argc, char** argv) {
	/* 读取图像 */
	string dirP = argv[1];		// 标定图像目录
	string dirC = argv[2];		// 拍摄的标定图像目录
	getCoorRelation(dirP, dirC);


	waitKey(0);
	return 0;
}
/********************************************************************************
*																				*
*   Description:			Print indication of reading status of images 		*
*																				*
*	Parameters:																	*
*		img:				The matrix with image data							*
*		filename:			The filename of the image							*
*																				*
*********************************************************************************
*																				*
*   Written and developed by Songzhi ZHENG.										*
*   Copyright © 2021 Songzhi ZHENG. All rights reserved.						*
*																				*
********************************************************************************/


#include "declarations.h"

void imOpenIndicator(Mat img, string filename) {
	if (img.empty()) {
		cerr << "Failed to load '" << filename << "'.\n";
		exit(-1);
	} else {
		cout << "'" << filename << "' opened.\n";
	}
}
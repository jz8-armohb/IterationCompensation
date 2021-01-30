#include "declarations.h"


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


void imOpenIndicator(Mat img, string filename) {
	if (img.empty()) {
		cerr << "Failed to load '" << filename << "'.\n";
		exit(-1);
	} else {
		cout << "'" << filename << "' opened.\n";
	}
}




/********************************************************************************
*																				*
*   Description:		Insert a suffix between	the filename and the extension,	*
*						with an option to change a new extension				*
*																				*
*	Parameters:																	*
*		filename:		Input filename (including extension)					*
*		extPrev:		Previous file extension	(with ".")						*
*		suffixNew:		Suffix of the new filename								*
* 		exteNew:		New file extension (with ".")							*
*																				*
*	Returns:																	*
*		filenameOut:	Output filename											*
*																				*
*********************************************************************************
*																				*
*   Written and developed by Songzhi ZHENG.										*
*   Copyright © 2021 Songzhi ZHENG. All rights reserved.						*
*																				*
********************************************************************************/


string addSuffix(string filenameIn, string extPrev, string suffixNew, string extNew) {
	string filenameOut = filenameIn.substr(0, filenameIn.length() - extPrev.length()) + suffixNew + extNew;
	return filenameOut;
}
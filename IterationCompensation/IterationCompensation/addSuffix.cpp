/********************************************************************************
*																				*
*   Description:		Insert a suffix between	the filename and the extension,	*
*						with an option to change a new extension				*
*																				*
*	Parameters:																	*
*		string filename:	Input filename (including extension)				*
*		string extPrev:		Previous file extension	(with ".")					*
*		string suffixNew:	Suffix of the new filename							*
* 		string exteNew:		New file extension (with ".")						*
*																				*
*	Returns:																	*
*		string filenameOut:	Output filename										*
*																				*
*********************************************************************************
*																				*
*   Written and developed by Songzhi ZHENG.										*
*   Copyright © 2021 Songzhi ZHENG. All rights reserved.						*
*																				*
********************************************************************************/


#include "declarations.h"

string addSuffix(string filenameIn, string extPrev, string suffixNew, string extNew) {
	string filenameOut = filenameIn.substr(0, filenameIn.length() - extPrev.length()) + suffixNew + extNew;
	return filenameOut;
}
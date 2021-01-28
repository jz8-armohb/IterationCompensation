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


#include "declarations.h"

string addSuffix(string filenameIn, string extPrev, string suffixNew, string extNew) {
	string filenameOut = filenameIn.substr(0, filenameIn.length() - extPrev.length()) + suffixNew + extNew;
	return filenameOut;
}
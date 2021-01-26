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
string addSuffix(string filenameIn, string extPrev, string suffixNew, string extNew) {
	string filenameOut = filenameIn.substr(0, filenameIn.length() - extPrev.length()) + suffixNew + extNew;
	return filenameOut;
}
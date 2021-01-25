/********************************************************************************
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
	/****************************************************************************
	*	Call getCoordRelation()													*
	****************************************************************************/
	string dirP = argv[1];		// Directory of the input calibration images
	string dirC = argv[2];		// Directory of the captured calibration images
	string dirPC = argv[3];		// Directory of the coordinate relation
	getCoordRelation(dirP, dirC, dirPC);


	waitKey(0);
	return 0;
}
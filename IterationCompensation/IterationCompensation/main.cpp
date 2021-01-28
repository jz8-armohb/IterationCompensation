/********************************************************************************
*																				*
*   Description:			Main function										*
*																				*
*	Parameters:																	*
*		int argc:				Number of command line arguments 				*
*		string filename:		Array of command line arguments					*
*																				*
*	Returns:																	*
*		int:					Exit code										*
*																				*
*********************************************************************************
*																				*
*   Written and developed by Lipi NIU & Songzhi ZHENG.							*
*   Copyright © 2021 Lipi NIU & Songzhi ZHENG. All rights reserved.				*
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
	//getCoordRelation(dirP, dirC, dirPC);
	testEigen();
	

	waitKey(0);
	return 0;
}
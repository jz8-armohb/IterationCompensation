#include "declarations.h"


void testEigen() {

    //MatrixXd MM(80, 8);     // Data from MALTLAB
    //FILE* fpread;
    //fpread = fopen(".\\test_data\\MM.txt", "r");
    //if (fpread == NULL) {
    //    printf("file is error.");
    //    exit(-1);
    //} else {
    //    cout << "Successfully opened file.\n";
    //}
    //for (int i = 0; i < 80; i++) {
    //    for (int j = 0; j < 8; j++) {
    //        fscanf(fpread, "%lf", &MM(i, j));
    //    }
    //}
    //fclose(fpread);
    ////cout << "MM = \n" << MM << endl;

    //MatrixXd b(80, 1);      // Data from MALTLAB
    //fpread = fopen(".\\test_data\\b.txt", "r");
    //if (fpread == NULL) {
    //    printf("file is error.");
    //    exit(-1);
    //} else {
    //    cout << "Successfully opened file.\n";
    //}
    //for (int i = 0; i < 80; i++) {
    //    for (int j = 0; j < 1; j++) {
    //        fscanf(fpread, "%lf", &b(i, j));
    //    }
    //}
    //fclose(fpread);
    ////cout << "b = \n" << b << endl;


    //// SVD decomposition
    //cout << "The least-squares solution is:\n"
    //    << MM.bdcSvd(ComputeThinU | ComputeThinV).solve(b) << endl;

    //// QR decomposition
    //cout << "The solution using the QR decomposition is:\n"
    //    << MM.colPivHouseholderQr().solve(b) << endl;

    //// normal equations
    //cout << "The solution using normal equations is:\n" << (MM.transpose() * MM).ldlt().solve(MM.transpose() * b) << endl;




    ArrayXXd a(2, 2);
    ArrayXXd b(2, 2);
    ArrayXXd c(2, 2);
    a << 1, 2, 
        3, 4;
    b << -4, 2,
        0, -6;
    c = a + b;
    ArrayXXd::Index maxRow, maxCol;
    double mincoeff = b.minCoeff(&maxRow, &maxCol);
    cout << mincoeff << endl << maxRow << endl << maxCol;;
    cout << "a(0,1) = " << a(0, 1) << endl;
}
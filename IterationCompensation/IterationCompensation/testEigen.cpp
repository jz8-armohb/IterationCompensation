#include "declarations.h"


void testEigen() {
    MatrixXd A(3, 2);
    A << 1, 2,
        3, 4,
        5, 6;
    cout << "Here is the matrix A:\n" << A << endl;
    VectorXd b(3);
    b << 5,
        11,
        17;
    cout << "Here is the right hand side b:\n" << b << endl;

    //A.block(1, 0, 1, A.cols()) << 7, 8;
    //cout << "Here is the matrix A:\n" << A << endl;

    // SVD decomposition
    cout << "The least-squares solution is:\n"
        << A.bdcSvd(ComputeThinU | ComputeThinV).solve(b) << endl;

    // QR decomposition
    cout << "The solution using the QR decomposition is:\n"
        << A.colPivHouseholderQr().solve(b) << endl;

    // normal equations
    cout << "The solution using normal equations is:\n" << (A.transpose() * A).ldlt().solve(A.transpose() * b) << endl;
}
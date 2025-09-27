#include "MathOperation.h"
#include "Matrix.h"
#include <iostream>
using namespace std;

Matrix MathOperation::Add( const Matrix& mtxA, const Matrix& mtxB ) {
	int mtxArow = mtxA.GetRowCount();
	int mtxAcol = mtxA.GetColCount();
	int mtxBrow = mtxB.GetRowCount();
	int mtxBcol = mtxB.GetColCount();

	Matrix result(mtxArow, mtxAcol);
	if(mtxArow != mtxBrow || mtxAcol != mtxBcol){
		cerr << "Error. We cann't add this matrix." << endl;
			return Matrix(0,0);
	}else {
		for(int i=0; i<mtxArow; i++) {
			for(int j=0; j<mtxAcol; j++){
				result.At(i, j) = mtxA.At(i,j) + mtxB.At(i,j);
			}
		}
	}
	return result;
}

Matrix MathOperation::Mult( const Matrix& mtxA, const Matrix& mtxB ) {
	int mtxArow = mtxA.GetRowCount();
	int mtxAcol = mtxA.GetColCount();
	int mtxBrow = mtxB.GetRowCount();
	int mtxBcol = mtxB.GetColCount();

	Matrix result(mtxArow, mtxAcol);
	if(mtxArow != mtxBcol || mtxAcol != mtxBrow){
		cerr << "Error. We cann't multyplay this matrix." << endl;
			return Matrix(0,0);
	}else {
		for(int i=0; i<mtxArow; i++) {
			for(int j=0; j<mtxAcol; j++){
				result.At(i,j) = mtxA.At(i,j) * mtxB.At(i,j);
			}
		}
	}
	return result;
}

void MathOperation::Transpose( Matrix& mtxA ) {
	int oldRow = mtxA.GetRowCount();
	int oldCol = mtxA.GetColCount();
	Matrix m(oldCol, oldRow);

	for(int i=0; i<oldRow; i++) {
		for(int j=0; j<oldCol; j++){
			m.At(j, i) = mtxA.At(i, j);
		}
	}
    mtxA = m;
}


#include "Matrix.h"
#include <iostream>
using namespace std;

Matrix::Matrix(int nRows, int nCols, bool bInitWithRandom)
	: m_rows(nRows), m_cols(nCols), m_random(bInitWithRandom) {

	matrix = new int*[m_rows];
	for(int i=0; i<m_rows; i++){
		matrix[i] = new int[m_cols];
	}
    
	if(m_random) {
		initWithRandom();
	}else{
		initWithUserInput();
	}
}


Matrix::~Matrix() {
	for(int i=0; i<m_rows; i++){
		delete[] matrix[i]; 
	}
	delete[] matrix;
}

Matrix::Matrix( const Matrix& mtxOther ) {
	m_rows = mtxOther.m_rows;
	m_cols = mtxOther.m_cols;

	matrix = new int*[m_rows];
	for(int i=0; i<m_rows; i++){
		matrix[i] = new int[m_cols];
	}

    for(int i=0; i<m_rows; i++){
		for(int j=0; j<m_cols; j++){
			matrix[i][j] = mtxOther.matrix[i][j];
		}
	}                       
}   

Matrix& Matrix::operator=(const Matrix& mtx){
	if(this == &mtx) return *this;
	for (int i = 0; i < m_rows; i++) {
			delete[] matrix[i];
	}
	delete[] matrix;

	m_rows=mtx.m_rows;
	m_cols=mtx.m_cols;
   	matrix = new int*[m_rows];
 	for(int i=0;i<m_rows;i++){
		matrix[i] = new int[m_cols];
	}	

    for(int i=0; i<m_rows; i++){
		for(int j=0; j<m_cols; j++){
			matrix[i][j] = mtx.At(i, j);
		}
	}                       
	return *this;
}

int& Matrix::At( int row, int col ) { return matrix[row][col];}
int Matrix::At( int row, int col ) const { return matrix[row][col];}

int Matrix::GetRowCount() const { return m_rows;}
int Matrix::GetColCount() const { return m_cols;}

void Matrix::initWithRandom(){
	for(int i=0; i<m_rows; i++){
		for(int j=0; j<m_cols; j++){
			int rdmN = 1+rand()%100;
			matrix[i][j] = rdmN;
		}
	}
}

void Matrix::initWithUserInput(){
    for(int i=0; i<m_rows; i++){
		for(int j=0; j<m_cols; j++){
			int num;
			cout << "enter a [" << i << "," << j << "] = ";
			cin >> num;	
			matrix[i][j] = num;
		}
	}
	
}

void Matrix::initWithZeros(){
    for(int i=0; i<m_rows; i++){
		for(int j=0; j<m_cols; j++){
			matrix[i][j] = 0;
		}
	}
}









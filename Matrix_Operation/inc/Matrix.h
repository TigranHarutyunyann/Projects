#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
private:
	int** matrix;
	int m_rows, m_cols;
	bool m_random;

	void initWithRandom();
	void initWithUserInput();
	void initWithZeros();
public:
	Matrix(int nRows, int nCols, bool bInitWithRandom = true);
    ~Matrix();
	Matrix(const Matrix& mtxOther);
	Matrix& operator=(const Matrix& mtx);

    int& At( int row, int col );
    int At( int row, int col) const;
    int GetRowCount() const; 
    int GetColCount() const; 
};

#endif

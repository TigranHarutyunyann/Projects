#include <iostream>
#include "Matrix.h"
#include "MathOperation.h"
#include "Printer.h"
using namespace std;

int main() {
	
	srand(time(0));
    Matrix mtxA( 11, 12);
	cout << "A matrix" << endl;
	Printer::PrintToConsole(mtxA);

	mtxA.At( 3, 5 ) = 13;
  	mtxA.At( 10, 11 ) = 36;

    Matrix mtxB( 12, 11);
	cout << "B matrix" << endl;
	Printer::PrintToConsole(mtxB);


	MathOperation::Add( mtxA, mtxB );  // out. error
   	
	Matrix mtxMult( MathOperation::Mult( mtxA, mtxB ) );
	cout << "add" << endl;
   	Printer::PrintToConsole( mtxMult );


	cout << "\nBefore Transpose mtxA: " << mtxA.GetRowCount() << " " << mtxA.GetColCount() << endl;
	MathOperation::Transpose( mtxA );
	cout << "After Transpose mtxA: " << mtxA.GetRowCount() << " " << mtxA.GetColCount() << endl;
    cout << endl;

	cout << "A " << mtxA.GetRowCount() << " " << mtxA.GetColCount() << endl;
	cout << "B " << mtxB.GetRowCount() << " " << mtxB.GetColCount() << endl;

	cout << "add" << endl;
    Printer::PrintToConsole( MathOperation::Add( mtxA, mtxB ) );

	return 0;
}


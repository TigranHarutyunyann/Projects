#include "Printer.h"
#include "Matrix.h"
#include <iostream>
using namespace std;


void Printer::PrintToConsole( const Matrix& mtxA ) {
	for(int i=0; i<mtxA.GetRowCount(); i++) {
		for(int j=0; j<mtxA.GetColCount(); j++){
			cout << mtxA.At(i, j) << " ";
		}
		cout << endl;
	}
	cout << endl;
}

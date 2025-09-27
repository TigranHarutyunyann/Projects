#include <iostream>
#include <string>
#include "Encoder.h"
#include "Decoder.h"
#include "Print.h"
#include "unit_test.h"
using namespace std;

int main() {
	
	int Move;
	cout << "Enter a number for shifer: ";
	cin >> Move;
    cin.ignore();

	const int size = 255;
	char input[size];
	cout << "Input: ";
	cin.getline(input, size);
	
	string test = input;

	Encoder::call(input, Move);
	print(input);
	Decoder::call(input, Move);
	print(input);

	unit_test(test, input);
      
	return 0;
}


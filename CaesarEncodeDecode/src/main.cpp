#include <iostream>
#include <string>
#include "Encoder.h"
#include "Decoder.h"
#include "Print.h"
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

	Encoder::call(input, Move);
	print(input);
	Decoder::call(input, Move);
	print(input);
      
	return 0;
}


#include "Print.h"
#include <iostream>
using namespace std;

void print(char arr[]) {
	for(int i=0; arr[i]!='\0'; i++){
		cout << arr[i];
	}
	cout << endl;
}

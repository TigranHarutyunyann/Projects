#include <iostream>
#include <string>
#include "unit_test.h"
using namespace std;

void unit_test(const string& firstVersionInText, const string endVersionInText){
	if(firstVersionInText == endVersionInText){
		cout << "Great work" << endl;
	}else {
		cout << "Error" << endl;
	}
}

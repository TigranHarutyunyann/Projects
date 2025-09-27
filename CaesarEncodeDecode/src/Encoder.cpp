#include "Encoder.h"
using namespace std;

void Encoder::call(char arr[], int Move){
    for(int i=0; arr[i]!='\0'; i++) {
        char c = arr[i];

        if(c >= 'a' && c <= 'z'){
            arr[i] = 'a' + ( (c - 'a' + Move) % 26 );
        }
        else if(c >= 'A' && c <= 'Z'){
            arr[i] = 'A' + ( (c - 'A' + Move) % 26 );
        }
        else if(c >= '0' && c <= '9'){
            arr[i] = '0' + ( (c - '0' + Move) % 10 );
        }
        else {
            arr[i] = c;
        }
    }
}


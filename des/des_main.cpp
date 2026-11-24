#include <iostream>
#include <string>
#include "des.h"
using namespace std;

int main()
{
    cout << "Test vector" << endl;
    string c1 = desEncrypt("0000000000001111", "0000000000000000");
    cout << "ciphertext: " << c1 << endl;
    cout << endl;


    return 0;
}
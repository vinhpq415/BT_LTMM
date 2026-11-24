#include <iostream>
#include <string>
#include "aes.h"
using namespace std;

int main()
{
    cout << "Test vector 1 (lop)" << endl;
    string c1 = aesEncrypt("00000000000000000000000000001111", "00000000000000000000000000000000");
    cout << "ciphertext: " << c1 << endl;
    cout << endl;
    return 0;
}
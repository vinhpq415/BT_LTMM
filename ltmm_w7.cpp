#include <iostream>
#include <string>
#include "gf.h"

using namespace std;



int main()
{
    int m4 = 19;    // x^4 + x + 1                
    int m8 = 283;   // x^8 + x^4 + x^3 + x + 1    

    int n;
    cout << "Chon truong GF(2^n)";
    cin >> n;

    int m;
    if (n == 4) m = m4;
    else m = m8;

    string inputA, inputB;
    cout << "Nhap a(x): ";
    cin >> inputA;
    cout << "Nhap b(x): ";
    cin >> inputB;

    int a = binaryToInt(inputA);
    int b = binaryToInt(inputB);
    int c = gfMultiply(a, b, n, m);

    cout << "m(x) = ";
    printPoly(m);
    cout << endl;
    cout << "a(x) = ";
    printPoly(a);
    cout << endl;
    cout << "b(x) = ";
    printPoly(b);
    cout << endl;
    cout << "a(x) * b(x) = ";
    printPoly(c);
    cout << endl;

    return 0;
}

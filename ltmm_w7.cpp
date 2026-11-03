#include <iostream>
#include <string>
#include "gf.h"

using namespace std;



int main()
{
{
    int n;
    cout << "Chon truong GF(2^n) (4 hoac 8): ";
    cin >> n;

    // Kiem tra n
    int m = getModulus(n);
    if (m == 0) {
        cout << "Chi ho tro n = 4 hoac n = 8" << endl;
        return 1;
    }

    string inputA, inputB;
    cout << "Nhap a(x): ";
    cin >> inputA;
    cout << "Nhap b(x): ";
    cin >> inputB;

    // Kiem tra chuoi nhap vao chi co 0 va 1
    if (!isBinary(inputA) || !isBinary(inputB)) {
        cout << "a(x), b(x) chi duoc gom cac chu so 0 va 1" <<endl;
        return 1;
    }

    int a = binaryToInt(inputA);
    int b = binaryToInt(inputB);

    // Kiem tra bac cua a(x), b(x) phai nho hon n
    if (degree(a) >= n || degree(b) >= n) {
        cout << "Bac cua a(x), b(x) phai nho hon " << n << endl;
        return 1;
    }

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

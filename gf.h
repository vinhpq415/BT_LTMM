#ifndef GF_H
#define GF_H

#include <iostream>
#include <string>
using namespace std;

// In da thuc ra man hinh
void printPoly(int p)
{
    if (p == 0) {
        cout << "0";
        return;
    }
    bool first = true;
    for (int i = 15; i >= 0; i--) {
        if ((p >> i) & 1) {
            if (!first) cout << " + ";
            if (i == 0) cout << "1";
            else if (i == 1) cout << "x";
            else cout << "x^" << i;
            first = false;
        }
    }
}

//a(x) * b(x) mod m(x) tren GF(2^n)
int gfMultiply(int a, int b, int n, int m)
{
    int result = 0;
    for (int i = 0; i < n; i++) {
		// Neu bit thu i cua b bang 1 thi cong a vao result
        if ((b >> i) & 1) {
            result = result ^ a;
        }
        // Nhan a voi x: dich trai 1 bit
        a = a << 1;
        // Neu bac cua a = n thi tru di m(x) 
        if ((a >> n) & 1) {
            a = a ^ m;
        }
    }
    return result;
}

int binaryToInt(string s)
{
    int value = 0;
    for (int i = 0; i < s.length(); i++) {
        value = value * 2 + (s[i] - '0');
    }
    return value;
}

#endif
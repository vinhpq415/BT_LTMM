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

// Chon m(x) theo n, tra ve 0 neu n sai
int getModulus(int n)
{
    if (n == 4) return 19;    // x^4 + x + 1
    if (n == 8) return 283;   // x^8 + x^4 + x^3 + x + 1
    return 0;
}

// Kiem tra chuoi chi gom cac ky tu 'binary
bool isBinary(string s)
{
    if (s.length() == 0) return false;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != '0' && s[i] != '1') return false;
    }
    return true;
}

// Tim bac cua da thuc, da thuc 0 thi tra ve -1
int degree(int p)
{
    for (int i = 15; i >= 0; i--) {
        if ((p >> i) & 1) return i;
    }
    return -1;
}


#endif
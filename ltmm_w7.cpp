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

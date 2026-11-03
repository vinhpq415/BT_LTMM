#include <iostream>
#include <string>
#include "gf.h"
using namespace std;

int passCount = 0;
int failCount = 0;

// So sanh ket qua voi gia tri mong doi
void check(string testName, int result, int expected)
{
    if (result == expected) {
        cout << "[PASS] " << testName << endl;
        passCount++;
    } else {
        cout << "[FAIL] " << testName << ": ket qua = " << result << ", mong doi = " << expected << endl;
        failCount++;
    }
}

int main()
{
    int m4 = 19;    // x^4 + x + 1
    int m8 = 283;   // x^8 + x^4 + x^3 + x + 1

    // 1. Test ham binaryToInt
    check("binaryToInt 0", binaryToInt("0"), 0);
    check("binaryToInt 1011", binaryToInt("1011"), 11);
    check("binaryToInt 10011", binaryToInt("10011"), 19);

    // 2. Test GF(2^4), tinh tay
    // (x + 1)(x^2 + x + 1) = x^3 + 1, khong can rut gon
    int a = binaryToInt("0011");
    int b = binaryToInt("0111");
    check("GF(2^4): 0011 * 0111", gfMultiply(a, b, 4, m4), binaryToInt("1001"));

    // x^3 * x = x^4 = x + 1, co rut gon
    a = binaryToInt("1000");
    b = binaryToInt("0010");
    check("GF(2^4): 1000 * 0010", gfMultiply(a, b, 4, m4), binaryToInt("0011"));

    // 3. Test GF(2^8), vi du trong chuan AES
    a = binaryToInt("01010111");
    b = binaryToInt("10000011");
    check("GF(2^8): 01010111 * 10000011", gfMultiply(a, b, 8, m8), binaryToInt("11000001"));

    a = binaryToInt("01010011");
    b = binaryToInt("11001010");
    check("GF(2^8): 01010011 * 11001010", gfMultiply(a, b, 8, m8), binaryToInt("00000001"));

    // 4. Thu tat ca cac cap x, y trong GF(2^4)
    int errors = 0;
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) {
            int xy = gfMultiply(x, y, 4, m4);
            int yx = gfMultiply(y, x, 4, m4);
            // x * y phai bang y * x
            if (xy != yx) errors++;
            // ket qua phai nho hon 16
            if (xy >= 16) errors++;
        }
        // x * 1 phai bang x
        if (gfMultiply(x, 1, 4, m4) != x) errors++;
    }
    check("GF(2^4): thu tat ca cac cap", errors, 0);

    // 5. Test cac ham kiem tra dau vao
    check("getModulus(4)", getModulus(4), 19);
    check("getModulus(8)", getModulus(8), 283);
    check("getModulus(5) khong ho tro", getModulus(5), 0);

    check("isBinary 1011", isBinary("1011"), true);
    check("isBinary 102", isBinary("102"), false);
    check("isBinary abc", isBinary("abc"), false);

    check("degree(0)", degree(0), -1);
    check("degree(1)", degree(1), 0);
    check("degree(19)", degree(19), 4);
    check("degree(283)", degree(283), 8);

    cout << endl;
    cout << "Dung: " << passCount << ", Sai: " << failCount << endl;
    if (failCount > 0) {
        cout << "CO TEST BI SAI!" << endl;
        return 1;
    }
    cout << "TAT CA TEST DEU DUNG" << endl;
    return 0;
}
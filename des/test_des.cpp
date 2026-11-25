#include <iostream>
#include <string>
#include "des.h"
using namespace std;

int passCount = 0;
int failCount = 0;

void check(string testName, int result, int expected)
{
    if (result == expected) {
        cout << "Pass " << testName << endl;
        passCount++;
    } else {
        cout << "Fail " << testName << ": ket qua = " << result << ", mong doi = " << expected << endl;
        failCount++;
    }
}


void checkHex(string testName, string result, string expected)
{
    if (result == expected) {
        cout << "Pass " << testName << endl;
        passCount++;
    } else {
        cout << "Fail " << testName << ": ket qua = " << result << ", mong doi = " << expected << endl;
        failCount++;
    }
}

int main()
{
    string subkeys[16];

    // Cac ham nho
    checkHex("hexToBin A1", hexToBin("A1"), "10100001");
    checkHex("binToHex 10100001", binToHex("10100001"), "A1");
    checkHex("xorBits", xorBits("1100", "1010"), "0110");
    checkHex("leftShift", leftShift("10110", 2), "11010");

    
    generateSubkeys(hexToBin("0000000000000000"), subkeys);
    int zeroCount = 0;
    for (int i = 0; i < 16; i++) {
        if (binToHex(subkeys[i]) == "000000000000") {
            zeroCount++;
        }
    }
    check("khoa 0: so khoa con bang 0", zeroCount, 16);

    
    string ip = permute(hexToBin("0000000000001111"), IP, 64);
    checkHex("vector lop: IP", binToHex(ip), "00C000C000000000");
    string right = ip.substr(32, 32);
    checkHex("vector lop: f(R0, K1)", binToHex(feistel(right, subkeys[0])), "D8D8DBBC");

    
    generateSubkeys(hexToBin("133457799BBCDFF1"), subkeys);
    checkHex("vector chuan: K1", binToHex(subkeys[0]), "1B02EFFC7072");
    checkHex("vector chuan: K16", binToHex(subkeys[15]), "CB3D8B0E17F5");

   
    cout.setstate(ios::failbit);
    string c = desEncrypt("0000000000001111", "0000000000000000");
    
    // Khoa yeu: ma hoa 2 lan se ra lai ban ro
    string twice = desEncrypt(c, "0000000000000000");
    cout.clear();
    checkHex("ciphertext vector lop", c, "9DA00EAA3FFC2AED");
    
    checkHex("khoa yeu: ma hoa 2 lan ra lai ban ro", twice, "0000000000001111");

    cout << endl;
    cout << "Dung: " << passCount << ", Sai: " << failCount << endl;
    if (failCount > 0) {
        cout << "Sai" << endl;
        return 1;
    }
    cout << "Dung" << endl;
    return 0;
}
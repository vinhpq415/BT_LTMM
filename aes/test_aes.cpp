#include <iostream>
#include <string>
#include "aes.h"
using namespace std;

int passCount = 0;
int failCount = 0;


void check(string testName, int result, int expected)
{
    if (result == expected) {
        cout << "pass " << testName << endl;
        passCount++;
    } else {
        cout << "fail " << testName << ": ket qua = " << result << ", mong doi = " << expected << endl;
        failCount++;
    }
}


void checkHex(string testName, string result, string expected)
{
    if (result == expected) {
        cout << "pass " << testName << endl;
        passCount++;
    } else {
        cout << "fail " << testName << ": ket qua = " << result << ", mong doi = " << expected << endl;
        failCount++;
    }
}

int main()
{
    // y = A * x^(-1) + C
    check("nghich dao cua 0x11 la 0xB4", gfMultiply(0x11, 0xB4, 8, 283), 1);
    check("sbox(0x00)", sbox(0x00), 0x63);
    check("sbox(0x11)", sbox(0x11), 0x82);

    // round key 
    int key[16];
    int roundKeys[11][16];
    hexToBytes("00000000000000000000000000000000", key);
    keyExpansion(key, roundKeys);
    checkHex("round key 0", bytesToHex(roundKeys[0], 16), "00000000000000000000000000000000");
    checkHex("round key 1", bytesToHex(roundKeys[1], 16), "62636363626363636263636362636363");
    checkHex("round key 10", bytesToHex(roundKeys[10], 16), "b4ef5bcb3e92e21123e951cf6f8f188e");

    
    int state[16];
    hexToBytes("00000000000000000000000000001111", state);
    addRoundKey(state, roundKeys[0]);
    checkHex("vong 0: AddRoundKey", bytesToHex(state, 16), "00000000000000000000000000001111");
    subBytes(state);
    checkHex("vong 1: SubBytes", bytesToHex(state, 16), "63636363636363636363636363638282");
    shiftRows(state);
    checkHex("vong 1: ShiftRows", bytesToHex(state, 16), "63636382636382636363636363636363");
    mixColumns(state);
    checkHex("vong 1: MixColumns", bytesToHex(state, 16), "82825bba825bba826363636363636363");
    addRoundKey(state, roundKeys[1]);
    checkHex("vong 1: AddRoundKey", bytesToHex(state, 16), "e0e138d9e038d9e10100000001000000");

    // Tat in ra man hinh trong luc chay aesEncrypt, roi bat lai
    cout.setstate(ios::failbit);
    string c = aesEncrypt("00000000000000000000000000001111", "00000000000000000000000000000000");
    cout.clear();
    checkHex("ciphertext vector", c, "442758df6dda9edb6bf1468a17b93fe5");
    

    cout << endl;
    cout << "Dung: " << passCount << ", Sai: " << failCount << endl;
    if (failCount > 0) {
        cout << "Sai" << endl;
        return 1;
    }
    cout << "Dung" << endl;
    return 0;
}
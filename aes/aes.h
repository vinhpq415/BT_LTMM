#ifndef AES_H
#define AES_H

#include <iostream>
#include <string>
#include "../gf.h"
using namespace std;

int hexCharToInt(char ch)
{
    if (ch >= '0' && ch <= '9') return ch - '0';
    if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
    return ch - 'A' + 10;
}

void hexToBytes(string hex, int bytes[16])
{
    for (int i = 0; i < 16; i++) {
        bytes[i] = hexCharToInt(hex[2 * i]) * 16 + hexCharToInt(hex[2 * i + 1]);
    }
}

string bytesToHex(int bytes[], int n)
{
    string digits = "0123456789abcdef";
    string result = "";
    for (int i = 0; i < n; i++) {
        result = result + digits[bytes[i] / 16];
        result = result + digits[bytes[i] % 16];
    }
    return result;
}

// S-box: y = A * x^(-1) + C
int sbox(int x)
{
    //x^(-1)
    int inv = 0;
    for (int i = 1; i < 256; i++) {
        if (gfMultiply(x, i, 8, 283) == 1) {
            inv = i;
        }
    }
    int c = 0x63;
    int y = 0;
    for (int i = 0; i < 8; i++) {
        int bit = ((inv >> i) & 1)
                ^ ((inv >> ((i + 4) % 8)) & 1)
                ^ ((inv >> ((i + 5) % 8)) & 1)
                ^ ((inv >> ((i + 6) % 8)) & 1)
                ^ ((inv >> ((i + 7) % 8)) & 1)
                ^ ((c >> i) & 1);
        y = y | (bit << i);
    }
    return y;
}

//thay sbox
void subBytes(int state[16])
{
    for (int i = 0; i < 16; i++) {
        state[i] = sbox(state[i]);
    }
}

//shif row
void shiftRows(int state[16])
{
    int temp[16];
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            temp[4 * c + r] = state[4 * ((c + r) % 4) + r];
        }
    }
    for (int i = 0; i < 16; i++) {
        state[i] = temp[i];
    }
}

void mixColumns(int state[16])
{
    int temp[16];
    for (int c = 0; c < 4; c++) {
        int a0 = state[4 * c];
        int a1 = state[4 * c + 1];
        int a2 = state[4 * c + 2];
        int a3 = state[4 * c + 3];
        temp[4 * c]     = gfMultiply(a0, 2, 8, 283) ^ gfMultiply(a1, 3, 8, 283) ^ a2 ^ a3;
        temp[4 * c + 1] = a0 ^ gfMultiply(a1, 2, 8, 283) ^ gfMultiply(a2, 3, 8, 283) ^ a3;
        temp[4 * c + 2] = a0 ^ a1 ^ gfMultiply(a2, 2, 8, 283) ^ gfMultiply(a3, 3, 8, 283);
        temp[4 * c + 3] = gfMultiply(a0, 3, 8, 283) ^ a1 ^ a2 ^ gfMultiply(a3, 2, 8, 283);
    }
    for (int i = 0; i < 16; i++) {
        state[i] = temp[i];
    }
}

void addRoundKey(int state[16], int roundKey[16])
{
    for (int i = 0; i < 16; i++) {
        state[i] = state[i] ^ roundKey[i];
    }
}

// Sinh 11 round key tu khoa 16 byte
void keyExpansion(int key[16], int roundKeys[11][16])
{
    int w[44][4];
    // 4 word dau la chinh khoa
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            w[i][j] = key[4 * i + j];
        }
    }
    int rcon = 1;
    for (int i = 4; i < 44; i++) {
        int temp[4];
        for (int j = 0; j < 4; j++) {
            temp[j] = w[i - 1][j];
        }
        if (i % 4 == 0) {
            // RotWord: dich vong trai 1 byte
            int first = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = first;
            // SubWord: qua sbox
            for (int j = 0; j < 4; j++) {
                temp[j] = sbox(temp[j]);
            }
            // XOR Rcon vao byte dau, roi nhan rcon voi 2
            temp[0] = temp[0] ^ rcon;
            rcon = gfMultiply(rcon, 2, 8, 283);
        }
        for (int j = 0; j < 4; j++) {
            w[i][j] = w[i - 4][j] ^ temp[j];
        }
    }
    // 4 word = 1 roundkey
    for (int r = 0; r < 11; r++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                roundKeys[r][4 * i + j] = w[4 * r + i][j];
            }
        }
    }
}

string aesEncrypt(string plainHex, string keyHex)
{
    int state[16];
    int key[16];
    int roundKeys[11][16];
    hexToBytes(plainHex, state);
    hexToBytes(keyHex, key);
    keyExpansion(key, roundKeys);

    cout << "plaintext : " << plainHex << endl;
    cout << "key       : " << keyHex << endl;

    // Vong 0: chi AddRoundKey
    cout << "round 0" << endl;
    cout << "roundkey  : " << bytesToHex(roundKeys[0], 16) << endl;
    addRoundKey(state, roundKeys[0]);
    cout << "after ark : " << bytesToHex(state, 16) << endl;

    for (int round = 1; round <= 10; round++) {
        cout << "round " << round << endl;
        cout << "start     : " << bytesToHex(state, 16) << endl;
        subBytes(state);
        cout << "subbytes  : " << bytesToHex(state, 16) << endl;
        shiftRows(state);
        cout << "shiftrows : " << bytesToHex(state, 16) << endl;
        // Vong cuoi khong co MixColumns
        if (round < 10) {
            mixColumns(state);
            cout << "mixcols   : " << bytesToHex(state, 16) << endl;
        }
        cout << "roundkey  : " << bytesToHex(roundKeys[round], 16) << endl;
        addRoundKey(state, roundKeys[round]);
    }
    return bytesToHex(state, 16);
}

#endif
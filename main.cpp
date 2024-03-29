#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <cmath>
#include <string>
#include <iomanip>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

unsigned char sBox[256] = {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

unsigned char rcon[256] = {
    0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
    0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39,
    0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a,
    0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,
    0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef,
    0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc,
    0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b,
    0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3,
    0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94,
    0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20,
    0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35,
    0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f,
    0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04,
    0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63,
    0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd,
    0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d
};

unsigned char invSbox[256] = {
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};

void printState(unsigned char* state) {
    cout << hex;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 16; j += 4) {
            cout << right << setfill('0') << setw(2) << static_cast<unsigned int>(state[i + j]) << " ";
        }
        cout << endl;
    }

    cout << dec;
}

unsigned char gmul(uint8_t a, uint8_t b) {
    uint8_t p = 0; /* the product of the multiplication */
    unsigned char x;
    while (a && b) {
        if (b & 1) /* if b is odd, then add the corresponding a to p (final product = sum of all a's corresponding to odd b's) */
            p ^= a; /* since we're in GF(2^m), addition is an XOR */

        if (a & 0x80) /* GF modulo: if a >= 128, then it will overflow when shifted left, so reduce */
            a = (a << 1) ^ 0x1b; /* XOR with the primitive polynomial x^8 + x^4 + x^3 + x + 1 (0b1_0001_1011) � you can change it but it must be irreducible */
        else
            a <<= 1; /* equivalent to a*2 */
        b >>= 1; /* equivalent to b // 2 */
    }

    x = p;

    return x;
}

void addRoundKey(unsigned char* state, unsigned char* roundKey) {
    for (int i = 0; i < 16; i++) {
        state[i] = static_cast<unsigned int>(state[i]^roundKey[i]);
    }
}

void subBytes(unsigned char* state) {
    for (int i = 0; i < 16; i++) {
        state[i] = sBox[state[i]];
    }
}

void shiftRows(unsigned char* state) {
    //Second Row
    int one = state[1], two = state[5], three = state[9], four = state[13];

    state[9] = four;
    state[5] = three;
    state[1] = two;
    state[13] = one;

    //Third Row
    one = state[2], two = state[6], three = state[10], four = state[14];

    state[2] = three;
    state[6] = four;
    state[10] = one;
    state[14] = two;

    //Fourth Row
    one = state[3], two = state[7], three = state[11], four = state[15];

    state[3] = four;
    state[7] = one;
    state[11] = two;
    state[15] = three;
}

void mixColumns(unsigned char* state) {
    unsigned char newBox[16] = {};

    for (int i = 0; i < 16; i++) {
        newBox[i] = state[i];
    }

    unsigned char tBoxOne, tBoxTwo, tBoxThree, tBoxFour, tBoxMinusOne, tBoxMinusTwo, tBoxMinusThree;

    for (int i = 0; i < 16; i++) {
        if (i == 0 || i == 4 || i == 8 || i == 12) {
            state[i] = (gmul(2, newBox[i]))^(gmul(2, newBox[i+1])^newBox[i+1])^newBox[i+2]^newBox[i+3];
        } else if (i == 1 || i == 5 || i == 9 || i == 13) {
            state[i] = newBox[i-1] ^ (gmul(2, newBox[i])) ^ (gmul(2, newBox[i+1])^newBox[i+1]) ^ newBox[i+2];
        } else if (i == 2 || i == 6 || i == 10 || i == 14) {
            state[i] = newBox[i-2] ^ newBox[i-1] ^ (gmul(2, newBox[i])) ^ (gmul(2, newBox[i+1])^newBox[i+1]);
        } else if (i == 3 || i == 7 || i == 11 || i == 15) {
            state[i] = (gmul(2, newBox[i-3])^newBox[i-3]) ^ newBox[i-2] ^ newBox[i-1] ^ (gmul(2, newBox[i]));
        }
    }
}

void inverseSubBytes(unsigned char *state) {
    for (int i = 0; i < 16; i++){
        state[i] = invSbox[state[i]];
    }
}

void wordPadding(unsigned char *state) {
    int stateLen = strlen((char*)state);

    if (stateLen < 16) {
        int padd = 16 - stateLen;

        for (int j = 16 - padd; j < 16; j++) {
            state[j] = padd;
        }
    }
}

void inverseShiftRows(unsigned char *state) {
    //Second Row
    int one = state[1], two = state[5], three = state[9], four = state[13];

    state[9] = two;
    state[5] = one;
    state[1] = four;
    state[13] = three;

    //Third Row
    one = state[2], two = state[6], three = state[10], four = state[14];

    state[2] = three;
    state[6] = four;
    state[10] = one;
    state[14] = two;

    //Fourth Row
    one = state[3], two = state[7], three = state[11], four = state[15];

    state[3] = two;
    state[7] = three;
    state[11] = four;
    state[15] = one;
}

void inverseMixColumns(unsigned char *state) {
    unsigned char newBox[16] = {};

    for (int i = 0; i < 16; i++) {
        newBox[i] = state[i];
    }

    unsigned char tBoxOne, tBoxTwo, tBoxThree, tBoxFour, tBoxMinusOne, tBoxMinusTwo, tBoxMinusThree;

    for (int i = 0; i < 16; i++) {
        if (i == 0 || i == 4 || i == 8 || i == 12) {
            state[i] = gmul(14, newBox[i])^gmul(11, newBox[i+1])^gmul(13, newBox[i+2])^gmul(9, newBox[i+3]);
        } else if (i == 1 || i == 5 || i == 9 || i == 13) {
            state[i] = gmul(9, newBox[i-1]) ^ gmul(14, newBox[i])^gmul(11, newBox[i+1])^gmul(13, newBox[i+2]);
        } else if (i == 2 || i == 6 || i == 10 || i == 14) {
            state[i] = gmul(13, newBox[i-2])^gmul(9, newBox[i-1])^gmul(14, newBox[i])^gmul(11, newBox[i+1]);
        } else if (i == 3 || i == 7 || i == 11 || i == 15) {
            state[i] = gmul(11, newBox[i-3]) ^ gmul(13, newBox[i-2]) ^ gmul(9, newBox[i-1]) ^ gmul(14, newBox[i]);
        }
    }
}

void rotWord(unsigned char *w) {
    unsigned char t = w[0];
    w[0] = w[1];
    w[1] = w[2];
    w[2] = w[3];
    w[3] = t;
}

void subWord(unsigned char *w) {
    unsigned char t = w[0];
    w[0] = sBox[w[0]];
    w[1] = sBox[w[1]];
    w[2] = sBox[w[2]];
    w[3] = sBox[w[3]];
}

void expandKey(unsigned char *key, unsigned char *expandedKey) {
    for (int i = 0; i < 16; i++) {
        expandedKey[i] = key[i];
    }

    int i = 16;
    int rconIt = 1;
    unsigned char w[4];

    while (i < 176) {
        for (int j = 0; j < 4; j++) {
            w[j] = expandedKey[j + i - 4];
        }

        if (i % 16 == 0) {
            rotWord(w);
            subWord(w);
            w[0] ^= rcon[rconIt++];
        }

        for (unsigned char a = 0; a < 4; a++) {
            expandedKey[i] = expandedKey[i - 16] ^ w[a];
            i++;
        }
    }
}

void aesEncrypt(unsigned char *plaintxt, unsigned char *expandedKey) {
    // initial round key addition
    addRoundKey(plaintxt, expandedKey);

    // rounds 1 - 9
    for (int i = 0; i < 9; i++) {
        subBytes(plaintxt);
        shiftRows(plaintxt);
        mixColumns(plaintxt);
        addRoundKey(plaintxt, &expandedKey[(16 * i) + 16]);
    }

    // final round 10 without mixColumns
    subBytes(plaintxt);
    shiftRows(plaintxt);
    addRoundKey(plaintxt, &expandedKey[160]);
}

void ustrncpy(unsigned char *dest, unsigned char *src, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

void uxorn(unsigned char *dest, unsigned char *src, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] ^= src[i];
    }
}

void aesDecrypt(unsigned char *cyphertxt, unsigned char *expandedKey) {
    // initial round key addition
    addRoundKey(cyphertxt, &expandedKey[160]);

    // rounds 1 - 9
    for (int i = 9; i > 0; i--) {
        inverseShiftRows(cyphertxt);
        inverseSubBytes(cyphertxt);
        addRoundKey(cyphertxt, &expandedKey[16 * i]);
        inverseMixColumns(cyphertxt);
    }

    // final round 10 without inverseMixColumns
    inverseShiftRows(cyphertxt);
    inverseSubBytes(cyphertxt);
    addRoundKey(cyphertxt, expandedKey);
}

void cbcEncrypt(string infname, string outfname, string keyfname, string ivfname) {
    FILE *keyfile = fopen(keyfname.c_str(), "rb");
    FILE *ivfile = fopen(ivfname.c_str(), "rb");
    FILE *infile = fopen(infname.c_str(), "rb");
    FILE *outfile = fopen(outfname.c_str(), "wb");

    if (keyfile == NULL || ivfile == NULL || infile == NULL || outfile == NULL) {
        perror("Error opening file");
        exit(1);
    }

    int bytesRead;

    unsigned char key[16];
    unsigned char iv[16];

    bytesRead = fread(key, 1, 16, keyfile);
    if (bytesRead != 16) {
        cout << "Error: key file should contain atleast 16 bytes" << endl;
        exit(1);
    }
    fread(iv, 1, 16, ivfile);

    if (bytesRead != 16) {
        cout << "Error: ivfile file should contain atleast 16 bytes" << endl;
        exit(1);
    }

    fclose(keyfile);
    fclose(ivfile);

    unsigned char expandedKey[176];

    unsigned char bytes[16];
    unsigned char oldBytes[16];

    ustrncpy(oldBytes, iv, 16);

    expandKey(key, expandedKey);

    // CBC encrypt
    while ((bytesRead = fread(bytes, 1, 16, infile)) == 16) {
        uxorn(bytes, oldBytes, 16);
        aesEncrypt(bytes, expandedKey);
        fwrite(bytes, 1, bytesRead, outfile);
        ustrncpy(oldBytes, bytes, 16);
    }

    // handle last bytes
    if (bytesRead != 0) {
        int padd;
        padd = 16 - bytesRead;
        for (int i = bytesRead; i < 16; i++) {
            bytes[i] = padd;
        }
        uxorn(bytes, oldBytes, 16);
        aesEncrypt(bytes, expandedKey);
        fwrite(bytes, 1, 16, outfile);
        ustrncpy(oldBytes, bytes, 16);
    }

    fclose(infile);
    fclose(outfile);
}

void cbcDecrypt(string infname, string outfname, string keyfname, string ivfname) {
    FILE *keyfile = fopen(keyfname.c_str(), "rb");
    FILE *ivfile = fopen(ivfname.c_str(), "rb");
    FILE *infile = fopen(infname.c_str(), "rb");
    FILE *outfile = fopen(outfname.c_str(), "wb");

    if (keyfile == NULL || ivfile == NULL || infile == NULL || outfile == NULL) {
        perror("Error opening file");
        exit(1);
    }

    int bytesRead;

    unsigned char key[16];
    unsigned char iv[16];

    bytesRead = fread(key, 1, 16, keyfile);
    if (bytesRead != 16) {
        cout << "Error: key file should contain atleast 16 bytes" << endl;
        exit(1);
    }
    fread(iv, 1, 16, ivfile);

    if (bytesRead != 16) {
        cout << "Error: ivfile file should contain atleast 16 bytes" << endl;
        exit(1);
    }

    fclose(keyfile);
    fclose(ivfile);

    unsigned char expandedKey[176];

    unsigned char bytes[16];
    unsigned char oldBytes[16];
    unsigned char veryOldBytes[16];

    unsigned char checkBytes[16];
    int checkedBytes;
    fpos_t pos;

    ustrncpy(oldBytes, iv, 16);

    expandKey(key, expandedKey);

    ustrncpy(veryOldBytes, iv, 16);


    // CBC decrypt
    while ((bytesRead = fread(bytes, 1, 16, infile)) == 16) {
        fgetpos(infile,&pos);
        checkedBytes = fread(checkBytes, 1, 16, infile);

        if (checkedBytes == 0) {
            aesDecrypt(bytes, expandedKey);
            uxorn(bytes, veryOldBytes, 16);
            int equalCount = 0;
            int lastCharVal = (int)bytes[15];

            for (int i = 15; i > 0; i--){
                if ((int)bytes[i] == lastCharVal) {
                    equalCount++;
                } else {
                    break;
                }
            }

            if (equalCount > 1) {
                fwrite(&bytes, 1, (16 - equalCount), outfile);
            } else {
                fwrite(bytes, 1, bytesRead, outfile);
            }

            break;
        } else {
            // Give the value to bytes;
            fsetpos(infile,&pos);
        }

        ustrncpy(oldBytes, bytes, 16);
        aesDecrypt(bytes, expandedKey);
        uxorn(bytes, veryOldBytes, 16);
        fwrite(bytes, 1, bytesRead, outfile);
        ustrncpy(veryOldBytes, oldBytes, 16);
    }

    fclose(infile);
    fclose(outfile);
}

int main() {
    string infname, outfname, keyfname, ivfname;
    int mode;

    cout << "Choose mode" << endl
         << "1. Encrypt" << endl
         << "2. Decrypt" << endl
         << "Choose: ";
    cin >> mode;

    if (mode != 1 && mode != 2) {
        cout << "Error: no such mode" << endl;
        return -1;
    }

    cout << "Enter input filename: ";
    cin >> infname;

    cout << "Enter output filename: ";
    cin >> outfname;

    cout << "Enter key filename: ";
    cin >> keyfname;

    cout << "Enter iv filename: ";
    cin >> ivfname;

    if (mode == 1) {
        cbcEncrypt(infname, outfname, keyfname, ivfname);
        cout << "ENCRIPTION SUCCESSFUL" << endl;
    } else {
        cbcDecrypt(infname, outfname, keyfname, ivfname);
        cout << "DECRYPTION SUCCESSFUL" << endl;
    }

    return 0;
}

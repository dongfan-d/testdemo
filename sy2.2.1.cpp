#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char BYTE;  // 8位字节
typedef unsigned long DWORD; // 32位无符号整数

// 初始置换表 IP
int IP[] = { 
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17,  9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// 逆初始置换 IP^-1
int IP_INV[] = { 
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41,  9, 49, 17, 57, 25
};

// 初始置换
void initialPermutation(BYTE *block) {
    BYTE temp[8];
    for (int i = 0; i < 8; i++) temp[i] = block[i];
    for (int i = 0; i < 64; i++) {
        int pos = IP[i] - 1;
        int byte_pos = pos / 8;
        int bit_pos = pos % 8;
        if (temp[byte_pos] & (1 << (7 - bit_pos))) {
            block[i / 8] |= (1 << (7 - (i % 8)));
        } else {
            block[i / 8] &= ~(1 << (7 - (i % 8)));
        }
    }
}

// 逆初始置换
void inverseInitialPermutation(BYTE *block) {
    BYTE temp[8];
    for (int i = 0; i < 8; i++) temp[i] = block[i];
    for (int i = 0; i < 64; i++) {
        int pos = IP_INV[i] - 1;
        int byte_pos = pos / 8;
        int bit_pos = pos % 8;
        if (temp[byte_pos] & (1 << (7 - bit_pos))) {
            block[i / 8] |= (1 << (7 - (i % 8)));
        } else {
            block[i / 8] &= ~(1 << (7 - (i % 8)));
        }
    }
}

// DES 轮函数（简化版，仅示例）
void desFeistel(BYTE *block, BYTE *subkey) {
    // 这里只是一个占位函数，完整实现需要 S 盒、扩展置换、XOR 操作等
    for (int i = 0; i < 8; i++) {
        block[i] ^= subkey[i];
    }
}

// DES 加密（简化版）
void desEncrypt(BYTE *plaintext, BYTE *key, BYTE *ciphertext) {
    memcpy(ciphertext, plaintext, 8);
    initialPermutation(ciphertext);
    for (int i = 0; i < 16; i++) {
        desFeistel(ciphertext, key);  // 这里用密钥做简单 XOR 处理
    }
    inverseInitialPermutation(ciphertext);
}

// DES 解密（简化版）
void desDecrypt(BYTE *ciphertext, BYTE *key, BYTE *plaintext) {
    memcpy(plaintext, ciphertext, 8);
    initialPermutation(plaintext);
    for (int i = 0; i < 16; i++) {
        desFeistel(plaintext, key);  // 轮函数与加密相同（简化版）
    }
    inverseInitialPermutation(plaintext);
}

// 测试函数
int main() {
 BYTE plaintext[9] = "DES TEST";  // 长度 9，包含 '\0'
  // 8 字节明文
    BYTE key[9] = "12345678";        // 8 字节密钥
    BYTE ciphertext[8];
    BYTE decrypted[8];

    printf("原始明文: %s\n", plaintext);

    // 加密
    desEncrypt(plaintext, key, ciphertext);
    printf("加密后数据: ");
    for (int i = 0; i < 8; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    // 解密
    desDecrypt(ciphertext, key, decrypted);
    printf("解密后明文: %s\n", decrypted);

    return 0;
}



#include <stdint.h>

// Rotation macros
#define ROR(x, r) ((x >> r) | (x << (16 - r)))
#define ROL(x, r) ((x << r) | (x >> (16 - r)))

// Key schedule function
void speck32_key_schedule(const uint16_t K[4], uint16_t round_keys[22]) {
    uint16_t b = K[0], a[3] = {K[1], K[2], K[3]};
    round_keys[0] = b;
    for (int i = 0; i < 21; i++) {
        a[i % 3] = (ROL(a[i % 3], 7) + b) ^ i;
        b = ROR(b, 2) ^ a[i % 3];
        round_keys[i + 1] = b;
    }
}

// Encryption function
void speck32_encrypt(uint16_t block[2], const uint16_t round_keys[22]) {
    uint16_t x = block[0], y = block[1];
    for (int i = 0; i < 22; i++) {
        x = (ROR(x, 7) + y) ^ round_keys[i];
        y = ROL(y, 2) ^ x;
    }
    block[0] = x; block[1] = y;
}

// Decryption function
void speck32_decrypt(uint16_t block[2], const uint16_t round_keys[22]) {
    uint16_t x = block[0], y = block[1];
    for (int i = 21; i >= 0; i--) {
        y = ROR(y ^ x, 2);
        x = ROL((x ^ round_keys[i]) - y, 7);
    }
    block[0] = x; block[1] = y;
}

// Example usage:
/*
#include <stdio.h>
int main() {
    uint16_t key[4] = {0x1918, 0x1110, 0x0908, 0x0100}; // 64-bit key
    uint16_t data[2] = {0x6574, 0x694c}; // 32-bit data (as two 16-bit words)
    uint16_t round_keys[22];

    speck32_key_schedule(key, round_keys);

    speck32_encrypt(data, round_keys);
    printf("Encrypted: %04X %04X\n", data[0], data[1]);

    speck32_decrypt(data, round_keys);
    printf("Decrypted: %04X %04X\n", data[0], data[1]); // Original data

    return 0;
}
*/


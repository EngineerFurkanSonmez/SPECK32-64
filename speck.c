#include "speck.h"

// Key schedule function
void speck32_key_schedule(const uint16_t K[4], uint16_t round_keys[22]) {
    uint16_t b = K[0], a[3] = {K[1], K[2], K[3]};
    round_keys[0] = b;
    for (int i = 0; i < 21; i++) {
        // Corrected based on Speck paper: l_i+m-1 = (k_i + ROR^alpha(l_i)) XOR i
        // alpha = 7 for key schedule
        a[i % 3] = (ROR(a[i % 3], 7) + b) ^ i;
        // Corrected based on Speck paper: k_i+1 = ROL^beta(k_i) XOR l_i+m-1
        // beta = 2 for key schedule
        b = ROL(b, 2) ^ a[i % 3];
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
        x = ROL(((x ^ round_keys[i]) - y), 7); // Added parentheses for clarity
    }
    block[0] = x; block[1] = y;
}

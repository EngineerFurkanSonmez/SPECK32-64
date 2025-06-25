#ifndef SPECK_H
#define SPECK_H

#include <stdint.h>

// Rotation macros
#define ROR(x, r) ((x >> r) | (x << (16 - r)))
#define ROL(x, r) ((x << r) | (x >> (16 - r)))

// Key schedule function
void speck32_key_schedule(const uint16_t K[4], uint16_t round_keys[22]);

// Encryption function
void speck32_encrypt(uint16_t block[2], const uint16_t round_keys[22]);

// Decryption function
void speck32_decrypt(uint16_t block[2], const uint16_t round_keys[22]);

#endif // SPECK_H

#include <stdio.h>
#include "speck.h"

// Example usage:
int main() {
    // Test Vector for Speck32/64
    // Using original data from the repo to test encrypt/decrypt round trip
    uint16_t key[4] = {0x1918, 0x1110, 0x0908, 0x0100};
    uint16_t data[2] = {0x6574, 0x694c};
    uint16_t original_plaintext[2] = {0x6574, 0x694c};
    uint16_t round_keys[22];

    printf("Original Plaintext: %04X %04X\n", data[0], data[1]);
    speck32_key_schedule(key, round_keys);

    speck32_encrypt(data, round_keys);
    printf("Encrypted Ciphertext: %04X %04X\n", data[0], data[1]);

    speck32_decrypt(data, round_keys);
    printf("Decrypted Plaintext: %04X %04X\n", data[0], data[1]);

    if (data[0] == original_plaintext[0] && data[1] == original_plaintext[1]) {
        printf("SUCCESS: Decryption matches original plaintext!\n");
    } else {
        printf("FAILURE: Decryption DOES NOT match original plaintext!\n");
    }

    return 0;
}

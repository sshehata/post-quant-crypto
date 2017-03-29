#ifndef REFERENCE_H
#define REFERENCE_H

#include "types.h"
#include "list.h"

#include <stdbool.h>

//void key_gen(size_t k, size_t n, uint8_t S_inv[k][BYTES(k)], uint8_t G[n][BYTES(k)], uint8_t P_inv[n][BYTES(n)], uint8_t G_pub[n][BYTES(k)]);
void key_gen(size_t k, size_t n, size_t s, uint8_t S_inv[k][BYTES(k)], uint8_t G[n][BYTES(k)], uint8_t P_inv[s][n][BYTES(n)], uint8_t G_pub[s][n][BYTES(k)]);
void encrypt(size_t k, size_t n, size_t s, uint8_t G_pub[s][n][BYTES(k)], uint8_t m[BYTES(k)], uint8_t e[BYTES(n)], uint8_t c[s][BYTES(n)]);
void decrypt(size_t k, size_t n, size_t s, uint8_t S_inv[k][BYTES(k)], uint8_t G[n][BYTES(k)], uint8_t P_inv[s][n][BYTES(n)], uint8_t z[BYTES(n)], List *decrypted);
unsigned int sign(size_t k, size_t n, uint8_t S_inv[k][BYTES(k)], uint8_t G[n][BYTES(k)], unsigned int inv_perm[n / 2], uint8_t z[BYTES(n)], uint8_t signature[BYTES(k)]);
bool verify(size_t k, size_t n, uint8_t G_pub[n][BYTES(k)], uint8_t z[BYTES(n)], uint8_t sig[BYTES(k)]);
void decode(size_t k, size_t n, uint8_t G[n][BYTES(k)], uint8_t y[BYTES(n)], List *Lp);

#endif

#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>

#include "types.h"
#include "list.h"

void random_vector(size_t d, uint8_t v[BYTES(d)]);
void random_error(size_t start, size_t len, uint8_t e[BYTES(len)]);
void random_matrix(size_t rows, size_t columns, uint8_t a[columns][BYTES(rows)]);
void identity_matrix(size_t k, size_t n, uint8_t a[k][BYTES(n)]);
bool equals(size_t k, uint8_t a[BYTES(k)], uint8_t b[BYTES(k)]);
void all_errors(List *v, size_t d, size_t k, uint8_t e_[BYTES(k)]);

uint8_t scalar_prod(size_t rows, size_t columns, size_t column, uint8_t v[BYTES(rows)], uint8_t A[columns][BYTES(rows)]);
void vector_matrix_mult(size_t rows, size_t columns, uint8_t v[BYTES(rows)], uint8_t A[columns][BYTES(rows)], uint8_t w[BYTES(columns)]);
void multiply(size_t rows, size_t columns, size_t column, uint8_t in[BYTES(rows)], uint8_t A[columns][BYTES(rows)], uint8_t out[BYTES(columns)]);
void matrix_multiply(size_t k, size_t p, size_t n, uint8_t a[p][BYTES(k)], uint8_t b[n][BYTES(p)], uint8_t c[n][BYTES(k)]);
unsigned int rank(size_t k, size_t n, uint8_t a[n][BYTES(k)]);
unsigned int invert(size_t dim, uint8_t a[dim][BYTES(dim)], uint8_t b[dim][BYTES(dim)]);


uint8_t randr(unsigned int min, unsigned int max);
uint8_t get_bit(uint8_t a, size_t i);
uint8_t MSB_mask(size_t t);
void BytewiseOperation(uint8_t (*operator)(uint8_t, uint8_t), size_t k, size_t start, size_t end, uint8_t a[BYTES(k)], uint8_t b[BYTES(k)], uint8_t c[BYTES(k)]);

uint8_t and(uint8_t a, uint8_t b);
uint8_t xor(uint8_t a, uint8_t b);
void random_permutation(size_t k, unsigned int a[k]);
size_t sum(size_t k, const unsigned int a[k]);
size_t min(unsigned int a, unsigned int b);

#endif




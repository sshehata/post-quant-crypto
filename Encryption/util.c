#include "util.h"

#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include <stdio.h>

static unsigned int gaussian_elimination(size_t dim, uint8_t a[dim][BYTES(dim)]);
static void add_pivot(size_t dim, uint8_t a[dim][BYTES(dim)], size_t pivot_row, size_t pivot_column);
static void swap_columns(size_t k, size_t n, uint8_t a[n][BYTES(k)], size_t i, size_t j);
static bool is_pivot(size_t rows, uint8_t column[BYTES(rows)], size_t row_elem);
static void transpose(size_t p, size_t q, uint8_t a[q][BYTES(p)], uint8_t a_t[p][BYTES(q)]);
static void get_row(size_t k, size_t n, uint8_t a[n][BYTES(k)], size_t row, uint8_t a_row[BYTES(n)]);

uint8_t and(uint8_t a, uint8_t b) { return a & b; }
uint8_t xor(uint8_t a, uint8_t b) { return a ^ b; }

uint8_t get_bit(uint8_t a, size_t i)
{
	return (a >> (7 - (i % 8))) & 1;
}

/*
 * Mask out the overflowing bits when the number of rows/columns 
 * does not fit exactly in to X bytes. 
 */
uint8_t MSB_mask(size_t t)
{
	return (0xff << (8 - t % 8));
}

uint8_t LSB_mask(size_t t)
{
	return MSB_mask(t) ^ 0xff;
}

size_t sum(size_t k, const unsigned int a[k])
{
    size_t sum = 0;
    for (size_t i = 0; i < k; i++){
        sum += a[i];
    }
    return sum;
}

size_t min(unsigned int a, unsigned int b)
{
    return a <= b ? a : b;
}

/* Combine a and b byte-for-byte using a supplied binary operator  */ 
void BytewiseOperation(uint8_t (*operator)(uint8_t, uint8_t), size_t k, size_t start, size_t end,
			uint8_t a[BYTES(k)], uint8_t b[BYTES(k)], uint8_t c[BYTES(k)])
{
    uint8_t first_byte = c[start / 8] & MSB_mask(start);
    uint8_t last_byte = c[end / 8] & LSB_mask(end);
    
    if ((end / 8) == (start / 8)) {
        c[start / 8] = first_byte ^ last_byte ^
                      ((*operator)(a[start / 8], b[start / 8]) & LSB_mask(start) & MSB_mask(end));
    } else {
        c[start / 8] = first_byte ^ ((*operator)(a[start / 8], b[start / 8]) & LSB_mask(start)); 
        for (size_t i = start / 8 + 1; i < end / 8; i++) {
            c[i] = (*operator)(a[i], b[i]);
        }
        c[end / 8] = last_byte ^ ((*operator)(a[end / 8], b[end / 8]) & MSB_mask(end));
    }
 
}

uint8_t randr(unsigned int min, unsigned int max)
{
	double scaled = (double) rand() / RAND_MAX;
	return (max - min + 1) * scaled + min;
}


void random_vector(size_t k, uint8_t v[BYTES(k)])
{
	uint8_t random[BYTES(k)];		
	for (size_t i = 0; i <= k / 8; i++) {
		random[i] = randr(0,255);
	}
	BytewiseOperation(xor, k, 0, k, v, random, v);  
}

void random_error(size_t start, size_t len, uint8_t e[BYTES(len)])
{
	memset(e, 0, BYTES(len));
	for (size_t i = start / 8; i < BYTES(len); i++) {
		e[i] = randr(0, 2);
		e[i] ^= randr(0, 2) << 2;
		e[i] ^= randr(0, 2) << 4;
		e[i] ^= randr(0, 2) << 6;
	}
    e[start / 8] &= (MSB_mask(start) ^ 0xff);
    e[BYTES(len) - 1] &= MSB_mask(len);
}

void random_matrix(size_t rows, size_t columns, uint8_t a[columns][BYTES(rows)])
{
    for (size_t i = 0; i < columns; i++) {
		uint8_t random[BYTES(rows)];		
        for (size_t j = 0; j <= rows / 8; j++) {
			random[j] = randr(0,255);
        }
		BytewiseOperation(xor, rows, 0, rows, a[i], random, a[i]);
    }
}

void identity_matrix(size_t k, size_t n, uint8_t a[n][BYTES(k)])
{
	size_t t = k < n ? k : n;
	for (size_t i = 0; i < t; i++)
		a[i][i / 8] = 0x80 >> (i % 8);
}

bool equals(size_t k, uint8_t a[BYTES(k)], uint8_t b[BYTES(k)])
{
    for (size_t i = 0; i < k / 8; i++) {
        if (a[i] != b[i])
            return false;
    }
    
    return (a[k / 8] >> (8 - k % 8)) == (b[k / 8] >> (8 - k % 8)) ;
}

/*
 * Implementation from http://graphics.stanford.edu/~seander/bithacks.html#ParityWith64Bits 
 */
static uint8_t parity(uint8_t a)
{
	return (((a * 0x0101010101010101ULL) & 0x8040201008040201ULL) % 0x1FF) & 1;
}

/* The scalar product of vector v with a specified column of matrix A */ 
uint8_t scalar_prod(size_t k, size_t n, size_t column, uint8_t v[BYTES(k)], 
    uint8_t A[n][BYTES(k)])
{	
	uint8_t tmp[BYTES(k)];
	memset(tmp, 0, BYTES(k));
	BytewiseOperation(and, k, 0, k, v, A[column], tmp);
	
	uint8_t prod = 0;
	for (size_t i = 0; i <= k / 8; i++) {
		prod ^= tmp[i];
	}
	
	return parity(prod);
}

/* List matrix multiplication of vector v with matrix A */ 
void vector_matrix_mult(size_t rows, size_t columns, 
		uint8_t v[BYTES(rows)], uint8_t A[columns][BYTES(rows)], uint8_t w[BYTES(columns)])
{
    memset(w, 0, BYTES(columns)); 
    for (size_t i = 0; i < columns; i++) {
		w[i / 8] ^= (scalar_prod(rows, columns, i, v, A) << (7 - i % 8));
    }    
}

/* Multiply a p x q matrix (a) with a q x r matrix (b) to obtain a p x r matrix (c)  */
void matrix_multiply(size_t p, size_t q, size_t r,
	uint8_t a[q][BYTES(p)], uint8_t b[r][BYTES(q)], uint8_t c[r][BYTES(p)])
{
	memset(c, 0, BYTES(p) * r);
    uint8_t a_t[p][BYTES(q)];
    memset(a_t, 0, BYTES(q) * p);
    transpose(p, q, a, a_t);
        
	// QUITE INEFFICIENT DUE TO COLUMN-MAJOR ORDER. LEADS TO CACHE-THRASHING.    
    for (size_t i = 0; i < r; i++) {
        for (size_t j = 0; j < p; j++) {
            c[i][j / 8] ^= (scalar_prod(q, r, i, a_t[j], b) << (7 - j % 8));
        }
    }
}

static void transpose(size_t p, size_t q, uint8_t a[q][BYTES(p)], uint8_t a_t[p][BYTES(q)])
{
    for (size_t i = 0; i < q; i++) {
        for (size_t j = 0; j < p; j++) {
            get_row(p, q, a, j, a_t[j]);
        }
    }
}

/* Extract a specified row from matrix a which is in column major form. */
static void get_row(size_t k, size_t n, uint8_t a[n][BYTES(k)], size_t row, uint8_t a_row[BYTES(n)])
{
	memset(a_row, 0, BYTES(n));
	for (size_t i = 0; i < n; i++) {
		a_row[i / 8] ^= (get_bit(a[i][row / 8], row) << (7 - i % 8));
	}
}


/* Fisher-Yates shuffle. Inside-out variant. */
void random_permutation(size_t k, unsigned int a[k])
{
    a[0] = 0;
    for (size_t i = 1; i < k; i++) {
      size_t j = randr(0, i);
      if (j != i) {
	a[i] = a[j];
      }
      a[j] = i;
    }
}



void all_errors(List *v, size_t d, size_t k, uint8_t e_[BYTES(k)])
{
	assert(d % 2 == 0);
	uint8_t e[BYTES(k)];
    memset(e, 0, sizeof(e));
	memcpy(e, e_, sizeof(e));
	if (d > 0) {	
        d -= 2;		
		all_errors(v, d, k, e);
		
		e[d / 8] = e_[d / 8] ^ (0x01 << (6 - d % 8));
		all_errors(v, d, k, e);
		
		e[d / 8] = e_[d / 8] ^ (0x02 << (6 - d % 8));
		all_errors(v, d, k, e);
	} else {
		list_append(v, k, e);	
	}
}



unsigned int rank(size_t k, size_t n, uint8_t a[n][BYTES(k)])
{
	uint8_t copy[n][BYTES(k)];
	memcpy(copy, a, sizeof(copy));	
	return gaussian_elimination(k, copy);
}

/* 
 * Perform gaussian elimination on matrix a using elementary COLUMN operations. 
 * The resulting matrix is LOWER triangular.
 */
static unsigned int gaussian_elimination(size_t dim, uint8_t a[dim][BYTES(dim)])
{	
	unsigned int rank = 0;
		
	for (size_t i = 0; i < dim; i++) {
		for (size_t j = rank; j < dim; j++) {
			if (is_pivot(dim, a[j], i)) {
				swap_columns(dim, dim, a, j, rank);
				add_pivot(dim, a, i, rank);
				rank++;
				break;
			} 
		}
	}
	
	return rank;
}

static bool is_pivot(size_t rows, uint8_t column[BYTES(rows)], size_t row_elem)
{
	return get_bit(column[row_elem / 8], row_elem);
}

static void swap_columns(size_t k, size_t n, uint8_t a[n][BYTES(k)], size_t i, size_t j)
{
	size_t bytes = BYTES(k);
	uint8_t tmp[bytes];
	memcpy(tmp, a[i], bytes);
	memcpy(a[i], a[j], bytes);
	memcpy(a[j], tmp, bytes);
}

static void add_pivot(size_t dim, uint8_t a[dim][BYTES(dim)], size_t pivot_row, size_t pivot_column)
{
	for (size_t j = pivot_column + 1; j < dim; j++) {		
        if (is_pivot(pivot_row, a[j], pivot_row)) {
			BytewiseOperation(xor, dim, pivot_row, dim, a[j], a[pivot_column], a[j]);
		}	
	}
}

/* 
 * Invert a square matrix a by simultaneously performing the elementary
 * column operations of gaussian elimination to the identity matrix b. 
 */
unsigned int invert(size_t dim, uint8_t a[dim][BYTES(dim)], uint8_t b[dim][BYTES(dim)])
{	
	memset(b, 0, BYTES(dim) * dim);
	uint8_t a_tmp[dim][BYTES(dim)];
	memcpy(a_tmp, a, BYTES(dim) * dim + 1);
	identity_matrix(dim, dim, b);
	unsigned int rank = 0;
	
	// Forward gaussian elim
    for (size_t i = 0; i < dim; i++) {
        for (size_t j = rank; j < dim; j++) {
            if (is_pivot(dim, a_tmp[j], i)) {
                swap_columns(dim, dim, a_tmp, j, rank);
                swap_columns(dim, dim, b, j, rank);

                for (size_t k = rank + 1; k < dim; k++) {
					if (is_pivot(i, a_tmp[k], i)) {			
						BytewiseOperation(xor, dim, 0, dim, a_tmp[k], a_tmp[rank], a_tmp[k]);
						BytewiseOperation(xor, dim, 0, dim, b[k], b[rank], b[k]);
					}						
                }

                rank++;
                break;
            } 
        }
    }

    assert(rank == dim);

    // Backward gaussian elim
    for (size_t i = dim; i --> 0; ) {
        for (size_t j = i; j --> 0; ) {
            if (is_pivot(dim, a_tmp[j], i)) {
				BytewiseOperation(xor, dim, 0, dim, b[j], b[i], b[j]);
            }
        }
    }
	
	return rank;
}
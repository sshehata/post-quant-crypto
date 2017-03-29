#include "reference_s.h"
#include "params.h"
#include "util.h"
#include "print_utils.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/* ------------------ Key generation functions ------------ */

static void create_S(size_t k, uint8_t S[k][BYTES(k)]);
static void create_G(size_t k, size_t n, uint8_t G[n][BYTES(k)]);
static void create_P(size_t n, uint8_t P[n][BYTES(n)], unsigned int perm[n / 2]);

void key_gen(size_t k, size_t n, 
    uint8_t S_inv[k][BYTES(k)], 
    uint8_t G[n][BYTES(k)], 
    uint8_t P_inv[n][BYTES(n)], 
    uint8_t G_pub[n][BYTES(k)])
{

    uint8_t S[k][BYTES(k)];
    uint8_t P[n][BYTES(n)];
    uint8_t SG[n][BYTES(k)];
    unsigned int perm[n / 2];
    
    create_S(k, S);
    invert(k, S, S_inv);
    
    create_G(k, n, G);
    
    memset(G_pub, 0, n * BYTES(k));
    memset(SG, 0, sizeof(SG));    
    matrix_multiply(k, k, n, S, G, SG);
    
    create_P(n, P, perm);
    invert(n, P, P_inv);
    
    // Permute the columns of SG
    for (size_t i = 0; i < n / 2; i++) {
        memcpy(G_pub[2 * i], SG[2 * perm[i]], BYTES(k)); 
        memcpy(G_pub[2 * i + 1], SG[2 * perm[i] + 1], BYTES(k)); 
    }       
}



static void create_S(size_t k, uint8_t S[k][BYTES(k)])
{
    memset(S, 0, k * BYTES(k));
    do {
        random_matrix(k, k, S);
    } while (rank(k, k, S) != k);
}

static void create_G(size_t k, size_t n, uint8_t G[n][BYTES(k)])
{
	memset(G, 0, n * BYTES(k));
	identity_matrix(k, n, G);
	
    size_t Ki = 0;
    size_t ni = k; 
	for (size_t i = 0; i < NUMBER_OF_BLOCKS; i++) {
        Ki += B_k[i];
		for (size_t column = ni; column < ni + B_n[i]; column++) {
			uint8_t random_column[BYTES(k)];
			for (size_t j = 0; j <= Ki / 8; j++) {
				random_column[j] = randr(0,255);
			}
			zip_with(xor, k, 0, Ki, G[column], random_column, G[column]);  
		}
        ni += B_n[i];
	}
}

static void create_P(size_t n, uint8_t P[n][BYTES(n)], unsigned int perm[n / 2])
{
    memset(P, 0, n * BYTES(n));
    permute(n / 2, perm);

    for (size_t i = 0; i < n / 2; i++) {   
        P[2 * i][(2 * perm[i]) / 8] = 1 << (7 - (2 * perm[i]) % 8);
        P[2 * i + 1][(2 * perm[i] + 1) / 8] = 1 << (7 - (2 * perm[i] + 1) % 8);
    }
}


/* ---------------- Encryption/decryption functions ---------- */

void encrypt(size_t k, size_t n, uint8_t G_pub[n][BYTES(k)], uint8_t m[BYTES(k)], uint8_t e[BYTES(n)], uint8_t c[BYTES(n)])
{
  memset(c, 0, BYTES(n));
  vector_matrix_mult(k, n, m, G_pub, c); 
  zip_with(xor, n, 0, n, c, e, c);
}

void decrypt(size_t k, size_t n, 
    uint8_t S_inv[k][BYTES(k)], 
    uint8_t G[n][BYTES(k)], 
    uint8_t P_inv[n][BYTES(n)], 
    uint8_t z[BYTES(n)], 
    List *decrypted)
{
	uint8_t m[BYTES(k)];
	uint8_t y[BYTES(n)];
	List L;
	list_init(&L, k);

	vector_matrix_mult(n, n, z, P_inv, y);
	decode(k, n, G, y, &L);
	
    for (size_t i = 0; i < L.size; i++) {
		vector_matrix_mult(k, k, list_get(&L, i), S_inv, m); 
	   	list_append(decrypted, k, m);
    }
	
	list_free(&L);
}



/* ----------- Decoding functions ----------- */

static void create_first_block_candidates(List *T0, size_t k, size_t n, 
    uint8_t G[n][BYTES(k)], uint8_t y[BYTES(n)], uint8_t y0[BYTES(k)]);

static bool valid_candidate(size_t k, size_t n, uint8_t G[n][BYTES(k)], uint8_t y[BYTES(n)], uint8_t cand[BYTES(k)], size_t block);

static void extend(List *next, size_t k, uint8_t y0[BYTES(k)], uint8_t cand[BYTES(k)], size_t block, size_t step);

static unsigned int list_decode(size_t k, size_t n, uint8_t G[n][BYTES(k)], uint8_t y[BYTES(n)],uint8_t y0[BYTES(k)], List *Lp, size_t start_round);


void decode(size_t k, size_t n, uint8_t G[n][BYTES(k)], uint8_t y[BYTES(n)], List *Lp)
{
    uint8_t y0[BYTES(k)];
    memcpy(y0, y, sizeof(y0));
    create_first_block_candidates(Lp, k, n, G, y, y0);
    list_decode(k, n, G, y, y0, Lp, 1);   
}

static unsigned int list_decode(size_t k, size_t n, 
    uint8_t G[n][BYTES(k)], 
    uint8_t y[BYTES(n)],
    uint8_t y0[BYTES(k)],
    List *Lp,
    size_t start_block)
{
    List T;
	list_init(&T, k);
    
    printf("L%zd = %zd\n", start_block, Lp->size);

	for (size_t block = start_block; block < NUMBER_OF_BLOCKS; block++) {		
        T.size = 0;
        for (size_t i = 0; i < Lp->size; i++) {
            extend(&T, k, y0, list_get(Lp, i), block, 0); 
		}
                
        Lp->size = 0;
        for (size_t i = 0; i < T.size; i++) {
            if ( valid_candidate(k, n, G, y, list_get(&T, i), block) ) {
                list_append(Lp, k, list_get(&T, i));
                
                if (SIGNATURE) {
                    list_free(&T);
                    return 1;
                }
            }
        }
        
        printf("L%zd = %zd\n", block + 1, Lp->size);
	}    
    list_free(&T);
    
    return Lp->size;
}

static void create_first_block_candidates(List *T0, size_t k, size_t n, 
    uint8_t G[n][BYTES(k)], uint8_t y[BYTES(n)], uint8_t y0[BYTES(k)])
{
	List E_K0;
	list_init(&E_K0, k);
    uint8_t seed_error[BYTES(k)];
    memset(seed_error, 0, sizeof(seed_error));
	all_errors(&E_K0, B_k[0], k, seed_error);

    for (size_t i = 0; i < E_K0.size; i++) {
        uint8_t (*e)[BYTES(k)] = list_get(&E_K0, i);
		zip_with(xor, k, 0, B_k[0], *e, y0, *e);
        if ( valid_candidate(k, n, G, y, *e, 0) ) {
            list_append(T0, k, *e);    
        }
    }    
	
	list_free(&E_K0);
}

static bool valid_candidate(size_t k, size_t n, uint8_t G[n][BYTES(k)], uint8_t y[BYTES(n)], uint8_t cand[BYTES(k)], size_t block)
{
	uint8_t cand_encoding[BYTES(n)];
    memset(cand_encoding, 0, sizeof(cand_encoding));
	size_t block_start_column = k + sum(block, B_n);

	for (size_t i = block_start_column; i < block_start_column + B_n[block]; i += 2) {
		
		cand_encoding[i / 8] ^= (scalar_prod(k, n, i, cand, G) << (7 - i % 8));
		cand_encoding[(i+1) / 8] ^= (scalar_prod(k, n, i+1, cand, G) << (7 - (i+1) % 8));

		uint8_t slice = ((cand_encoding[i / 8] ^ y[i / 8]) >> (6 - i % 8)) & 0x3;

		if (slice == 0x3) {
			return false;
		}
	}
	
	return true;
}

static void extend(List *next, size_t k, uint8_t y0[BYTES(k)], uint8_t cand[BYTES(k)], size_t block, size_t step)
{
    uint8_t x[BYTES(k)];
    memset(x, 0, sizeof(x));

	if (step < B_k[block]) {
	
		memcpy(x, cand, sizeof(x));	
		size_t step_slice = sum(block, B_k) + step;
		uint8_t y0_ki_mask = 0x3 << (6 - step_slice % 8);
		
		// e = 00	
		x[step_slice / 8] ^= (y0[step_slice / 8] & y0_ki_mask); 
		extend(next, k, y0, x, block, step + 2);
		
		// e = 01	
		x[step_slice / 8] ^= (0x55 & y0_ki_mask); 
		extend(next, k, y0, x, block, step + 2);
		
		// e = 10	
		x[step_slice / 8] ^= (0xff & y0_ki_mask); 
		extend(next, k, y0, x, block, step + 2);	
	} else {
		list_append(next, k, cand);	
	}	
}


/* -------------- Signature/verification functions -------------*/

static void sign_decode(size_t k, size_t n, 
    uint8_t G[n][BYTES(k)], uint8_t y[BYTES(n)], uint8_t x[BYTES(k)]);

static bool survive_block(size_t k, size_t n, size_t Ki, size_t block, 
    uint8_t G[n][BYTES(k)], uint8_t y[BYTES(n)], uint8_t y0[BYTES(k)], uint8_t x[BYTES(k)]);

static void expand(size_t k, size_t Ki, size_t ki, size_t ni, 
    List *L, uint8_t y0[BYTES(k)], uint8_t x[BYTES(k)]);

static size_t exp_limit(size_t ni)
{
    return ceil(pow(2, ni) / pow(3, ni / 2));
}    


unsigned int sign(size_t k, size_t n, 
    uint8_t S_inv[k][BYTES(k)], 
    uint8_t G[n][BYTES(k)], 
    uint8_t P_inv[n][BYTES(n)], 
    uint8_t z[BYTES(n)], 
    uint8_t signature[BYTES(k)])
{
    uint8_t x[BYTES(k)], y[BYTES(n)];
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));
    
    vector_matrix_mult(n, n, z, P_inv, y);
	sign_decode(k, n, G, y, x);
    vector_matrix_mult(k, k, x, S_inv, signature); 

    return 1;
}

static void sign_decode(size_t k, size_t n, uint8_t G[n][BYTES(k)], uint8_t y[BYTES(n)], uint8_t x[BYTES(k)])
{
    size_t list_decode_point = NUMBER_OF_BLOCKS - 1;
    uint8_t e0[BYTES(k)], y0[BYTES(k)];
    memcpy(y0, y, sizeof(y0));
 
	List L; 
	list_init(&L, k);
 
	bool valid_cand = false;
    
    while (!valid_cand) {
		size_t Ki = B_k[0];
        memset(x, 0, BYTES(k));     
        random_error(0, Ki, e0);
        zip_with(xor, k, 0, Ki, y0, e0, x);
		
        if (valid_candidate(k, n, G, y, x, 0)) {
			for (size_t block = 1; block < list_decode_point; block++) {
				if ( !survive_block(k, n, Ki, block, G, y, y0, x) ) {
					goto NEW_CANDIDATE;
				}
				Ki += B_k[block];
            }	
            L.size = 0;
            list_append(&L, k, x);
            valid_cand = (list_decode(k, n, G, y, y0, &L, list_decode_point) > 0); 
		} 

        NEW_CANDIDATE:;    
	} 

    memcpy(x, list_get(&L, 0), BYTES(k));
    printf("sign_decode: L.size = %zd\n", L.size);
    printf("selected candidate:\n");
    print_vector(stdout, k, x);
	      
    list_free(&L);
}

static bool survive_block(size_t k, size_t n, size_t Ki, size_t block, uint8_t G[n][BYTES(k)], uint8_t y[BYTES(n)], uint8_t y0[BYTES(k)], uint8_t x[BYTES(k)])
{
	List L;
	list_init(&L, k);
	expand(k, Ki, B_k[block], B_n[block], &L, y0, x);

	for (size_t j = 0; j < L.size; j++) {	
		if ( valid_candidate(k, n, G, y, list_get(&L, j), block) ) {
			zip_with(xor, k, Ki, Ki + B_k[block], x, list_get(&L, j), x);
			list_free(&L);
			return true;
		}
	}	
	
	list_free(&L);
	
	return false;
}

static void expand(size_t k, size_t Ki, size_t ki, size_t ni, List *L, uint8_t y0[BYTES(k)], uint8_t x[BYTES(k)])
{
	uint8_t e_ki[BYTES(k)], expanded[BYTES(k)];
    for (size_t i = 0; i < exp_limit(ni); i++) {    
        random_error(0, k, e_ki); 
        memcpy(expanded, x, sizeof(expanded));
        zip_with(xor, k, Ki, Ki + ki, y0, e_ki, expanded);
		list_append(L, k, expanded);
    }
}

bool verify(size_t k, size_t n, uint8_t G_pub[n][BYTES(k)], uint8_t z[BYTES(n)], uint8_t sig[BYTES(k)])
{
	uint8_t y[BYTES(n)];
    memset(y, 0, sizeof(y));
	vector_matrix_mult(k, n, sig, G_pub, y);
	zip_with(xor, n, 0, n, y, z, y);
	for (size_t i = 0; i < n; i += 2) {
		uint8_t slice = (y[i / 8] >> (6 - i % 8)) & 0x3;
		if (slice == 0x3) {
            printf("Problem at i = %zd\n", i);
            print_vector(stdout, i + 2, y);

			return false;
		}
	}
	
	return true;
}


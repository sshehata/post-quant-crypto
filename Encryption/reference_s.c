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
static void create_P(size_t n, uint8_t P[n][BYTES(n)]);
static void create_Pi_from_P(size_t n, uint8_t P[n][BYTES(n)], uint8_t Pi[n][BYTES(n)]);

void key_gen(size_t k,
             size_t n,
             size_t s,
             uint8_t S_inv[k][BYTES(k)],
             uint8_t G[n][BYTES(k)],
             uint8_t P_inv[s][n][BYTES(n)],
             uint8_t G_pub[s][n][BYTES(k)])
{
    
    uint8_t S[k][BYTES(k)]; 
    uint8_t p[s][n][BYTES(n)];
    uint8_t P[n][BYTES(n)];
    uint8_t SG[s][n][BYTES(k)];
    uint8_t g[s][n][BYTES(k)];

    printf("creating S matrix\n");
    create_S(k, S);
    invert(k, S, S_inv);
    printf("created S matrix!\n");

    printf("creating P matrix...\n");
    create_P(n, P);
    printf("created P matrix\n");
    printf("creating G matrix...\n");
    create_G(k, n, G);
    printf("created G matrix!\n");

    // Compute G_1 ... G_s-1 
    printf("creating Gs matrices...\n");
    memset(g, 0, s * n * BYTES(k));
    for (size_t i = 0; i < s-1; i++)
      random_matrix(k, n, g[i]);
   

    // Compute G_s
    matrix_add(k, n, G, g[s-1], g[s-1]);
    for(size_t i = 0; i < s - 1; i++)
      matrix_add(k, n, g[i], g[s-1], g[s-1]);
    printf("created Gs matrices!\n");
    
    // Compute public key Gi
    printf("computing public key\n");
    memset(G_pub, 0, s* n * BYTES(k));
    memset(SG, 0, s * n * BYTES(k));
    for (size_t i = 0; i < s; i++) {
      matrix_multiply(k, k, n, S, G, SG[i]);
      create_Pi_from_P(n, P, p[i]);
      matrix_multiply(k, n, n, SG[i], p[i], G_pub[i]);
    }
    printf("computed public key\n");

    printf("computing private key\n");
    // Compute the inverse permutation
    for (size_t i = 0; i < s; i++)
      invert_permutation_matrix(n, p[i], P_inv[i]);
    printf("computed private key\n");
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
			BytewiseOperation(xor, k, 0, Ki, G[column], random_column, G[column]);
		}
        ni += B_n[i];
	}
}

static void create_P(size_t n, uint8_t P[n][BYTES(n)])
{
  unsigned int perm[n/L];
  memset(P, 0, n * BYTES(n));
  random_permutation(n / L, perm);

  for (size_t i = 0; i < n / L; i++) {
    for (size_t j = 0; j < L; j++)
      P[L * i + j][(L * perm[i] + j) / 8] = 1 << (7 - (L * perm[i] + j) % 8);
  }

}

static void create_Pi_from_P(size_t n, uint8_t P[n][BYTES(n)], uint8_t Pi[n][BYTES(n)])
{
  unsigned int perm[L];
  memcpy(Pi, P, n*BYTES(n));
  for (size_t i = 0; i < n / L; i++) {
    memset(perm, 0, L);
    random_permutation(L, perm); 
    permute_columns(n, n, Pi, L, perm, i * L);
  }
}


/* ---------------- Encryption/decryption functions ---------- */

//TODO: Fix error vector input
void encrypt(size_t k, size_t n, size_t s, uint8_t G_pub[s][n][BYTES(k)], uint8_t m[BYTES(k)], uint8_t e[s][BYTES(n)], uint8_t c[s][BYTES(n)])
{
    memset(c, 0, s*BYTES(n));
    for (size_t i = 0; i < s; i++) {
      vector_matrix_mult(k, n, m, G_pub[i], c[i]);
      BytewiseOperation(xor, n, 0, n, c[i], e[i], c[i]);    // TODO: fix error vector application
    }
}

void decrypt(size_t k, size_t n, size_t s, uint8_t S_inv[k][BYTES(k)], uint8_t G[n][BYTES(k)], uint8_t P_inv[s][n][BYTES(n)], uint8_t z[s][BYTES(n)], List *decrypted)
{
  uint8_t m[BYTES(k)];
  uint8_t y[BYTES(n)];
  uint8_t c_prime[s][BYTES(n)];
  List L;
  list_init(&L, k);

  memset(c_prime, 0, s*BYTES(n));
  memset(y, 0, BYTES(n));
  FILE *fp_out_S    = fopen("S.txt", "w");
  
  
  for (size_t i = 0; i < s; i++) {
      vector_matrix_mult(n, n, z[i], P_inv[i], c_prime[i]);
      BytewiseOperation(xor, n, 0, n, c_prime[i], y, y);
  }
   
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
		BytewiseOperation(xor, k, 0, B_k[0], *e, y0, *e);
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

	for (size_t i = block_start_column; i < block_start_column + B_n[block]; i += 4) {
		
		cand_encoding[i / 8] ^= (scalar_prod(k, n, i, cand, G) << (7 - i % 8));
		cand_encoding[(i+1) / 8] ^= (scalar_prod(k, n, i+1, cand, G) << (7 - (i+1) % 8));
		cand_encoding[(i+2) / 8] ^= (scalar_prod(k, n, i+2, cand, G) << (7 - (i+2) % 8));
		cand_encoding[(i+3) / 8] ^= (scalar_prod(k, n, i+3, cand, G) << (7 - (i+3) % 8));

		uint8_t slice = ((cand_encoding[i / 8] ^ y[i / 8]) >> (4 - i % 8)) & 0x0f;

		if (slice == 0x7 || slice == 0xb || slice > 0xc) {
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
		uint8_t y0_ki_mask = 0x0f << (4 - step_slice % 8);

		// e = 00
		x[step_slice / 8] ^= (y0[step_slice / 8] & y0_ki_mask);
		extend(next, k, y0, x, block, step + 4);

		// e = 01
		x[step_slice / 8] ^= (0x11 & y0_ki_mask);
		extend(next, k, y0, x, block, step + 4);

		// e = 10
		x[step_slice / 8] ^= (0x22 & y0_ki_mask);
		extend(next, k, y0, x, block, step + 4);

		// e = 11
		x[step_slice / 8] ^= (0x33 & y0_ki_mask);
		extend(next, k, y0, x, block, step + 4);

		// e = 100
		x[step_slice / 8] ^= (0x44 & y0_ki_mask);
		extend(next, k, y0, x, block, step + 4);

		// e = 101
		x[step_slice / 8] ^= (0x55 & y0_ki_mask);
		extend(next, k, y0, x, block, step + 4);

		// e = 110
		x[step_slice / 8] ^= (0x66 & y0_ki_mask);
		extend(next, k, y0, x, block, step + 4);

		// e = 1000
		x[step_slice / 8] ^= (0x88 & y0_ki_mask);
		extend(next, k, y0, x, block, step + 4);

		// e = 1001
		x[step_slice / 8] ^= (0x99 & y0_ki_mask);
		extend(next, k, y0, x, block, step + 4);

		// e = 1010
		x[step_slice / 8] ^= (0xAA & y0_ki_mask);
		extend(next, k, y0, x, block, step + 4);

		// e = 1011
		x[step_slice / 8] ^= (0xcc & y0_ki_mask);
		extend(next, k, y0, x, block, step + 4);
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


unsigned int sign(size_t k, size_t n, size_t s,
    uint8_t S_inv[k][BYTES(k)],
    uint8_t G[n][BYTES(k)],
    uint8_t P_inv[s][n][BYTES(n)],
    uint8_t z[s][BYTES(n)],
    uint8_t signature[BYTES(k)])
{
  uint8_t x[BYTES(k)], y[s][BYTES(n)];
  uint8_t Y[BYTES(n)];
  memset(Y, 0, BYTES(n));
  memset(x, 0, BYTES(k));
  memset(y, 0, s * BYTES(n));
  for (size_t i = 0; i < s; i++) {
    vector_matrix_mult(n, n, z[i], P_inv[i], y[i]);
    BytewiseOperation(xor, n, 0, n, y[i], Y, Y);
  }

  sign_decode(k, n, G, Y, x);
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
        BytewiseOperation(xor, k, 0, Ki, y0, e0, x);

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
			BytewiseOperation(xor, k, Ki, Ki + B_k[block], x, list_get(&L, j), x);
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
        BytewiseOperation(xor, k, Ki, Ki + ki, y0, e_ki, expanded);
		list_append(L, k, expanded);
    }
}

bool find_split(size_t s, uint8_t errors[s]) {
    for (size_t i = 0; i < N_ERROR_SPLITS; i++) {
        if (VALID_ERROR_SPLITS[i][0] == errors[0] &&
            VALID_ERROR_SPLITS[i][1] == errors[1])
                return true;
    }
    return false;
}

bool verify(size_t k,
    size_t n,
    size_t s,
    uint8_t G_pub[s][n][BYTES(k)],
    uint8_t z[s][BYTES(n)],
    uint8_t sig[BYTES(k)])
{
  uint8_t y[s][BYTES(n)];
  memset(y, 0, s * BYTES(n));
  for (size_t i = 0; i < s; i++) {
    vector_matrix_mult(k, n, sig, G_pub[i], y[i]);
    BytewiseOperation(xor, n, 0, n, y[i], z[i], y[i]);
  }
  
  print_vector(stdout, n, y[0]);
  print_vector(stdout, n, y[1]);

  uint8_t errors[2];
  for (size_t i = 0; i < n; i+=4) {
    errors[0] = (y[0][i/8] >> (4 - i % 8)) & 0xf;
    errors[1] = (y[1][i/8] >> (4 - i % 8)) & 0xf;
    printf("%zu %zu\n", y[0][i/8], y[1][i/8]);
    if (!find_split(s, errors))
        return false;
  }

  return true;
}

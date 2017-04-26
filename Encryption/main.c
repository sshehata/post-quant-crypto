#include "types.h"
#include "params.h"
#include "reference.h"
#include "util.h"
#include "print_utils.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <assert.h>

size_t test_scheme();

int main(int argc, char *argv[])
{
  assert(NUMBER_OF_BLOCKS_K == NUMBER_OF_BLOCKS_N);

  srand(time(NULL));
  print_parameters();

  test_scheme();
  return 0;
}

size_t test_scheme()
{
  size_t k = sum(NUMBER_OF_BLOCKS, B_k);
  size_t n = k + sum(NUMBER_OF_BLOCKS, B_n);

  uint8_t S_inv[k][BYTES(k)];
  uint8_t G[n][BYTES(k)];
  uint8_t G_pub[n][BYTES(k)];
  unsigned int inv_perm[n / 2];

  uint8_t m[BYTES(k)];
  uint8_t e[BYTES(n)], z[BYTES(n)];

  FILE *fp_out_S_inv = fopen("S_inv.txt", "w");
  FILE *fp_out_G     = fopen("G.txt", "w");
  FILE *fp_out_P_inv = fopen("P_inv.txt", "w");
  FILE *fp_out_G_pub = fopen("G_pub.txt", "w");

  key_gen(k, n, S_inv, G, inv_perm, G_pub);

  print_matrix(fp_out_S_inv, k, k, S_inv); fclose(fp_out_S_inv);
  print_matrix(fp_out_G,     k, n, G); fclose(fp_out_G);
  print_integer_vector(fp_out_P_inv, n/2, inv_perm); fclose(fp_out_P_inv);
  print_matrix(fp_out_G_pub, k, n, G_pub); fclose(fp_out_G_pub);

  List decrypt_list;
  list_init(&decrypt_list, k);

  // Encryption: m |- S -> x |- G -> y |- P -> z -> z + e

  random_vector(k, m);
  random_error(0, n, e);

  //encrypt(k, n, G_pub, m, e, z);

  //// Decryption: z + e |- P^-1 -> y + e' |- Decode -> {x1, x2, ...} |- S^-1 -> m
  //decrypt(k, n, S_inv, G, inv_perm, z, &decrypt_list);

  //printf("\n");
  //for (size_t i = 0; i < decrypt_list.size; i++) {
  //  uint8_t (*mp)[BYTES(k)] = list_get(&decrypt_list, i);
  //  if (equals(k, m, *mp)) {
  //    printf("Message successfully decrypted!\n");
  //  }
  //}

  list_free(&decrypt_list);

  return decrypt_list.size;
}

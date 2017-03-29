#include "types.h"

#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include "print_utils.h"


int main(int argc, char *argv) {
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
  uint8_t P_inv[S][k][BYTES(k)];
  uint8_t G[n][BYTES(k)];
  uint8_t G_pub[S][n][BYTES(k)];

  FILE *fp_out_S_inv = fopen("S_inv.txt", "w");
  FILE *fp_out_G     = fopen("G.txt", "w");
  FILE *fp_out_P_inv = fopen("P_inv.txt", "w");
  FILE *fp_out_G_pub = fopen("G_pub.txt", "w");

  key_gen(k, n, S, S_inv, G, P_inv, G_pub);

  print_matrix(fp_out_S_inv, k, k, S_inv); fclose(fp_out_S_inv);
  print_matrix(fp_out_G,     k, n, G); fclose(fp_out_G);
  for (size_t i = 0; i < S; i++) {
    print_matrix(fp_out_P_inv, n, n, P_inv[i]);
    print_matrix(fp_out_G_pub, k, n, G_pub[i]);
  }
  fclose(fp_out_P_inv);
  fclose(fp_out_G_pub);
}

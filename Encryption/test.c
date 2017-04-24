#include "types.h"

#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <sys/resource.h>
#include "print_utils.h"
#include "reference_s.h"

size_t test_scheme();

int main(int argc, char *argv[]) {
  assert(NUMBER_OF_BLOCKS_K == NUMBER_OF_BLOCKS_N);

  const rlim_t kStackSize = 1024 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
    if (rl.rlim_cur < kStackSize)
    {
      rl.rlim_cur = kStackSize;
      result = setrlimit(RLIMIT_STACK, &rl);
      if (result != 0)
      {
        fprintf(stderr, "setrlimit returned result = %d\n", result);
      }
    }
  }


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
  uint8_t P_inv[S][n][BYTES(n)];
  uint8_t G[n][BYTES(k)];
  uint8_t G_pub[S][n][BYTES(k)];
  
  uint8_t m[BYTES(k)];
  uint8_t e[S][BYTES(n)], z[S][BYTES(n)];

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
 
  List decrypt_list;
  list_init(&decrypt_list, k);
  
 
  random_vector(k, m);
  random_error_split(S, L, n, e);
  
  
  // Encryption: m |- S -> x |- G -> y |- P -> z -> z + e
  encrypt(k, n, S, G_pub, m, e, z);

  // Decryption: z + e |- P^-1 -> y + e' |- Decode -> {x1, x2, ...} |- S^-1 -> m
  decrypt(k, n, S, S_inv, G, P_inv, z, &decrypt_list);
  
  printf("decrypt %u", decrypt_list.size);

  printf("\n");
  FILE *fp_out_v     = fopen("V.txt", "w");
  for (size_t i = 0; i < decrypt_list.size; i++) {
    uint8_t (*mp)[BYTES(k)] = list_get(&decrypt_list, i);
    fprintf(fp_out_v, "mp%zu \n", i);
    print_vector(fp_out_v, k, *mp);
    if (equals(k, m, *mp)) {
      printf("Message successfully decrypted!\n");
    }
  }

  list_free(&decrypt_list);

  return decrypt_list.size;
}

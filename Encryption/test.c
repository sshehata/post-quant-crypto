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
  
 
  for (size_t i = 0; i < S; i++) {
    random_vector(n, z[i]);
  }
  uint8_t sig[BYTES(k)];
  memset(sig, 0, sizeof(sig));


  if (sign(k, n, S, S_inv, G, P_inv, z, sig) > 0 && verify(k, n, S, G_pub, z, sig)) {
    printf("Signature found!\n");
  } else {
    printf("No signature found.\n");
  }	

  list_free(&decrypt_list);

  return decrypt_list.size;
}

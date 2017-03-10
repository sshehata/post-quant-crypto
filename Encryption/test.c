#include "types.h"

#include "error_split.h"

#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include "print_utils.h"



int main(int argc, char *argv[])
{
  assert(NUMBER_OF_BLOCKS_K == NUMBER_OF_BLOCKS_N);

  srand(time(NULL));
  print_parameters();

  test_scheme();

  return 0;
}


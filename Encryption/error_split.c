#include "types.h"
#include "params.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


bool in_array(uint8_t value, size_t size, uint8_t arr[size]) {
  for(size_t i = 0; i < size; i++)
    if (arr[i] == value)  return true;
  return false;
}

void enumerate_tuples(size_t s, size_t num_e, size_t num_tuples, uint8_t e_tuples[num_tuples][s], uint8_t e[num_e]) {
  size_t tup_pos = 0;
  while(tup_pos < s) {
    size_t num_strings = pow(num_e, (s - tup_pos - 1));
    size_t index = 0;
    size_t e_index = 0;
    while(index < num_tuples) {
      if (index % num_strings == 0 && index > 0)
        e_index = (e_index + 1) % num_e;
      e_tuples[index++][tup_pos] = e[e_index];
    }
    tup_pos++;
  }
}

void enumerate_e(size_t num_e, uint8_t e[num_e]) {
  for (size_t i = 0; i < num_e; i++)
    e[i] = i;
}

/* Granulation l assumed to be <= 8 */

void get_error_splits(size_t ess, uint8_t error_set[ess], size_t s, size_t *num_error_splits) {
  // e <- F^l_2
  size_t num_e = pow(2, L);
  uint8_t e[num_e];
  enumerate_e(num_e, e);

  // (e_1, e_2, ..., e_s)
  size_t num_tuples = pow(num_e, s);
  uint8_t e_tuples[num_tuples][s];
  enumerate_tuples(s, num_e, num_tuples, e_tuples, e);

  for(int i = 0; i < num_tuples; i++) {
    uint8_t sum = 0;
    for(int j = 0; j < s; j++)
      sum ^= e_tuples[i][j];
    if (in_array(sum, ess, error_set)) {
      // TODO: copy tuple
      (*num_error_splits)++;
    }
  }
}

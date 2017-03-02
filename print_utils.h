#ifndef PRINT_UTILS_H
#define PRINT_UTILS_H

#include "types.h"
#include "params.h"
#include "util.h"

#include <inttypes.h>
#include <stdio.h>


void read_from_file(char *file, size_t rows, size_t columns, uint8_t a[columns][BYTES(rows)]);
void print_matrix(FILE *fp, size_t rows, size_t columns, uint8_t a[columns][BYTES(rows)]);
void print_parameters();

void print_vector(FILE *fp, size_t n, uint8_t a[BYTES(n)]);

#endif
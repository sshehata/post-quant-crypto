#include "print_utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>


void print_matrix(FILE *fp, size_t rows, size_t columns, uint8_t a[columns][BYTES(rows)])
{
	for (size_t i = 0; i < rows; i++){
		fprintf(fp, "[");
		for (size_t j = 0; j < columns; j++){
			fprintf(fp, "%"PRIu8"", get_bit(a[j][i / 8], i));	
		}
		fprintf(fp, "]\n");	
	}	
}

void print_vector(FILE *fp, size_t n, uint8_t a[BYTES(n)])
{
	for (size_t i = 0; i < n; i++) {
		fprintf(fp, "%"PRIu8, get_bit(a[i / 8], i));
	}
	fprintf(fp, "\n");
}

void print_integer_vector(FILE *fp, size_t n, unsigned int a[n])
{
	for (size_t i = 0; i < n; i++) {
		fprintf(fp, "%d ", a[i]);
	}
	fprintf(fp, "\n");
}


void print_parameters()
{
    size_t k = sum(NUMBER_OF_BLOCKS, B_k);
    size_t n = k + sum(NUMBER_OF_BLOCKS, B_n);
	printf("K = %zu\n", k);
	printf("N = %zu\n", n);
	printf("K_1 = %u\n", B_k[0]);
    printf("N_w = %u\n", B_n[NUMBER_OF_BLOCKS - 1]);
	printf("#Blocks = %zd\n", NUMBER_OF_BLOCKS);
    if (SIGNATURE) { printf("LD_point = %zd\n", NUMBER_OF_BLOCKS - 1); }

	printf("\n");
}

void read_from_file(char * file, size_t rows, size_t columns, uint8_t a[columns][BYTES(rows)])
{
	memset(a, 0, BYTES(rows) * columns * sizeof(uint8_t));
	FILE *fp = fopen(file,"r");
   	if(!fp) {
        fprintf(stderr,"error opening file...exiting\n");
        exit(1);
	}
	char str[1000];
    size_t i = 0;	
    while ((fgets(str, 1000, fp) != NULL) && (i < rows)) {
    	for (size_t j = 1; j < strlen(str) - 1; j += 2){
    		uint8_t val = atoi(str + j);
			a[j / 2][i / 8] |= (val << (7 - (i % 8)));
    	}
    	i++;
    }
    
   fclose(fp);

}
#ifndef VECTOR_H
#define VECTOR_H

#include "types.h"

#define LIST_INITIAL_CAPACITY 1000

typedef struct {
	size_t size;
	size_t capacity;
    size_t elem_size;
	uint8_t (*data)[];
} List;

void list_init(List *list, size_t k);

void list_append(List *list, size_t k, uint8_t value[BYTES(k)]);

void * list_get(List *list, size_t index);

void list_free(List *list);

#endif
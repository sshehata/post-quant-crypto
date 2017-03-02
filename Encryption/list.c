#include "list.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void double_capacity_if_full(List *list); 


void list_init(List *list, size_t k) 
{
	list->size = 0;
	list->capacity = LIST_INITIAL_CAPACITY;
    list->elem_size = BYTES(k);
	list->data = malloc(list->elem_size * list->capacity);
}

void list_append(List *list, size_t k, uint8_t value[BYTES(k)]) 
{
	double_capacity_if_full(list);
    uint8_t (*target)[BYTES(k)] = list->data;
	memcpy(target[list->size++], value, list->elem_size);    
}

void  * list_get(List *list, size_t index) 
{
	if (index >= list->size) {
		printf("Index %zd out of bounds for list of size %zd\n", index, list->size);
		exit(1);
	}

    return (*(list->data) + index * list->elem_size);
}

static void double_capacity_if_full(List *list) 
{
	if (list->size >= list->capacity) {
		list->capacity *= 2;
		uint8_t (*realloced)[list->elem_size] = realloc(list->data, list->elem_size * list->capacity);
        if (realloced == NULL) {
            printf("Failed to reallocate memory for list of capacity %zd\n", list->capacity);
            exit(1);
        }
        list->data = realloced;        
	}
}

void list_free(List *list) 
{
	free(list->data);
	list->data = NULL;
}


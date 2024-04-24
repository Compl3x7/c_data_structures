#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "my_vector.h"

#define INIT_ARRAY_SIZE 16

Vector* vector_create()
{
    Vector *v = malloc(sizeof(Vector));
    v->array = malloc(INIT_ARRAY_SIZE * sizeof(Vector));
    v->last = v->array + INIT_ARRAY_SIZE - 1;
    v->size = 0;
    return v;
}

void vector_destroy(Vector *v)
{
    free(v->array);
    free(v);
}
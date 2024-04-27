#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "my_vector.h"

#define INIT_ARRAY_SIZE 16

Vector* vector_create()
{
    Vector *v = malloc(sizeof(Vector));
    v->array = malloc(INIT_ARRAY_SIZE * sizeof(double));
    v->array_size = INIT_ARRAY_SIZE;
    v->size = 0;
    return v;
}

void vector_println(Vector *v)
{
    printf("[");
    for (int i = 0; i < v->size; i++)
    {
        char *format = i == v->size - 1 ? "%.2f" : "%.2f, ";
        printf(format, v->array[i]);
    }
    printf("]\n");
}

int vector_is_empty(Vector *v)
{
    return v->size == 0;
}

int vector_size(Vector *v)
{
    return v->size;
}

double vector_get(Vector *v, int index)
{
    assert(v->size > 0);
    assert(index >= 0 && index < v->size);
    return v->array[index];
}

int vector_find(Vector *v, double value)
{
    assert(v->size > 0);
    int left = 0;
    int right = v->size - 1;
    while (left <= right)
    {
        if (v->array[left] == value) 
            return left;
        if (v->array[right] == value)
            return right;
        left++;
        right--;
    }
    return -1;
}

/* Auxiliar enum for resize function */
typedef enum ResizeRatio
{
    DOUBLE_SIZE,
    HALF_SIZE
} ResizeRatio;

/* Resizes array to either double it's size or half
Auxiliary function */
void vector_resize(Vector *v, ResizeRatio ratio)
{
    v->array_size = ratio == DOUBLE_SIZE ? v->array_size << 1 : v->array_size >> 1;
    v->array = realloc(v->array, v->array_size * sizeof(double));
}

void vector_add(Vector *v, double value)
{
    if (v->size >= v->array_size)
        vector_resize(v, DOUBLE_SIZE);
    v->array[v->size++] = value;
}


void vector_remove(Vector *v)
{
    assert(v->size > 0);
    v->size--; //Lazy delete
    if (v->size < v->array_size >> 1)
        vector_resize(v, HALF_SIZE);
}


void vector_destroy(Vector *v)
{
    free(v->array);
    free(v);
}
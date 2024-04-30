#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "my_vector.h"

#define INIT_ARRAY_SIZE 16

VectorError VECTOR_GLOBAL_ERROR = VECTOR_SUCCESS;

Vector* vector_create()
{
    Vector *v = malloc(sizeof(Vector));
    v->buffer = malloc(INIT_ARRAY_SIZE * sizeof(double));
    v->buffer_size = INIT_ARRAY_SIZE;
    v->size = 0;
    return v;
}

void vector_println(Vector *v)
{
    printf("[");
    for (size_t i = 0; i < v->size; i++)
    {
        char *format = i == v->size - 1 ? "%.2f" : "%.2f, ";
        printf(format, v->buffer[i]);
    }
    printf("]\n");
}

int vector_is_empty(Vector *v)
{
    return v->size == 0;
}

size_t vector_size(Vector *v)
{
    return v->size;
}

/* Checks for possible errors, stores it on error and returns it's value 
Auxiliary funtion */
VectorError has_errors(VectorError *error, Vector *v, int empty_check, size_t *index_to_check)
{
    if (error == NULL) //Ignoring errors
        return VECTOR_SUCCESS; 

    if (empty_check && v->size == 0)
        *error = VECTOR_EMPTY;
    else if (index_to_check != NULL && *index_to_check >= v->size)
        *error = VECTOR_OUT_OF_BOUNDS;
    else
        *error = VECTOR_SUCCESS;

    return *error;
}

double vector_get(Vector *v, size_t index, VectorError *error)
{   
    if (has_errors(error, v, 0, &index))
        return 0;

    return v->buffer[index];
}

size_t vector_find(Vector *v, double value, int *found)
{
    size_t left = 0;
    size_t right = v->size - 1;
    *found = 1;
    while (left <= right)
    {
        if (v->buffer[left] == value) 
            return left;
        if (v->buffer[right] == value)
            return right;
        left++;
        right--;
    }
    *found = 0;
    return *found;
}

/* Auxiliar enum for resize function */
typedef enum ResizeRatio
{
    DOUBLE_SIZE,
    HALF_SIZE
} ResizeRatio;

/* Resizes buffer to either double it's size or half
Auxiliary function */
void vector_resize(Vector *v, ResizeRatio ratio)
{
    v->buffer_size = ratio == DOUBLE_SIZE ? v->buffer_size << 1 : v->buffer_size >> 1;
    v->buffer = realloc(v->buffer, v->buffer_size * sizeof(double));
}

void vector_add(Vector *v, double value)
{
    if (v->size >= v->buffer_size)
        vector_resize(v, DOUBLE_SIZE);
        
    v->buffer[v->size++] = value;
}

void vector_add_at_index(Vector *v, size_t index, double value, VectorError *error)
{
    if (has_errors(error, v, 0, &index))
        return;

    if (v->size >= v->buffer_size)
        vector_resize(v, DOUBLE_SIZE);

    double *src = v->buffer + index;
    memmove(src + 1, src, (v->size - index) * sizeof(double));
    v->buffer[index] = value;
    v->size++;
}

void vector_add_to_start(Vector *v, double value)
{
    if (v->size == 0)
        vector_add(v, value);
    else
        vector_add_at_index(v, 0, value, NULL); //Ignore error checking by passing NULL  
}

void vector_remove(Vector *v, VectorError *error)
{
    if (has_errors(error, v, 1, NULL))
        return;

    v->size--; //Lazy delete

    if (v->size < v->buffer_size >> 1)
        vector_resize(v, HALF_SIZE);
}

void vector_remove_at_index(Vector *v, size_t index, VectorError *error)
{
    if (has_errors(error, v, 0, &index))
        return;

    if (index == v->size - 1)
        vector_remove(v, NULL); //Ignore error checking by passing NULL
    else
    {
        double *src = v->buffer + index + 1;
        memmove(src - 1, src, (v->size - index) * sizeof(double));
        v->size--;

        if (v->size < v->buffer_size >> 1)
            vector_resize(v, HALF_SIZE);
    }
}

void vector_remove_first(Vector *v, VectorError *error)
{
    if (v->size == 1)
        vector_remove(v, error);
    else
        vector_remove_at_index(v, 0, error);    
}


void vector_destroy(Vector *v)
{
    free(v->buffer);
    free(v);
}
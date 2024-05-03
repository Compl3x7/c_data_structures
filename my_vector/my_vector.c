#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "my_vector.h"

#define INIT_ARRAY_SIZE 16

VectorError VECTOR_GLOBAL_ERROR;

Vector* vector_create()
{
    srand(time(NULL));
    Vector *v = malloc(sizeof(Vector));
    v->buffer = malloc(INIT_ARRAY_SIZE * sizeof(double));
    v->buffer_size = INIT_ARRAY_SIZE;
    v->size = 0;
    return v;
}

Vector* vector_copy(Vector *v)
{
    Vector *v_copy = malloc(sizeof(Vector));
    v_copy->buffer = malloc(v->buffer_size * sizeof(double));
    memcpy(v_copy->buffer, v->buffer, v->size * sizeof(double));
    v_copy->buffer_size = v->buffer_size;
    v_copy->size = v->size;
    return v_copy;
}

void vector_destroy(Vector *v)
{
    free(v->buffer);
    free(v);
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
VectorError check_errors(VectorError *error, Vector *v, int empty_check, size_t *index_to_check)
{
    if (error == IGNORE_ERRORS) //Ignoring error checks
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
    if (check_errors(error, v, 0, &index) != VECTOR_SUCCESS)
        return 0;

    return v->buffer[index];
}

size_t vector_find(Vector *v, double value, int *found)
{
    *found = 1;
    for (size_t i = 0; i < v->size; i++)
        if (v->buffer[i] == value)
            return i;
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
    if (check_errors(error, v, 0, &index) != VECTOR_SUCCESS)
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
        vector_add_at_index(v, 0, value, IGNORE_ERRORS);  
}

void vector_remove(Vector *v, VectorError *error)
{
    if (check_errors(error, v, 1, NULL))
        return;

    v->size--; //Lazy delete

    if (v->size < v->buffer_size >> 1)
        vector_resize(v, HALF_SIZE);
}

void vector_remove_at_index(Vector *v, size_t index, VectorError *error)
{
    if (check_errors(error, v, 0, &index))
        return;

    if (index == v->size - 1)
        vector_remove(v, IGNORE_ERRORS);
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

void vector_set_at_index(Vector *v, size_t index, double value, VectorError *error)
{
    if (check_errors(error, v, 0, &index) != VECTOR_SUCCESS)
        return;

    v->buffer[index] = value;
}

/* Swaps elements at i and j in vector
Auxiliary function */
void vector_swap(Vector *v, size_t i, size_t j)
{
    double temp = v->buffer[i];
    v->buffer[i] = v->buffer[j];
    v->buffer[j] = temp;
}

size_t vector_partition(Vector *v, size_t low, size_t high, int(*cmp)(double, double))
{
    size_t size = high - low + 1;
    size_t pivot_index = low + rand() % size;
    double pivot = v->buffer[pivot_index];
    vector_swap(v, low, pivot_index); //Pivot is temporarily in v->buffer[low] to perform a traditional partition

    size_t i = low + 1;
    size_t j = high;
    while (i < j)
    {
        while (cmp(v->buffer[i], pivot) <= 0 && i <= high)
            i++;
        while (cmp(v->buffer[j], pivot) > 0 && j >= low)
            j++;
        if (i < j)
            vector_swap(v, i, j);
    }
    vector_swap(v, low, j);
    return j;
}

void vector_bounded_rqsort(Vector *v, size_t low, size_t high, int(*cmp)(double, double))
{
    if (low >= high)
        return;

    size_t pivot_index = vector_partition(v, low, high, cmp);
    vector_bounded_rqsort(v, low, pivot_index - 1, cmp);
    vector_bounded_rqsort(v, pivot_index + 1, high, cmp);
}

void vector_rqsort(Vector *v, int(*cmp)(double, double))
{
    vector_bounded_rqsort(v, 0, v->size - 1, cmp);
}
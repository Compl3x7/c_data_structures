#ifndef MY_VECTOR_H
#define MY_VECTOR_H

/* Vector struct */
typedef struct Vector
{
    double *buffer;
    size_t buffer_size;
    size_t size;
} Vector;

/* Enum for error handling when needed
VECTOR_SUCCESS = 0
VECTOR_EMPTY = 1
VECTOR_OUT_OF_BOUNDS = 2 */
typedef enum VectorError 
{
    VECTOR_SUCCESS,
    VECTOR_EMPTY,
    VECTOR_OUT_OF_BOUNDS
} VectorError;

/* Global variable for error handling use, to avoid the need of declaring multiple */
extern VectorError VECTOR_GLOBAL_ERROR;

/* Creates a new empty vector and returns its reference, changing such will lead to undefined behavior
All vector functions expect a reference returned by this function, so it is the caller's resposability to ensure such condition when using this library
Must be freed later with vector_destroy() */
Vector* vector_create();

/* Prints a vector to stdout */
void vector_println(Vector *v);

/* Checks if a vector is empty
Returns 1 if it is 0 otherwise */
int vector_is_empty(Vector *v);

/* Returns size of a vector */
size_t vector_size(Vector *v);

/* Returns value at given index of vector
If given index is invalid, error value is set to true (!= VECTOR_SUCCESS) and return value is to be ignored */
double vector_get(Vector *v, size_t index, VectorError *error);

/* Returns index of the first given value found on a vector, using a two pointer search
If none were found, found value is set to 0 and return value is to be ignored */
size_t vector_find(Vector *v, double value, int *found);

/* Adds given value at the end of a vector */
void vector_add(Vector *v, double value);

/* Adds given value at given index of a vector
If given index is invalid, error value is set to true (!= VECTOR_SUCCESS) and no element will be added */
void vector_add_at_index(Vector *v, size_t index, double value, VectorError *error);

/* Adds given value at start of a vector */
void vector_add_to_start(Vector *v, double value);

/* Removes value at the end of a vector
This is actually done by using a lazy delete so the element continues in memory until reallocation
If vector is empty, error value is set to true (!= VECTOR_SUCCESS) and no element will be removed */
void vector_remove(Vector *v, VectorError *error);

/* Removes value at given index of a vector
If given index is invalid, error value is set to true (!= VECTOR_SUCCESS) and no element will be removed */
void vector_remove_at_index(Vector *v, size_t index, VectorError *error);

/* Removes first value of a vector
If vector is empty, error value is set to true (!= VECTOR_SUCCESS) and no element will be removed */
void vector_remove_first(Vector *v, VectorError *error);


/* Frees all allocated memory of a vector */
void vector_destroy(Vector *v);

#endif
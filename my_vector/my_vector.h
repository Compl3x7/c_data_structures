#ifndef my_vector_h
#define my_vector_h

/* Vector declaration and it's members */
typedef struct Vector
{
    double *array;
    unsigned int array_size;
    unsigned int size;
} Vector;

/* Creates a new empty vector
Must be freed later with vector_destroy() */
Vector* vector_create();

/* Prints a vector to stdout */
void vector_println(Vector *v);

/* Checks if a vector is empty
Returns 1 if it is 0 otherwise */
int vector_is_empty(Vector *v);

/* Returns size of a vector */
int vector_size(Vector *v);

/* Returns value at given index of a vector
Fails assertion if vector is empty or if given index is invalid */
double vector_get(Vector *v, int index);

/* Returns index of the first given value found on a vector, using a two pointer search, or -1 if none were found
Fails assertion if list is empty */
int vector_find(Vector *v, double value);

/* Adds given value at the end of a vector */
void vector_add(Vector *v, double value);


/* Removes value at the end of a vector
This is actually done by using a lazy delete so the element continues in memory
Fails assertion if list is empty */
void vector_remove(Vector *v);


/* Frees all allocated memory of a vector */
void vector_destroy(Vector *v);

#endif
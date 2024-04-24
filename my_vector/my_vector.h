#ifndef my_vector_h
#define my_vector_h

typedef struct Vector
{
    double *array;
    double *last;
    unsigned int size;
} Vector;

Vector* vector_create();


void vector_destroy(Vector *v);

#endif
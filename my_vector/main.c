#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "my_vector.h"

int main()
{
    srand(time(NULL));
    
    Vector *v = vector_create();
    vector_println(v);
    printf("Size: %zu Empty: %d\n\n", vector_size(v), vector_is_empty(v));

    for (int i = 0; i < 10; i++)
        vector_add(v, i);
    vector_println(v);
    printf("Size: %zu Empty: %d\n\n", vector_size(v), vector_is_empty(v));

    int i = 3;
    double d = vector_get(v, i, &VECTOR_GLOBAL_ERROR);
    VECTOR_GLOBAL_ERROR ? printf("Error occured on getting v[%d]\n\n", i) : printf("v[%d] = %lf\n", i, d);
    i = 11; //Out of bounds
    d = vector_get(v, i, &VECTOR_GLOBAL_ERROR);
    VECTOR_GLOBAL_ERROR ? printf("Error occured on getting v[%d]\n\n", i) : printf("v[%d] = %lf\n\n", i, d);

    int found;
    d = 5;
    i = vector_find(v, d, &found);
    found ? printf("Found %lf on v[%d]\n", d, i) : printf("Not found %lf\n", d);
    d = 3.14;
    i = vector_find(v, d, &found);
    found ? printf("Found %lf on v[%d]\n\n", d, i) : printf("Didn't found %lf\n\n", d);

    vector_println(v);
    printf("Size: %zu Allocated size: %zu\n\n", vector_size(v), v->buffer_size);

    for (int i = 0; i < 5; i++)
        vector_remove(v, NULL);
    vector_println(v);
    printf("Size: %zu Allocated size: %zu\n\n", vector_size(v), v->buffer_size);


    vector_destroy(v);

    return 0;
}
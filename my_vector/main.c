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
    printf("Array size = %d\n", v->array_size);
    printf("Size = %d\n", vector_size(v));

    for (int i = 0; i < 100; i++)
        vector_add(v, i); 

    vector_println(v);
    printf("Array size = %d\n", v->array_size);
    printf("Size = %d\n", vector_size(v));    

    for (int i = 0; i < 50; i++)
        vector_remove(v); 

    vector_println(v);
    printf("Array size = %d\n", v->array_size);
    printf("Size = %d\n", vector_size(v));    

    vector_destroy(v);

    return 0;
}
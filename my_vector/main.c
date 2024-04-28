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

    vector_add(v, 0);
    vector_println(v);

    vector_remove_first(v);
    vector_println(v);

    for (int i = 0; i < 10; i++)
        vector_add(v, i); 
    vector_println(v);

    vector_remove(v);
    vector_println(v);
    
    vector_remove_first(v);
    vector_println(v);
    
    vector_remove_at_index(v, 5);
    vector_println(v);
    
    vector_destroy(v);

    return 0;
}
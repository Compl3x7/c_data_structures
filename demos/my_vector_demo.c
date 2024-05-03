#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "./../my_vector/my_vector.h" //Long ass include

int cmp(double d1, double d2)
{
    return d1 - d2;
}

int main()
{
    /* Simple demo used for testing*/
    
    Vector *v = vector_create();

    for (int i = 0; i < 20; i++)
        vector_add(v, rand() % 100);
    vector_println(v);
    

    vector_rqsort(v, cmp);
    vector_println(v);

    vector_destroy(v);

    return 0;
}
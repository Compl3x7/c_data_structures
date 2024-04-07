#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "my_lists.h"

void remove_duplicates(List *l)
{
    if (l->size < 2)
        return;
    List t = list_tail(l);
    list_tail_remove_all(l, &t, list_head(l));
    remove_duplicates(&t);
}

int main()
{
    List *l = new_list();
    for (int i = 0; i < 10; i++)
        list_add(l, rand());
    list_println(l);

    list_ssort(l, list_ssort_cmp_ascending);

    list_println(l);

    free_list(l);

    return 0;
}
#ifndef my_list_h
#define my_list_h

/* Node declaration and it's members
Auxiliary declaration */
typedef struct Node
{
    double value;
    struct Node *next;
} Node;

/* List declaration and it's members */
typedef struct List
{
    Node *first;
    Node *last;
    unsigned int size;
} List;

/* Creates a new empty list
Must be freed later with list_destroy() */
List* list_create();

/* Prints a list to stdout */
void list_println(List *l);

/* Checks if a list is empty
Returns 1 if it is 0 otherwise */
int list_is_empty(List *l);

/* Returns size of a list */
int list_size(List *l);

/* Returns first value in a list
Fails assertion if list is empty */
double list_head(List *l);

/* Returns a vision of a list that represents every node but the first of a given list
Returned vision isn't allocated in the heap to avoid unnecessary memory handling
If used later with other functions, it should be stored in a variable of type List and passed as an argument to other function like "&list"

E.g.
...
List t = list_tail(l);
list_println(&t);
...

Fails assertion if list is empty

Doing operations directly to this vision might lead to unexpected changes in the original list
To handle that, all adding and removing functions have a duplicate called list_tail_...() that will do those same operations but handle any weird changes */
List list_tail(List *l);

/* Returns a new list that represents every node but the first of given list
Fails assertion if list is empty

Must be freed later with list_destroy() */
List* list_tail_copy(List *l);

/* Returns value at given index of a list
Fails assertion if list is empty or if given index is invalid */
double list_get(List *l, int index);

/* Returns index of given value on a list or -1 if none were found
Fails assertion if list is empty */
int list_find(List *l, double value);

/* Adds given value at the beginning of a list */
void list_add(List *l, double value);

/* Same as list_add, but made to handle operations to a tail vision of a list
Fails assertion if tail isn't list's tail */
void list_tail_add(List *l, List *tail, double value);

/* Adds given value at the end of a list */
void list_add_to_end(List *l, double value);

/* Same as list_add_to_end, but made to handle operations to a tail vision of a list
Fails assertion if tail isn't list's tail */
void list_tail_add_to_end(List *l, List *tail, double value);

/* Adds given value at specified index of a list
Fails assertion if given index is invalid */
void list_add_at_index(List *l, int index, double value);

/* Same as list_add_at_index, but made to handle operations to a tail vision of a list
Fails assertion if tail isn't list's tail or if given index is invalid */
void list_tail_add_at_index(List *l, List *tail, int index, double value);

/* Removes first element of a list
Fails assertion if list is empty */
void list_remove_first(List *l);

/* Same as list_remove_first, but made to handle operations to a tail vision of a list
Fails assertion list is empty, if tail is empty or if tail isn't list´s tail */
void list_tail_remove_first(List *l, List *tail);

/* Removes element at specified index of a list
Fails assertion if list is empty or if given index is invalid */
void list_remove_at_index(List *l, int index);

/* Same as list_remove_at_index, but made to handle operations to a tail vision of a list
Fails assertion list is empty, if tail is empty, if tail isn't list´s tail or if given index is invalid */
void list_tail_remove_at_index(List *l, List *tail, int index);

/* Removes last element of a list
Fails assertion if list is empty */
void list_remove_last(List *l);

/* Same as list_remove_last, but made to handle operations to a tail vision of a list
Fails assertion list is empty, if tail is empty or if tail isn't list´s tail */
void list_tail_remove_last(List *l, List *tail);

/* Removes first instance of given value
Returns 1 if it is removed, 0 otherwise
Fails assertion if list is empty */
int list_remove(List *l, double value);

/* Same as list_remove, but made to handle operations to a tail vision of a list
Fails assertion list is empty, if tail is empty or if tail isn't list´s tail */
int list_tail_remove(List *l, List *tail, double value);

/* Removes all instances of given value
Returns number of removals by the end
Fails assertion if list is empty */
int list_remove_all(List *l, double value);

/* Same as list_remove_all, but made to handle operations to a tail vision of a list
Fails assertion list is empty, if tail is empty or if tail isn't list´s tail */
int list_tail_remove_all(List *l, List *tail, double value);

/* Changes value at specified index of a list to given value
Fails assertion if list is empty or if given index is invalid */
void list_set_at_index(List *l, int index, double value);

/* Simple implementation of selection sort for this implementation of lists
Sorts list according to given compare function

Some simple compare functions come already with this library:
-list_ssort_cmp_ascending()
-list_ssort_cmp_descending()

Has a time complexity of O(n^2) */
void list_ssort(List *l, int(*cmp)(const Node*, const Node*));

/* Same as list_ssort(), but with a recursive implementation

Has a time complexity of O(n^2) */
void list_ssort_recursive(List *l, int(*cmp)(const Node*, const Node*));

/* Compare function for list_ssort()
Will sort by ascending order if passed as an argument to list_ssort() */
int list_ssort_cmp_ascending(const Node *n1, const Node *n2);

/* Compare function for list_ssort()
Will sort by descending order if passed as an argument to list_ssort() */
int list_ssort_cmp_descending(const Node *n1, const Node *n2);

/* Returns a deep copy of a list
Must be freed later with list_destroy() */
List* list_copy(List *l);

/* Frees all allocated memory of a list */
void list_destroy(List *l);

#endif
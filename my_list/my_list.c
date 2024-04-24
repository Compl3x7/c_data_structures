#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "my_list.h"


//Node struct and functions

/* Creates new node
Auxiliary function */
Node* node_create(double value, Node *next)
{
    Node *n = malloc(sizeof(Node));
    n->value = value;
    n->next = next;
    return n;
}

/* Prints node to stdout
Auxiliary function */
void node_print(Node *n)
{
    if (n->next == NULL)
        printf("%.2f", n->value);
    else
       printf("%.2f, ", n->value); 
}

/* Frees all allocated memory of a node
Auxiliary function */
void node_destroy(Node *n)
{
    free(n);
}


//List struct and functions

List* list_create()
{
    List *l = malloc(sizeof(List));
    l->first = NULL;
    l->last = NULL;
    l->size = 0;
    return l;
}

void list_println(List *l)
{
    printf("{");
    Node *n_iterator = l->first;
    while (n_iterator != NULL)
    {
        node_print(n_iterator);
        n_iterator = n_iterator->next; //Goes forward idk
    }
    printf("}\n");
}

//"Getting information" from list functions

int list_is_empty(List *l)
{
    return l->first == NULL;
}

int list_size(List *l)
{
    return l->size;
}

double list_head(List *l)
{
    assert(l->first != NULL);
    return l->first->value;
}

List list_tail(List *l)
{
    assert(l->first != NULL);
    List tail;
    tail.first = l->first->next;
    tail.last = l->last;
    tail.size = l->size - 1;
    return tail; //No one in their right mind would use this vision for operations right?
}

double list_get(List *l, int index)
{
    assert(l->first != NULL);
    assert(index >= 0 && index < l->size);
    Node *n_iterator = l->first;
    for (int i = 0; i < index; i++)
        n_iterator = n_iterator->next; //Goes forward idk
    return n_iterator->value;
}

int list_find(List *l, double value)
{
    assert(l->first != NULL);
    int index = -1;
    Node *n_iterator = l->first;
    int i = 0;
    while (n_iterator != NULL)
    {
        if (n_iterator->value == value)
        {
            index = i;
            break;
        }
        n_iterator = n_iterator->next; //Goes forward idk
        i++;
    }
    return index;
}

//Adding to list functions

void list_add(List *l, double value)
{
    // Node *old_n = l->first;
    // Node *new_n = node_create(value, old_n);
    l->first = node_create(value, l->first);
    if (l->first->next == NULL)
        l->last = l->first;
    l->size++;
}

void list_tail_add(List *l, List *tail, double value)
{
    assert(l->first->next == tail->first);
    list_add(tail, value);
    l->first->next = tail->first;
    l->last = tail->last;
    l->size++;
}

void list_add_to_end(List *l, double value)
{
    if (l->first == NULL) 
        list_add(l, value);
    else
    {
        Node *new_n = node_create(value, NULL);
        l->last->next = new_n;
        l->last = new_n;
        l->size++;
    }
}

void list_tail_add_to_end(List *l, List *tail, double value)
{
    assert(l->first->next == tail->first);
    list_add_to_end(tail, value);
    l->last = tail->last;
    l->size++;
}

void list_add_at_index(List *l, int index, double value)
{
    assert(index >= 0 && index < l->size);
    if (index == 0) 
        list_add(l, value); 
    else
    {
        Node *n_iterator = l->first;
        for (int i = 0; i < index - 1; i++) //Goes to element at index - 1
            n_iterator = n_iterator->next; //Goes forward idk
        //Node *new_n = node_create(value, n_iterator->next);
        n_iterator->next = node_create(value, n_iterator->next);
        l->size++;
    }
}

void list_tail_add_at_index(List *l, List *tail, int index, double value)
{
    assert(l->first->next == tail->first);
    assert(index >= 0 && index < tail->size);
    if (index == 0)
        list_tail_add(l, tail, value);
    else
    {
        list_add_at_index(tail, index, value);
        l->size++;
    }    
}

//Removing from list functions

/* Removes element after given node
Fails assertion if list is empty
Auxiliary function */
void list_remove_after_element(List *l, Node *before)
{
    assert(l->first != NULL);
    Node *next_next = before->next->next;
    if (next_next == NULL)
        l->last = before;
    node_destroy(before->next);
    before->next = next_next;
    l->size--;
}

void list_remove_first(List *l)
{
    assert(l->first != NULL);
    Node *n_ptr = l->first;
    l->first = l->first->next;
    node_destroy(n_ptr);
    l->size--;
}

void list_tail_remove_first(List *l, List *tail)
{
    assert(l->first != NULL);
    assert(tail->first != NULL);
    assert(l->first->next == tail->first);
    list_remove_first(tail);
    l->first->next = tail->first;
    l->size--;
}

void list_remove_at_index(List *l, int index)
{
    assert(l->first != NULL);
    assert(index >= 0 && index < l->size);
    if (index == 0) //Handles case where first element of list is the one to be removed
    {
        list_remove_first(l);
        return;
    }

    Node *n_iterator = l->first;
    for (int i = 0; i < index - 1; i++) //Goes to element at index - 1
            n_iterator = n_iterator->next; //Goes forward idk
    list_remove_after_element(l, n_iterator);

    if (l->size == 0) //If all elements of the list were deleted set pointer to last element null, just like pointer to first element
        l->last = NULL; //Do I really need this?
}

void list_tail_remove_at_index(List *l, List *tail, int index)
{
    assert(l->first != NULL);
    assert(tail->first != NULL);
    assert(l->first->next == tail->first);
    assert(index >= 0 && index < tail->size);
    if (index == 0)
        list_tail_remove_first(l, tail);
    else
    {
        list_remove_at_index(tail, index);
        l->last = tail->last;
        l->size--;
    }
}

void list_remove_last(List *l)
{
    assert(l->first != NULL);
    list_remove_at_index(l, l->size - 1);
}

void list_tail_remove_last(List *l, List *tail)
{
    assert(l->first != NULL);
    assert(tail->first != NULL);
    assert(l->first->next == tail->first);
    list_remove_last(tail);
    l->last = tail->last;
    l->size--;
}

int list_remove(List *l, double value)
{
    assert(l->first != NULL);
    int removal = 0;
    if (l->first->value == value) //Handles case where first element of list is the one to be removed
    {
        list_remove_first(l);
        removal = 1;
        return removal; //Returns right away since we only want to delete the first instance of given value
    }

    Node *n_iterator = l->first;
    while (n_iterator->next != NULL)
    {
        if(n_iterator->next->value == value)
        {
            list_remove_after_element(l, n_iterator);
            removal = 1;
            break;
        }
        n_iterator = n_iterator->next; //Goes forward idk
    }

    if (l->size == 0) //If all elements of the list were deleted set pointer to last element null, just like pointer to first element
        l->last = NULL; //Do I really need this?
    return removal;
}

int list_tail_remove(List *l, List *tail, double value)
{
    assert(l->first != NULL);
    assert(tail->first != NULL);
    assert(l->first->next == tail->first);
    int removal = list_remove(tail, value);
    if (removal)
    {
        l->first->next = tail->first;
        l->last = tail->last;
        l->size--;
    }
    return removal;
}

int list_remove_all(List *l, double value)
{
    assert(l->first != NULL);
    int n_removal = 0;
    while (l->first != NULL && l->first->value == value) //Since we might delete multiple elements, while the first one is the one to be deleted we delete the first element
    {
        list_remove_first(l);
        n_removal++;
    }

    Node *n_iterator = l->first;
    while (l->first != NULL && n_iterator->next != NULL) //Will only enter while loop if there are any elements left after initial deletions
    {
        if(n_iterator->next->value == value)
        {
            list_remove_after_element(l, n_iterator);
            n_removal++; //We don't neeed to go forward since, virtually we already did by shifting everything to the left after deletion
        }
        else
            n_iterator = n_iterator->next; //Goes forward idk
    }

    if (l->size == 0) //If all elements of the list were deleted set pointer to last element null, just like pointer to first element
        l->last = NULL; //Do I really need this?
    return n_removal;
}

int list_tail_remove_all(List *l, List *tail, double value)
{
    assert(l->first != NULL);
    assert(tail->first != NULL);
    assert(l->first->next == tail->first);
    int n_removal = list_remove_all(tail, value);
    if (n_removal > 0)
    {
        l->first->next = tail->first;
        l->last = tail->last;
        l->size = l->size - n_removal;
    }
    return n_removal;
}

//Changing list functions

void list_set_at_index(List *l, int index, double value)
{
    assert(l->first != NULL);
    assert(index >= 0 && index < l->size);
    Node *n_iterator = l->first;
    for (int i = 0; i < index; i++)
        n_iterator = n_iterator->next; //Goes forward idk
    n_iterator->value = value;
}
 
void list_ssort(List *l, int(*cmp)(const Node*, const Node*))
{   
    if (l->first == NULL) return;
    Node *outer_n_iterator = l->first;
    while (outer_n_iterator->next != NULL)
    {
        Node *min = outer_n_iterator;
        Node *inner_n_iterator = outer_n_iterator->next;
        while (inner_n_iterator != NULL)
        {
            if (cmp(inner_n_iterator, min) < 0) 
                min = inner_n_iterator;
            inner_n_iterator = inner_n_iterator->next; //Goes forward idk
        }    
        double min_value = min->value;
        min->value = outer_n_iterator->value;
        outer_n_iterator->value = min_value;
        outer_n_iterator = outer_n_iterator->next; //Goes forward since all nodes before this one are now sorted
    }
}

void list_ssort_recursive(List *l, int(*cmp)(const Node*, const Node*))
{   
    if (l->first == NULL) return;
    Node *min = l->first;
    Node *n_iterator = min->next;
    while (n_iterator != NULL)
    {
        if (cmp(n_iterator, min) < 0) 
            min = n_iterator;
        n_iterator = n_iterator->next; //Goes forward idk
    }    
    double min_value = min->value;
    min->value = l->first->value;
    l->first->value = min_value;

    List tail = list_tail(l);
    list_ssort_recursive(&tail, cmp);
}

//Some cmp functions

int list_ssort_cmp_ascending(const Node *n1, const Node *n2)
{
    return n1->value - n2->value;
}

int list_ssort_cmp_descending(const Node *n1, const Node *n2)
{
    return -list_ssort_cmp_ascending(n1, n2);
}

//Copy list functions

List* list_copy(List *l)
{
    List *l_cpy = list_create();
    Node *n_iterator = l->first;
    while (n_iterator != NULL)
    {
        list_add_to_end(l_cpy, n_iterator->value);
        n_iterator = n_iterator->next; //Goes forward idk
    }
    return l_cpy;
}

List* list_tail_copy(List *l)
{
    assert(l->first != NULL);
    List *l_tail = list_create();
    Node *n_iterator = l->first->next;
    while (n_iterator != NULL)
    {
        list_add_to_end(l_tail, n_iterator->value);
        n_iterator = n_iterator->next; //Goes forward idk
    }
    return l_tail;
}

//Freeing memory functions

void list_destroy(List *l)
{
    while (l->first != NULL)
        list_remove_first(l);
    free(l);
}
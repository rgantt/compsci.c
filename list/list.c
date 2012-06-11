#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

node *new_node( list_entry value ) {
    node *n = malloc( sizeof( node ) );
    n->next = NULL;
    // oops, this assumes string
    n->value = strdup( value );
    return n;
}

void destroy_list( node *head ) {
    node *current = head, *next;
    while( current->next != NULL ) {
        next = current;
        current = current->next;
        free(next->value);
        free(next);
    }
    free(current->value);
    free(current);
}

void add_node( node *head, node *new ) {
    while( head->next != NULL ) {
        head = head->next;
    }
    head->next = new;
}

void delete_node( node *head, list_entry value ) {
    node *current = head, *previous;
    if( current == NULL ) return;
    previous = current;
    current = current->next;
    // if there is a multi-element list, keep a pointer to the previous element so we can
    // easily update the pointers to remove the deleted one
    do {
        if( strcmp( current->value, value ) == 0 ) {
            previous->next = current->next;
            free(current->value);
            free(current);
            return;
        }
    } while( ( current != NULL ) && ( current = current->next ) && ( previous = previous->next ) );
}

node *find_node( node *head, list_entry value ) {
    do {
        //if( head->value == value ) {
        if( strcmp( head->value, value ) == 0 ) {
            return head;
        }
    } while( ( head = head->next ) != NULL );
    return NULL;
}

void print_list( node *head ) {
    while( head->next != NULL ) {
        printf( "%s -> ", head->value );
        head = head->next;
    }
    printf( "%s -> 0\n", head->value );
}

#ifndef ILIST
#define ILIST

typedef char* list_entry;

typedef struct node {
    struct node *next;
    list_entry value;
} node;

node *new_node( list_entry );
void destroy_list( node * );
void add_node( node *, node * );
void delete_node( node *, list_entry );
node *find_node( node *, list_entry );
void print_list( node * );

#endif

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct Node {
	struct Node *next;
	Entry *value;
} Node;

Node *new( char *value ) {
	Node *n = malloc( sizeof( Node ) );
	n->next = NULL;
	n->value = strdup( value );
	return n;
}

void add( Node *node, Node *new ) {
	while( node->next != NULL ) {
		node = node->next;
	}
	node->next = new;
}

Node *find( Node *node, Node *search ) {
	do {
		if( node == search ) {
			return node;
		}
	} while( ( node = node->next ) != NULL );
}

void printList( Node *head ) {
	while( head->next != NULL ) {
		printf( "%s -> ", head->value );
		head = head->next;
	}
	printf( "%s -> 0\n", head->value );
}
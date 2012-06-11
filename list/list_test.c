#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "suite.h"
#include "list.h"

void list_test_add() {
    node *first = new_node("first");
    node *second = new_node("second");
    node *third = new_node("third");

    add_node( first, second );
    add_node( first, third );

    assert_equals_str( first->next->value, "second", "test_add" );
    assert_equals_str( first->next->next->value, "third", "test_add" );

    destroy_list(first);
}

void list_test_find() {
    node *first = new_node("first");
    node *second = new_node("second");
    node *third = new_node("third");
    
    add_node( first, second );
    add_node( first, third );
    
    assert_equals_str( find_node( first, "second" )->value, "second", "test_find" ); 
    
    destroy_list(first);
}

void list_test_remove() {
    node *first = new_node("first");
    node *second = new_node("second");
    node *third = new_node("third");
    node *fourth = new_node("fourth");
    
    add_node( first, second );
    add_node( first, third );
    add_node( first, fourth );
    
    delete_node( first, "second" );
    
    assert_equals_str( first->value, "first", "test_remove" );
    assert_equals_str( first->next->value, "third", "test_remove" );
    assert_equals_str( first->next->next->value, "fourth", "test_remove" );
    
    destroy_list(first);
}

int main( int argc, char **argv ) {
    suite_init();

    list_test_add();
    list_test_find();
    list_test_remove();

    suite_report();

    return 0;
}

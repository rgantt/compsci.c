#include <stdio.h>
#include "suite.h"
#include "queue-stack.h"

void test_queue_enqueue_dequeue() {
    queue *q = new_queue();
    
    enqueue( q, "foo" );
    
    assert_equals_str( "foo", dequeue(q), "test_queue_enqueue_dequeue" );
    
    destroy_queue(q);
}

void test_queue_multi_element_dequeue() {
    queue *q = new_queue();
    
    enqueue( q, "first" );
    enqueue( q, "second" );
    
    assert_equals_str( "first", dequeue(q), "test_queue_multi_element_dequeue" );
    assert_equals_str( "second", dequeue(q), "test_queue_multi_element_dequeue" );
    
    destroy_queue(q);
}

/**
 * test that our wraparound logic won't blow up the queue
 */
void test_queue_multi_enqueue_dequeue() {
    queue *q = new_queue();
    
    enqueue( q, "first" );
    enqueue( q, "second" );
    enqueue( q, "third" );
    enqueue( q, "fourth" );
    dequeue( q );
    dequeue( q );
    printf("adding fifth\n");
    enqueue( q, "fifth" );
    printf("adding sixth\n");
    enqueue( q, "sixth" );
    printf("done");
    
    assert_equals_str( "third", dequeue(q), "test_queue_multi_enqueue_dequeue" );
    
    destroy_queue(q);
    
}

int main( int argc, char **argv ) {
    suite_init();
    
    test_queue_enqueue_dequeue();
    test_queue_multi_element_dequeue();
    test_queue_multi_enqueue_dequeue(); 
    
    suite_report();
    return 0;    
}

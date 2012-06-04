#include "suite.h"
#include "queue.h"

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

int main( int argc, char **argv ) {
    suite_init();
    
    test_queue_enqueue_dequeue();
    test_queue_multi_element_dequeue();
    
    suite_report();
    return 0;    
}

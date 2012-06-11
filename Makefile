suite:
	cc -Wall -g -I. -c suite.c -o suite.o

clean:
	rm -f suite.o a.out

clean-win:
	rm -f suite.o a.exe
	
list: suite
	cc -Wall -g -I. list/*.c suite.o
	
stack: suite
	cc -Wall -g -I. stack/stack.c stack/stack_test.c suite.o

stack-queue: suite
	cc -Wall -g -I. stack/stack-queue.c stack/stack_test.c suite.o
	
hashmap: suite
	cc -Wall -g -I. hashmap/*.c suite.o

queue: suite
	cc -Wall -g -I. queue/queue.c queue/queue_test.c suite.o
	
queue-stack: suite
	cc -Wall -g -I. -Istack stack/stack.c queue/queue-stack.c queue/queue_test.c suite.o

suite:
	cc -Wall -g -I. -c suite.c -o suite.o

clean:
	rm -f suite.o a.out

clean-win:
	rm -f suite.o a.exe
	
list: suite
	cc -Wall -g -I. list/*.c suite.o
	
stack: suite
	cc -Wall -g -I. stack/*.c suite.o
	
hashmap: suite
	cc -Wall -g -I. hashmap/*.c suite.o

queue: suite
	cc -Wall -g -I. queue/*.c suite.o

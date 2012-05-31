suite:
	cc -Wall -g -I. -c suite.c -o suite.o

clean:
	rm -f suite.o a.out

clean-win:
	rm -f suite.o a.exe
	
stack: suite
	cc -Wall -g -I. stack/*.c suite.o
	
hashmap: suite
	cc -Wall -g -I. hashmap/*.c suite.o

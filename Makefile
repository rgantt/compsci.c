suite:
	gcc -Wall -c suite.c -o suite.o

clean:
	rm suite.o a.exe
	
stack: suite
	gcc -Wall -I. stack/*.c suite.o
	
hashmap: suite
	gcc -Wall -I. hashmap/*.c suite.o
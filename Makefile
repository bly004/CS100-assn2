all: rshell

rshell: main.o
	mkdir bin
	g++ -Wall -Werror -ansi -pedantic main.o -o bin/rshell 

clean: 
	rm -f ./bin
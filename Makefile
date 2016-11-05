all: rshell

rshell: main.o
	mkdir bin
	g++ -Wall -Werror -ansi -pedantic /src/main.cpp -o bin/rshell 

clean: 
	rm -f ./bin
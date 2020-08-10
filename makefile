assembler: main.o first_run.o data.o utils.o data.o
	gcc  -g   -pedantic -Wall main.o first_run.o utils.o data.o -lm -o assembler

main.o: main.c first_run.h data.h utils.h
	gcc -c  -Wall -pedantic main.c -o main.o

first_run.o: first_run.c utils.h data.c first_run.h
	gcc -c  -Wall -pedantic first_run.c -o first_run.o

data.o: data.c data.h
	gcc -c  -Wall -pedantic data.c -o data.o

utils.o: utils.c utils.h
	gcc -c -Wall -pedantic utils.c -o utils.o


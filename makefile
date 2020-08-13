assembler: main.o first_run.o data.o utils.o data.o second_run.o
	gcc  -g   -pedantic -Wall main.o first_run.o utils.o data.o second_run.o -lm -o assembler

main.o: main.c first_run.h data.h utils.h second_run.h
	gcc -c  -Wall -pedantic main.c -o main.o

first_run.o: first_run.c utils.h data.c first_run.h
	gcc -c  -Wall -pedantic first_run.c -o first_run.o

data.o: data.c data.h
	gcc -c  -Wall -pedantic data.c -o data.o

utils.o: utils.c utils.h data.h
	gcc -c -Wall -pedantic utils.c -o utils.o

second_run.o: second_run.c second_run.h utils.h data.h first_run.h
	gcc -c -Wall -pedantic second_run.c -o second_run.o


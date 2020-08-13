assembler: main.o first_run.o data.o utils.o data.o second_run.o
	gcc  -g   -pedantic -Wall -ansi main.o first_run.o utils.o data.o second_run.o -lm -o assembler

main.o: main.c first_run.h data.h utils.h second_run.h
	gcc -c -pedantic -Wall -ansi  main.c -o main.o

first_run.o: first_run.c utils.h data.c first_run.h
	gcc -c -pedantic -Wall -ansi  first_run.c -o first_run.o

data.o: data.c data.h
	gcc -c  -pedantic -Wall -ansi  data.c -o data.o

utils.o: utils.c utils.h data.h
	gcc -c -pedantic -Wall -ansi  utils.c -o utils.o

second_run.o: second_run.c second_run.h utils.h data.h first_run.h
	gcc -c -pedantic -Wall -ansi  second_run.c -o second_run.o


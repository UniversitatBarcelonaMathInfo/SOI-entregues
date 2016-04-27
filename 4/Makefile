all: segundos principal

segundos: segundos.o
	gcc segundos.o -o segundos -Wall

segundos.o: segundos.c
	gcc segundos.c -c -Wall

principal: principal.o
	gcc principal.o -o principal -Wall

principal.o: principal.c
	gcc principal.c -c -Wall

clear:
	rm *.o -f segundos principal

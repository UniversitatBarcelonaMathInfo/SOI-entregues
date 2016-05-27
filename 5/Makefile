OBJ	= malloctest malloc.so testAll
FLAGS	= -g -Wall -Wextra -W

all: ${OBJ}

malloc.so: malloc.c
	gcc -shared -fPIC malloc.c -o malloc.so ${FLAGS}

malloctest: malloctest.c
	gcc malloctest.c -o malloctest ${FLAGS}

testAll: testAll.c
	gcc testAll.c -o testAll ${FLAGS}

clear: 
	rm ${OBJ} -f

# Per evitar problemes like hi ha un fitxer anomenat all i ja no compila res mes
.PHONY: all clear

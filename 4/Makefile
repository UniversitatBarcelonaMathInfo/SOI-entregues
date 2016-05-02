# Informacio: http://www.adp-gmbh.ch/cpp/gcc/create_lib.html
# Ja que donava errors de compilacio la llibreria dinamica donada al tema 1

# Es important posar la llibreria primer
# sino es possible que no existeixi la llibreria per a crear els objectes.
# O puc fer aixi ja que la llibreria es dinamica
all: librw_pid.so principal segundos minutos horas

# -L.: Es per direccionar on es troba la llibreria entrada per -l rw_pid
# Tota la resta es normal de crear objectes
principal: principal.o
	gcc -L. principal.o -o principal -Wall -l rw_pid
segundos: segundos.o
	gcc -L. segundos.o -o segundos -Wall -l rw_pid
minutos: minutos.o
	gcc -L. minutos.o -o minutos -Wall -l rw_pid
horas: horas.o
	gcc -L. horas.o -o horas -Wall -l rw_pid

# Per aconseguir que el codi es compili nomes quan hi ha hagut canvis
principal.o: principal.c
	gcc principal.c -c -Wall
segundos.o: segundos.c
	gcc segundos.c -c -Wall
minutos.o: minutos.c
	gcc minutos.c -c -Wall
horas.o: horas.c
	gcc horas.c -c -Wall

# Llibreria dinamica, gracies als apunts del tema 1
librw_pid.so: rw_pid.o
	gcc -shared -o librw_pid.so rw_pid.o
rw_pid.o: rw_pid.c
	gcc -c -fPIC -Wall rw_pid.c

# Eliminar tot el que es compila
# Tambe elimina el residu de la execucio dels programes '*.pid'
clear:
	rm -f *.o segundos principal minutos horas *.pid *.so

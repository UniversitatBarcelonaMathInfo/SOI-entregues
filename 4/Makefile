all: segundos principal

segundos: segundos.o rw_pid.so
	gcc segundos.o -o segundos -Wall rw_pid.so

segundos.o: segundos.c
	gcc segundos.c -c -Wall

principal: principal.o rw_pid.so
	gcc principal.o -o principal -Wall rw_pid.so

principal.o: principal.c
	gcc principal.c -c -Wall

# Llibreria dinamica
rw_pid.so: rw_pid.o
	gcc -shared -o rw_pid.so rw_pid.o
rw_pid.o: rw_pid.c
	gcc rw_pid.c -c -fPIC -Wall

clear:
	rm *.o -f segundos principal minutos horas *.pid

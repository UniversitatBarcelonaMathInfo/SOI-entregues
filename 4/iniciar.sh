rm *.pid -f
./limpiar.sh
export LD_LIBRARY_PATH=$(pwd):$LD_LIBRARY_PATH
./principal&
./segundos&
./minutos&
./horas&

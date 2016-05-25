#!/bin/bash

if [ $# == 0 ]
then
	export LD_PRELOAD=/$PWD/malloc.so
	./malloctest
elif [ $1 == ls ]
then
	export LD_PRELOAD=/$PWD/malloc.so
	ls --color=auto
elif [ $1 == gdb ]
then
	echo "escriu: set enviroment LD_PRELOAD=./malloc.so"
	gdb malloctest -q
elif [ $1 == fir ]
then
	export LD_PRELOAD=/$PWD/malloc.so
	firefox
else
	echo "no se"
fi
#else if [ $1 == ls ]
#then
#	ls
#fi

# For gdb:
#
# gdb ./malloctest
# (gdb) set enviroment LD_PRELOAD=./malloc.so
# (gdb) ... run

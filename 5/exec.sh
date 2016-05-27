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
	echo "escriu: set environment LD_PRELOAD=./malloc.so"
	gdb malloctest -q
elif [ $1 == fir ]
then
	export LD_PRELOAD=/$PWD/malloc.so
	firefox
elif [ $1 == all ]
then
	export LD_PRELOAD=/$PWD/malloc.so
	./testAll
elif [ $1 == a ]
then
	echo "escriu: set environment LD_PRELOAD=./malloc.so"
	gdb testAll -q
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

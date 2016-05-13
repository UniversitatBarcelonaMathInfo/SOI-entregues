#!/bin/bash

#info: http://tldp.org/LDP/Bash-Beginners-Guide/html/sect_07_01.html
aux=$(ps aux | egrep '\./(principal|segundos|minutos|horas)$')
if [ $? -eq 0 ]
then
	kill -SIGKILL $(ps aux | egrep '/(principal|segundos|minutos|horas)$' | awk '{print $2}')
#	kill -SIGKILL $(echo $aux | awk '{print $2}') // Per funcionar necesitaria un for...
	if [ $? -ne 0 ]
	then
#		kill -9 $(echo $aux | awk '{print $2}')
		kill -9 $(ps aux | egrep '/(principal|segundos|minutos|horas)$' | awk '{print $2}')
		echo "Bug, no se perque a casa meva no va..."
	fi
	echo "OK: eliminat"
else
	echo "No hi ha inicialitzat els programes dits"
fi

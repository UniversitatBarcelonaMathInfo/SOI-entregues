#info: http://tldp.org/LDP/Bash-Beginners-Guide/html/sect_07_01.html
ps aux | egrep '/(principal|segundos|minutos|horas)'
if [ $? -eq 0 ]
then
	kill -SIGKILL $(ps aux | egrep '/(principal|segundos|minutos|horas)' | awk '{print $2}')
	echo "eliminat"
else
	echo "ERROR, cap fitxer"
fi

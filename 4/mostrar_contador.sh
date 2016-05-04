# Per a mostrar l'hora del contador
kill -SIGALRM $(ps aux | egrep '/(principal)' | awk '{print $2}')
if [ $? -ne 0 ]
then # no em funciona a casa amb el SIGALRM
	kill -14 $(ps aux | egrep '/(principal)' | awk '{print $2}')
fi

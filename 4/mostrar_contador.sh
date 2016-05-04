# Per a mostrar l'hora del contador
kill -14 $(ps aux | egrep '/(principal)' | awk '{print $2}')
#kill -SIGALARM $(ps aux | egrep '/(principal)' | awk '{print $2}')

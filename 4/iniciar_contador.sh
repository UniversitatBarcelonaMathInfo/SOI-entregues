# inicialitzar el contador
kill -10 $(ps aux | egrep '/(principal)' | awk '{print $2}')

# No em funcionava amb -SIGCONT
kill -SIGCONT $(ps aux | egrep '/(principal)' | awk '{print $2}')

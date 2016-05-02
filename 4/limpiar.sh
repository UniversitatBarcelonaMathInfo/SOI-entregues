ps aux | egrep '/(principal|segundos|minutos|horas)'
kill $(ps aux | egrep '/(principal|segundos|minutos|horas)' | awk '{print $2}')

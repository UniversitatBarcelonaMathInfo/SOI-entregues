kill $(ps aux | egrep '/(principal)' | awk '{print $2}')

a=$(ps aux | egrep '/(principal)' | awk '{print $2}')
kill -SIGCONT $a

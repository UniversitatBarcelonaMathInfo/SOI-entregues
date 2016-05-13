#!/bin/bash

# El SIGTERM l'envia per defecte kill. No cal posar mes parametres
kill $(ps aux | egrep '/(principal)' | awk '{print $2}')

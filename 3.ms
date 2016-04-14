\" Definim com volem les equacions a on les volem
.EQ
delim @$
.EN

.TL
Shell Scripting

.AU
Arnau Sistach Reinoso

.AI
Entrega de la pr\(`actica 3

.AB
Un cop llegit el document de la pr\(`actica 3, intentarem fer els problemes demanats.
.AE
\" Aqui acaba la presentació per defecte que hi ha

.NH
Problema
\" Pregunta 1.1
.IP
all=$(find coreutils-8.25)

\" Pregunta 1.2
.IP
<<<<<<< HEAD
echo "$all" | egrep "\.o$" | xargs rm
=======
\" WARNING !!!! diu d'aprofitar el resultat anterior + no usar bucles...
arnau % find coreutils-8.25 -name "*.o" -exec rm {} \\\;
>>>>>>> f7363bbc0a07c2c36e896a592b0470df6ceb6e4d

\" Pregunta 1.3
.IP
<<<<<<< HEAD
echo "$all" | egrep "\.c$" | xargs touch --date="2016-4-23"
=======
\" No arribo a pillar lo de quan deiu el pas 11, no veig com puc aprofitar el resultat anterior..., ja que els he eliminat...
\" WARNING !!!!
arnau % find coreutils-8.25 -name "*.c" -exec touch --date="2016-4-23" {} \\\;
>>>>>>> f7363bbc0a07c2c36e896a592b0470df6ceb6e4d

\" Pregunta 1.4
.IP
<<<<<<< HEAD
echo "$all" | egrep "/s[^/]*\\\.h" | xargs touch --date="2016-4-23"
=======
\" WARNING !!!! aprofitar el resultat del pas 1?? jo flipo, no se com fer-ho
arnau % find coreutils-8.25 -name "s*.h" -exec touch --date="2016-4-23" {} \\\;
>>>>>>> f7363bbc0a07c2c36e896a592b0470df6ceb6e4d

\" Problema 2
.NH
Problema

\" 2.1
.NH 2
Buscar tots els fitxers d'extenci\('o txt.

\" Problema 3
.NH
Problema
.IP
egrep "(this.*to)|(to.*this)" book.txt

\" 3.2
.IP
egrep "ly\\b" book.txt

\" 3.3
.IP
egrep "\\b[[:lower:]]{4}\\b" book.txt

\" 3.4
.IP
egrep "\\b[aeiou][[:alpha:]]*ing\\b" book.txt

\" 3.5
.IP
arnau % sed 's/\\b[aeiou][[:alpha:]]*ing/&-yeah!/g' book.txt

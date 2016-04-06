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
.LP
Fer anar el que s'ha ensenyat en aquest document.

\" Pregunta 1.1
.NH 2
Trobar tots els fitxers i subdirectori dins del directori coreutils-8.25
.LP
	En el document ens han ensenyat que \('es el find. Si no entres cap codici\('o buscar\(`a sense m\('es.
.b
Llavors nom\('es hem de tenir a vista el directori coreutils-8.25.
.IP
arnau % find coreutils-8.25

\" Pregunta 1.2
.NH 2
Eliminar tots els d'extenci\('o .o.
.LP
	El mateix find, permet executar programes. D'aquesta forma podem executar el rm que eliminar\(`a els
fitxers no desitjats.
.IP
\" WARNING !!!! diu d'aprofitar el resultat anterior + no usar bucles...
arnau % find coreutils-8.25 -name "*.o" -exec rm {} \\\;

\" Pregunta 1.3
.NH 2
Canvia la data dels fitxers amb extenci\('o .c.
.LP
	Per a buscar els fitxers amb extenci\('o .c, fem un find amb -name "*.o". Ara per canviar la data dels fitxers,
\('es tant f\(`acil com usar el touch amb --date="yyyy-mm-dd".
.IP
\" No arribo a pillar lo de quan deiu el pas 11, no veig com puc aprofitar el resultat anterior..., ja que els he eliminat...
\" WARNING !!!!
arnau % find coreutils-8.25 -name "*.c" -exec touch --date="2016-4-23" {} \\\;

\" Pregunta 1.4
.NH 2
El mateix que la pregunta anterior, per\(`o amb nom inicial s i extensi\('o .h.
.LP
Aquest en concret no cont\('e complexitat.
.IP
\" WARNING !!!! aprofitar el resultat del pas 1?? jo flipo, no se com fer-ho
arnau % find coreutils-8.25 -name "s*.h" -exec touch --date="2016-4-23" {} \\\;

\" Problema 2
.NH
Problemes

\" 2.1
.NH 2
Buscar tots els fitxers d'extenci\('o txt.

\" Problema 3
.NH
Problemes
.LP
Buscar dins dels fitxers.

\" 3.1
.NH 2
Buscar this i to a la mateixa l\('inia.
.LP
	grep "paraula a buscar" nomFitxer, podrem buscar la l\('inia que cont\('e el car\(`acter buscat. Repetim l'operaci\('o i obtinmdrem el resultat demanat.
.IP
arnau % egrep "this.*to\\|to.*this" book.txt

\" 3.2
.NH 2
Buscar alguna paraula que acabi en ly.
.LP
Tenim egrep, que ens permet posar exprecions. On \\b permet definir no caracter alfanum\(`eric.
.IP
arnau % egrep "ly\\b" book.txt

\" 3.3
.NH 2
Buscar paraules de 4 lletres en minuscula.
.LP
Gr\(`acies a \\b podem limitar la paraula, i tamb\('e tenim [[:lower:]] on estan definits les minuscules.
.IP
arnau % egrep "\\b[[:lower:]]{4}\\b" book.txt

\" 3.4
.NH 2
Buscar paraules que comen\(,cen per una vocal i acaben per ing.
.LP
Tot \('es una repetici\('o dels anteriors menys el fet de que accepti patrons diferents "comen\(,car per una vocal".
.IP
arnau % egrep "\\b[aeiou][[:alpha:]]*ing\\b" book.txt

\" 3.5
.NH 2
Repeteix la busqueda del 3.4, on afegir un -yeah! al final.
.LP
sed \('es una funci\('o que funciona igual que egrep a l'hora de buscar. Llavors nom\('es cal afegir que escrigui -yeah!.
Per a fer-ho tenim & que torna a escriure el que ha buscat.
.IP
arnau % sed 's\\b[aeiou][[:alpha:]]*ing/&-yeah!/' book.txt

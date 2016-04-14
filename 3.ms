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
.IP\" Pregunta 1.1
all=$(find coreutils-8.25)
.IP\" Pregunta 1.2
rm $(echo "$all" | egrep "\\.o$")
.IP \" Pregunta 1.3
touch --date="2016-4-23" $(echo "$all" | egrep "\\.c$")
.IP \" Pregunta 1.4
touch --date="2016-4-23" $(echo "$all" | egrep "/s[^/]*\\.h")

.NH \" Problema 2
Problema
.IP \" 2.1
wc $(find base_dades -type f -name "*.txt" | egrep "/etext[[:digit:]]{2}/") > table.txt
.IP
sort table.txt -rnk2 -o tmp.txt
.IP
printf "El numero %3d\n" `wc -l tmp.txt | awk '{print $1}'`
.IP
echo "Los 10 ficheros con mayor numero palabras"
.IP
head -n 10 tmp.txt
.IP
echo "Los 10 ficheros con menos palabras"
.IP
tail -n 10 tmp.txt

.NH \" Problema 3
Problema
.IP
egrep "(this.*to)|(to.*this)" book.txt
.IP \" 3.2
egrep "ly\\b" book.txt
.IP \" 3.3
egrep "\\b[[:lower:]]{4}\\b" book.txt
.IP \" 3.4
egrep "\\b[aeiou][[:alpha:]]*ing\\b" book.txt
.IP \" 3.5
sed 's/\\b[aeiou][[:alpha:]]*ing/&-yeah!/g' book.txt

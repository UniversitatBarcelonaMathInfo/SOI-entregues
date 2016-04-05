# 1 Buscar tots els fitxers extencio txt que estan dins el directori
# Com que pregunta per a fitxers: -type f, i pel nom -name "*.txt" -> find base_dades -type f -name "*.txt"

# 2 Filtrar la busqueda anterior i quedar-se nomes amb els que tenen subdirectori etextXX on X es un digit
# Com que es filtrar, el find ja no serveix, el mes facil seria fer una busqueda am tot...
# Ara tenim egrep "/etext[[:digit:]]{2}/" les / perque es un subdirectori

rm table.txt # per no fer un fitxer infinitament gran
for file in `find base_dades -type f -name "*.txt" | egrep "/etext[[:digit:]]{2}/"`
do
	wc $file >> table.txt # 3 fer wc i posar-ho tot dins de table.txt
done

# 4 Ordenar el table.txt per la segona columna i guardar-ho a tmp.txt
# man sort > -o defineix la sortida i -k com vols ordenar, -k2 per la segona columna, -n es per dir que ordeni numericament
sort table.txt -k2 -n -o tmp.txt

# 5 Imprimir Un missatge amb el nombre de fitxers analitzats
printf "El numero %3d\n" `wc -l tmp.txt | awk '{print $1}'`

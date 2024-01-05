#!/bin/bash

# Vérifier le nombre d'arguments
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <chemin_fichier_csv> [-h | -d | -... ]"
    exit 1
fi

# Vérifier et créer le dossier temp /!\ A REVOIR ICI CAR C4EST A LA FIN QU4IL FAUT SUPP MAIS CE TCHECK EST PAS MAL AUSSI
if [ ! -d temp ]; then
    mkdir temp
#else
 #x   rm -rf temp/*
fi

# Vérifier et créer le dossier images
if [ ! -d images ]; then
    mkdir images
else
    rm -rf images/*
fi

# Vérifier si l'argument 1 est bien un fichier valide
if [ ! -f "$1" ]; then
    echo "$1 n'est pas un fichier CSV valide."
    exit 1
fi


# Mesurer le temps avant le traitement
start_time=$(date +%s)

# Traitement des cas
case "$2" in
    -h)
        echo "Aide en cours de développement ..."
        exit 0
        ;;
    -d)
        echo "On rentre dans le -d"
        conducteurs_csv="$1"  # Chemin vers le fichier CSV des conducteurs

        # Utiliser awk pour extraire les noms des conducteurs et le nombre de trajets
        awk -F ";" '{count[$6]++} END {for (c in count) print c, count[c]}' "$conducteurs_csv" |
            sort -k2,2nr |  # Trier par le nombre de trajets en ordre décroissant
            head -n 10 |    # Garder les 10 premiers conducteurs
            awk '{print $2, $1}' > temp/conducteurs_d1.txt  # Inverser l'ordre pour le graphique

        # Créer un graphique horizontal avec Gnuplot
        gnuplot -e "set terminal pngcairo; set output 'images/graphique_d1.png'; set xlabel 'Nombre de trajets'; set ylabel 'Conducteurs'; set ytics nomirror; set style fill solid; set title 'Conducteurs avec le plus de trajets'; plot 'temp/conducteurs_d1.txt' using 2:1:xticlabels(1) with boxes title 'Nombre de trajets'"
        ;;
        
    *)
        echo "option inconnu apprend a lire tete de zeb"
        exit 1
        ;;
esac


# Mesurer le temps après le traitement ======== bonne idée je note
end_time=$(date +%s)
elapsed_time=$((end_time - start_time))
echo "Durée totale des traitements : $elapsed_time secondes"

# Créer le graphique avec GnuPlot
gnuplot -e "datafile='chemin_vers_le_fichier_de_sortie'" -e "outputfile='images/graphique.png'" chemin_vers_le_script_gnuplot

echo "Traitement terminé avec succès. Le graphique a été créé dans le dossier 'images'."

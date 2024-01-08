#!/bin/bash

# Vérifier le nombre d'arguments
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <chemin_fichier_csv> [-h | -d | -... ]"
    exit 1
fi

# Vérifier et créer le dossier temp /!\ A REVOIR ICI CAR C4EST A LA FIN QU4IL FAUT SUPP MAIS CE TCHECK EST PAS MAL AUSSI
if [ ! -d temp ]; then
    mkdir temp
else
    rm -rf temp/*
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

    # -h : Aide pour comprendre la commande
    -h)
        echo "Aide en cours de développement ..."
        exit 0
        ;;

    # cas -d1 : Nombre totale de tajet par chauffeur 
    -d1)
        echo "Traitement de votre demande en cours ..."
        data_csv="$1"  # Chemin vers le fichier CSV des conducteurs

        # Extraire les noms des conducteurs et le nombre de trajets
        awk -F ";" '{count[$6]+=1} END {for (c in count) print c,";" count[c]}' "$data_csv" |
        sort -t';' -k2 -n -r | head -10 > temp/conducteurs1.txt
        tac temp/conducteurs1.txt > temp/conducteurs2.txt

        # Créer le graphique avec Gnuplot
        echo       "set terminal pngcairo enhanced font 'arial,10' size 800,600
                    set output 'images/conducteurs.png'
                    set datafile separator ';'

                    set style fill solid
                    set title font 'Arial,18'
                    set title 'Nombres totales de trajets par chauffeurs'
                    set margin 15,2,7,5

                    set ylab 'Noms des chauffeurs' font 'Arial, 15' offset -6,0
                    set xlab 'Nombres de trajets' font 'Arial, 15' offset 2,0

                    set xrange [3400:4600]
                    set yrange [-0.5:8.5]
                    set ytics rotate by 60 offset 1,.2 right


                    plot 'temp/conducteurs2.txt' u (\$2/2):0:(\$2/2):(0.35/2.):ytic(1) w boxxy ti 'Trajet'" > temp/conducteurs.gp
        
        gnuplot temp/conducteurs.gp
        ;;

    # cas -d2 : La distance parcouru par chaque chauffeur
    -d2)
        echo "Traitement de votre demande en cours ..."
        data_csv="$1"  # Chemin vers le fichier CSV des conducteurs

        awk -F ";" '{count[$6]+=$5} END {for (c in count) print c,";" count[c]}' "$data_csv" | 
        sort -t';' -k2 -n -r | head -10 > temp/distance1.txt
        tac temp/distance1.txt > temp/distance2.txt

        echo       "set terminal pngcairo enhanced font 'arial,10' size 800,600
                    set output 'images/distance.png'
                    set datafile separator ';'

                    set style fill solid
                    set title font 'Arial,18'
                    set title 'Distance parcouru par chaque chauffeur'
                    set margin 15,2,7,5

                    set ylab 'Noms des chauffeurs' font 'Arial, 15' offset -6,0
                    set xlab 'Distance parcouru' font 'Arial, 15' offset 2,0

                    set xrange [100000:160000]
                    set yrange [-0.5:8.5]
                    set ytics rotate by 60 offset 1,.2 right


                    plot 'temp/distance2.txt' u (\$2/2):0:(\$2/2):(0.35/2.):ytic(1) w boxxy ti 'Distance en KM'" > temp/distance.gp
        
        gnuplot temp/distance.gp
        ;;

    -l)
        echo "Traitement de votre demande en cours ..."
        data_csv="$1"  # Chemin vers le fichier CSV des conducteurs

        awk -F ";" '{count[$1]+=$5} END {for (c in count) print c,";" count[c]}' ../../Documents/data.csv | sort -t";" -k2 -n -r | 
        head -10 | sort -t";" -k1 -n> temp/trajet1.txt
 
        echo   "set terminal pngcairo enhanced font 'arial,10' size 800,600
                set output 'images/trajet_distance.png'
                set datafile separator ';'

                set style data histogram
                set style fill solid border -1

                set title 'Histogramme Vertical des Distances de Trajets' font 'Arial, 15'
                set xlabel 'Identifiant du Trajet' font 'Arial, 12' offset 0,-0.3
                set ylabel 'Distance (km)' font 'Arial, 12' offset 0.3,0
                set style fill solid 1
                set boxwidth 0.8

                set lmargin 10
                set rmargin 2
                set tmargin 4
                set bmargin 4

                plot 'temp/trajet1.txt' u 2:xtic(1) title 'Nbr Km' lc 'red'" > temp/trajet2.gp

        gnuplot temp/trajet2.gp
        ;;

    *)
        echo "option inconnu apprend a lire tete de zeb"
        exit 1
        ;;
esac

# Pour supprimer tous les fichiers dans le dossiers temps /!\ voir si nécessaire dans la consigne 
rm -rf temp/*

# Mesurer le temps après le traitement (pour voir si respect la contrainte de temps)
end_time=$(date +%s)
elapsed_time=$((end_time - start_time))
echo "Durée totale des traitements : $elapsed_time secondes"


echo "Traitement terminé avec succès. Le graphique a été créé dans le dossier 'images'."

#Pour les addtions dans les traitements, bash ne prend pas en compte les nombres négatifs, discuter si on choisit de faire 
#un coéfitent pour déduire l'erreur (0.4 * nbr_de_ligne). 


#p + coord_flip() pour tourner un graphique gnuplot : a tester voir ce que ca donnne .
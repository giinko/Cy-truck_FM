#!/bin/bash

# Vérifier le nombre d'arguments
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <chemin_fichier_csv> [-h | -d | -... ]"
    exit 1
fi

if [ "$#" -gt 2 ]; then
    echo "Usage: $0 <chemin_fichier_csv> [-h | -d | -... ]"
    exit 1
fi

# Vérifier si l'argument 1 est bien un fichier valide
if [ ! -f "$1" ]; then
    echo "$1 n'est pas un fichier CSV valide."
    exit 1
fi

# Vérifier le dossier temp
if [ ! -d temp ]; then
    mkdir temp
else
    rm -rf temp/*
fi

# Vérifier le dossier images
if [ ! -d images ]; then
    mkdir images
else
    rm -rf images/*
fi

# Mesurer le temps avant le traitement
start_time=$(date +%s)

# Traitement des cas
case "$2" in

    # -h : Aide pour comprendre la commande
    -h|--help)
        echo "Usage: $0 <chemin_fichier_csv> [-h | -d1 | -d2 | -l ]"
    echo
    echo "Options:"
    echo "  -h, --help    Affiche cette aide"
    echo "  -d1           Affiche le nombre total de trajets par chauffeur"
    echo "  -d2           Affiche la distance totale parcourue par chaque chauffeur"
    echo "  -l            Affiche un histogramme vertical des distances de trajets"
    echo "  -traitement 5 *Explication du traitement 5*"
    echo
    echo "Exemples:"
    echo "  $0 fichier.csv -d1"
    echo "  $0 fichier.csv -d2"
    echo "  $0 fichier.csv -l"
    exit 0
        ;;

    # cas -d1 : Nombre totale de tajet par chauffeur 
    -d1)
        echo "Traitement de votre demande en cours ..."
        data_csv="$1"  # Chemin vers le fichier CSV des conducteurs

        # Extraire les noms des conducteurs et le nombre de trajets
        awk -F ";" '{if ($2==1){count[$6]+=1}} END {for (c in count) print c,";" count[c]}' "$data_csv" |
        sort -t';' -k2,2nr | head -10 | tac > temp/conducteurs2.txt

        # Créer le graphique avec Gnuplot
        echo       "set terminal pngcairo enhanced font 'arial,10' size 800,600
                    set output 'images/conducteurs.png'
                    set datafile separator ';'
                    unset key

                    set style fill solid
                    set title font 'Arial,18'
                    set title 'Nombres totales de trajets par chauffeurs'
                    set margin 24,2,3.5,3.5

                    set ylab 'Noms des chauffeurs' font 'Arial, 15' offset -1.8,0
                    set xlab 'Nombres de trajets' font 'Arial, 15' offset 2,0

                    set yrange [-0.75:9.75]

                    plot 'temp/conducteurs2.txt' u (\$2/2):0:(\$2/2):(0.75/2.):ytic(1) w boxxy ti 'Trajet' lc 'blue'" > temp/conducteurs.gp
        
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
                    unset key

                    set style fill solid
                    set title font 'Arial,18'
                    set title 'Distance parcouru par chaque chauffeur'
                    set margin 24,2,3.5,3.5

                    set ylab 'Noms des chauffeurs' font 'Arial, 15' offset -1.8,0
                    set xlab 'Distance parcouru' font 'Arial, 15' offset 2,0
                    set yrange [-0.75:9.75]


                    plot 'temp/distance2.txt' u (\$2/2):0:(\$2/2):(0.75/2.):ytic(1) w boxxy ti 'Distance en KM' lc 'blue'" > temp/distance.gp
        
        gnuplot temp/distance.gp
        ;;

    -l)
        echo "Traitement de votre demande en cours ..."
        data_csv="$1"  # Chemin vers le fichier CSV des conducteurs

        awk -F ";" '{count[$1]+=$5} END {for (c in count) print c,";" count[c]}' "$data_csv" | sort -t";" -k2 -n -r | 
        head -10 | sort -t";" -k1 -n> temp/trajet1.txt
 
        echo   "set terminal pngcairo enhanced font 'arial,10' size 800,600
                set output 'images/trajet_distance.png'
                set datafile separator ';'
                unset key

                set style data histogram
                set style fill solid 1
                set boxwidth 1.9
                set margin 10,2,4,4

                set title 'Histogramme Vertical des Distances de Trajets' font 'Arial, 15'
                set xlabel 'Identifiant du Trajet' font 'Arial, 12' offset 0,-0.3
                set ylabel 'Distance (km)' font 'Arial, 12' offset 0.3,0

                plot 'temp/trajet1.txt' u 2:xtic(1) title 'Nbr Km' lc 'blue'" > temp/trajet2.gp

        gnuplot temp/trajet2.gp
        ;;

    -t)
        echo "Traitement de votre demande en cours ..."
        data_csv="$1"  # Chemin vers le fichier CSV des conducteurs

        cd progc/src
        ./traitement_t "$data_csv" > ../../temp/traitement_t.txt
        cd ../..

        echo   "
                set terminal pngcairo enhanced font 'arial,10' size 800,600
                set output 'images/histogram.png'
                set datafile separator ';'

                set style data histogram
                set style fill solid 1
                set boxwidth 1.4
                set margin 8,3,6,3

                set xtic rotate by -40 

                set title 'Histogramme Vertical du Nombre de Trajet par ville' font 'Arial, 15'
                set xlabel 'Nombre de trajet' font 'Arial, 12' offset 0,-0.3
                set ylabel 'Noms des villes' font 'Arial, 12' offset 1,0

                plot 'temp/traitement_t.txt' using 3:xtic(1) title 'Total Trajet' lt 1 lc 'blue', \
                '' using 2:xtic(1) title 'Départ de Trajet' lt 2 lc '#0394fc'" > temp/traitement_t.gp

        gnuplot temp/traitement_t.gp
        ;;

    -s)
        echo "Traitement de votre demande en cours ..."
        data_csv="$1"  # Chemin vers le fichier CSV des conducteurs

        cd progc/src
        ./traitement_s "$data_csv" > ../../temp/traitement_s.txt
        cd ../..

        echo "
          

            "
            #pas encore fonctionnel !! a finir !
        ;;
    *)
        echo "option inconnue, veuillez réessayez"
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/fonction_s.h"

int main(int argc, char const *argv[])
{

    if(argc != 2){
        printf("Erreur d'appel de la fonction AVL\n");
        exit(1);
    }

    const char* chemin = argv[1];
    
    //On ajoute ../../ vu que le répertoire où se situe main.sh est plus haut
    char* concat = malloc(sizeof(char)*(strlen("../../") + strlen(chemin) + 1));
    strcpy(concat, "../../");
    strcat(concat, chemin);

    //Initialisation de L'AVL
    AVL* abr = malloc(sizeof(AVL));
    abr=NULL;

    //Ouverture fichier data
    FILE *fichier;

    fichier = fopen(concat,"r");

    free(concat);

    // Lire chaque ligne du fichier .csv
    char ligne[1024];
    while (fgets(ligne, sizeof(ligne), fichier)) {

        //Pour lire chaque ligne du .csv et l'ajouter à une structure.
        char* token = strtok(ligne, ";");
        Ligne_csv* ligne_csv = malloc(sizeof(Ligne_csv));

        ligne_csv->route_id = atoi(token);

        token = strtok(NULL, ";");
        ligne_csv->etape_id = atoi(token);

        token = strtok(NULL, ";");
        ligne_csv->ville_1 = strdup(token);

        token = strtok(NULL, ";");
        ligne_csv->ville_2 = strdup(token);

        token = strtok(NULL, ";");
        ligne_csv->distance = atof(token);

        token = strtok(NULL, ";");
        ligne_csv->nom_chauffeur = strdup(token);

        Informations* infos = malloc(sizeof(Informations));
        infos->cle = ligne_csv->route_id;

        AVL* cherche = rechercher_noeud(abr,ligne_csv->route_id);

        //Si le noeud existe, alors on ajoute, sinon on créé
        if (cherche){

            cherche->info->min = min(cherche->info->min,ligne_csv->distance);
            cherche->info->max = max(cherche->info->max,ligne_csv->distance);
            cherche->info->tot += ligne_csv->distance;
            cherche->info->count +=1;

        }

        else{
            infos->id_trajet = ligne_csv->route_id;
            infos->min = ligne_csv->distance;
            infos->max = ligne_csv->distance;
            infos->tot = ligne_csv->distance;
            infos->count = 1;

            abr = inserer(abr,infos);
        }
    }


    AVL* arbre = malloc(sizeof(AVL));
    arbre=NULL;

    // Creer un AVL en fonction de (max-min)
    final_tri(abr,&arbre);

    int c = 0;

    // Prendre uniquement les 50 plus grands
    infixe_inverse(arbre,&c);

    // Libere la memoire alouée à l'arbre
    liberer_arbre(arbre);

    return 0;
}

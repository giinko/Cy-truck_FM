#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/fonction_t.h"

int main(int argc, char const *argv[])
{

    if(argc != 2){
        printf("Erreur d'appelle de la fonction AVL\n");
        exit(1);
    }

    const char* chemin = argv[1];
    
    //On ajoute ../../ vue que le répertoit ou est main.sh est plus haut
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

    char ligne[1024];
    while (fgets(ligne, sizeof(ligne), fichier)) {

        //Pour lire chaque ligne du csv et l'ajouter a une structure.
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

        // Si l'etape vaut 1 on va aussi ajouter le trajet de départ
        if(ligne_csv->etape_id == 1){

            Informations* infos_v1 = malloc(sizeof(Informations));
            unsigned long cle_v1 = char_to_int(ligne_csv->ville_1);
            infos_v1->nom = ligne_csv->ville_1;
            infos_v1->cle = cle_v1;

            AVL* cherche_v1 = rechercher_noeud(abr,cle_v1);

            if (cherche_v1){
                cherche_v1->info->nbr_trajet += 1;
                cherche_v1->info->nbr_trajet_1 += 1;
            }

            else{
                infos_v1->nbr_trajet = 1;
                infos_v1->nbr_trajet_1 = 1;
                abr = inserer(abr,infos_v1);
            }
        }

        // On creer les infos du noeud
        Informations* infos = malloc(sizeof(Informations));
        unsigned long cle = char_to_int(ligne_csv->ville_2);
        infos->nom = ligne_csv->ville_2;
        infos->cle = cle;

        // On regarde si un noeud existe avec ce nom de ville
        AVL* cherche = rechercher_noeud(abr,cle);
        
        if (cherche){
            cherche->info->nbr_trajet+=1;
        }

        else{
            infos->nbr_trajet = 1;
            infos->nbr_trajet_1 = 0;
            abr = inserer(abr,infos);
        }
    }

    AVL* arbre = malloc(sizeof(AVL));
    arbre=NULL;

    //Cree un AVL trier en fonction du nombre de trajet
    final_tri(abr,&arbre);

    int c = 0;
    int index = 0;

    //Cree un tableau avec les 10 derniers noeuds de L'AVL
    Informations* tab = malloc(10 * sizeof(Informations));
    infixe_inverse(&tab,arbre,&c,&index);

    //Trier le tableau par ordre alphabetique
    qsort(tab, 10, sizeof(Informations), comparer_noms);

    //Afficher les 10 trajets avec le plus de trajet
    for (int i = 0; i < 10; i++) {
        printf("%s;%d;%d\n", tab[i].nom,tab[i].nbr_trajet,tab[i].nbr_trajet_1);
    }

    liberer_tableau(tab,10);
    liberer_arbre(arbre);

    return 0;
}
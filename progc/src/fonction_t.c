#include "../header/fonction_t.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Transforme une chaîne de caractère en nombre unique
unsigned long char_to_int(char* chaine) {
    int compteur = 0;
    unsigned long num_tot = 0;
    char car = chaine[0];
    while (car != '\0') {
        int tt = car - 64;
        if (tt > 0) {
            num_tot = (num_tot * 10) + tt;
        }
        compteur += 1;
        car = *(chaine + compteur);
    }
    return num_tot;
}

// Fonction qui renvoie le max entre 2 valeurs
int max(int a, int b) {
    if (a > b){
        return a;
    }
    else{
        return b;
    }
}

// Fonction qui creer un nouveau noeud
AVL* creation_noeud(Informations* info) {

    AVL* nouveau = malloc(sizeof(AVL));
    nouveau->info = info;
    nouveau->valeur = info->cle;
    nouveau->gauche = NULL;
    nouveau->droite = NULL;
    nouveau->hauteur = 1;

    return nouveau;
}


// Fonction qui donne la hauteur d'un noeud 
int hauteur(AVL* noeud) {
    if (noeud == NULL)
        return 0;
    return noeud->hauteur;
}

//Fonction qui calcule l'équilibre d'un noeud
int equilibre_avl(AVL* noeud) {
    if (noeud == NULL)
        return 0;
    return hauteur(noeud->gauche) - hauteur(noeud->droite);
}

// Fonction qui effectue une rotation simple à droite
AVL* rotation_droite(AVL* noeud) {

    AVL* noeud_1 = noeud->gauche;
    AVL* noeud_2 = noeud_1->droite;

    // Effectue la rotation
    noeud_1->droite = noeud;
    noeud->gauche = noeud_2;

    // Met à jour les hauteurs
    noeud->hauteur = max(hauteur(noeud->gauche), hauteur(noeud->droite)) + 1;
    noeud_1->hauteur = max(hauteur(noeud_1->gauche), hauteur(noeud_1->droite)) + 1;

    return noeud_1;
}

//Fonction qui effectue une rotation simple à gauche
AVL* rotation_gauche(AVL* noeud) {
    AVL* noeud_1 = noeud->droite;
    AVL* noeud_2 = noeud_1->gauche;

    // Effectue la rotation
    noeud_1->gauche = noeud;
    noeud->droite = noeud_2;

    // Met à jour les hauteurs
    noeud->hauteur = max(hauteur(noeud->gauche), hauteur(noeud->droite)) + 1;
    noeud_1->hauteur = max(hauteur(noeud_1->gauche), hauteur(noeud_1->droite)) + 1;

    return noeud_1;
}


//Insérer un noeud dans l'AVL
AVL* inserer(AVL* noeud, Informations* info){

    if (noeud == NULL)
        return creation_noeud(info);

    //Insertion du noeud en fonction de sa valeur
    if (info->cle < noeud->valeur)
        noeud->gauche = inserer(noeud->gauche, info);
    else if (info->cle > noeud->valeur)
        noeud->droite = inserer(noeud->droite, info);
    else 
        return noeud;

    //Met a jour la valeur du noeud
    noeud->hauteur = 1 + max(hauteur(noeud->gauche), hauteur(noeud->droite));

    //Verifie que le noeud est équilibré
    int equilibre = equilibre_avl(noeud);

    // Cas de déséquilibre gauche-gauche
    if (equilibre > 1 && info->cle < noeud->gauche->valeur)
        return rotation_droite(noeud);

    // Cas de déséquilibre droite-droite
    if (equilibre < -1 && info->cle > noeud->droite->valeur)
        return rotation_gauche(noeud);

    // Cas de déséquilibre gauche-droite
    if (equilibre > 1 && info->cle > noeud->gauche->valeur) {
        noeud->gauche = rotation_gauche(noeud->gauche);
        return rotation_droite(noeud);
    }

    // Cas de déséquilibre droite-gauche
    if (equilibre < -1 && info->cle < noeud->droite->valeur) {
        noeud->droite = rotation_droite(noeud->droite);
        return rotation_gauche(noeud);
    }

    return noeud;
}

//Fonction de recherche dans l'AVL
AVL* rechercher_noeud(AVL* noeud, unsigned long valeur) {
    if (noeud == NULL || valeur == noeud->valeur)
        return noeud;

    if (valeur < noeud->valeur)
        return rechercher_noeud(noeud->gauche, valeur);
    else
        return rechercher_noeud(noeud->droite, valeur);
}

//Parcours infixe 
void infixe(AVL* arbre) {
    if (arbre != NULL) {
        infixe(arbre->gauche);
        printf("nom ville : %s - nbr_t : %d :- nbr_c : %d \n", arbre->info->nom, arbre->info->nbr_trajet,arbre->info->nbr_trajet_1);
        infixe(arbre->droite);
    }
}

void final_tri(AVL* initial, AVL** final) {
    if (initial != NULL) {
        initial->info->cle = initial->info->nbr_trajet;
        *final = inserer(*final, initial->info);

        final_tri(initial->gauche, final);
        final_tri(initial->droite, final);
    }
}

void infixe_inverse(Informations** tab,AVL* abr, int* compteur,int* index) {
    
    

    if (abr != NULL && *compteur < 10) {

        infixe_inverse(tab,abr->droite, compteur,index);

        if (*compteur < 10) {
            (*tab)[*index].nom = strdup(abr->info->nom);
            (*tab)[*index].cle = abr->info->cle;
            (*tab)[*index].nbr_trajet = abr->info->nbr_trajet;
            (*tab)[*index].nbr_trajet_1 = abr->info->nbr_trajet_1;
            
            (*index)++;
            (*compteur)++;
        }

        infixe_inverse(tab,abr->gauche, compteur,index);
    }
}

// Fonction de comparaison pour qsort
int comparer_noms(const void* a, const void* b) {
    return strcmp(((Informations*)a)->nom, ((Informations*)b)->nom);
}

// Parcourir l'AVL et remplir le tableau avec les noms
void remplir_tableau(AVL* racine, Informations* tableau, int* index) {
    if (racine != NULL) {
        remplir_tableau(racine->gauche, tableau, index);
        strcpy(tableau[*index].nom, racine->info->nom);
        (*index)++;
        remplir_tableau(racine->droite, tableau, index);
    }
}

// libérer l'espace alloué pour l'AVL
void liberer_arbre(AVL* noeud) {
    if (noeud != NULL) {
        liberer_arbre(noeud->gauche);
        liberer_arbre(noeud->droite);

        free(noeud->info->nom);
        free(noeud->info);

        free(noeud);
    }
}

// libérer l'espace alloué pour le tableau
void liberer_tableau(Informations* tableau, int taille) {
    for (int i = 0; i < taille; i++) {
        free(tableau[i].nom);
    }
    free(tableau);
}

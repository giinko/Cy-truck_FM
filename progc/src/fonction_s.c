#include "../header/fonction_s.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction qui reenvoie le max entre 2 valeurs
int max(int a, int b) {
    if (a >= b){
        return a;
    }
    else{
        return b;
    }
}

// Fonction qui reenvoie le min entre 2 valeurs
int min(int a,int b){
    if (a <= b){
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
AVL* rechercher_noeud(AVL* noeud, int valeur) {
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
        printf("%d;%d;%d\n", arbre->info->id_trajet,arbre->info->min,arbre->info->max);
        infixe(arbre->droite);
    }
}

void final_tri(AVL* initial, AVL** final) {
    if (initial != NULL) {
        initial->info->cle = (initial->info->max)-(initial->info->min);
        *final = inserer(*final, initial->info);

        final_tri(initial->gauche, final);
        final_tri(initial->droite, final);
    }
}

void infixe_inverse(AVL* abr, int* compteur) {
    
    

    if (abr != NULL && *compteur < 50) {

        infixe_inverse(abr->droite, compteur);

        if (*compteur < 50) {
            int moy = (abr->info->tot)/(abr->info->count);
            printf("%d;%d;%d;%d\n", abr->info->id_trajet,abr->info->min,abr->info->max,moy);
            (*compteur)++;
        }

        infixe_inverse(abr->gauche, compteur);
    }
}

void liberer_arbre(AVL* noeud) {
    if (noeud != NULL) {
        liberer_arbre(noeud->gauche);
        liberer_arbre(noeud->droite);

        free(noeud->info);

        free(noeud);
    }
}
#include "../header/avl.h"
#include <stdio.h>
#include <stdlib.h>

// Fonction qui creer un nouveau noeud
AVL* creation_noeud(int valeur) {

    AVL* nouveau = malloc(sizeof(AVL));
    nouveau->valeur = valeur;
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

// Fonction qui reenvoie le max entre 2 valeurs
int max(int a, int b) {
    if (a > b){
    	return a;
    }
    else{
    	return b;
    }
}

//Fonction qui calcule l'équilibre d'un noeud
int equilibre_avl(AVL* noeud) {
    if (noeud == NULL)
        return 0;
    return hauteur(noeud->gauche) - hauteur(noeud->droite);
}

// Fonction qui effectue une rotation simple à droite
AVL* rotation_droite(AVL* noeud){

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

// Insérer un noeud dans l'AVL
AVL* inserer(AVL* noeud, int valeur){

    if (noeud == NULL)
        return creation_noeud(valeur);

    // Insertion du noeud en fonction de sa valeur
    if (valeur < noeud->valeur)
        noeud->gauche = inserer(noeud->gauche, valeur);
    else if (valeur > noeud->valeur)
        noeud->droite = inserer(noeud->droite, valeur);
    else 
    	return noeud;

    // Met a jour la valeur du noeud
    noeud->hauteur = 1 + max(hauteur(noeud->gauche), hauteur(noeud->droite));

    // Verifie que le noeud est équilibré
    int equilibre = equilibre_avl(noeud);

    //Déséquilibre gauche-gauche
    if (equilibre > 1 && valeur < noeud->gauche->valeur)
        return rotation_droite(noeud);

    //Déséquilibre droite-droite
    if (equilibre < -1 && valeur > noeud->droite->valeur)
        return rotation_gauche(noeud);

    //Déséquilibre gauche-droite
    if (equilibre > 1 && valeur > noeud->gauche->valeur) {
        noeud->gauche = rotation_gauche(noeud->gauche);
        return rotation_droite(noeud);
    }

    //Déséquilibre droite-gauche
    if (equilibre < -1 && valeur < noeud->droite->valeur) {
        noeud->droite = rotation_droite(noeud->droite);
        return rotation_gauche(noeud);
    }

    return noeud;
}

//Parcours infixe 
void infixe(AVL* arbre){
    if (arbre != NULL) {
        infixe(arbre->gauche);
        printf("%d ", arbre->valeur);
        infixe(arbre->droite);
    }
}
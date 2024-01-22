#ifndef AVL_H
#define AVL_H

typedef struct avl {
    int valeur;
    struct avl *gauche;
    struct avl *droite;
    int hauteur;
}AVL;

AVL* creation_noeud(int valeur);
int hauteur(AVL* noeud);
int max(int a, int b);
AVL* rotation_droite(AVL* noeud);
AVL* rotation_gauche(AVL* noeud);
AVL* inserer(AVL* noeud, int valeur);
void infixe(AVL* arbre);

#endif
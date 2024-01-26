#ifndef AVL_H
#define AVL_H

typedef struct{
    int cle;
    char* nom_ville;
    int nbr_trajet;
    int nbr_cond;
}Etape;

typedef struct avl {
    Etape* info;
    int valeur;
    struct avl *gauche;
    struct avl *droite;
    int hauteur;
}AVL;

typedef struct {
    unsigned int route_id;
    unsigned short etape_id;
    char* ville_1;
    char* ville_2;
    float distance;
    char* nom_chauffeur;
}Ligne_csv;

AVL* creation_noeud(int valeur);
int hauteur(AVL* noeud);
int max(int a, int b);
AVL* rotation_droite(AVL* noeud);
AVL* rotation_gauche(AVL* noeud);
AVL* inserer(AVL* noeud, int valeur);
void infixe(AVL* arbre);

#endif
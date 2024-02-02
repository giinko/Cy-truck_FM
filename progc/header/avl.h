#ifndef AVL_H
#define AVL_H

typedef struct {
    unsigned int route_id;
    unsigned short etape_id;
    char* ville_1;
    char* ville_2;
    float distance;
    char* nom_chauffeur;
} Ligne_csv;

typedef struct{
    char* nom;
    unsigned long cle;
    int nbr_trajet_1;
    int nbr_trajet;
}Informations;

// Structure noeud AVL
typedef struct avl {
    unsigned long valeur;
    Informations* info;
    struct avl *gauche;
    struct avl *droite;
    int hauteur;
}AVL;

unsigned long char_to_int(char* chaine);
int max(int a, int b);
AVL* creation_noeud(Informations* info);
int hauteur(AVL* noeud);
int equilibre_avl(AVL* noeud);
AVL* rotation_droite(AVL* noeud);
AVL* rotation_gauche(AVL* noeud);
AVL* inserer(AVL* noeud, Informations* info);
AVL* rechercher_noeud(AVL* noeud, unsigned long valeur);
void infixe(AVL* arbre);
//================
void final_tri(AVL* initial, AVL** final);
void infixe_inverse(Informations** tab,AVL* abr, int* compteur,int* index);
int comparer_noms(const void* a, const void* b);
void remplir_tableau(AVL* racine, Informations* tableau, int* index);


void liberer_arbre(AVL* noeud);
void liberer_tableau(Informations* tableau, int taille);


#endif
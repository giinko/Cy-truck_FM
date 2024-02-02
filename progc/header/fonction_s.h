#ifndef FONCTION_S
#define FONCTION_S

typedef struct {
    unsigned int route_id;
    unsigned short etape_id;
    char* ville_1;
    char* ville_2;
    float distance;
    char* nom_chauffeur;
}Ligne_csv;

typedef struct{
    int cle;
    int id_trajet;
    int min;
    int max;
    int tot;
    int count;
}Informations;

// Structure noeud AVL
typedef struct avl {
    Informations* info;
    int valeur;
    struct avl *gauche;
    struct avl *droite;
    int hauteur;
}AVL;

int max(int a, int b);
int min(int a,int b);
AVL* creation_noeud(Informations* info);
int hauteur(AVL* noeud);
int equilibre_avl(AVL* noeud);
AVL* rotation_droite(AVL* noeud);
AVL* rotation_gauche(AVL* noeud);
AVL* inserer(AVL* noeud, Informations* info);
AVL* rechercher_noeud(AVL* noeud, int valeur);
void infixe(AVL* arbre);
void final_tri(AVL* initial, AVL** final);
void infixe_inverse(AVL* abr, int* compteur);
void liberer_arbre(AVL* noeud);

#endif
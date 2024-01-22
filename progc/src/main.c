#include "../header/main.h"
#include "../header/avl.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char const* argv[]){

	if(argc != 3){
		printf("Erreur d'appelle de la fonction AVL\n");
		exit(1);
	}

	const char* chemin = argv[1];
	int colonne_tri = atoi(argv[2]);

	printf("Voici le chemin : %s \n", chemin);
	printf("Le chiffre : %d \n\n", colonne_tri);

	AVL* abr = NULL;

    abr = inserer(abr, 10);
    abr = inserer(abr, 50);
    abr = inserer(abr, 40);
    abr = inserer(abr, 30);
    abr = inserer(abr, 20);

    printf("Arbre AVL après insertion : ");
    infixe(abr);
    printf("\n");

	return 0;
}
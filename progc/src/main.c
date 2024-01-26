#include "../header/main.h"
#include "../header/avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


unsigned long char_to_int(char* chaine){
	int compteur = 0;
	unsigned long num_tot=0;
	char car = chaine[0];
	while(car != '\0'){
		int tt = car-65;
		if(tt>0){num_tot = (num_tot+tt)*10;}
		compteur+=1;
		car=*(chaine+compteur);
	}
	return num_tot;
}


int main(int argc,char const* argv[]){

	if(argc != 3){
		printf("Erreur d'appelle de la fonction AVL\n");
		exit(1);
	}

	// Deja check dans le script shell
	const char* chemin_csv = argv[1];
	int colonne_tri = atoi(argv[2]);

	AVL* abr = NULL;

	FILE *fichier;
	fichier = fopen(chemin_csv,"r");

	if (fichier == NULL){
		printf("Impossible d'ouvrir le fichier.");
		exit(1); // Traiter les codes d'erreur a la fin.
	}

	char ligne[1024];
	while (fgets(ligne, sizeof(ligne),fichier)){
		// Insérer la valeur qui nous intéresse dans le AVL

		char* token = strtok(ligne, ";");
		Ligne_csv* ligne_csv = malloc(sizeof(Ligne_csv)); 

        ligne_csv->route_id = atoi(token);

        token = strtok(NULL, ";");
        ligne_csv->etape_id = atoi(token);

        token = strtok(NULL, ";");
        ligne_csv->ville_1 = malloc(strlen(token)+1);
        strcpy(ligne_csv->ville_1,token);

        token = strtok(NULL, ";");
        ligne_csv->ville_2 = malloc(strlen(token)+1);
        strcpy(ligne_csv->ville_2,token);

        token = strtok(NULL, ";");
        ligne_csv->distance = atof(token);

        token = strtok(NULL, ";");
        ligne_csv->nom_chauffeur = malloc(strlen(token)+1);
        strcpy(ligne_csv->nom_chauffeur,token);

		inserer()
	}
	

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
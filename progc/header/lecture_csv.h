#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	unsigned int route_id;
	unsigned short etape_id;
	char* ville_1;
	char* ville_2;
	float distance;
	char* nom_chauffeur;
}Ligne_csv;

typedef struct fichier_csv{
	Ligne_csv* ligne_csv;
	struct fichier_csv* suiv;
}Fichier_csv;

typedef struct{
	Fichier_csv* tete;
	Fichier_csv* queue;
	int taille;
}File_fichier_csv;


File_fichier_csv* lecture_csv(char* chemin_csv);
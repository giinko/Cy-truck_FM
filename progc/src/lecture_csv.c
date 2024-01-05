#include "../header/lecture_csv.h"


File_fichier_csv* lecture_csv(char* chemin_csv){

	FILE *fichier;
	fichier = fopen(chemin_csv,"r");

	if (fichier == NULL){
		printf("Impossible d'ouvrir le fichier.");
		exit(0); // Traiter les codes d'erreur a la fin.
	}

	//Création de la file 
	File_fichier_csv* file_fichier_csv = malloc(sizeof(File_fichier_csv));
	file_fichier_csv->tete = NULL;
	file_fichier_csv->queue = NULL;
	file_fichier_csv->taille = 0;

	char ligne[1024];

	while (fgets(ligne, sizeof(ligne),fichier)){

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

        Fichier_csv* new_fichier_csv = malloc(sizeof(Fichier_csv));
        new_fichier_csv->suiv = NULL;
        new_fichier_csv->ligne_csv = ligne_csv;

        if (file_fichier_csv->taille==0){
        	file_fichier_csv->tete = new_fichier_csv;
        	file_fichier_csv->queue = new_fichier_csv;
        	file_fichier_csv->taille+=1;
        }
        else{
        	file_fichier_csv->queue->suiv = new_fichier_csv;
        	file_fichier_csv->queue = new_fichier_csv;
        	file_fichier_csv->taille+=1;
        }
	}

	fclose(fichier);

	return file_fichier_csv;
}

int main(){

	char* chemin_csv = "../../../../Documents/data.csv";
	File_fichier_csv* file_csv = lecture_csv(chemin_csv);

	printf("Traitement terminé !\n");

	Fichier_csv* chainon = file_csv->tete;
	while (chainon != NULL){
		//printf("Nom chauffeur : %s \n",chainon->ligne_csv->nom_chauffeur);
		chainon = chainon->suiv;
	}

	printf("Tout s'est bien passé !\n");
	return 0;
}
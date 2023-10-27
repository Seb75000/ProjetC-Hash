#include <stdio.h>
#include <string.h>
#include "crypto.h"
#include <time.h>

#define MAX_LINE_LENGTH 1024

// Fonction support pour le -G du programme principal : 
// lit le dictionnaire et génère le fichier de hashtable en conséquence.

int generateHashtable(int argc, char* argv[]){
    char *strFile1 = argv[2];
    char *strFile2 = argv[3];
    char *algo = argv[5];

    // définition de l'algorithme par défaut : sha256
    if (algo == NULL) {
        algo = "sha256";
    }

    int nbLignes = 0;
    // pour le calcul du temps d'exécution
    clock_t debex, finex;
    double temps_ecoule;

    debex = clock();
    printf("Génération du fichier de hash...\n");

    if ((argc >= 3) && (strcmp(argv[1], "-G") == 0)){
        FILE *fileIn = fopen(strFile1, "r");
        if (fileIn == NULL) {
            fprintf(stderr, "Erreur : impossible d'ouvrir le fichier \n");
            return 1;
        }

        // L'argument 2 est le chemin du fichier à écrire
        FILE *fileOut = fopen(strFile2, "a");

        char ligne[MAX_LINE_LENGTH];
        // while (fgets(ligne, MAX_LINE_LENGTH, fileIn) && nbLignes < 1000000) { // pour limiter le nombre de lignes traitées, sinon on meurt de vieillesse avec valgrind :(
        while (fgets(ligne, MAX_LINE_LENGTH, fileIn)) {
            // On s'assure que la ligne se termine par un caractère nul,
            // sinon le hash va porter sur des caractères en trop.
            int len = strlen(ligne);
            if (len > 0 && ligne[len - 1] == '\n') {
                // printf("Ligne : %s longueur : %d\n", ligne, len);
                ligne[len - 1] = '\0';
            }

            // char* resultat = hashage(ligne, "sha256");
            char* resultat = hashage(ligne, algo);
            // on exclut le cas de la ligne vide
            if (resultat)  {
                // printf("Ligne : %s - SHA256 : %s\n", ligne, resultat);
                fprintf(fileOut, "%s\t%s\n", resultat, ligne);
                free(resultat);
                nbLignes++;
            }
            // de quoi faire patienter pendantl la génération
            if (nbLignes % 100000 == 0) {
                printf("%d lignes traitées...\n", nbLignes);
            }
        }
        fclose(fileIn);
        fclose(fileOut);

        finex = clock();
        temps_ecoule = (double)(finex - debex) / CLOCKS_PER_SEC;
        printf("...terminée. \n\n");
        printf("Création du fichier de hash : %d lignes en %f secondes.\n\n", nbLignes, temps_ecoule);

    }
    return 0;
}

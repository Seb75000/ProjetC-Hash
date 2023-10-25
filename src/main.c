#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include "generateHashtable.h"
#include "findInHashtable.h"
#include "crypto.h"

#define MAX_LINE_LENGTH 1024


//TODO : gérer les args
// appel exemple : hash.exe -G <fichier_dictionnaire> <fichier_hashtable> -a <algorithme>
// ou hash.exe -L <fichier_hastable> <fichier_sortie> -a <algorithme>
// -G : génération de dictionnaire
// -a : algorithme de hachage (sha1, sha256, md5)
// -L : lecture de hash depuis un fichier hastable
// -H : affichage de l'aide

int main(int argc, char* argv[] ) {

    // Cas 1 : génération de hashtable
    if ((argc >= 3) && (strcmp(argv[1], "-G") == 0)){
        if ((argv[5] == NULL) || (strcmp(argv[5], "md5") == 0) || (strcmp(argv[5], "sha1") == 0) || (strcmp(argv[5], "sha256") == 0) || (strcmp(argv[5], "sha512") == 0)) {
            generateHashtable(argc, argv);
        }
        else
        {
            printf("Erreur : algorithme de hachage non supporté. Veuillez consulter l'aide.\n");
            return 1;
        }

    }
    // Cas 2 : chercher dans la hashtable
    else if ((argc >= 3) && (strcmp(argv[1], "-L") == 0))
    {
        findInHashtable(argc, argv);
    }
    //TODO faire un truc ici
    // Cas autre : erreur de paramètres d'entrée : afficher l'aide
    else
    {
        printf("Aide à l'utilisation de %s :\n\n", argv[0]);
        printf("Génération de la hashtable à partir du dictionnaire :\n");
        printf("\thash.exe -G <fichier_dictionnaire> <fichier_hashtable> (-a ALGO)\n");
        printf("\t <fichier_dictionnaire> : fichier contenant les mots à hasher\n");
        printf("\t <fichier_hashtable> : fichier de sortie contenant les hashs et les mots en clair.");
        printf("\t\tSi le fichier existe déjà, les hashs seront ajoutés à la suite, même si d'algorithme différent.\n");
        printf("\t -a ALGO : algorithme de hachage à utiliser (facultatif. Par défaut, sha256 sera utilisé)\n");
        printf("\tAlgorithmes de hachage supportés : celles de la librairie OpenSSL\n");
        printf("\t\tExemples : sha1, sha256, md5...\n\n");
        printf("Recherche de hashs dans la hashtable :\n");
        printf("\tcat MesHash | hash.exe -L <fichier_hastable>\n");
        printf("\t <fichier_hastable> : fichier contenant les hashs et les mots en clair, avec \"\\n\" comme séparateur de ligne.\n\n");

        printf("Affichage de l'aide :\n");
        printf("\thash.exe -H\n");
        return 1;
    }
    return 0;
}

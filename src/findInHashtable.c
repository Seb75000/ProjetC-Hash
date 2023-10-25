#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Limite arbitraire à la taille d'une ligne de fichier texte d'origine
#define MAX_LINE_LENGTH 1024

typedef struct node {
    char *clair;
    char *hash;
    struct node* left;
    struct node* right;
} node_t;

// Fonction d'initialisation d'un arbre vide
node_t* initTree() {
    return NULL;
}

// Fonction de création d'un nouveau noeud
node_t* createNode(char *clair, char *hash) {
    node_t* nouveauNoeud = malloc(sizeof(node_t));
    if (nouveauNoeud) {
        nouveauNoeud->clair = (clair != NULL) ? strdup(clair) : NULL; // petit hack pour accepter un clair "null"
        nouveauNoeud->hash = strdup(hash);
        nouveauNoeud->left = nouveauNoeud->right = NULL;
    }
    return nouveauNoeud;
}

// Fonction d'insertion dans l'arbre
node_t* insertNode(node_t* root, char *hash, char *clair) {    
    // Si nouvelle insertion, on crée un nouveau noeud
    if (root == NULL) {        
        return createNode(clair, hash);
    }

    // Comparaison pour décider si le nœud doit être inséré dans le sous-arbre gauche ou droit
    int cmp = strcmp(hash, root->hash);

    if (cmp < 0) {
        root->left = insertNode(root->left, hash, clair);        
    } else if (cmp > 0) {
        root->right = insertNode(root->right, hash, clair);
    }

    return root;
}

// Fonction de recherche d'un noeud avec une clé "hash"
node_t* searchNode(node_t* root, char *hash) {
    if (root == NULL || strcmp(hash, root->hash) == 0) {
        return root;
    }

    if (strcmp(hash, root->hash) < 0) {
        return searchNode(root->left, hash);
    }

    return searchNode(root->right, hash);
}

void displayTree(node_t* root, int deep) {
    if (root != NULL) {
        for (int i = 0; i < deep; i++) {
            printf("|");
        }
        printf("%s - %s\n", root->hash, root->clair);
        displayTree(root->left, deep + 1);
        displayTree(root->right, deep + 1);
    } 
}

// Fonction de destruction de l'arbre
void destroyTree(node_t* root) {
    if (root == NULL) {
        return;
    }

    destroyTree(root->left);
    destroyTree(root->right);

    free(root->clair);
    free(root->hash);
    free(root);
}

int findInHashtable (int argc, char* argv[]){
    char *strFile1 = argv[2];    
    int nbHash = 0;

    // d'abord on récupère le stdin, qu'on stocke dans une liste à traiter ensuite
    int max_lines = 1000; // Nombre maximum de lignes à lire
    char buffer[100];   // Chaque ligne fait max 64 caractères
    char* lines[max_lines]; // Tableau de pointeurs vers des lignes

    int line_count = 0;
    while (line_count < max_lines && fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Allouer de la mémoire pour la ligne et copier son contenu
        size_t length = strlen(buffer);
        if (length > 0 && buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0'; // Remplacer '\n' par '\0'
        }

        lines[line_count] = malloc(strlen(buffer) + 1);
        strcpy(lines[line_count], buffer);
        line_count++;
    }

    // pour le calcul du temps d'exécution
    clock_t debex, finex;
    double temps_ecoule;


    debex = clock();
    node_t* root = initTree();
    FILE *fileIn = fopen(strFile1, "r");
    if (fileIn == NULL) {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier \n");
        return 1;
    }

    char ligne[MAX_LINE_LENGTH];

    printf("Lecture du fichier de hash et création de l'arbre de recherche...\n");


    // On lit et on scinde la ligne entre ce qui précède la 1ere tabulation, et la suite
    while (fgets(ligne, MAX_LINE_LENGTH, fileIn)) {
        // On s'assure que la ligne se termine par un caractère nul,
        int len = strlen(ligne);
        if (len > 0 && ligne[len - 1] == '\n') {
            ligne[len - 1] = '\0';
        }

        // Découper la ligne en champs en utilisant la tabulation comme délimiteur
        char *hash = strtok(ligne, "\t");
        char *clair = strtok(NULL, "\0");  // Le deuxième champ inclut tout jusqu'au \0

        root = insertNode(root, hash, clair);        
        nbHash++;        
    }
    // fin du parcours du fichier : on ferme !
    fclose(fileIn);
    finex = clock();
    temps_ecoule = (double)(finex - debex) / CLOCKS_PER_SEC;    
    printf("Création de l'arbre : %d entrées en %f secondes.\n", nbHash, temps_ecoule);
    printf("----------------------------------------------------------------- \n\n");
    debex = clock();


    // maintenant on peut commencer la recherche depuis la liste de hash passée par stdin
    for (int i = 0; i < line_count; i++) {
        printf("Recherche du hash : %s\n", lines[i]);
        node_t* recherche = searchNode(root, lines[i]);        
        if (recherche != NULL) {
            printf("Clair : %s, Hash : %s\n\n", recherche->clair, recherche->hash);
        } else {
            printf("Antécédant du hash non trouvé.\n\n");
        }        
        free(lines[i]); // Libérer la mémoire allouée pour chaque ligne
    }

    // // Recherche du noeud à partir d'un hash   
    // // ici pour "iloveyou08"
    // node_t* recherche = searchNode(root, "267283dd9ebdcc14c5343623ea6b5fb0a3312f4066c65d196fb23019052d1511");
    // if (recherche != NULL) {
    //     printf("Clair : %s, Hash : %s\n", recherche->clair, recherche->hash);
    // } else {
    //     printf("Noeud non trouvé.\n");
    // }

    finex = clock();
    temps_ecoule = (double)(finex - debex) / CLOCKS_PER_SEC;
    printf("Recherche dans l'arbre :  %f secondes.\n\n", temps_ecoule);

    // Freemem à gogo !!!
    destroyTree(root);

    return 0;
}
    
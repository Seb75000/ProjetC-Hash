#ifndef FINDINASHTABLE_H
#define FINDINASHTABLE_H

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

node_t* initTree();

node_t* createNode(char *clair, char *hash);

node_t* insertNode(node_t* root, char *hash, char *clair);

node_t* searchNode(node_t* root, char *hash);

void displayTree(node_t* root, int deep);

void destroyTree(node_t* root);

int findInHashtable (int argc, char* argv[]);

#endif
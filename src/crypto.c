#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

// fonction qui renvoie le hash d'une string passée en paramètre, pour l'algo demandé en paramètre
char* hashage(const char* strInput, const char* algo) {
    // Initialisations du hash, copié-volé de https://www.openssl.org/docs/man1.0.2/man3/EVP_MD_CTX_create.html
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;
    OpenSSL_add_all_digests();
    char* hash = NULL;
    md = EVP_get_digestbyname(algo);

    if (md == NULL) {
        fprintf(stderr, "Algorithme de hachage non valide : %s\n", algo);
        return NULL;
    }

    mdctx = EVP_MD_CTX_create();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, strInput, strlen(strInput));
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);

    hash = (char*)malloc(md_len * 2 + 1);
    if (hash == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour le hachage.\n");
        return NULL;
    }

    for (int i = 0; i < md_len; i++) {
        sprintf(&hash[i * 2], "%02x", md_value[i]);
    }

    EVP_MD_CTX_destroy(mdctx);
    EVP_cleanup();
    return hash;
}
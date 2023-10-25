#ifndef CRYPTO_H
#define CRYPTO_H

#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>


char* hashage(const char* strInput, const char* algo);

#endif
#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int boolean;
#define TRUE 1
#define FALSE 0
#define MAX 100
#define ERRO_NULL -32

char* ler_linha();
void exibir_linha(char* linha);
boolean apagar_linha(char** linha);
void exibir_booleano();

#endif // UTIL_H
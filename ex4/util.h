#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int boolean;
#define TRUE 1
#define FALSE 0
#define MAX 100
#define ERRO_MEM -300    // Ocorre quando uma alocacao de momoria falha;
#define ERRO_SIM -301    // Ocorre quando uma funcao recebe como parametro um simbolo invalido (Simbolo != {1,2,...,9,10,V,D,R});
#define ERRO_NUM -302    // Ocorre quando uma funcao recebe como parametro um numero invalido;
#define ERRO_NULL -303   // Ocorre quando uma funcao recebe como parametro um ponteiro que aponta para NULL;

char* ler_palavra();
void exibir_palavra(char* palavra);
boolean apagar_palavra(char** palavra);
void exibir_booleano();

#endif // UTIL_H
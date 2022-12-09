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
#define ERRO_SIM -301    // Ocorre quando uma funcao recebe como parametro um simbolo invalido
#define ERRO_NUM -302    // Ocorre quando uma funcao recebe como parametro um numero invalido;
#define ERRO_NULL -303   // Ocorre quando uma funcao recebe como parametro um ponteiro que aponta para NULL;

int ler_inteiro();
char* ler_dado();
void exibir_dado(char* dado);
boolean apagar_dado(char** dado);
void exibir_booleano();

#endif // UTIL_H
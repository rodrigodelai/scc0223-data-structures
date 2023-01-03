#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int boolean;
#define TRUE 1
#define FALSE 0
#define ERRO_MEM -300    // Ocorre quando uma alocacao de momoria falha;
#define ERRO_SIM -301    // Ocorre quando uma funcao recebe como parametro um simbolo invalido
#define ERRO_NUM -302    // Ocorre quando uma funcao recebe como parametro um numero invalido;
#define ERRO_NULL -303   // Ocorre quando uma funcao recebe como parametro um ponteiro que aponta para NULL;

int ler_opcao();
int ler_inteiro(FILE* arquivo);
char* ler_texto(FILE* arquivo);
void exibir_texto(char* texto);
boolean apagar_texto(char** texto);
void exibir_booleano(boolean bool);
int max(int num1, int num2);

#endif // UTIL_H
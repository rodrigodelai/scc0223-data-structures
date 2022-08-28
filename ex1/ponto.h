#ifndef PONTO_H
#define PONTO_H

#include <stdio.h>
#include <stdlib.h>
#define ERRO_NULL -32000
#define TRUE 1
#define FALSE 0
typedef int boolean;

typedef struct ponto_st PONTO;

PONTO* ponto_criar();
boolean ponto_posicionar(PONTO* ponto, float abscissa, float ordenada);
float ponto_abscissa(PONTO* ponto);
float ponto_ordenada(PONTO* ponto);
void ponto_exibir(PONTO* ponto);
boolean ponto_destruir(PONTO* ponto);    

#endif //PONTO_H
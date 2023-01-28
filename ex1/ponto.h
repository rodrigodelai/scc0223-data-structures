#ifndef PONTO_H
#define PONTO_H

#include "util.h"

typedef struct ponto_st PONTO;

PONTO* ponto_criar();
boolean ponto_posicionar(PONTO* ponto, float abscissa, float ordenada);
float ponto_obter_abscissa(PONTO* ponto);
float ponto_obter_ordenada(PONTO* ponto);
void ponto_exibir(PONTO* ponto);
boolean ponto_destruir(PONTO** ponto);    

#endif //PONTO_H
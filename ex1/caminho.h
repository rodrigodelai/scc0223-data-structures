#ifndef CAMINHO_H
#define CAMINHO_H

#include "ponto.h"

typedef struct caminho_st CAMINHO;

CAMINHO* caminho_criar(int pontos);
boolean caminho_adicionar(PONTO* novo_ponto, CAMINHO* caminho);
PONTO* caminho_fim(CAMINHO* caminho);
int caminho_qnt_pontos(CAMINHO* caminho);
boolean caminho_remover(CAMINHO* caminho);
void caminho_exibir(CAMINHO* caminho);
float caminho_distancia(CAMINHO* caminho);
boolean caminho_destruir(CAMINHO** caminho);

#endif //CAMINHO_H
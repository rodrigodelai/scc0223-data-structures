#ifndef CAMINHO_H
#define CAMINHO_H

#include "ponto.h"

typedef struct caminho_st CAMINHO;

CAMINHO* caminho_criar(int capacidade);
boolean caminho_adicionar(CAMINHO* caminho, PONTO* novo_ponto);
int caminho_obter_capacidade(CAMINHO* caminho);
int caminho_obter_qnt_pontos(CAMINHO* caminho);
float caminho_calcula_distancia(CAMINHO* caminho);
void caminho_exibir(CAMINHO* caminho);
PONTO* caminho_remover(CAMINHO* caminho);
boolean caminho_destruir(CAMINHO** caminho);

void ler_e_armazenar_pontos(CAMINHO* caminho);
void exibir_distancia_percorrida(CAMINHO* caminho);

#endif //CAMINHO_H
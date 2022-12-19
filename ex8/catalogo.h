#ifndef CATALOGO_H
#define CATALOGO_H

#include "jogo.h"

typedef struct catalogo_st CATALOGO;

CATALOGO* catalogo_criar();
boolean catalogo_adicionar(CATALOGO* catalogo, JOGO* jogo);
boolean catalogo_buscar(CATALOGO* catalogo, JOGO* jogo);
boolean catalogo_remover(CATALOGO* catalogo, int ano);
JOGO* catalogo_obter_raiz(CATALOGO* catalogo);
int catalogo_obter_profundidade(CATALOGO* catalogo);
int catalogo_obter_qnt_jogos(CATALOGO* catalogo);
void catalogo_exibir(CATALOGO* catalogo, int opcao);
void catalogo_exibir_nomes(CATALOGO* catalogo, int opcao);
boolean catalogo_destruir(CATALOGO** catalogo);

void ler_novo_catalogo(CATALOGO* catalogo);
void realizar_remocoes(CATALOGO* catalogo);

#endif // CATALOGO_H
#ifndef CATALOGO_H
#define CATALOGO_H

#include "jogo.h"

typedef struct catalogo_st CATALOGO;

CATALOGO* catalogo_criar();
boolean catalogo_adicionar(CATALOGO* catalogo, JOGO* jogo);
boolean catalogo_remover(CATALOGO* catalogo);
JOGO* catalogo_topo(CATALOGO* catalogo);
int catalogo_qnt_jogos(CATALOGO* catalogo);
void catalogo_exibir(CATALOGO* catalogo);
void catalogo_exibir_por_empresa(CATALOGO* catalogo, char* empresa);
void catalogo_exibir_por_ano(CATALOGO* catalogo, char* ano);
boolean opcao_filtrar_por_empresa(char* opcao);
boolean opcao_filtrar_por_ano(char* opcao);
boolean catalogo_destruir(CATALOGO** catalogo);

#endif // CATALOGO_H
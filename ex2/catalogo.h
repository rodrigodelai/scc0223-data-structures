#ifndef CATALOGO_H
#define CATALOGO_H

#include "jogo.h"

typedef struct catalogo_st CATALOGO;

CATALOGO* catalogo_criar();
boolean catalogo_adicionar(CATALOGO* catalogo, JOGO* jogo);
boolean catalogo_remover(CATALOGO* catalogo);
void catalogo_exibir(CATALOGO* catalogo);
JOGO* catalogo_topo(CATALOGO* catalogo);
JOGO* catalogo_buscar_nome(CATALOGO* catalogo, char* nome);
JOGO* catalogo_buscar_empresa(CATALOGO* catalogo, char* nome);
JOGO* catalogo_buscar_ano(CATALOGO* catalogo, char* nome);
boolean catalogo_destruir(CATALOGO** catalogo);

#endif // CATALOGO_H
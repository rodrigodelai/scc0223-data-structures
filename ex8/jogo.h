#ifndef JOGO_H
#define JOGO_H

#include "util.h"

typedef struct jogo_st JOGO;

JOGO* jogo_criar();
boolean jogo_definir_nome(JOGO* jogo, char* novo_nome);
boolean jogo_definir_empresa(JOGO* jogo, char* nova_empresa);
boolean jogo_definir_ano(JOGO* jogo, int novo_ano);
char* jogo_obter_nome(JOGO* jogo);
char* jogo_obter_empresa(JOGO* jogo);
int jogo_obter_ano(JOGO* jogo);
void jogo_exibir(JOGO* jogo);
boolean jogo_destruir(JOGO** jogo);

#endif // JOGO_H

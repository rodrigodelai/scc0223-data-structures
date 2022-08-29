#ifndef JOGO_H
#define JOGO_H

#include "util.h"

typedef struct jogo_st JOGO;

JOGO* jogo_criar();
boolean jogo_alterar_nome(JOGO* jogo, char* nome);
boolean jogo_alterar_empresa(JOGO* jogo, char* empresa);
boolean jogo_alterar_ano(JOGO* jogo, char* ano);
char* jogo_acessar_nome(JOGO* jogo);
char* jogo_acessar_empresa(JOGO* jogo);
char* jogo_acessar_ano(JOGO* jogo);
void jogo_exibir(JOGO* jogo);
boolean jogo_destruir(JOGO* jogo);

#endif // JOGO_H

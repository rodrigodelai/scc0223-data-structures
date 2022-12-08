#ifndef BANCO_H
#define BANCO_H

#include "conta.h"

typedef struct banco_st BANCO;

BANCO* banco_criar();
boolean banco_destruir(BANCO** banco);

void ler_e_armazenar_contas(BANCO* banco);
void realizar_operacao(BANCO* banco);

#endif // BANCO_H
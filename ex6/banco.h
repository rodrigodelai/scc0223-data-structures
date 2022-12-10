#ifndef BANCO_H
#define BANCO_H

#include "conta.h"

typedef struct banco_st BANCO;

BANCO* banco_criar();
boolean banco_adicionar_conta (BANCO* banco, CONTA* conta);
CONTA* banco_buscar_conta(BANCO* banco, long cpf);
CONTA* banco_remover_conta(BANCO* banco, long cpf);
CONTA* banco_obter_raiz(BANCO* banco);
int banco_obter_profundidade(BANCO* banco);
void banco_exibir_cpfs(BANCO* banco);
boolean banco_destruir(BANCO** banco);

boolean opcao_insercao(char* opcao);
boolean opcao_busca(char* opcao);
boolean opcao_remocao(char* opcao);

void ler_e_armazenar_contas(BANCO* banco);
void realizar_operacao(BANCO* banco);

#endif // BANCO_H
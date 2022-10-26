#ifndef OPERACAO_H
#define OPERACAO_H

#include "big_number.h"

typedef struct operacao_st OPERACAO;

boolean opcao_soma(char* operacao);
boolean opcao_igual(char* operacao);
boolean opcao_maior(char* operacao);
boolean opcao_menor(char* operacao);
BIG_NUMBER operacao_somar(BIG_NUMBER operando_1, BIG_NUMBER operando_2);
boolean operacao_igual(BIG_NUMBER operando_1, BIG_NUMBER operando_2);
boolean operacao_maior(BIG_NUMBER operando_1, BIG_NUMBER operando_2);
boolean operacao_menor(BIG_NUMBER operando_1, BIG_NUMBER operando_2);

int ler_qnt_de_operacoes();
void operar_dois_big_numbers();

#endif // OPERACAO_H

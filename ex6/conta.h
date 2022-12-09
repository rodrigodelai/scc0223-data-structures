#ifndef CONTA_H
#define CONTA_H

#include "util.h"

typedef struct conta_st CONTA;

CONTA* conta_criar();
boolean conta_definir_cpf(CONTA* conta, long int cpf);
boolean conta_definir_nome(CONTA* conta, char* nome);
boolean conta_definir_idade(CONTA* conta, int idade);
boolean conta_definir_saldo(CONTA* conta, long int saldo);
long int conta_extrair_cpf(char* cpf);
long int conta_extrair_saldo(char* saldo);
long int conta_obter_cpf(CONTA* conta);
char* conta_obter_nome(CONTA* conta);
int conta_obter_idade(CONTA* conta);
long int conta_obter_saldo(CONTA* conta);
char* conta_converter_cpf(long cpf);
char* conta_converter_saldo(long saldo);
void conta_exibir(CONTA* conta);
boolean conta_destruir(CONTA** carta);

#endif // CONTA_H
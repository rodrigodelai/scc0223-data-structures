#ifndef BIG_NUMBER_H
#define BIG_NUMBER_H

#include "util.h"

typedef struct big_number_st BIG_NUMBER;

BIG_NUMBER* big_number_criar_numero();
boolean big_number_definir_numero(BIG_NUMBER* big_number, char* numero);
char* big_number_obter_numero(BIG_NUMBER* big_number);
void big_number_exibir_numero(BIG_NUMBER* big_number);
boolean big_number_destruir_numero(BIG_NUMBER** big_number);

boolean big_number_adicionar_parte(BIG_NUMBER* big_number, int parte_do_numero);
int big_number_obter_parte(BIG_NUMBER* big_number, int posicao);
void big_number_exibir_parte(BIG_NUMBER* big_number, int posicao);
int big_number_remover_parte(BIG_NUMBER* big_number, int posicao);

int big_number_obter_inicio(BIG_NUMBER* big_number);
int big_number_obter_fim(BIG_NUMBER* big_number);
int big_number_obter_qnt_partes(BIG_NUMBER* big_number);
int big_number_obter_sinal(BIG_NUMBER* big_number);

#endif // BIG_NUMBER_H
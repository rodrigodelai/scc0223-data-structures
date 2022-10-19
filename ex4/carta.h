#ifndef CARTA_H
#define CARTA_H

#include "util.h"

typedef struct carta_st CARTA;

CARTA* carta_criar();
boolean carta_definir_naipe(char* naipe);
boolean carta_definir_simbolo(char* simbolo);
boolean carta_definir_valor(int valor);
int carta_extrair_valor(char* simbolo);
char* carta_obter_naipe(CARTA* carta);
char* carta_obter_simbolo(CARTA* carta);
int carta_obter_valor(CARTA* carta);
void carta_exibir(CARTA* carta);
boolean carta_destruir(CARTA* carta);

#endif // CARTA_H
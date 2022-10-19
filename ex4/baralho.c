#include "baralho.h"

typedef struct no_st NO;

struct no_st{
    CARTA* carta;
    NO* anterior;
};

struct baralho_st{
    NO* topo;
    int qnt_cartas;
};

BARALHO* baralho_criar();
boolean baralho_empilhar(BARALHO* baralho, CARTA* carta);
CARTA* baralho_desempilhar(BARALHO* baralho);
CARTA* baralho_obter_topo(BARALHO* baralho);
int baralho_obter_qnt_cartas(BARALHO* baralho);
boolean baralho_esta_vazio(BARALHO* baralho);
void baralho_exibir(BARALHO* baralho);
boolean baralho_destruir(BARALHO** baralho);

void ler_novo_baralho(BARALHO* baralho);
void jogar_blackjack(BARALHO* baralho); 
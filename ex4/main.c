#include "baralho.h"

int main(){

    BARALHO* baralho = baralho_criar();
    ler_novo_baralho(baralho);
    jogar_blackjack(baralho);
    baralho_destruir(&baralho);

    return 0;
}
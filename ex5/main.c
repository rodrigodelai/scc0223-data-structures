#include "operacao.h"

int main(){

    int operacoes = ler_qnt_de_operacoes();
    while (operacoes--) operar_dois_big_numbers();

    return 0;
}
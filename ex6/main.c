/*  Disciplina: SCC0223 - Estruturas de Dados I
    Exercício: Conta Bancária (6)
    Aluno: Rodrigo Delai
    Nº USP: 11849074
*/

#include "banco.h"

int main(){

    BANCO* banco = banco_criar();
    ler_e_armazenar_contas(banco);
    realizar_operacao(banco);
    banco_destruir(&banco);

    return 0;
}
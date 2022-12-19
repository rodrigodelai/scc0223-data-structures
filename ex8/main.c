/*  Disciplina: SCC0223 - Estruturas de Dados I
    Exercício: Catálogo de Jogos II (8)
    Aluno: Rodrigo Delai
    Nº USP: 11849074
*/

#include "catalogo.h"


int main(){

    CATALOGO* catalogo = catalogo_criar();
    ler_novo_catalogo(catalogo);

    int opcao = ler_opcao();
    realizar_remocoes(catalogo);
    catalogo_exibir_nomes(catalogo, opcao);
    
    catalogo_destruir(&catalogo);

    return 0;
}
/*  Disciplina: SCC0223 - Estruturas de Dados I
    Exercício: Pontos Cartesianos (1)
    Aluno: Rodrigo Delai
    Nº USP: ######
*/

#include <stdio.h>
#include "caminho.h"

int main(){
    
    CAMINHO* caminho = caminho_criar(ler_inteiro_nao_negativo());
    ler_e_armazenar_pontos(caminho);
    exibir_distancia_percorrida(caminho);
    caminho_destruir(&caminho);

    return 0;
}
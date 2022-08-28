/*  Disciplina: SCC0223 - Estruturas de Dados I
    Exercício: Pontos Cartesianos (1)
    Aluno: Rodrigo Delai
    Nº USP: 11849074
*/

#include <stdio.h>
#include "caminho.h"

int main(){
    int qnt_pontos = 0;

    scanf("%d", &qnt_pontos);

    CAMINHO* caminho = caminho_criar(qnt_pontos);

	// Leitura e armazenamento dos dados
    for(int i=0; i<qnt_pontos; i++){
        float abscissa = 0, ordenada = 0;
        scanf("%f %f", &abscissa, &ordenada);
        PONTO* novo_ponto = ponto_criar();
        ponto_posicionar(novo_ponto, abscissa, ordenada);
        caminho_adicionar(novo_ponto, caminho);
    }

	// Cálculo e exibição dos resultados
    printf("%.2f\n", caminho_distancia(caminho));

    caminho_destruir(&caminho);

    return 0;
}
#include "util.h"

int ler_inteiro_nao_negativo(){
    int numero = -1;
    scanf("%d", &numero);

    while (numero < 0){
        printf("Por gentileza, insira um valor não negativo: ");
        scanf("%d", &numero);
    }

    return numero;
}
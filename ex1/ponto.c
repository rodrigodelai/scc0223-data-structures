#include "ponto.h"

struct ponto_st{
    float abscissa;
    float ordenada;
};

PONTO* ponto_criar(){
    PONTO* novo_ponto = (PONTO*) malloc(sizeof(PONTO));
    return novo_ponto;
}

boolean ponto_posicionar(PONTO* ponto, float abscissa, float ordenada){
    if(ponto == NULL){
        printf("Erro ao posicionar: %d\n", ERRO_NULL);
        return FALSE;
    }
    
    ponto->abscissa = abscissa;
    ponto->ordenada = ordenada;

    return TRUE;
}

float ponto_abscissa(PONTO* ponto){
    return ponto->abscissa;
}

float ponto_ordenada(PONTO* ponto){
    return ponto->ordenada;
}


void ponto_exibir(PONTO* ponto){
    if(ponto == NULL)
        printf("Erro ao exibir ponto: %d\n", ERRO_NULL);
    else 
        printf("x = %.2f, y = %.2f;\n", ponto->abscissa, ponto->ordenada);
}

boolean ponto_destruir(PONTO* ponto){
    if(ponto == NULL){
        printf("Erro ao destruir ponto: %d\n", ERRO_NULL);
        return FALSE;
    }

    ponto->abscissa = 0;
    ponto->ordenada = 0;
    free(ponto);

    return TRUE;
}
#include "caminho.h"
#include <math.h>

struct caminho_st{
    PONTO** lista;
    int qnt_pontos;
};

CAMINHO* caminho_criar(int pontos){
    CAMINHO* novo_caminho = (CAMINHO*) malloc(sizeof(CAMINHO));

    if(novo_caminho != NULL){
        novo_caminho->lista = (PONTO**) malloc(pontos*sizeof(PONTO*));
        novo_caminho->qnt_pontos = 0;
    }
    
    return novo_caminho;
}

boolean caminho_adicionar(PONTO* novo_ponto, CAMINHO* caminho){
    if(novo_ponto == NULL || caminho == NULL){
        printf("Erro ao adicionar: %d\n", ERRO_NULL);
        return FALSE;
    }

    caminho->lista[caminho->qnt_pontos] = novo_ponto;
    caminho->qnt_pontos++;

    return TRUE;
};

PONTO* caminho_fim(CAMINHO* caminho){
    return caminho->lista[caminho->qnt_pontos-1];
}

int caminho_qnt_pontos(CAMINHO* caminho){
    return caminho->qnt_pontos;
}

boolean caminho_remover(CAMINHO* caminho){
    if(caminho == NULL){
        printf("Erro ao remover do caminho: %d\n", ERRO_NULL);
        return FALSE;
    }
    
    caminho->lista[caminho->qnt_pontos-1] = NULL;
    caminho->qnt_pontos--;

    return TRUE;
}

void caminho_exibir(CAMINHO* caminho){
    if(caminho == NULL){
        printf("Erro ao exibir caminho: %d\n", ERRO_NULL);
    }
    else{
        for(int i=0; i<caminho->qnt_pontos; i++){
            ponto_exibir(caminho->lista[i]);
        }
    }
}

float caminho_distancia(CAMINHO* caminho){
    if(caminho == NULL){
        printf("Erro ao calcular distancia: %d\n", ERRO_NULL);
        return ERRO_NULL;
    }

    float distancia = 0;
    float delta_x = 0;
    float delta_y = 0;

    for(int i=1; i<caminho->qnt_pontos; i++){
        delta_x = ponto_abscissa(caminho->lista[i]) - ponto_abscissa(caminho->lista[i-1]);
        delta_y = ponto_ordenada(caminho->lista[i]) - ponto_ordenada(caminho->lista[i-1]);

        distancia += sqrt(pow(delta_x, 2) + pow(delta_y, 2));
    }

    return distancia;
}

boolean caminho_destruir(CAMINHO** caminho){
    if(*caminho == NULL){
        printf("Erro ao destruir caminho: %d\n", ERRO_NULL);
        return FALSE;
    }

    while((*caminho)->qnt_pontos > 0){
        PONTO* ultimo_ponto = caminho_fim(*caminho);

        if(caminho_remover(*caminho))
            ponto_destruir(ultimo_ponto);
        else
            break;
    }

    if((*caminho)->qnt_pontos == 0){
        free((*caminho)->lista);
        (*caminho)->lista = NULL;

        free(*caminho);
        *caminho = NULL;

        return TRUE;
    }

    return TRUE;
}
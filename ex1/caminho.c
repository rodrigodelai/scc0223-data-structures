#include "caminho.h"

struct caminho_st{
    PONTO** lista;
    int capacidade;
    int qnt_pontos;
};

CAMINHO* caminho_criar(int capacidade){
    CAMINHO* novo_caminho = (CAMINHO*) calloc(1, sizeof(CAMINHO));

    if (novo_caminho == NULL){
        printf("Erro ao criar um novo caminho: %d", ERRO_MEM);
        return NULL;
    }

    novo_caminho->lista = (PONTO**) calloc(capacidade, sizeof(PONTO*));
    novo_caminho->capacidade = capacidade;

    return novo_caminho;
}

boolean caminho_adicionar(CAMINHO* caminho, PONTO* novo_ponto){
    if (caminho == NULL || novo_ponto == NULL){
        printf("Erro ao adicionar ponto ao caminho: %d\n", ERRO_NULL);
        return FALSE;
    }

    caminho->lista[caminho->qnt_pontos] = novo_ponto;
    caminho->qnt_pontos++;

    return TRUE;
};

int caminho_obter_capacidade(CAMINHO* caminho){
    if (caminho == NULL){
        printf("Erro ao obter capacidade: %d\n", ERRO_NULL);
        return -1;
    }

    return caminho->capacidade;
}

int caminho_obter_qnt_pontos(CAMINHO* caminho){
    if (caminho == NULL){
        printf("Erro ao obter quantidade de pontos: %d\n", ERRO_NULL);
        return -1;
    }

    return caminho->qnt_pontos;
}

PONTO* caminho_remover(CAMINHO* caminho){
    if (caminho == NULL){
        printf("Erro ao remover ultimo ponto do caminho: %d\n", ERRO_NULL);
        return NULL;
    }
    
    int qnt_pontos = caminho->qnt_pontos;

    if (!qnt_pontos)
        return NULL;

    PONTO* removido = caminho->lista[qnt_pontos - 1];

    caminho->lista[qnt_pontos - 1] = NULL;
    caminho->qnt_pontos--;

    return removido;
}

void caminho_exibir(CAMINHO* caminho){
    if (caminho == NULL){
        printf("Erro ao exibir caminho: %d\n", ERRO_NULL);
        return;
    }

    int qnt_pontos = caminho->qnt_pontos;

    while (qnt_pontos--)
        ponto_exibir(caminho->lista[qnt_pontos]);
}

float caminho_calcula_distancia(CAMINHO* caminho){
    if (caminho == NULL){
        printf("Erro ao calcular distancia: %d\n", ERRO_NULL);
        return -1;
    }

    float distancia = 0;
    float delta_x = 0;
    float delta_y = 0;

    int qnt_pontos = caminho->qnt_pontos;

    for(int i = 1; i < qnt_pontos; i++){
        delta_x = ponto_obter_abscissa(caminho->lista[i]) - ponto_obter_abscissa(caminho->lista[i-1]);
        delta_y = ponto_obter_ordenada(caminho->lista[i]) - ponto_obter_ordenada(caminho->lista[i-1]);

        distancia += sqrt(pow(delta_x, 2) + pow(delta_y, 2));
    }

    return distancia;
}

boolean caminho_destruir(CAMINHO** caminho){
    if (*caminho == NULL){
        printf("Erro ao destruir caminho: %d\n", ERRO_NULL);
        return FALSE;
    }

    int qnt_pontos = (*caminho)->qnt_pontos;

    while (qnt_pontos--){
        PONTO* removido = caminho_remover(*caminho); 
        ponto_destruir(&removido);
    }

    free((*caminho)->lista);
    (*caminho)->lista = NULL;

    free(*caminho);
    *caminho = NULL;
        
    return TRUE;
}

void ler_e_armazenar_pontos(CAMINHO* caminho){
    if (caminho == NULL){
        printf("Erro ao ler e armazenar pontos: %d\n", ERRO_NULL);
        return;
    }

    for (int i = 0; i < caminho->capacidade; i++){
        float abscissa = 0, ordenada = 0;
        scanf("%f %f", &abscissa, &ordenada);

        PONTO* ponto = ponto_criar();
        ponto_posicionar(ponto, abscissa, ordenada);
        caminho_adicionar(caminho, ponto);
    }
}

void exibir_distancia_percorrida(CAMINHO* caminho){
    if (caminho == NULL){
        printf("Erro ao exibir distancia percorrida: %d\n", ERRO_NULL);
        return;
    }

    printf("%.2f\n", caminho_calcula_distancia(caminho));
}
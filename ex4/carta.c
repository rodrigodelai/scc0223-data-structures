#include "carta.h"

struct carta_st{
    char* naipe;
    char* simbolo;
    int valor;
};

CARTA* carta_criar(){
    CARTA* carta = (CARTA*) malloc(sizeof(CARTA));
    
    if (carta == NULL){
        printf("Erro ao criar carta: %d\n", ERRO_MEM);
        return carta;
    }

    carta->naipe = NULL;
    carta->simbolo = NULL;
    carta->valor = 0;

    return carta;
}

boolean carta_definir_naipe(CARTA* carta, char* naipe){
    if (carta == NULL || naipe == NULL){
        printf("Erro ao definir naipe: %d.\n", ERRO_NULL);
        return FALSE;
    }

    if (carta->naipe != NULL) apagar_palavra(&carta->naipe);

    carta->naipe = naipe;
    return TRUE;
}

boolean carta_definir_simbolo(CARTA* carta, char* simbolo){
    if (carta == NULL || simbolo == NULL){
        printf("Erro ao definir simbolo: %d.\n", ERRO_NULL);
        return FALSE;
    }

    if (carta->simbolo != NULL) apagar_palavra(&carta->simbolo);

    carta->simbolo = simbolo;
    return TRUE;
}

boolean carta_definir_valor(CARTA* carta, int valor){
    if (carta == NULL){
        printf("Erro ao definir valor: %d.\n", ERRO_NULL);
        return FALSE;
    }

    if (valor > 10 || valor < 1){
        printf("Erro ao definir valor: %d.\n", ERRO_NUM);
        return FALSE;
    }

    carta->valor = valor;
    return TRUE;
}

int carta_extrair_valor(char* simbolo){
    if (simbolo == NULL){
        printf("Erro ao extrair valor: %d.\n", ERRO_NULL);
        return 0;
    }

    int valor;

    if (strcmp(simbolo, "V") == 0 || strcmp(simbolo, "D") == 0 || strcmp(simbolo, "R") == 0) valor = 10;
    else if ((valor = atoi(simbolo)) > 10 || valor < 1) printf("Erro ao extrair valor: %d.\n", ERRO_SIM);

    return valor;
}

char* carta_obter_naipe(CARTA* carta){
    if (carta == NULL){
        printf("Erro ao obter naipe: %d.\n", ERRO_NULL);
        return NULL;
    }

    return carta->naipe;
}

char* carta_obter_simbolo(CARTA* carta){
    if (carta == NULL){
        printf("Erro ao obter simbolo: %d.\n", ERRO_NULL);
        return NULL;
    }

    return carta->simbolo;
}
int carta_obter_valor(CARTA* carta){
    if (carta == NULL){
        printf("Erro ao obter valor: %d.\n", ERRO_NULL);
        return 0;
    }

    return carta->valor;
}

void carta_exibir(CARTA* carta){
    if (carta == NULL) printf("Erro ao exibir carta: %d.\n", ERRO_NULL);
    else printf("%-10s %2s %10d\n", carta->naipe, carta->simbolo, carta->valor);
}

boolean carta_destruir(CARTA** carta){
    if (carta == NULL || *carta == NULL){
        printf("Erro ao destruir carta: %d.\n", ERRO_NULL);
        return FALSE;
    }

    apagar_palavra(&((*carta)->naipe));
    apagar_palavra(&((*carta)->simbolo));
    (*carta)->valor = 0;

    free(*carta);
    *carta = NULL;
    
    return TRUE;
}
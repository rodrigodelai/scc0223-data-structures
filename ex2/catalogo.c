#include "catalogo.h"

struct catalogo_st
{
    JOGO** lista;
    int qnt_jogos;
};

CATALOGO* catalogo_criar(){
    CATALOGO* novo_catalogo = (CATALOGO*) malloc(sizeof(CATALOGO));

    if (novo_catalogo == NULL){
        printf("Erro ao criar catalogo: %d\n", ERRO_NULL);
        return novo_catalogo;
    }

    novo_catalogo->lista = (JOGO**) malloc(sizeof(JOGO*));

    if (novo_catalogo->lista == NULL){
        printf("Erro ao criar lista no catalogo: %d\n", ERRO_NULL);
        return NULL;
    }

    novo_catalogo->lista[0] = NULL;
    novo_catalogo->qnt_jogos = 0;

    return novo_catalogo;
}

boolean catalogo_adicionar(CATALOGO* catalogo, JOGO* jogo){
    if (jogo == NULL || catalogo == NULL){
        printf("Erro ao adicionar jogo: %d\n", ERRO_NULL);
        return FALSE;
    }

    catalogo->lista = (JOGO**) realloc(catalogo->lista, (catalogo->qnt_jogos + 1) * sizeof(JOGO*));

    if (catalogo->lista == NULL){
        printf("Erro ao alterar lista no catalogo: %d\n", ERRO_NULL);
        return FALSE;
    }

    catalogo->lista[catalogo->qnt_jogos] = jogo;
    catalogo->qnt_jogos++;

    return TRUE;
}

boolean catalogo_remover(CATALOGO* catalogo){
    if (catalogo == NULL){
        printf("Erro ao remover jogo: %d\n", ERRO_NULL);
        return FALSE;
    }

    if (catalogo->qnt_jogos == 0){
        printf("Erro ao remover jogo: O catalogo está vazio\n");
        return FALSE;
    }

    catalogo->lista[catalogo->qnt_jogos - 1] = NULL;
    catalogo->qnt_jogos--;

    return TRUE;
}

JOGO* catalogo_topo(CATALOGO* catalogo){
    if (catalogo == NULL){
        printf("Erro ao acessar topo: %d\n", ERRO_NULL);
        return NULL;
    }    

    if (catalogo->qnt_jogos == 0){
        printf("Erro ao acessar topo: O catálogo está vazio\n");
        return NULL;
    }

    return catalogo->lista[catalogo->qnt_jogos - 1];
}

void catalogo_exibir(CATALOGO* catalogo){
    if (catalogo == NULL){
        printf("Erro ao exibir catalogo: %d\n", ERRO_NULL);
    }
    else{
        printf("-------------------------------------------------\n");
        printf("                CATALOGO DE JOGOS\n");              
        printf("-------------------------------------------------\n");

        int i = catalogo->qnt_jogos;

        while (i > 0){
            jogo_exibir(catalogo->lista[i-1]);
            printf("-------------------------------------------------\n");
            i--;
        }
    }
}

JOGO* catalogo_buscar_nome(CATALOGO* catalogo, char* nome);
JOGO* catalogo_buscar_empresa(CATALOGO* catalogo, char* nome);
JOGO* catalogo_buscar_ano(CATALOGO* catalogo, char* nome);

boolean catalogo_destruir(CATALOGO** catalogo){
    if (catalogo == NULL || *catalogo == NULL){
        printf("Erro ao destruir catalogo: %d\n", ERRO_NULL);
        return FALSE;
    }

    while ((*catalogo)->qnt_jogos > 0){
        JOGO* topo = catalogo_topo(*catalogo);

        if (catalogo_remover(*catalogo)) jogo_destruir(&topo);
        else break;
    }
    
    free((*catalogo)->lista);
    (*catalogo)->lista = NULL;

    free(*catalogo);
    *catalogo = NULL;

    return TRUE;
}
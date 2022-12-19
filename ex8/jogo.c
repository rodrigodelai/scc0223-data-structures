#include "jogo.h"

struct jogo_st
{
    char* nome;
    char* empresa;
    int ano;
};

JOGO* jogo_criar(){
    JOGO* novo_jogo = (JOGO*) calloc(1, sizeof(JOGO));
    
    if (novo_jogo == NULL)
        printf("Erro ao criar jogo: %d\n", ERRO_NULL);

    return novo_jogo;
}

boolean jogo_definir_nome(JOGO* jogo, char* novo_nome){
    if (jogo == NULL || novo_nome == NULL){
        printf("Erro ao definir nome: %d\n", ERRO_NULL);
        return FALSE;
    }

    free(jogo->nome);
    jogo->nome = novo_nome;

    return TRUE;
}

boolean jogo_definir_empresa(JOGO* jogo, char* nova_empresa){
    if (jogo == NULL || nova_empresa == NULL){
        printf("Erro ao definir empresa: %d\n", ERRO_NULL);
        return FALSE;
    }

    free(jogo->empresa);
    jogo->empresa = nova_empresa;

    return TRUE;
}

boolean jogo_definir_ano(JOGO* jogo, int novo_ano){
    if (jogo == NULL){
        printf("Erro ao definir ano: %d\n", ERRO_NULL);
        return FALSE;
    }

    jogo->ano = novo_ano;
    
    return TRUE;
}

char* jogo_obter_nome(JOGO* jogo){
    if (jogo == NULL){
        printf("Erro ao obter nome: %d\n", ERRO_NULL);
        return NULL;
    }

    return jogo->nome;
}

char* jogo_obter_empresa(JOGO* jogo){
    if (jogo == NULL){
        printf("Erro ao obter empresa: %d\n", ERRO_NULL);
        return NULL;
    }

    return jogo->empresa;
}

int jogo_obter_ano(JOGO* jogo){
    if (jogo == NULL){
        printf("Erro ao obter ano: %d\n", ERRO_NULL);
        return 0;
    }

    return jogo->ano;
}

void jogo_exibir(JOGO* jogo){
    if (jogo == NULL){
        printf("Erro ao exibir jogo: %d\n", ERRO_NULL);
        return;
    }
    
    printf("Nome:    %35s\n", jogo->nome);
    printf("Empresa: %35s\n", jogo->empresa);
    printf("Ano:     %35d\n", jogo->ano);
}

boolean jogo_destruir(JOGO** jogo){
    if (jogo == NULL){
        printf("Erro ao destruir jogo: %d\n", ERRO_NULL);
        return FALSE;
    }

    free((*jogo)->nome);
    free((*jogo)->empresa);

    (*jogo)->nome = NULL;
    (*jogo)->empresa = NULL;
    (*jogo)->ano = 0;

    free(*jogo);
    *jogo = NULL;

    return TRUE;
}
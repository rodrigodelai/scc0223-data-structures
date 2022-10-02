#include "jogo.h"

struct jogo_st
{
    char* nome;
    char* empresa;
    int ano;
};

JOGO* jogo_criar(){
    JOGO* novo_jogo = (JOGO*) malloc(sizeof(JOGO));
    
    if (novo_jogo == NULL){
        printf("Erro ao criar jogo: %d\n", ERRO_NULL);
        return novo_jogo;
    }

    novo_jogo->nome = NULL;
    novo_jogo->empresa = NULL;
    novo_jogo->ano = 0;

    return novo_jogo;
}

boolean jogo_alterar_nome(JOGO* jogo, char* novo_nome){
    if (jogo == NULL || novo_nome == NULL){
        printf("Erro ao alterar nome: %d\n", ERRO_NULL);
        return FALSE;
    }

    free(jogo->nome);
    jogo->nome = novo_nome;

    return TRUE;
}

boolean jogo_alterar_empresa(JOGO* jogo, char* nova_empresa){
    if (jogo == NULL || nova_empresa == NULL){
        printf("Erro ao alterar empresa: %d\n", ERRO_NULL);
        return FALSE;
    }

    free(jogo->empresa);
    jogo->empresa = nova_empresa;

    return TRUE;
}

boolean jogo_alterar_ano(JOGO* jogo, int novo_ano){
    if (jogo == NULL){
        printf("Erro ao alterar ano: %d\n", ERRO_NULL);
        return FALSE;
    }

    jogo->ano = novo_ano;
    
    return TRUE;
}

char* jogo_acessar_nome(JOGO* jogo){
    if (jogo == NULL){
        printf("Erro ao acessar nome: %d\n", ERRO_NULL);
        return NULL;
    }

    return jogo->nome;
}

char* jogo_acessar_empresa(JOGO* jogo){
    if (jogo == NULL){
        printf("Erro ao acessar empresa: %d\n", ERRO_NULL);
        return NULL;
    }

    return jogo->empresa;
}

int jogo_acessar_ano(JOGO* jogo){
    if (jogo == NULL){
        printf("Erro ao acessar ano: %d\n", ERRO_NULL);
        return 0;
    }

    return jogo->ano;
}

void jogo_exibir(JOGO* jogo){
    if (jogo == NULL){
        printf("Erro ao exibir jogo: %d\n", ERRO_NULL);
    } 
    else {
        printf("Nome:    %40s\n", jogo->nome);
        printf("Empresa: %40s\n", jogo->empresa);
        printf("Ano:     %40d\n", jogo->ano);
    }
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
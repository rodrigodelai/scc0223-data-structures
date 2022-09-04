#include "jogo.h"

struct jogo_st
{
    char* nome;
    char* empresa;
    char* ano;
};

JOGO* jogo_criar(){
    JOGO* novo_jogo = (JOGO*) malloc(sizeof(JOGO));
    
    if (novo_jogo == NULL){
        printf("Erro ao criar jogo: %d\n", ERRO_NULL);
        return novo_jogo;
    }
    
    novo_jogo->nome = (char*) malloc(2*sizeof(char));
    novo_jogo->empresa = (char*) malloc(2*sizeof(char));
    novo_jogo->ano = (char*) malloc(5*sizeof(char));

    if (novo_jogo->nome == NULL || novo_jogo->empresa == NULL || novo_jogo->ano == NULL){
        printf("Erro ao criar nome, empresa ou ano: %d\n", ERRO_NULL);
        return novo_jogo;
    }

    strcpy(novo_jogo->nome, "-");
    strcpy(novo_jogo->empresa, "-");
    strcpy(novo_jogo->ano, "0000");

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

boolean jogo_alterar_ano(JOGO* jogo, char* novo_ano){
    if (jogo == NULL || novo_ano == NULL){
        printf("Erro ao alterar ano: %d\n", ERRO_NULL);
        return FALSE;
    }

    free(jogo->ano);
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

char* jogo_acessar_ano(JOGO* jogo){
    if (jogo == NULL){
        printf("Erro ao acessar ano: %d\n", ERRO_NULL);
        return NULL;
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
        printf("Ano:     %40s\n", jogo->ano);
    }
}

boolean jogo_destruir(JOGO** jogo){
    if (jogo == NULL){
        printf("Erro ao destruir jogo: %d\n", ERRO_NULL);
        return FALSE;
    }

    free((*jogo)->nome);
    free((*jogo)->empresa);
    free((*jogo)->ano);

    (*jogo)->nome = NULL;
    (*jogo)->ano = NULL;
    (*jogo)->empresa = NULL;

    free(*jogo);
    *jogo = NULL;

    return TRUE;
}
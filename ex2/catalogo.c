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

int catalogo_qnt_jogos(CATALOGO* catalogo){
    if (catalogo == NULL){
        printf("Erro ao acessar quantidade de jogos: %d\n", ERRO_NULL);
        return 0;
    }

    return catalogo->qnt_jogos;
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

void catalogo_exibir_por_empresa(CATALOGO* catalogo, char* empresa){
    if (catalogo == NULL || empresa == NULL){
        printf("Erro ao exibir por empresa: %d\n", ERRO_NULL);
    }
    else{
        boolean nada_encontrado = TRUE;

        for (int i = 0; i < catalogo_qnt_jogos(catalogo); i++){
            if (strcmp(empresa, jogo_acessar_empresa(catalogo->lista[i])) == 0){
                printf("%s\n", jogo_acessar_nome(catalogo->lista[i]));
                nada_encontrado = FALSE;
            }
        }
    
        if (nada_encontrado) printf("Nada encontrado\n");
    }
    apagar_linha(&empresa);
}

void catalogo_exibir_por_ano(CATALOGO* catalogo, char* ano){
    if (catalogo == NULL || ano == NULL){
        printf("Erro ao exibir por ano: %d\n", ERRO_NULL);
    }
    else{
        boolean nada_encontrado = TRUE;

        for (int i = 0; i < catalogo_qnt_jogos(catalogo); i++){
            if (strcmp(ano, jogo_acessar_ano(catalogo->lista[i])) == 0){
                printf("%s\n", jogo_acessar_nome(catalogo->lista[i]));
                nada_encontrado = FALSE;
            }
        }
    
        if (nada_encontrado) printf("Nada encontrado\n");
    }
    apagar_linha(&ano);
}

boolean opcao_filtrar_por_empresa(char* opcao){
    if (opcao == NULL){
        printf("Erro ao selecionar filtro de empresa: %d\n", ERRO_NULL);
        return FALSE;
    }

    if (strcmp(opcao, "E") == 0){
        apagar_linha(&opcao);
        return TRUE;
    }
    else{
        return FALSE;
    }
}

boolean opcao_filtrar_por_ano(char* opcao){
    if (opcao == NULL){
        printf("Erro ao selecionar filtro de ano: %d\n", ERRO_NULL);
        return FALSE;
    }

    if (strcmp(opcao, "A") == 0){
        apagar_linha(&opcao);
        return TRUE;
    }
    else{
        return FALSE;
    }
}

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
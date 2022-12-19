#include "catalogo.h"

typedef struct no_st NO;

struct no_st{
    JOGO* jogo;
    NO* direita;
    NO* esquerda;
};

struct catalogo_st{
    NO* raiz;
    int profundidade;;
    int qnt_jogos;
};

CATALOGO* catalogo_criar(){
    CATALOGO* novo_catalogo = (CATALOGO*) calloc(1, sizeof(CATALOGO));

    if (novo_catalogo == NULL)
        printf("Erro ao criar catalogo: %d\n", ERRO_MEM);

    return novo_catalogo;
}

static NO* criar_no(){
    NO* no = (NO*) calloc(1, sizeof(NO));

    if (no == NULL)
        printf("Erro ao criar no: %d\n.", ERRO_MEM);

    return no;
}

static boolean destruir_no(NO** no){
    if (*no == NULL || no == NULL){
        printf("Erro ao destruir no: %d\n.", ERRO_NULL);
        return FALSE;
    }
    
    (*no)->jogo = NULL;
    (*no)->direita = NULL;
    (*no)->esquerda = NULL;
    
    free(*no);
    *no = NULL;

    return TRUE;
}

boolean catalogo_adicionar(CATALOGO* catalogo, JOGO* jogo){
    if (jogo == NULL || catalogo == NULL){
        printf("Erro ao adicionar jogo: %d\n", ERRO_NULL);
        return FALSE;
    }

    // Codigo que adiciona um jogo ao catalogo;

    return TRUE;
}

boolean catalogo_buscar(CATALOGO* catalogo, JOGO* jogo){
    if (jogo == NULL || catalogo == NULL){
        printf("Erro ao buscar jogo: %d\n", ERRO_NULL);
        return FALSE;
    }

    // Codigo que busca um jogo do catalogo;

    return TRUE;
}

boolean catalogo_remover(CATALOGO* catalogo, int ano){
    if (catalogo == NULL){
        printf("Erro ao remover jogo: %d\n", ERRO_NULL);
        return FALSE;
    }

    // Codigo que remove um jogo do catalogo;

    return TRUE;
}

JOGO* catalogo_obter_raiz(CATALOGO* catalogo){
    if (catalogo == NULL){
        printf("Erro ao obter raiz: %d\n", ERRO_NULL);
        return NULL;
    }    

    return catalogo->raiz->jogo;
}

static int catalogo_calcular_profundidade(NO* raiz){
    if (raiz == NULL)
        return 0;

    int altura_arv_esq = catalogo_calcular_profundidade(raiz->esquerda);
    int altura_arv_dir = catalogo_calcular_profundidade(raiz->direita);

    return altura_arv_esq > altura_arv_dir ? altura_arv_esq + 1 : altura_arv_dir + 1;
}

int catalogo_obter_profundidade(CATALOGO* catalogo){
    if (catalogo == NULL){
        printf("Erro ao obter profundidade: %d\n", ERRO_NULL);
        return -1;
    }

    return (catalogo->profundidade = catalogo_calcular_profundidade(catalogo->raiz) - 1);
}


int catalogo_obter_qnt_jogos(CATALOGO* catalogo){
    if (catalogo == NULL){
        printf("Erro ao obter quantidade de jogos: %d\n", ERRO_NULL);
        return -1;
    }

    return catalogo->qnt_jogos;
}

void catalogo_exibir(CATALOGO* catalogo, int opcao){
    if (catalogo == NULL){
        printf("Erro ao exibir catalogo: %d\n", ERRO_NULL);
        return;
    }

    printf("-------------------------------------------------\n");
    printf("                CATALOGO DE JOGOS\n");              
    printf("-------------------------------------------------\n");

    // Codigo que exibe todos os jogos do catalogo;

}

void catalogo_exibir_nomes(CATALOGO* catalogo, int opcao){
    if (catalogo == NULL){
        printf("Erro ao exibir nomes: %d\n", ERRO_NULL);
        return;
    }

    printf("Exibindo nomes...\n");
}

static void recursao_destruir(NO* raiz) {
    if (raiz != NULL) {
        recursao_destruir(raiz->esquerda);
        recursao_destruir(raiz->direita);

        jogo_destruir(&raiz->jogo);
        destruir_no(&raiz);
    }
}

boolean catalogo_destruir(CATALOGO** catalogo){
    if (*catalogo == NULL || catalogo == NULL){
        printf("Erro ao destruir catalogo: %d\n", ERRO_NULL);
        return FALSE;
    }

    recursao_destruir((*catalogo)->raiz);

    (*catalogo)->raiz = NULL;
    (*catalogo)->profundidade = 0;

    free(*catalogo);
    *catalogo = NULL;

    return TRUE;
}

void ler_novo_catalogo(CATALOGO* catalogo){
    if (catalogo == NULL){
        printf("Erro ao ler novo catalogo: %d\n", ERRO_NULL);
        return;
    }

    FILE* csv = fopen("CSV.csv", "r");

    if (!csv) {
        printf("Erro ao abrir arquivo. Nao foi possivel ler um novo catalogo.\n");
        return;
    }

    fseek(csv, 3, SEEK_SET); // Ignora os 3 primeiros bytes com informacoes sobre o enconding (UTF-8) do arquivo;

    char* texto = NULL;

    while ((texto = ler_texto(csv)) != NULL){
        JOGO* jogo = jogo_criar();
        jogo_definir_nome(jogo, texto);
        jogo_definir_ano(jogo, ler_inteiro(csv));
        jogo_definir_empresa(jogo, ler_texto(csv));
        catalogo_adicionar(catalogo, jogo);
    }

    fclose(csv);
}

void realizar_remocoes(CATALOGO* catalogo){
    if (catalogo == NULL){
        printf("Erro ao realizar remocoes: %d\n", ERRO_NULL);
        return;
    }

    printf("Realizando remocoes...\n");
}
#include "banco.h"

typedef struct no_st NO;

struct no_st{
    CONTA* conta;
    NO* direita;
    NO* esquerda;
};

struct banco_st{
    NO* raiz;
    int profundidade;
};

BANCO* banco_criar(){
    BANCO* banco = (BANCO*) malloc(sizeof(BANCO));

    if (banco == NULL){
        printf("Erro ao criar banco: %d\n", ERRO_MEM);
        return banco;
    }

    banco->raiz = NULL;
    banco->profundidade = 0;
    
    return banco;
}

static NO* criar_no(){
    NO* no = (NO*) malloc(sizeof(NO));

    if (no == NULL){
        printf("Erro ao criar no: %d\n.", ERRO_MEM);
        return no;
    }

    no->conta = NULL;
    no->direita = NULL;
    no->esquerda = NULL;

    return no;
}

static boolean destruir_no(NO** no){
    if (*no == NULL || no == NULL){
        printf("Erro ao destruir no: %d\n.", ERRO_NULL);
        return FALSE;
    }
    
    (*no)->conta = NULL;
    (*no)->direita = NULL;
    (*no)->esquerda = NULL;
    
    free(*no);
    *no = NULL;

    return TRUE;
}

static NO* banco_adicionar_no(NO* raiz, CONTA* conta) {
    if (raiz == NULL) {
        raiz = criar_no();
        raiz->conta = conta;
    }
    else if (conta_obter_cpf(conta) > conta_obter_cpf(raiz->conta)){
        raiz->direita = banco_adicionar_no(raiz->direita, conta);
    }
    else if (conta_obter_cpf(conta) < conta_obter_cpf(raiz->conta)){
        raiz->esquerda = banco_adicionar_no(raiz->esquerda, conta);
    }
    else {
        conta_destruir(&conta);
    }

    return raiz;
}

boolean banco_adicionar_conta (BANCO* banco, CONTA* conta){
    if (banco == NULL || conta == NULL){
        printf("Erro ao adicionar conta: %d\n.", ERRO_NULL);
        return FALSE;
    }
    
    banco->raiz = banco_adicionar_no(banco->raiz, conta);

    return (banco->raiz != NULL);
}

static NO* banco_buscar_no(NO *raiz, long cpf){
    if (raiz == NULL) 
        return NULL;

    long cpf_no_atual = conta_obter_cpf(raiz->conta);

    if (cpf == cpf_no_atual) 
        return raiz;
    else if (cpf < cpf_no_atual) 
        return banco_buscar_no(raiz->esquerda, cpf);
    else 
        return banco_buscar_no(raiz->direita, cpf);
}

CONTA* banco_buscar_conta(BANCO* banco, long cpf){
    if (banco == NULL){
        printf("Erro ao buscar conta: %d\n.", ERRO_NULL);
        return NULL;
    }

    NO* retorno = banco_buscar_no(banco->raiz, cpf);
    if (retorno != NULL) 
        return retorno->conta;

    return NULL;
}

static NO* substituir_pelo_minimo_da_direita(NO* substitui, NO* raiz, NO* anterior){
    if (substitui->esquerda != NULL)
        return substituir_pelo_minimo_da_direita(substitui->esquerda, raiz, substitui);
    
    if (raiz == anterior)
        anterior->direita = substitui->direita;
    else 
        anterior->esquerda = substitui->direita;

    CONTA* removida = raiz->conta;
    raiz->conta = substitui->conta;
    substitui->conta = removida;
    
    return substitui;
}

static NO* banco_remover_no(NO** raiz, long cpf){
    NO* removido;

    if (*raiz == NULL) 
        return NULL;

    long cpf_no_atual = conta_obter_cpf((*raiz)->conta);

    if (cpf == cpf_no_atual){
        if ((*raiz)->esquerda == NULL || (*raiz)->direita == NULL){
            removido = *raiz;

            if((*raiz)->esquerda == NULL) 
                *raiz = (*raiz)->direita;
            else 
                *raiz = (*raiz)->esquerda;
        }
        else {
            removido = substituir_pelo_minimo_da_direita((*raiz)->direita, *raiz, *raiz);
        }

        return removido;
    }
    else {
        if (cpf < cpf_no_atual) 
            return banco_remover_no(&(*raiz)->esquerda, cpf);
        else 
            return banco_remover_no(&(*raiz)->direita, cpf);
    }
}

CONTA* banco_remover_conta(BANCO* banco, long cpf){
    if (banco == NULL){
        printf("Erro ao remover conta: %d\n.", ERRO_NULL);
        return FALSE;
    }

    NO* removido = banco_remover_no(&banco->raiz, cpf);

    if (removido != NULL){
        CONTA* removida = removido->conta;
        destruir_no(&removido);
        return removida;
    }

    return NULL;
}


CONTA* banco_obter_raiz(BANCO* banco){
    if (banco == NULL){
        printf("Erro ao obter raiz: %d\n", ERRO_NULL);
        return NULL;
    }

    return banco->raiz->conta;
}

static int banco_calcular_profundidade(NO* raiz){
    if (raiz == NULL)
        return 0;

    int altura_arv_esq = banco_calcular_profundidade(raiz->esquerda);
    int altura_arv_dir = banco_calcular_profundidade(raiz->direita);

    return altura_arv_esq > altura_arv_dir ? altura_arv_esq + 1 : altura_arv_dir + 1;
}


int banco_obter_profundidade(BANCO* banco){
    if (banco == NULL){
        printf("Erro ao obter profundidade: %d\n", ERRO_NULL);
        return -1;
    }

    return (banco->profundidade = banco_calcular_profundidade(banco->raiz) - 1);
}


static void recursao_exibir(NO *raiz) {
    if (raiz != NULL) {
        printf("%011ld\n", conta_obter_cpf(raiz->conta));
        recursao_exibir(raiz->esquerda);
        recursao_exibir(raiz->direita);
    }
}

void banco_exibir_cpfs(BANCO* banco){
    if (banco == NULL){
        printf("Erro ao exibir cpfs: %d\n", ERRO_NULL);
    }
    else {
        printf("Preorder\n");
        recursao_exibir(banco->raiz);
    }
}

static void recursao_destruir(NO* raiz) {
    if (raiz != NULL) {
        recursao_destruir(raiz->esquerda);
        recursao_destruir(raiz->direita);

        conta_destruir(&raiz->conta);
        destruir_no(&raiz);
    }
}

boolean banco_destruir(BANCO** banco){
    if (*banco == NULL || banco == NULL){
        printf("Erro ao destruir banco: %d\n", ERRO_NULL);
        return FALSE;
    }

    recursao_destruir((*banco)->raiz);

    (*banco)->raiz = NULL;
    (*banco)->profundidade = 0;

    free(*banco);
    *banco = NULL;

    return TRUE;
}

boolean opcao_busca(char* opcao){
    if (opcao == NULL){
        printf("Erro ao selecionar opcao: %d\n", ERRO_NULL);
        return FALSE;
    }

    if (strcmp(opcao, "B") == 0){
        apagar_dado(&opcao);
        return TRUE;
    }
    else{
        return FALSE;
    }
}

boolean opcao_remocao(char* opcao){
    if (opcao == NULL){
        printf("Erro ao selecionar opcao: %d\n", ERRO_NULL);
        return FALSE;
    }

    if (strcmp(opcao, "R") == 0){
        apagar_dado(&opcao);
        return TRUE;
    }
    else{
        return FALSE;
    }
}

boolean opcao_insercao(char* opcao){
    if (opcao == NULL){
        printf("Erro ao selecionar opcao: %d\n", ERRO_NULL);
        return FALSE;
    }

    if (strcmp(opcao, "I") == 0){
        apagar_dado(&opcao);
        return TRUE;
    }
    else{
        return FALSE;
    }
}

static void ler_uma_conta(CONTA* conta){
    conta_definir_cpf(conta, conta_extrair_cpf(ler_dado()));
    conta_definir_nome(conta, ler_dado());
    conta_definir_idade(conta, ler_inteiro());
    conta_definir_saldo(conta, conta_extrair_saldo(ler_dado()));    
}

void ler_e_armazenar_contas(BANCO* banco){
    if (banco == NULL){
        printf("Erro ao ler e armazenar contas: %d\n", ERRO_NULL);
    }
    else{
        int cadastros = 0;
        scanf("%d", &cadastros);

        while(cadastros--){
            CONTA* conta = conta_criar();
            ler_uma_conta(conta);
            banco_adicionar_conta(banco, conta);
        }
    }
}

void realizar_operacao(BANCO* banco){
    if (banco == NULL){
        printf("Erro ao realizar operacao: %d\n", ERRO_NULL);
    }
    else{
        char* opcao = ler_dado();

        if (opcao_busca(opcao)){
            CONTA* retorno = banco_buscar_conta(banco, conta_extrair_cpf(ler_dado()));

            if (retorno == NULL) 
                printf("Pessoa nao encontrada.\n");
            else 
                conta_exibir(retorno);
        }
        else if (opcao_remocao(opcao)){
            CONTA* retorno = banco_remover_conta(banco, conta_extrair_cpf(ler_dado()));

            if (retorno == NULL) {
                printf("Pessoa nao encontrada.\n");
            }
            else {
                conta_exibir(retorno);
                conta_destruir(&retorno);
            }

            banco_exibir_cpfs(banco);
        }
        else if (opcao_insercao(opcao)){
            CONTA* conta = conta_criar();
            ler_uma_conta(conta);
            banco_adicionar_conta(banco, conta);
            banco_exibir_cpfs(banco);
        }
        else {
            printf("Opcao invalida. Digite 'I' para insercao, 'B' para busca ou 'R' para remocao.\n");
            apagar_dado(&opcao);
            realizar_operacao(banco);
        }
    }
}
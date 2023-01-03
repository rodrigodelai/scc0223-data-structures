#include "catalogo.h"

typedef struct no_st NO;

struct no_st{
    JOGO *jogo;
    NO *direita;
    NO *esquerda;
    int altura;
};

struct catalogo_st{
    NO *raiz;
    int altura;
    int chamadas; // Artificio para remover todos os nos de um ano espeficico;
};

CATALOGO* catalogo_criar(){
    CATALOGO *novo_catalogo = (CATALOGO *)calloc(1, sizeof(CATALOGO));

    if (novo_catalogo == NULL)
        printf("Erro ao criar catalogo: %d\n", ERRO_MEM);

    return novo_catalogo;
}

static NO* criar_no(){
    NO *no = (NO *)calloc(1, sizeof(NO));

    if (no == NULL)
        printf("Erro ao criar no: %d\n.", ERRO_MEM);

    return no;
}

static int altura_no(NO *no){
    if (no == NULL)
        return -1;
    else
        return no->altura;
}

static boolean destruir_no(NO **no, CATALOGO* catalogo){
    if (*no == NULL || no == NULL){
        printf("Erro ao destruir no: %d\n.", ERRO_NULL);
        return FALSE;
    }

    #ifdef DEBUG
        printf("No destruido com sucesso.\n");
    #endif

    (*no)->jogo = NULL;
    (*no)->direita = NULL;
    (*no)->esquerda = NULL;
    (*no)->altura = -1;

    free(*no);
    *no = NULL;

    catalogo->chamadas--;

    return TRUE;
}

static int computar_altura_via_filhos(NO* no){
    if(no == NULL)
        return -1;

    return max(altura_no(no->esquerda), altura_no(no->direita)) + 1;
}

static NO* rotacionar_a_direita(NO* raiz_atual){

    #ifdef DEBUG
            printf("Rotacionar a direita... raiz_atual: %s, altura: %d\n", jogo_obter_nome(raiz_atual->jogo), raiz_atual->altura);
    #endif

    NO* nova_raiz = raiz_atual->esquerda;

    raiz_atual->esquerda = nova_raiz->direita;
    nova_raiz->direita = raiz_atual;

    raiz_atual->altura = computar_altura_via_filhos(raiz_atual); 
    nova_raiz->altura = max(altura_no(nova_raiz->esquerda), raiz_atual->altura) + 1;

    return nova_raiz;
}

static NO* rotacionar_a_esquerda(NO *raiz_atual){

    #ifdef DEBUG
            printf("Rotacionar a esquerda... raiz_atual: %s, altura: %d\n", jogo_obter_nome(raiz_atual->jogo), raiz_atual->altura);
    #endif

    NO* nova_raiz = raiz_atual->direita;

    raiz_atual->direita = nova_raiz->esquerda;
    nova_raiz->esquerda = raiz_atual;

    raiz_atual->altura = computar_altura_via_filhos(raiz_atual);
    nova_raiz->altura = max(altura_no(nova_raiz->direita), raiz_atual->altura) + 1;

    return nova_raiz;
}

static NO* rotacionar_esquerda_direita(NO* raiz_atual){
    raiz_atual->esquerda = rotacionar_a_esquerda(raiz_atual->esquerda);
    return rotacionar_a_direita(raiz_atual);
}

static NO* rotacionar_direita_esquerda(NO* raiz_atual){
    raiz_atual->direita = rotacionar_a_direita(raiz_atual->direita);
    return rotacionar_a_esquerda(raiz_atual);
}

static int calcular_fator_de_balanceamento(NO* no){
    return altura_no(no->esquerda) - altura_no(no->direita);
}

static NO* verificar_e_balancear(NO* raiz){
    if (raiz == NULL){
        return raiz;
    }

    #ifdef DEBUG
        printf("Verificando balanceamento... jogo: %s, altura: %d\n", jogo_obter_nome(raiz->jogo), raiz->altura);
    #endif
    
    if (calcular_fator_de_balanceamento(raiz) <= -2){

        #ifdef DEBUG
            printf("Fator de balanceamento -2:\n");
        #endif

        if (calcular_fator_de_balanceamento(raiz->direita) <= 0)
            raiz = rotacionar_a_esquerda(raiz);
        else
            raiz = rotacionar_direita_esquerda(raiz);
    }

    if (calcular_fator_de_balanceamento(raiz) >= 2){

        #ifdef DEBUG
            printf("Fator de balanceamento 2:\n");
        #endif

        if (calcular_fator_de_balanceamento(raiz->esquerda) >= 0)
            raiz = rotacionar_a_direita(raiz);
        else
            raiz = rotacionar_esquerda_direita(raiz);
    }

    return raiz;
}

NO* catalogo_adicionar_no(NO* raiz, JOGO* jogo){
    if (raiz == NULL){
        raiz = criar_no();
        raiz->jogo = jogo;
    }
    else if (jogo_obter_ano(jogo) < jogo_obter_ano(raiz->jogo)){
        raiz->esquerda = catalogo_adicionar_no(raiz->esquerda, jogo);
    }
    else if (jogo_obter_ano(jogo) > jogo_obter_ano(raiz->jogo)) {
        raiz->direita = catalogo_adicionar_no(raiz->direita, jogo);
    }
    else { // Mesmo ano de lancamento; Inserir em ordem alfabetica;
        if (strcmp(jogo_obter_nome(jogo), jogo_obter_nome(raiz->jogo)) < 0){
            raiz->esquerda = catalogo_adicionar_no(raiz->esquerda, jogo);
        }
        else if (strcmp(jogo_obter_nome(jogo), jogo_obter_nome(raiz->jogo)) > 0){
            raiz->direita = catalogo_adicionar_no(raiz->direita, jogo);
        }
        else {
            jogo_destruir(&jogo); // Descarta registros duplicados;
        }
    }

    raiz->altura = computar_altura_via_filhos(raiz);
    raiz = verificar_e_balancear(raiz);

    return raiz;
}

boolean catalogo_adicionar(CATALOGO* catalogo, JOGO* jogo){
    if (catalogo == NULL){
        printf("Erro ao adicionar jogo: %d\n", ERRO_NULL);
        return FALSE;
    }

    #ifdef DEBUG
        printf("Adicionando jogo: %s", jogo_obter_nome(jogo));

        if (catalogo->raiz != NULL) 
            printf(" ---------- RAIZ ATUAL: %s\n", jogo_obter_nome(catalogo->raiz->jogo));
        else 
            printf("\n"); 
    #endif

    catalogo->raiz = catalogo_adicionar_no(catalogo->raiz, jogo);
    catalogo->chamadas++;

    return (catalogo->raiz != NULL);
}

static NO* catalogo_buscar_no(NO *raiz, int ano){
    if (raiz == NULL) 
        return NULL;

    int ano_no_atual = jogo_obter_ano(raiz->jogo);

    if (ano == ano_no_atual){
        return raiz;
    }
    else if (ano < ano_no_atual){
        return catalogo_buscar_no(raiz->esquerda, ano);
    }
    else { 
        return catalogo_buscar_no(raiz->direita, ano);
    }
}

JOGO* catalogo_buscar(CATALOGO* catalogo, int ano){
    if (catalogo == NULL){
        printf("Erro ao buscar jogo: %d\n.", ERRO_NULL);
        return NULL;
    }

    NO* retorno = catalogo_buscar_no(catalogo->raiz, ano);
    
    if (retorno != NULL){
        return retorno->jogo;
    }

    return NULL;
}

static NO* substituir_pelo_maior_da_esquerda(NO* maior, NO* raiz, NO* anterior, CATALOGO* catalogo){
    if (maior->direita != NULL){
        raiz = substituir_pelo_maior_da_esquerda(maior->direita, raiz, maior, catalogo);
    }
    else {
        if (raiz == anterior){
            anterior->esquerda = maior->direita;
        }
        else {
            anterior->direita = maior->esquerda;
        }

        jogo_destruir(&(raiz->jogo));
        raiz->jogo = maior->jogo;
        destruir_no(&maior, catalogo);
    }

    return raiz;
}

static NO* catalogo_remover_no(NO** raiz, int ano, CATALOGO* catalogo){
    if (*raiz == NULL){
        return NULL;
    }

    if (ano < jogo_obter_ano((*raiz)->jogo)){
        (*raiz)->esquerda = catalogo_remover_no(&((*raiz)->esquerda), ano, catalogo);
    }
    else if (ano > jogo_obter_ano((*raiz)->jogo)){
        (*raiz)->direita = catalogo_remover_no(&((*raiz)->direita), ano, catalogo);
    }
    else {
        if ((*raiz)->esquerda == NULL || (*raiz)->direita == NULL){

            #ifdef DEBUG
                printf("Caso em que um dos filhos é NULL: %s\n", jogo_obter_nome((*raiz)->jogo));
            #endif

            NO* auxiliar = *raiz;
          
            if ((*raiz)->esquerda == NULL){
                *raiz = (*raiz)->direita;
            }
            else {
                *raiz = (*raiz)->esquerda;
            }

            jogo_destruir(&(auxiliar->jogo));
            destruir_no(&auxiliar, catalogo);
        }
        else {
            #ifdef DEBUG
                printf("Caso em que nenhum dos filhos é NULL: %s\n", jogo_obter_nome((*raiz)->jogo));
            #endif

            *raiz = substituir_pelo_maior_da_esquerda((*raiz)->esquerda, (*raiz), (*raiz), catalogo);
        }
    }    

    if ((*raiz) != NULL){
        (*raiz)->altura = computar_altura_via_filhos(*raiz);
    }

    *raiz = verificar_e_balancear(*raiz);
    
    return *raiz;
}

boolean catalogo_remover(CATALOGO* catalogo, int ano){
    if (catalogo == NULL){
        printf("Erro ao remover jogo: %d\n", ERRO_NULL);
        return FALSE;
    }

    catalogo->raiz = catalogo_remover_no(&(catalogo->raiz), ano, catalogo);

    return TRUE;
}

JOGO* catalogo_obter_raiz(CATALOGO *catalogo){
    if (catalogo == NULL){
        printf("Erro ao obter raiz: %d\n", ERRO_NULL);
        return NULL;
    }

    return catalogo->raiz->jogo;
}

int catalogo_obter_altura(CATALOGO *catalogo){
    if (catalogo == NULL){
        printf("Erro ao obter altura: %d\n", ERRO_NULL);
        return -1;
    }

    return catalogo->altura;
}


static void recursao_exibir(NO *raiz){
    if (raiz != NULL){
        jogo_exibir(raiz->jogo);
        printf("-------------------------------------------------\n");
        recursao_exibir(raiz->esquerda);
        recursao_exibir(raiz->direita);
    }
}

void catalogo_exibir(CATALOGO *catalogo){
    if (catalogo == NULL){
        printf("Erro ao exibir catalogo: %d\n", ERRO_NULL);
        return;
    }

    printf("-------------------------------------------------\n");
    printf("                CATALOGO DE JOGOS\n");
    printf("-------------------------------------------------\n");

    recursao_exibir(catalogo->raiz);
}

static void recursao_exibir_pre_ordem(NO *raiz){
    if (raiz != NULL){
        printf("%s\n", jogo_obter_nome(raiz->jogo));
        recursao_exibir_pre_ordem(raiz->esquerda);
        recursao_exibir_pre_ordem(raiz->direita);
    }
}

static void recursao_exibir_em_ordem(NO *raiz){
    if (raiz != NULL){
        recursao_exibir_em_ordem(raiz->esquerda);
        printf("%s\n", jogo_obter_nome(raiz->jogo));
        recursao_exibir_em_ordem(raiz->direita);
    }
}

static void recursao_exibir_pos_ordem(NO *raiz){
    if (raiz != NULL){
        recursao_exibir_pos_ordem(raiz->esquerda);
        recursao_exibir_pos_ordem(raiz->direita);
        printf("%s\n", jogo_obter_nome(raiz->jogo));
    }
}

void catalogo_exibir_nomes(CATALOGO *catalogo, int opcao){
    if (catalogo == NULL){
        printf("Erro ao exibir nomes: %d\n", ERRO_NULL);
        return;
    }

    if (opcao == 1)
        recursao_exibir_pre_ordem(catalogo->raiz);
    else if (opcao == 2)
        recursao_exibir_em_ordem(catalogo->raiz);
    else
        recursao_exibir_pos_ordem(catalogo->raiz);
}

static void recursao_destruir(NO *raiz, CATALOGO* catalogo){
    if (raiz != NULL){
        recursao_destruir(raiz->esquerda, catalogo);
        recursao_destruir(raiz->direita, catalogo);

        jogo_destruir(&raiz->jogo);
        destruir_no(&raiz, catalogo);
    }
}

boolean catalogo_destruir(CATALOGO **catalogo){
    if (*catalogo == NULL || catalogo == NULL){
        printf("Erro ao destruir catalogo: %d\n", ERRO_NULL);
        return FALSE;
    }

    recursao_destruir((*catalogo)->raiz, *catalogo);

    (*catalogo)->raiz = NULL;
    (*catalogo)->altura = -1;
    (*catalogo)->chamadas = 0;

    free(*catalogo);
    *catalogo = NULL;

    return TRUE;
}

void ler_novo_catalogo(CATALOGO *catalogo){
    if (catalogo == NULL){
        printf("Erro ao ler novo catalogo: %d\n", ERRO_NULL);
        return;
    }

    FILE* csv = fopen("CSV.csv", "r");

    if (!csv){
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

    char* entrada = (char*) calloc(5, sizeof(char));
    scanf("%s", entrada);

    while (strcmp(entrada, "F") != 0){
        int chamadas = catalogo->chamadas;

        int ano = atoi(entrada);
        catalogo_remover(catalogo, ano);

        while (catalogo->chamadas < chamadas){
            catalogo_remover(catalogo, ano);
            chamadas--;
        }

        scanf("%s", entrada);
    }

    apagar_texto(&entrada);
}
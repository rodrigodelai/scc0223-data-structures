#include "baralho.h"

typedef struct no_st NO;

struct no_st{
    CARTA* carta;
    NO* anterior;
};

struct baralho_st{
    NO* topo;
    int qnt_cartas;
};

static NO* criar_no(){
    NO* no = (NO*) malloc(sizeof(NO));

    if (no == NULL){
        printf("Erro ao criar no: %d\n.", ERRO_MEM);
        return no;
    }

    no->carta = NULL;
    no->anterior = NULL;

    return no;
}

static boolean destruir_no(NO** no){
    if (*no == NULL || no == NULL){
        printf("Erro ao destruir no: %d\n.", ERRO_NULL);
        return FALSE;
    }
    
    (*no)->carta = NULL;
    (*no)->anterior = NULL;
    
    free(*no);
    *no = NULL;

    return TRUE;
}

BARALHO* baralho_criar(){
    BARALHO* baralho = (BARALHO*) malloc(sizeof(BARALHO));

    if (baralho == NULL){
        printf("Erro ao criar baralho: %d\n.", ERRO_MEM);
        return baralho;
    }

    baralho->topo = NULL;
    baralho->qnt_cartas = 0;

    return baralho;
}

boolean baralho_empilhar(BARALHO* baralho, CARTA* carta){
    if (baralho == NULL || carta == NULL){
        printf("Erro ao empilhar carta: %d\n.", ERRO_NULL);
        return FALSE;
    }

    NO* no = criar_no();

    no->carta = carta;
    no->anterior = baralho->topo;

    baralho->topo = no;
    baralho->qnt_cartas++;

    return TRUE;
}

CARTA* baralho_desempilhar(BARALHO* baralho){
    if (baralho == NULL){
        printf("Erro ao desempilhar carta: %d\n.", ERRO_NULL);
        return NULL;
    }

    if (baralho_esta_vazio(baralho)){
        printf("Nao foi possivel desempilhar. O baralho esta vazio.\n.");
        return NULL;
    }

    CARTA* desempilhada = baralho->topo->carta;
    NO* desempilhado = baralho->topo;

    baralho->topo = desempilhado->anterior;
    baralho->qnt_cartas--;

    destruir_no(&desempilhado);

    return desempilhada;
}

CARTA* baralho_obter_topo(BARALHO* baralho){
    if (baralho == NULL){
        printf("Erro ao obter topo: %d\n.", ERRO_NULL);
        return NULL;
    }

    if (baralho_esta_vazio(baralho)){
        printf("Nao foi possivel obter topo. O baralho esta vazio.\n");
        return NULL;
    }

    return baralho->topo->carta;
}

int baralho_obter_qnt_cartas(BARALHO* baralho){
    if (baralho == NULL){
        printf("Erro ao obter quantidade de cartas: %d\n.", ERRO_NULL);
        return 0;
    }

    return baralho->qnt_cartas;
}

boolean baralho_esta_vazio(BARALHO* baralho){
    if (baralho == NULL){
        printf("Erro ao checar se baralho esta vazio: %d\n.", ERRO_NULL);
        return FALSE;
    }
    
    if (baralho->qnt_cartas == 0) return TRUE;
    else return FALSE;
}

void baralho_exibir(BARALHO* baralho){
    if (baralho == NULL){
        printf("Erro ao exibir baralho: %d\n.", ERRO_NULL);
    }
    else if (baralho_esta_vazio(baralho)){
        printf("Não ha o que exibir. O baralho esta vazio.\n");
    }
    else {
        printf("------------------------\n");
        printf("  IMPRESSAO DO BARALHO\n");
        printf("------------------------\n");
        printf("NAIPE     SIMB.    VALOR\n");
        printf("------------------------\n");

        NO* auxiliar = baralho->topo;
        
        for (int i = 0; i < baralho->qnt_cartas; i++){
            carta_exibir(auxiliar->carta);
            auxiliar = auxiliar->anterior;
        }

        printf("------------------------\n");
    }
}

boolean baralho_destruir(BARALHO** baralho){
    if (baralho == NULL || *baralho == NULL){
        printf("Erro ao destruir baralho: %d.\n", ERRO_NULL);
        return FALSE;
    }

    while (!baralho_esta_vazio(*baralho)){
        CARTA* desempilhada = baralho_desempilhar(*baralho);
        carta_destruir(&desempilhada);
    }

    free(*baralho);
    *baralho = NULL;

    return TRUE;
}

void ler_novo_baralho(BARALHO* baralho){
    for(int i = 0; i<52; i++){
        CARTA* carta = carta_criar();
        carta_definir_naipe(carta, ler_palavra());
        carta_definir_simbolo(carta, ler_palavra());
        carta_definir_valor(carta, carta_extrair_valor(carta_obter_simbolo(carta)));
        baralho_empilhar(baralho, carta);
    }
}

void jogar_blackjack(BARALHO* baralho){
    int soma = 0;

    while (soma < 21){
        CARTA* desempilhada = baralho_desempilhar(baralho);
        soma += carta_obter_valor(desempilhada);
        carta_destruir(&desempilhada);
    }

    if (soma == 21) printf("Ganhou ;)\n");
    else printf("Perdeu :(\nSoma :: %d\n", soma);
}
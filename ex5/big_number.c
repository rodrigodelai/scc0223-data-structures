#include "big_number.h"

typedef struct no_st NO;

struct no_st{
    int parte;
    NO* proximo;
};

struct big_number_st{
    NO* inicio; 
    NO* fim;
    int qnt_partes;
    int sinal;
};

static NO* criar_no(){
    NO* no = (NO*) malloc(sizeof(NO));

    if (no == NULL){
        printf("Erro ao criar no: %d\n.", ERRO_MEM);
        return no;
    }

    no->parte = 0;
    no->proximo = NULL;

    return no;
}

static boolean destruir_no(NO** no){
    if (*no == NULL || no == NULL){
        printf("Erro ao destruir no: %d\n.", ERRO_NULL);
        return FALSE;
    }
    
    (*no)->parte = 0;
    (*no)->proximo = NULL;
    
    free(*no);
    *no = NULL;

    return TRUE;
}

BIG_NUMBER* big_number_criar_numero(){
    BIG_NUMBER* big_number = (BIG_NUMBER*) malloc(sizeof(BIG_NUMBER));

    if (big_number == NULL){
        printf("Erro ao criar big_number: %d\n.", ERRO_MEM);
        return big_number;
    }

    big_number->inicio = NULL;
    big_number->fim = NULL;
    big_number->qnt_partes = 0;
    big_number->sinal = POSITIVO;

    return big_number;
}

boolean big_number_definir_numero(BIG_NUMBER* big_number, char* numero){
    if (big_number == NULL){
        printf("Erro ao definir numero: %d\n.", ERRO_NULL);
        return FALSE;
    }

    int algarismos = strlen(numero);
    int ajuste = 0;

    if (numero[0] == '-'){
        big_number->sinal = NEGATIVO;
        algarismos--;
        ajuste++;
    }

    int partes = algarismos % 4 == 0 ? algarismos / 4 : algarismos / 4 + 1;  

    #ifdef DEBUG
            printf("algarismos: %d, partes: %d\n\n", algarismos, partes);
    #endif

    for(int i = 1; i < partes + 1; i++){
        char parte[5]="";
        int indice;
        int passo;

        indice = algarismos-4*i < 0 ? 0 + ajuste : algarismos-4*i + ajuste;
        passo = algarismos-4*i < 0 ? algarismos % 4 : 4;

        #ifdef DEBUG
            printf("indice: %d, passo: %d\n", indice, passo);
        #endif
        
        strncpy(parte, numero + indice, passo);

        int parte_do_numero = atoi(parte);
        big_number_adicionar_parte(big_number, parte_do_numero);
    }

    while (big_number->fim->parte == 0) big_number_remover_parte(big_number, big_number->qnt_partes);

    apagar_palavra(&numero);

    return TRUE;
}


char* big_number_obter_numero(BIG_NUMBER* big_number){
    if (big_number == NULL){
        printf("Erro ao obter numero: %d\n.", ERRO_NULL);
        return FALSE;
    }

    if (big_number->qnt_partes == 0){
        printf("Erro ao obter numero: %d\n.", ERRO_NUM);
        return FALSE;
    }

    int parte = big_number->fim->parte;
    char str_parte[5] = "";
    sprintf(str_parte, "%d", parte);

    int indice = strlen(str_parte);

    char* numero = (char*) malloc(4 * sizeof(char) * (big_number->qnt_partes - 1) + indice + 1);
    numero[4 * (big_number->qnt_partes - 1) + indice] = '\0';

    #ifdef DEBUG
        printf("algarismos na parte final: %d\n", indice);
        printf("bytes alocados: %d\n", 4 * (big_number->qnt_partes - 1) + indice + 1);
    #endif
    
    strncpy(numero, str_parte, indice);

    int auxiliar = big_number->qnt_partes;

    while (--auxiliar){
        parte = big_number_obter_parte(big_number, auxiliar);
        sprintf(str_parte,"%d", parte);
        strncpy(numero + indice, str_parte, 4);
        indice += 4;
    }

    return numero;
}

void big_number_exibir_numero(BIG_NUMBER* big_number){
    if (big_number == NULL){
        printf("Erro ao exibir numero: %d\n.", ERRO_NULL);
    }
    else{
        if (big_number->sinal == NEGATIVO) printf("-");
        int auxiliar = big_number->qnt_partes + 1;
        while (--auxiliar) big_number_exibir_parte(big_number, auxiliar);
    }

    printf("\n");
}

boolean big_number_destruir_numero(BIG_NUMBER** big_number){
    if (*big_number == NULL || big_number == NULL){
        printf("Erro ao destruir numero: %d\n.", ERRO_NULL);
        return FALSE;
    }

    while ((*big_number)->qnt_partes) big_number_remover_parte(*big_number, (*big_number)->qnt_partes);

    if ((*big_number)->inicio != NULL) return FALSE;

    free(*big_number);
    *big_number = NULL;

    return TRUE;
}

boolean big_number_adicionar_parte(BIG_NUMBER* big_number, int parte_do_numero){
    if (big_number == NULL){
        printf("Erro ao adicionar parte do numero: %d\n.", ERRO_NULL);
        return FALSE;
    }
    
    #ifdef DEBUG
        printf("Adicionando a parte: %d\n\n", parte_do_numero);
    #endif

    NO* no = criar_no();
    
    if (big_number->qnt_partes == 0){
        big_number->inicio = no;
        big_number->fim = no;
    }
    else{
        big_number->fim->proximo = no;
        big_number->fim = no;
    }

    no->parte = parte_do_numero;
    big_number->qnt_partes++;

    return TRUE;
}

int big_number_obter_parte(BIG_NUMBER* big_number, int posicao){
    if (big_number == NULL){
        printf("Erro ao obter parte: %d.\n", ERRO_NULL);
        return 0;
    }

    if (posicao > big_number->qnt_partes || posicao < 1){
        printf("Erro ao obter parte: %d.\n", ERRO_NUM);
        return 0;
    }

    NO* auxiliar = big_number->inicio;

    while (--posicao) auxiliar = auxiliar->proximo;

    return auxiliar->parte;
}

void big_number_exibir_parte(BIG_NUMBER* big_number, int posicao){
    if (big_number == NULL){
        printf("Erro ao exibir parte: %d\n.", ERRO_NULL);
    }
    else if (posicao > big_number->qnt_partes || posicao < 1){
        printf("Erro ao exibir parte: %d\n.", ERRO_NUM);
    }
    else if (posicao == big_number->qnt_partes){
        printf("%d", big_number_obter_parte(big_number, posicao));
    }
    else{
         printf("%04d", big_number_obter_parte(big_number, posicao));
    }
}

int big_number_remover_parte(BIG_NUMBER* big_number, int posicao){
    if (big_number == NULL){
        printf("Erro ao remover parte: %d\n.", ERRO_NULL);
        return 0;
    }

    if (posicao > big_number->qnt_partes || posicao < 1){
        printf("Erro ao remover parte: %d\n.", ERRO_NUM);
        return 0;
    }

    #ifdef DEBUG
        printf("Removendo no %d...\n", posicao);
    #endif

    NO* auxiliar = big_number->inicio;
    NO* removido;

    if (posicao == 1){
        big_number->inicio = auxiliar->proximo;
        removido = auxiliar;
    } 
    else{
        while (--posicao - 1) auxiliar = auxiliar->proximo;
        removido = auxiliar->proximo;
        auxiliar->proximo = removido->proximo;
    }

    if (removido->proximo == NULL) big_number->fim = auxiliar;

    int parte = removido->parte;
    big_number->qnt_partes--;

    destruir_no(&removido);
    
    return parte;
}

int big_number_obter_inicio(BIG_NUMBER* big_number){
    if (big_number == NULL){
        printf("Erro ao obter inicio do big number: %d\n.", ERRO_NULL);
        return 0;
    }

    #ifdef DEBUG
        printf("inicio: %d\n", big_number->inicio->parte);
    #endif

    return big_number->inicio->parte;
}

int big_number_obter_fim(BIG_NUMBER* big_number){
    if (big_number == NULL){
        printf("Erro ao obter fim do big number: %d\n.", ERRO_NULL);
        return 0;
    }

    #ifdef DEBUG
        printf("fim: %d\n", big_number->fim->parte);
    #endif

    return big_number->fim->parte;
}

int big_number_obter_qnt_partes(BIG_NUMBER* big_number){
    if (big_number == NULL){
        printf("Erro ao obter quantidade de partes do big number: %d\n.", ERRO_NULL);
        return 0;
    }

    #ifdef DEBUG
        printf("partes: %d\n", big_number->qnt_partes);
    #endif

    return big_number->qnt_partes;
}

int big_number_obter_sinal(BIG_NUMBER* big_number){
    if (big_number == NULL){
        printf("Erro ao obter quantidade de partes do big number: %d\n.", ERRO_NULL);
        return POSITIVO;
    }

    return big_number->sinal;
}
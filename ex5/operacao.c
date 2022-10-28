#include "operacao.h"

boolean opcao_soma(char* operacao){
    if (operacao == NULL){
        printf("Erro ao verificar opcao de soma: %d.\n", ERRO_NULL);
        return FALSE;
    }

    if (strcmp(operacao, "soma") == 0){

        #ifdef DEBUG
            printf("Opcao 'soma' selecionada.\n");
        #endif

        return TRUE;
    }
    else{
        return FALSE;;
    }
}

boolean opcao_igual(char* operacao){
    if (operacao == NULL){
        printf("Erro ao verificar opcao de igualdade: %d.\n", ERRO_NULL);
        return FALSE;
    }

    if (strcmp(operacao, "igual") == 0){

        #ifdef DEBUG
            printf("Opcao 'igual' selecionada.\n");
        #endif

        return TRUE;
    }
    else{
        return FALSE;;
    }
}

boolean opcao_maior(char* operacao){
    if (operacao == NULL){
        printf("Erro ao verificar opcao 'maior': %d.\n", ERRO_NULL);
        return FALSE;
    }

    if (strcmp(operacao, "maior") == 0){
        
        #ifdef DEBUG
            printf("Opcao 'maior' selecionada.\n");
        #endif

        return TRUE;
    }
    else{
        return FALSE;;
    }
}

boolean opcao_menor(char* operacao){
    if (operacao == NULL){
        printf("Erro ao verificar opcao 'menor': %d.\n", ERRO_NULL);
        return FALSE;
    }

    if (strcmp(operacao, "menor") == 0){

        #ifdef DEBUG
            printf("Opcao 'menor' selecionada.\n");
        #endif

        return TRUE;
    }
    else{
        return FALSE;;
    }
}

BIG_NUMBER* operacao_soma(BIG_NUMBER* operando_1, BIG_NUMBER* operando_2){
    if (operando_1 == NULL || operando_2 == NULL){
        printf("Erro ao realizar operacao 'soma': %d.\n", ERRO_NULL);
        return FALSE;
    }

    BIG_NUMBER* resultado = big_number_criar_numero();

    int partes_1 = big_number_obter_qnt_partes(operando_1);
    int partes_2 = big_number_obter_qnt_partes(operando_2);

    int menor = partes_1 < partes_2 ? partes_1 : partes_2; 
    int maior = partes_1 > partes_2 ? partes_1 : partes_2; 
    
    boolean sobra = FALSE;

    for (int i = 1; i < menor + 1; i++){
        
        int parte = big_number_obter_parte(operando_1, i) + big_number_obter_parte(operando_2, i);

        if (sobra){
            parte++;
            sobra = FALSE;
        }
        
        if (parte / 1000 < 10) {
            big_number_adicionar_parte(resultado, parte);
        }
        else {
            parte -= 10000;
            big_number_adicionar_parte(resultado, parte);
            sobra = TRUE;
        }
    }

    
    BIG_NUMBER* numero_maior = partes_1 > partes_2 ? operando_1 : operando_2;

    for (int i = menor + 1; i < maior + 1; i++){
        
        #ifdef DEBUG
            printf("i: %d\n", i);
        #endif

        int parte = big_number_obter_parte(numero_maior, i);

        if (sobra){
            parte++;
            sobra = FALSE;
        }
        
        if (parte / 1000 < 10) {
            big_number_adicionar_parte(resultado, parte);
        }
        else {
            parte -= 10000;
            big_number_adicionar_parte(resultado, parte);
            sobra = TRUE;
        }
    }

    if (sobra) big_number_adicionar_parte(resultado, 1);

    return resultado;
}

boolean operacao_igual(BIG_NUMBER* operando_1, BIG_NUMBER* operando_2){
    if (operando_1 == NULL || operando_2 == NULL){
        printf("Erro ao realizar operacao 'igual': %d.\n", ERRO_NULL);
        return FALSE;
    }

    if (big_number_obter_qnt_partes(operando_1) != big_number_obter_qnt_partes(operando_2)){
        return FALSE;
    }

    int auxiliar = big_number_obter_qnt_partes(operando_1) + 1;

    while (--auxiliar){
        if (big_number_obter_parte(operando_1, auxiliar) != big_number_obter_parte(operando_2, auxiliar))
            return FALSE;
    }

    return TRUE;
}

boolean operacao_maior(BIG_NUMBER* operando_1, BIG_NUMBER* operando_2){
    if (operando_1 == NULL || operando_2 == NULL){
        printf("Erro ao realizar operacao 'maior': %d.\n", ERRO_NULL);
        return FALSE;
    }

    if (big_number_obter_qnt_partes(operando_1) < big_number_obter_qnt_partes(operando_2))
        return FALSE;

    if (big_number_obter_qnt_partes(operando_1) > big_number_obter_qnt_partes(operando_2))
        return TRUE;
    
    int auxiliar = big_number_obter_qnt_partes(operando_1) + 1;

    while (--auxiliar){
        if (big_number_obter_parte(operando_1, auxiliar) > big_number_obter_parte(operando_2, auxiliar))
            return TRUE;
        if (big_number_obter_parte(operando_1, auxiliar) < big_number_obter_parte(operando_2, auxiliar))
            return FALSE;
    }

    return FALSE;
}

boolean operacao_menor(BIG_NUMBER* operando_1, BIG_NUMBER* operando_2){
    if (operando_1 == NULL || operando_2 == NULL){
        printf("Erro ao realizar operacao 'menor': %d.\n", ERRO_NULL);
        return TRUE;
    }

    if (big_number_obter_qnt_partes(operando_1) < big_number_obter_qnt_partes(operando_2))
        return TRUE;

    if (big_number_obter_qnt_partes(operando_1) > big_number_obter_qnt_partes(operando_2))
        return FALSE;
    
    int auxiliar = big_number_obter_qnt_partes(operando_1) + 1;

    while (--auxiliar){
        if (big_number_obter_parte(operando_1, auxiliar) > big_number_obter_parte(operando_2, auxiliar))
            return FALSE;
        if (big_number_obter_parte(operando_1, auxiliar) < big_number_obter_parte(operando_2, auxiliar))
            return TRUE;
    }

    return FALSE;
}

void operar_dois_big_numbers(){
    BIG_NUMBER* operando_1 = big_number_criar_numero();
    BIG_NUMBER* operando_2 = big_number_criar_numero();
    BIG_NUMBER* resultado = NULL;
    
    char* operacao = ler_palavra();
    big_number_definir_numero(operando_1, ler_numero_completo());
    big_number_definir_numero(operando_2, ler_numero_completo());

    printf("Resultado :: ");

    if (opcao_soma(operacao)){
        resultado = operacao_soma(operando_1, operando_2);
        big_number_exibir_numero(resultado);
        big_number_destruir_numero(&resultado);
    }
    else if (opcao_igual(operacao)) exibir_booleano(operacao_igual(operando_1, operando_2));
    else if (opcao_maior(operacao)) exibir_booleano(operacao_maior(operando_1, operando_2));
    else if (opcao_menor(operacao)) exibir_booleano(operacao_menor(operando_1, operando_2));
    else printf("Opcao invalida. Nada sera feito.\n");

    apagar_palavra(&operacao);
    big_number_destruir_numero(&operando_1);
    big_number_destruir_numero(&operando_2);
};

int ler_qnt_de_operacoes(){
    int operacoes;
    scanf("%d", &operacoes);
    return operacoes;
}
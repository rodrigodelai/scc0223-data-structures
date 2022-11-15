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

    int sinal_op1 = big_number_obter_sinal(operando_1);
    int sinal_op2 = big_number_obter_sinal(operando_2);

    int partes_op1 = big_number_obter_qnt_partes(operando_1);
    int partes_op2 = big_number_obter_qnt_partes(operando_2);

    int partes_do_menor = partes_op1 < partes_op2 ? partes_op1 : partes_op2; 
    int partes_do_maior = partes_op1 > partes_op2 ? partes_op1 : partes_op2; 
    
    BIG_NUMBER* numero_com_mais_partes = partes_op1 > partes_op2 ? operando_1 : operando_2;
    BIG_NUMBER* resultado = big_number_criar_numero();

    boolean sobra = FALSE;
    boolean empresta = FALSE;

    if (sinal_op1 == sinal_op2){
        big_number_definir_sinal(resultado, sinal_op1);

        for (int i = 1; i <= partes_do_maior; i++){
        
            int parte = 0;

            if (i <= partes_do_menor)
                parte = big_number_obter_parte(operando_1, i) + big_number_obter_parte(operando_2, i);
            else 
                parte = big_number_obter_parte(numero_com_mais_partes, i);

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
    }
    else { // Numeros com sinais opostos
        BIG_NUMBER* numero_negativo = (sinal_op1 == NEGATIVO ? operando_1 : operando_2);
        BIG_NUMBER* numero_positivo = (sinal_op1 == POSITIVO ? operando_1 : operando_2);
        big_number_definir_sinal(numero_negativo, POSITIVO);

        int ajuste = 1;

        if (operacao_maior(numero_negativo, numero_positivo)){
            big_number_definir_sinal(resultado, NEGATIVO);
            ajuste = -1;
        }

        for (int i = 1; i <= partes_do_maior; i++){
        
            int parte = 0;

            if (i <= partes_do_menor)
                parte = (big_number_obter_parte(numero_positivo, i) - big_number_obter_parte(numero_negativo, i)) * ajuste;
            else 
                parte = big_number_obter_parte(numero_com_mais_partes, i);

            if (empresta){
                parte--;
                empresta = FALSE;
            }

            if (parte >= 0) {
                big_number_adicionar_parte(resultado, parte);
            }
            else {
                parte += 10000;
                big_number_adicionar_parte(resultado, parte);
                empresta = TRUE;
            }
        }

        if (big_number_obter_fim(resultado) == 0) big_number_remover_parte(resultado, partes_do_maior);
        big_number_definir_sinal(numero_negativo, NEGATIVO);
    }

    return resultado;
}

boolean operacao_igual(BIG_NUMBER* operando_1, BIG_NUMBER* operando_2){
    if (operando_1 == NULL || operando_2 == NULL){
        printf("Erro ao realizar operacao 'igual': %d.\n", ERRO_NULL);
        return FALSE;
    }

    if (big_number_obter_sinal(operando_1) != big_number_obter_sinal(operando_2)) return FALSE;
    if (big_number_obter_qnt_partes(operando_1) != big_number_obter_qnt_partes(operando_2)) return FALSE;

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

    int sinal_op1 = big_number_obter_sinal(operando_1);
    int sinal_op2 = big_number_obter_sinal(operando_2);

    if (sinal_op1 > sinal_op2) return TRUE;
    if (sinal_op1 < sinal_op2) return FALSE;

    int qnt_partes_op1 = big_number_obter_qnt_partes(operando_1); 
    int qnt_partes_op2 = big_number_obter_qnt_partes(operando_2); 

    if (qnt_partes_op1 * sinal_op1 < qnt_partes_op2 * sinal_op2) return FALSE;
    if (qnt_partes_op1 * sinal_op1 > qnt_partes_op2 * sinal_op2) return TRUE;
    
    int auxiliar = big_number_obter_qnt_partes(operando_1) + 1;

    while (--auxiliar){
        if (big_number_obter_parte(operando_1, auxiliar) * sinal_op1 > big_number_obter_parte(operando_2, auxiliar) * sinal_op2)
            return TRUE;
        if (big_number_obter_parte(operando_1, auxiliar) * sinal_op2 < big_number_obter_parte(operando_2, auxiliar) * sinal_op2)
            return FALSE;
    }

    return FALSE;
}

boolean operacao_menor(BIG_NUMBER* operando_1, BIG_NUMBER* operando_2){
    if (operando_1 == NULL || operando_2 == NULL){
        printf("Erro ao realizar operacao 'menor': %d.\n", ERRO_NULL);
        return TRUE;
    }

    return operacao_maior(operando_2, operando_1);
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
    if (operacoes < 0) operacoes = 0;
    return operacoes;
}
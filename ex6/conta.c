#include "conta.h"

#define SALDO_LIMITE 2147483647L // Valor máximo para o tipo "long int"

struct conta_st{
    char* nome;
    long cpf;
    int idade;
    long saldo;
};

CONTA* conta_criar(){
    CONTA* conta = (CONTA*) malloc(sizeof(CONTA));
    
    if (conta == NULL){
        printf("Erro ao criar conta: %d\n", ERRO_MEM);
        return conta;
    }

    conta->nome = NULL;
    conta->cpf = 0;
    conta->idade = 0;
    conta->saldo = 0;

    return conta;
}

boolean conta_definir_cpf(CONTA* conta, long cpf){
    if (conta == NULL){
        printf("Erro ao definir cpf: %d.\n", ERRO_NULL);
        return FALSE;
    }

    if (cpf < 1){
        printf("Erro ao definir cpf: %d.\n", ERRO_NUM);
        return FALSE;
    }

    conta->cpf = cpf;

    return TRUE;
}

boolean conta_definir_nome(CONTA* conta, char* nome){
    if (conta == NULL || nome == NULL){
        printf("Erro ao definir nome: %d.\n", ERRO_NULL);
        return FALSE;
    }

    if (conta->nome != NULL) apagar_dado(&conta->nome);

    conta->nome = nome;
    return TRUE;
}

boolean conta_definir_idade(CONTA* conta, int idade){
    if (conta == NULL){
        printf("Erro ao definir idade: %d.\n", ERRO_NULL);
        return FALSE;
    }

    if (idade > 150 || idade < 1){
        printf("Erro ao definir idade: %d.\n", ERRO_NUM);
        return FALSE;
    }

    conta->idade = idade;

    return TRUE;
}

boolean conta_definir_saldo(CONTA* conta, long saldo){
     if (conta == NULL){
        printf("Erro ao definir cpf: %d.\n", ERRO_NULL);
        return FALSE;
    }

    if (saldo > SALDO_LIMITE || saldo < -SALDO_LIMITE){
        printf("Erro ao definir saldo: %d.\n", ERRO_NUM);
        return FALSE;
    }

    conta->saldo = saldo;

    return TRUE;
}

long conta_extrair_cpf(char* str_cpf){
    if (str_cpf == NULL){
        printf("Erro ao extrair cpf: %d.\n", ERRO_NULL);
        return 0;
    }

     if (strlen(str_cpf) != 14){
        printf("Erro ao extrair cpf: %d.\n", ERRO_SIM);
        return 0;
    }
    
    char* auxiliar = (char*) malloc(sizeof(char) * 12);

    strncpy(auxiliar, str_cpf, 3);
    strncpy(auxiliar + 3, str_cpf + 4, 3);
    strncpy(auxiliar + 6, str_cpf + 8, 3);
    strncpy(auxiliar + 9, str_cpf + 12, 2);
    auxiliar[11] = '\0';

    long cpf= atol(auxiliar);

    apagar_dado(&auxiliar);
    apagar_dado(&str_cpf);

    return cpf;
}

long conta_extrair_saldo(char* str_saldo){
    if (str_saldo == NULL){
        printf("Erro ao extrair saldo: %d.\n", ERRO_NULL);
        return 0;
    }

    int tamanho = strlen(str_saldo);

     if (tamanho > 11){
        printf("Erro ao extrair saldo: %d.\n", ERRO_SIM);
        return 0;
    }

    char* auxiliar = (char*) calloc(12, sizeof(char));

    strncpy(auxiliar, str_saldo, tamanho-3);
    strncpy(auxiliar + tamanho - 3, str_saldo + tamanho - 2, 2);

    auxiliar[11] = '\0';

    long int saldo = atol(auxiliar);

    apagar_dado(&auxiliar);
    apagar_dado(&str_saldo);

    return saldo;
}

long conta_obter_cpf(CONTA* conta){
    if (conta == NULL){
        printf("Erro ao obter cpf: %d.\n", ERRO_NULL);
        return 0;
    }

    return conta->cpf;    
}

char* conta_obter_nome(CONTA* conta){
    if (conta == NULL){
        printf("Erro ao obter nome: %d.\n", ERRO_NULL);
        return NULL;
    }

    return conta->nome;    
}

int conta_obter_idade(CONTA* conta){
    if (conta == NULL){
        printf("Erro ao obter idade: %d.\n", ERRO_NULL);
        return 0;
    }

    return conta->idade;
}

long conta_obter_saldo(CONTA* conta){
    if (conta == NULL){
        printf("Erro ao obter saldo: %d.\n", ERRO_NULL);
        return 0;
    }

    return conta->saldo;    
}

char* conta_converter_cpf(long cpf){
    if (cpf < 1){
        printf("Erro ao converter cpf: %d.\n", ERRO_NUM);
        return NULL;
    }

    char* auxiliar = (char*) malloc(sizeof(char) * 12);
    sprintf(auxiliar, "%ld", cpf);

    char* str_cpf = (char*) malloc(sizeof(char) * 15);
    strcpy(str_cpf, "000.000.000-00");

    int tamanho = strlen(auxiliar);
    int indice = 13;

    while (tamanho--){
        if ((indice + 1) % 4 == 0) indice--;
        str_cpf[indice] = auxiliar[tamanho];
        indice--;
    }

    apagar_dado(&auxiliar);

    return str_cpf;
}

char* conta_converter_saldo(long saldo){
    if (saldo > SALDO_LIMITE || saldo < -SALDO_LIMITE){
        printf("Erro ao converter saldo: %d.\n", ERRO_NUM);
        return NULL;
    }

    char* auxiliar = (char*) malloc(sizeof(char) * 11);
    sprintf(auxiliar, "%ld", saldo);

    int tamanho = strlen(auxiliar);
    char* str_saldo = (char*) calloc((tamanho + 5), sizeof(char));

    str_saldo[0] = 'R';
    str_saldo[1] = '$';
    str_saldo[2] = ' ';

    int indice = tamanho + 3;
    int marcador = tamanho + 1;

    while (tamanho--){
        if (indice == marcador){
            str_saldo[indice] = '.';
            indice--;
        }
        str_saldo[indice] = auxiliar[tamanho];
        indice--;
    }

    apagar_dado(&auxiliar);

    return str_saldo;
}


void conta_exibir(CONTA* conta){
    if (conta == NULL){
        printf("Erro ao exibir conta: %d.\n", ERRO_NULL);
    }
    else{
        char* nome = conta_obter_nome(conta);   
        char* cpf = conta_converter_cpf(conta_obter_cpf(conta));
        int idade = conta_obter_idade(conta);
        char* saldo = conta_converter_saldo(conta_obter_saldo(conta));

        printf("Conta :: %s\nCPF :: %s\nIdade :: %d\nSaldo atual :: %s\n", nome, cpf, idade, saldo);

        apagar_dado(&cpf);
        apagar_dado(&saldo);
    }
}

boolean conta_destruir(CONTA** conta){
    if (conta == NULL || *conta == NULL){
        printf("Erro ao exibir conta: %d.\n", ERRO_NULL);
        return FALSE;
    }

    apagar_dado(&((*conta)->nome));
    (*conta)->nome = NULL;
    (*conta)->cpf = 0;
    (*conta)->idade = 0;
    (*conta)->saldo = 0;

    free(*conta);
    *conta = NULL;

    return TRUE;
}
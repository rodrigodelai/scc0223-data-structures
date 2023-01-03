#include "util.h"

int ler_opcao(){
    int opcao = 0;
    scanf(" %d", &opcao);
    return opcao;
}

char* ler_texto(FILE* arquivo){
    char separador = ';'; // Caracter que sinaliza o fim do texto
    char* texto = NULL;
    char caractere_atual = fgetc(arquivo);
    int indice_atual = 0;

    while (caractere_atual == separador || caractere_atual == '\n' || caractere_atual == '\r') // Limpa o buffer
        caractere_atual = fgetc(arquivo); 

    if (caractere_atual == EOF) // Sinaliza o fim do arquivo
        return NULL; 

    do {
        texto = (char*) realloc(texto, (indice_atual + 2) * sizeof(char));
        texto[indice_atual] = caractere_atual;
        
        indice_atual++;
        caractere_atual = fgetc(arquivo);

        if (caractere_atual == '\r') // Tratamento para ambiente Windows
            caractere_atual = fgetc(arquivo);

    } while (caractere_atual != separador && caractere_atual != '\n' && caractere_atual != EOF);

    texto[indice_atual] = '\0';

    return texto;
}

void exibir_texto(char* texto){
    if (texto == NULL) printf("Erro ao exibir texto: %d\n", ERRO_NULL);
    else printf("%s\n", texto);
}

boolean apagar_texto(char** texto){
    if (texto == NULL || *texto == NULL){
        printf("Erro ao excluir texto: %d\n", ERRO_NULL);
        return FALSE;
    }

    free(*texto);
    *texto = NULL;

    return TRUE;
}

int ler_inteiro(FILE* arquivo){
    int inteiro = 0;
    fscanf(arquivo," %d", &inteiro);
    return inteiro;
}

void exibir_booleano(boolean bool){
    if (bool == 1) printf("true\n");
    else if (bool == 0) printf("false\n");
    else printf("Erro ao imprimir booleano: Valor inesperado\n");
}

int max(int num1, int num2){
    return (num1 > num2 ? num1 : num2);
}
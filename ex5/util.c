#include "util.h"

char* ler_numero_completo(){
    char* numero = NULL;
    char caractere_atual = getchar();
    int indice_atual = 0;

    while (caractere_atual == 32 || caractere_atual == '\n' || caractere_atual == '\r') caractere_atual = getchar(); // Limpa o buffer
    if (caractere_atual == EOF) return NULL; // Sinaliza o fim do arquivo

    do{
        numero = (char*) realloc(numero, (indice_atual + 2) * sizeof(char));
        numero[indice_atual] = caractere_atual;
        
        indice_atual++;
        caractere_atual = getchar();

        if (caractere_atual == '\r') caractere_atual = getchar(); // Tratamento para ambiente Windows

    } while (caractere_atual != '\n' && caractere_atual != EOF && caractere_atual != 32);

    numero[indice_atual] = '\0';

    return numero;
}

char* ler_palavra(){
    char* palavra = (char*) calloc(TAM_MAX, sizeof(char));
    scanf(" %s", palavra);
    palavra = (char*) realloc(palavra, (strlen(palavra) + 1) * sizeof(char));
    return palavra;
}

void exibir_palavra(char* palavra){
    if (palavra == NULL) printf("Erro ao exibir palavra: %d\n", ERRO_NULL);
    else printf("%s\n", palavra);
}

boolean apagar_palavra(char** palavra){
    if (palavra == NULL || *palavra == NULL){
        printf("Erro ao excluir palavra: %d\n", ERRO_NULL);
        return FALSE;
    }

    free(*palavra);
    *palavra = NULL;

    return TRUE;
}

void exibir_booleano(boolean bool){
    if (bool == 1) printf("True\n");
    else if (bool == 0) printf("False\n");
    else printf("Erro ao imprimir booleano: Valor inesperado\n");
}
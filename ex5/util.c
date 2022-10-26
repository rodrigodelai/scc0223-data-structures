#include "util.h"

char* ler_parte_do_numero();

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
    if (bool == 1) printf("true\n");
    else if (bool == 0) printf("false\n");
    else printf("Erro ao imprimir booleano: Valor inesperado\n");
}
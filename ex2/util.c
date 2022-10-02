#include "util.h"

char* ler_linha(){
    char* linha = NULL;
    char caractere_atual = getchar();
    int indice_atual = 0;
    //int tam_disponivel = 1;

    while (caractere_atual == 32 || caractere_atual == '\n' || caractere_atual == '\r') caractere_atual = getchar(); // Limpa o buffer
    if (caractere_atual == EOF) return NULL; // Sinaliza o fim do arquivo

    do{
        linha = (char*) realloc(linha, (indice_atual + 2) * sizeof(char));
        linha[indice_atual] = caractere_atual;
        
        indice_atual++;
        caractere_atual = getchar();

        if (caractere_atual == '\r') caractere_atual = getchar(); // Tratamento para ambiente Windows

    } while (caractere_atual != '\n' && caractere_atual != EOF);

    linha[indice_atual] = '\0';

    if(strcmp(linha, "F") == 0){ // Condição para pular etapa
        free(linha);
        linha = NULL; 
    }

    return linha;
}

void exibir_linha(char* linha){
    if (linha == NULL) printf("Erro ao exibir linha: %d\n", ERRO_NULL);
    else printf("%s\n", linha);
}

boolean apagar_linha(char** linha){
    if (linha == NULL || *linha == NULL){
        printf("Erro ao excluir linha: %d\n", ERRO_NULL);
        return FALSE;
    }

    free(*linha);
    *linha = NULL;

    return TRUE;
}

int ler_inteiro(){
    int inteiro = 0;
    scanf(" %d", &inteiro);
    return inteiro;
}

void exibir_booleano(boolean bool){
    if (bool == 1) printf("true\n");
    else if (bool == 0) printf("false\n");
    else printf("Erro ao imprimir booleano: Valor inesperado\n");
}
#include "util.h"

char* ler_linha(){
    char* linha = NULL;
    char caractere_atual = getchar();
    int indice_atual = 0;
    int tam_disponivel = 1;

    while (caractere_atual == 32 || caractere_atual == '\n' || caractere_atual == '\r') caractere_atual = getchar(); // Limpa o buffer
    if (caractere_atual == EOF) return NULL; // Sinaliza o fim do arquivo

    do{
        if (tam_disponivel <= indice_atual+1){
            linha = (char*) realloc(linha, (tam_disponivel+5) * sizeof(char));
            tam_disponivel+=5;
        }

        linha[indice_atual] = caractere_atual;
        caractere_atual = getchar();
        indice_atual++;

        if (caractere_atual == '\r') caractere_atual = getchar(); // Tratamento para ambiente Windows

    } while (caractere_atual != '\n' && caractere_atual != EOF);

    linha[indice_atual] = '\0';

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

void exibir_booleano(boolean bool){
    if (bool == 1) printf("true\n");
    else if (bool == 0) printf("false\n");
    else printf("Erro ao imprimir booleano: Valor inesperado\n");
}
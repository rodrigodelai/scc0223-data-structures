#include "catalogo.h"

int main(){

    CATALOGO* catalogo = catalogo_criar();

    char* texto = NULL;

    // Leitura e armazenamento dos dados
    while ((texto = ler_linha()) != NULL){
        JOGO* jogo = jogo_criar();
        jogo_alterar_nome(jogo, texto);
        jogo_alterar_empresa(jogo, ler_linha());
        jogo_alterar_ano(jogo, ler_linha());
        catalogo_adicionar(catalogo, jogo);
    }

    // Aplicação de filtros e exibição dos dados
    while ((texto = ler_linha()) != NULL){
        if (opcao_filtrar_por_empresa(texto)){
            catalogo_exibir_por_empresa(catalogo, ler_linha());
        }
        else if (opcao_filtrar_por_ano(texto)){
            catalogo_exibir_por_ano(catalogo, ler_linha());
        }
        else {
            printf("Opção invalida. Digite 'A' para filtrar o catálogo por ano e 'E' para filtrar por empresa.\n");
            apagar_linha(&texto);
        }
    }

    catalogo_destruir(&catalogo);
    
    return 0;
}
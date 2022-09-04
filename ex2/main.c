#include "catalogo.h"

int main(){

    CATALOGO* catalogo = catalogo_criar();

    char* nome_do_jogo = NULL;

    // Leitura e armazenamento dos dados
    while ((nome_do_jogo = ler_linha()) != NULL){
        JOGO* jogo = jogo_criar();
        jogo_alterar_nome(jogo, nome_do_jogo);
        jogo_alterar_empresa(jogo, ler_linha());
        jogo_alterar_ano(jogo, ler_linha());
        catalogo_adicionar(catalogo, jogo);
    }

    catalogo_exibir(catalogo);
    catalogo_destruir(&catalogo);
    
    return 0;
}
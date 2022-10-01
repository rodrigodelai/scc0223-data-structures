#include "catalogo.h"

int main(){

    CATALOGO* catalogo = catalogo_criar();
    ler_novo_catalogo(catalogo);
    aplicar_filtros_de_exibicao(catalogo);
    catalogo_destruir(&catalogo);
    
    return 0;
}
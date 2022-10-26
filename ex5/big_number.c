#include "big_number.h"

typedef struct no_st NO;

struct no_st{
    int parte;
    NO* anterior;
};

struct big_number_st{
    NO* inicio;
    int qnt_partes;
};

static NO* criar_no();
static boolean destruir_no(NO** no);
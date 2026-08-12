#include "carta.h"

/*
    Database de exemplo, como uma opção para substituir os arquivos .json, caso seja necessário.
*/

const carta DB_CARDS[] = {
    {.name = "Dragão de Fogo", .attack = 8, .vida = 6},
    {.name = "Escudeiro",      .attack = 2, .vida = 4},
};

const int TOTAL_CARDS = sizeof(DB_CARDS) / sizeof(carta);
#include <stdio.h>
#include <stdlib.h>

#include "campo.h"



/* =============================================== ESTRUTURAS DE DADOS =============================================== */
/** CAMPO: Estrutura de dados para representar o campo de jogo.
 * 
 * @param cartas     Array de ponteiros para cartas no campo.
 * @param tamanho    Tamanho atual do campo.
 * @param capacidade Capacidade máxima do campo.
 */
typedef struct CampoStr{
    Carta** cartas;
    int tamanho;
    int capacidade;
} CampoStr;
/* =================================================================================================================== */



#define ROWS 3
#define COLS 4
/* =============================================== FUNÇÕES PRINCIPAIS ================================================ */
Campo criarCampo(){
    // 1: Aloca memória para o campo de jogo (array de ponteiros para cartas)
    CampoStr* campo = (CampoStr*)malloc(sizeof(CampoStr));
    // 1.1: Verifica se a alocação de memória foi bem-sucedida
    if(campo == NULL){
        printf("[ERROR]: criarCampo() [game.c]\n");
        printf("First game field memory allocation failed\n");
        return NULL;
    }

    campo->cartas = (Carta**)malloc(ROWS * sizeof(Carta*));

    // 2: Inicializa a matriz do campo de jogo, 
    // alocando memória para cada linha e inicializando as posições como NULL
    for(int i = 0; i < ROWS; i++){
        // 2.1: Aloca memória para cada linha do campo de jogo (array de ponteiros para cartas)
        campo->cartas[i] = (Carta*)malloc(COLS * sizeof(Carta));
        // 2.2: Verifica se a alocação de memória foi bem-sucedida
        if(campo->cartas[i] == NULL){
            printf("[ERROR]: criarCampo() [game.c]\n");
            printf("Second game field memory allocation failed\n");
            return NULL;
        }
        // 2.3: Inicializa cada posição do campo de jogo como NULL (sem carta)
        for(int j = 0; j < COLS; j++) {campo->cartas[i][j] = NULL;}
    }

    campo->tamanho = 0;
    campo->capacidade = 0;

    // 3: Retorna o ponteiro para o campo de jogo criado
    return campo;
}

bool adicionarCarta(Campo campo, Carta carta, bool playerFlag, int pos){
    CampoStr* c = (CampoStr*)campo;
    
    // 1: Verifica se a carta, o campo e a posição são válidos antes de adicionar a carta ao campo de jogo
    if(Carta_isNull(carta)){
        printf("[ERROR]: adicionarCarta() [game.c]\n");
        printf("Card is NULL, cannot add to field\n");
        return false;
    }
    if(c == NULL){
        printf("[ERROR]: adicionarCarta() [game.c]\n");
        printf("Field is NULL, cannot add to field\n");
        return false;
    }
    if(pos < 0 || pos > ROWS){
        printf("[ERROR]: adicionarCarta() [game.c]\n");
        printf("Position %d is out of bounds for the field of rows: [0 - %d]\n", pos, ROWS);
        return false;
    }

    // 2: Define a posição e a flag do jogador para a carta antes de adicioná-la ao campo de jogo
    setPos(carta, pos);
    setPlayerFlag(carta, playerFlag);

    // 3: Adiciona a carta ao campo de jogo na posição especificada, dependendo da flag do jogador (playerFlag)
    // flag = true:  Carta do jogador (Linha inferior do campo = ROWS-1)
    if(playerFlag){
        c->cartas[ROWS-1][pos] = carta;
        // printf("[INFO]: adicionarCarta() [game.c]\n");
        // printf("Card added to player's field at position %d\n\n", pos);
        return true;
    }
    // flag = false: Carta do oponente (Linha superior do campo = 0)
    else{
        c->cartas[0][pos] = carta;
        // printf("[INFO]: adicionarCarta() [game.c]\n");
        // printf("Card added to opponent's field at position %d\n\n", pos);
        return true;
    }
}

Carta removerCarta(Campo campo, Carta carta, bool playerFlag, int pos){
    CampoStr* c = (CampoStr*)campo;

    // 1: Verifica se a carta, o campo e a posição são válidos antes de remover a carta do campo de jogo
    if(Carta_isNull(carta)){
        printf("[ERROR]: removerCarta() [game.c]\n");
        printf("Card is NULL, cannot remove from field\n");
        return NULL;
    }
    if(c == NULL){
        printf("[ERROR]: removerCarta() [game.c]\n");
        printf("Field is NULL, cannot remove from field\n");
        return NULL;
    }
    if(pos < 0 || pos > ROWS){
        printf("[ERROR]: removerCarta() [game.c]\n");
        printf("Position %d is out of bounds for the field of rows: [0 - %d]\n", pos, ROWS);
        return NULL;
    }

    // 2: Remove a carta do campo de jogo na posição especificada, dependendo da flag do jogador (playerFlag)
    // flag = true:  Carta do jogador (Linha inferior do campo = ROWS-1)
    if(playerFlag){
        Carta carta = c->cartas[ROWS-1][pos];
        c->cartas[ROWS-1][pos] = NULL;      // Define a posição como NULL para indicar que não há carta nessa posição
        // printf("[INFO]: removerCarta() [game.c]\n");
        // printf("Card removed from player's field at position: [%d][%d]\n\n", ROWS-1, pos);
        return carta;
    }
    // flag = false: Carta do oponente (Linha superior do campo = 0)
    else{
        Carta carta = c->cartas[0][pos];
        c->cartas[0][pos] = NULL;       // Define a posição como NULL para indicar que não há carta nessa posição
        // printf("[INFO]: removerCarta() [game.c]\n");
        // printf("Card removed from opponent's field at position: [%d][%d]\n\n", 0, pos);
        return carta;
    }
}

static bool CartaIsInCampo(CampoStr* c, Carta carta){
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            if(getID(c->cartas[i][j]) == getID(carta)) return true;
        }
    }

    return false;
}

int atacarCarta(Campo campo, Carta atacante, Carta alvo){
    CampoStr* c = (CampoStr*)campo;

    // 1: Verifica se a carta atacante e a carta alvo são válidas antes de realizar o ataque
    if(c == NULL){
        printf("[ERROR]: atacarCarta() [game.c]\n");
        printf("Game field is NULL, cannot perform attack\n");
        return -1;
    }
    if(Carta_isNull(atacante)){
        printf("[ERROR]: atacarCarta() [game.c]\n");
        printf("Attacker card is NULL, cannot perform attack\n");
        return -1;
    }
    if(Carta_isNull(alvo)){
        printf("[ERROR]: atacarCarta() [game.c]\n");
        printf("Target card is NULL, cannot perform attack\n");
        return -1;
    }
    if(!CartaIsInCampo(c, atacante)){
        printf("[ERROR]: atacarCarta() [game.c]\n");
        printf("Attacker card is not on field, cannot perform attack\n");
        return -1;
    }
    if(!CartaIsInCampo(c, atacante)){
        printf("[ERROR]: atacarCarta() [game.c]\n");
        printf("Attacker card is not on field, cannot perform attack\n");
        return -1;
    }

    printf("[INFO]: atacarCarta() [game.c]\n");
    printf("Card %d attacked Card %d\n", getID(atacante), getID(alvo));
    printf("Attack: [%d], Life: [%d]\n", getAtk(atacante), getVida(alvo));

    // 2: Realiza o ataque da carta atacante contra a carta alvo, aplicando as regras do jogo
    // 2.1: Se o ataque da carta atacante for maior ou igual à vida da carta alvo, a carta alvo é removida do campo de jogo
    if(getAtk(atacante) >= getVida(alvo)){
        printf("Card [%d] killed by attack\n\n", getID(alvo));
        removerCarta(campo, alvo, getPlayerFlag(alvo), getPos(alvo));
        return getAtk(atacante);
    }
    // 2.2: Caso contrário, a vida da carta alvo é reduzida pelo valor do ataque da carta atacante
    else{
        setVida(alvo, getVida(alvo) - getAtk(atacante));
        printf("Card [%d] damaged by attack, remaining life: %d\n\n", getID(alvo), getVida(alvo));
        return getAtk(atacante);
    }
}

void liberarCampo(Campo campo){
    CampoStr* c = (CampoStr*)campo;

    // 1: Verifica se o campo de jogo é válido antes de liberar a memória alocada para ele
    if(c == NULL){
        printf("[ERROR]: liberarCampo() [game.c]\n");
        printf("Game field is NULL, cannot free memory\n");
        return;
    }

    // 2: Libera a memória alocada para cada carta no campo de jogo, chamando a função killCarta() para cada carta
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            if(c->cartas[i][j] != NULL){
                // printf("[INFO]: liberarCampo() [game.c]\n");
                // printf("Freeing card memory at position [%d][%d]\n\n", i, j);
                killCarta(c->cartas[i][j]);
                c->cartas[i][j] = NULL;
                printCampo(campo);
            }
        }free(c->cartas[i]);
    }free(c->cartas);

    free(c);

    // printf("[INFO]: liberarCampo() [game.c]\n");
    // printf("Game field memory freed successfully\n\n");
}
/* =================================================================================================================== */



/* =============================================== FUNÇÕES SECUNDÁRIAS =============================================== */
void printCampo(Campo campo){
    CampoStr* c = (CampoStr*)campo;

    // 1: Verifica se o campo de jogo é válido antes de imprimir seu estado atual
    if(c == NULL){
        printf("[ERROR]: printCampo() [game.c]\n");
        printf("Game field is NULL, cannot print\n");
        return;
    }

    // 2: Imprime o estado atual do campo de jogo, mostrando as cartas presentes e suas posições
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            printf("[%3d] ", getID(c->cartas[i][j]));
        }
        printf("\n");
    }printf("\n");
}

Carta getItemFromPositionCampo(Campo campo, int x, int y){
    CampoStr* c = (CampoStr*)campo;

    // 1: Verifica se o campo de jogo é válido antes de procurar e se os índices estão dentro do campo
    if(c == NULL){
        printf("[ERROR]: getItemFromPositionCampo() [game.c]\n");
        printf("Game field is NULL, cannot print\n");
        return NULL;
    }
    if(x > ROWS - 1 || y > COLS - 1 || x < 0 || y < 0){
        printf("[ERROR]: getItemFromPositionCampo() [game.c]\n");
        printf("Indexes out of bounds\n");
        return NULL;
    }

    // 2: Retorna o item na posição [x, y]
    return c->cartas[x][y];
}
/* =================================================================================================================== */

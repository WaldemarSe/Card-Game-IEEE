#include <stdio.h>
#include <stdlib.h>

#include "game.h"



/* =============================================== ESTRUTURAS DE DADOS =============================================== */
/** CAMPO: Estrutura de dados para representar o campo de jogo.
 * 
 * @param cartas     Array de ponteiros para cartas no campo.
 * @param tamanho    Tamanho atual do campo.
 * @param capacidade Capacidade máxima do campo.
 */
typedef struct campo{
    Carta* cartas;
    int tamanho;
    int capacidade;
}Campo;
/* =================================================================================================================== */



#define ROWS 3
#define COLS 4
/* =============================================== FUNÇÕES PRINCIPAIS ================================================ */
Carta** criarCampo(){
    // 1: Aloca memória para o campo de jogo (array de ponteiros para cartas)
    Carta** campo = (Carta**)malloc(ROWS * sizeof(Carta*));
    // 1.1: Verifica se a alocação de memória foi bem-sucedida
    if(campo == NULL){
        printf("[ERROR]: criarCampo() [game.c]\n");
        printf("First game field memory allocation failed\n");
        return NULL;
    }

    // 2: Inicializa a matriz do campo de jogo, 
    // alocando memória para cada linha e inicializando as posições como NULL
    for(int i = 0; i < ROWS; i++){
        // 2.1: Aloca memória para cada linha do campo de jogo (array de ponteiros para cartas)
        campo[i] = (Carta*)malloc(COLS * sizeof(Carta));
        // 2.2: Verifica se a alocação de memória foi bem-sucedida
        if(campo[i] == NULL){
            printf("[ERROR]: criarCampo() [game.c]\n");
            printf("Second game field memory allocation failed\n");
            return NULL;
        }
        // 2.3: Inicializa cada posição do campo de jogo como NULL (sem carta)
        for(int j = 0; j < COLS; j++) {campo[i][j] = NULL;}
    }

    // 3: Retorna o ponteiro para o campo de jogo criado
    return (Carta**)campo;
}

bool adicionarCarta(Carta** campo, Carta* carta, int pos){
    // 1: Verifica se a carta e o campo são válidos antes de adicionar a carta ao campo de jogo
    if(carta == NULL){
        printf("[ERROR]: adicionarCarta() [game.c]\n");
        printf("Card is NULL, cannot add to field\n");
        return false;
    }
    if(campo == NULL){
        printf("[ERROR]: adicionarCarta() [game.c]\n");
        printf("Field is NULL, cannot add to field\n");
        return false;
    }
    if(pos < 0 || pos > COLS-1){
        printf("[ERROR]: adicionarCarta() [game.c]\n");
        printf("Position %d is out of bounds for the field of columns: [0 : %d]\n\n", pos, COLS);
        return false;
    }

    // 3: Adiciona a carta ao campo de jogo na posição especificada, dependendo da flag do jogador (playerFlag)
    int coords[2];
    // flag = true:  Carta do jogador (Linha inferior do campo = ROWS-1)
    if(getPlayerFlag(carta)){
        campo[ROWS-1][pos] = carta;
        coords[0] = ROWS-1;
        coords[1] = pos;
        setPos(carta, coords);
        // printf("[INFO]: adicionarCarta() [game.c]\n");
        // printf("Card [%d] added to field at position [%d][%d]\n\n", getID(carta), coords[0], coords[1]);
        return true;
    }
    // flag = false: Carta do oponente (Linha superior do campo = 0)
    else{
        campo[0][pos] = carta;
        coords[0] = 0;
        coords[1] = pos;
        setPos(carta, coords);
        // printf("[INFO]: adicionarCarta() [game.c]\n");
        // printf("Card [%d] added to field at position [%d][%d]\n\n", getID(carta), coords[0], coords[1]);
        return true;
    }
}

bool removerCarta(Carta** campo, Carta* carta){
    // 1: Verifica se a carta e o campo são válidos antes de remover a carta do campo de jogo
    if(carta == NULL){
        printf("[ERROR]: removerCarta() [game.c]\n");
        printf("Card is NULL, cannot remove from field\n");
        return false;
    }
    if(campo == NULL){
        printf("[ERROR]: removerCarta() [game.c]\n");
        printf("Field is NULL, cannot remove from field\n");
        return false;
    }

    // 2: Remove a carta do campo
    int x = getPosX(carta);
    int y = getPosY(carta);
    killCarta(campo[x][y]);
    campo[x][y] = NULL;
    return true;
}

int atacarCartas(Carta** campo, bool ataqueFlag, Jogador* jogador){
    // 1: Verifica se a carta atacante e a carta alvo são válidas antes de realizar o ataque
    if(campo == NULL){
        printf("[ERROR]: atacarCarta() [game.c]\n");
        printf("Game field is NULL, cannot perform attack\n");
        return -1;
    }
    if(jogador == NULL){
        printf("[ERROR]: atacarCarta() [game.c]\n");
        printf("Player is NULL, cannot perform attack\n");
        return -1;
    }

    // 2: Realiza o ataque da carta atacante contra a carta alvo, aplicando as regras do jogo
    switch(ataqueFlag){
        case true:
            playerAtaque(campo);
            break;
        case false:
            oponenteAtaque(campo, jogador);
            break;
    }

    return 0;
}

void moverCartas(Carta **campo){
    // 1: Verifica se o campo é válido antes de mover as cartas para frente
    if(campo == NULL){
        printf("[ERROR]: moverCartas() [game.c]\n");
        printf("Field is NULL, cannot move cards\n");
        return;
    }

    // 2: Move as cartas para frente no campo de jogo
    int pos[2];
    for(int i = 0; i < COLS; i++){
        // 2.1: Verifica se há uma carta na posição atual antes de tentar movê-la para frente
        if(campo[0][i] != NULL){
            // 2.1: Verifica se a posição à frente está livre antes de mover a carta para frente
            if(campo[1][i] == NULL){
                campo[1][i] = campo[0][i];
                campo[0][i]   = NULL;
                pos[0] = 1;
                pos[1] = i;
                setPos(campo[1][i], pos);
            }
        }
    }
}

void liberarCampo(Carta** campo){
    // 1: Verifica se o campo de jogo é válido antes de liberar a memória alocada para ele
    if(campo == NULL){
        printf("[ERROR]: liberarCampo() [game.c]\n");
        printf("Game field is NULL, cannot free memory\n");
        return;
    }

    // 2: Libera a memória alocada para cada carta no campo de jogo, 
    // garantindo que todos os recursos sejam corretamente desalocados
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            if(campo[i][j] != NULL){
                killCarta(campo[i][j]);
                campo[i][j] = NULL;
                printCampo(campo);
            }
        }
    }

    // 3: Libera a memória alocada para cada linha do campo de jogo e,
    // em seguida, libera a memória alocada para o próprio campo
    for(int i = 0; i < ROWS; i++){
        free(campo[i]);
    }free(campo);
}
/* =================================================================================================================== */



/* =============================================== FUNÇÕES SECUNDÁRIAS =============================================== */
void printCampo(Carta** campo){
    // 1: Verifica se o campo de jogo é válido antes de imprimir seu estado atual
    if(campo == NULL){
        printf("[ERROR]: printCampo() [game.c]\n");
        printf("Game field is NULL, cannot print\n");
        return;
    }

    // 2: Imprime o estado atual do campo de jogo, mostrando as cartas presentes e suas posições
    printf("     CAMPO DE JOGO\n");
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            campo[i][j] == NULL ? printf("[   ]") : printf("[ %d ]", getID(campo[i][j]));
        }
        printf("\n");
    }printf("\n");
}

int playerAtaque(Carta** campo){
    // 1: Verifica se o campo de jogo é válido antes de realizar o ataque
    if(campo == NULL){
        printf("[ERROR]: playerAtaque() [game.c]\n");
        printf("Game field is NULL, cannot perform attack\n");
        return -1;
    }

    // 2: Cria ponteiros para a carta atacante e a carta alvo, inicializando-os como NULL
    Carta* atacante = NULL;
    Carta* alvo     = NULL;

    // 3: Percorre o campo de jogo, realizando o ataque da carta contra o alvo
    for(int i = 0; i < COLS; i++){
        // Verifica se há uma carta na última linha do campo (linha do jogador) para realizar o ataque
        if(campo[ROWS-1][i] != NULL){
            atacante = campo[ROWS-1][i];

            // Verifica se há uma carta a frente (linha do oponente) para realizar o ataque
            if(campo[ROWS-2][i] != NULL){
                alvo = campo[ROWS-2][i];

                printf("[INFO]: playerAtaque() [game.c]\n");
                printf("Card [%d] is attacking Card [%d]\n", getID(atacante), getID(alvo));
                printf("CARD [%d] ATK: %d\n", getID(atacante), getAtk(atacante));
                printf("CARD [%d] HP:  %d\n", getID(alvo), getVida(alvo));

                // Verifica se o ataque resultará na morte do alvo ou se ela sobreviverá ao ataque
                // CARTA MORRE
                if(getAtk(atacante) >= getVida(alvo)){
                    printf("Card [%d] killed!\n\n", getID(alvo));
                    removerCarta(campo, alvo);
                    alvo = NULL;
                }
                // CARTA SOBREVIVE
                else{
                    setVida(alvo, getVida(alvo) - getAtk(atacante));
                    printf("Card [%d] injured!\n", getID(alvo));
                    printf("Remaining life: %d\n\n", getVida(alvo));
                }
            }
        }
    }

    return 0;
}

int oponenteAtaque(Carta** campo, Jogador* jogador){
    // 1: Verifica se o campo de jogo e o jogador são válidos antes de realizar o ataque
    if(campo == NULL){
        printf("[ERROR]: playerAtaque() [game.c]\n");
        printf("Game field is NULL, cannot perform attack\n");
        return -1;
    }
    if(jogador == NULL){
        printf("[ERROR]: playerAtaque() [game.c]\n");
        printf("Player is NULL, cannot perform attack\n");
        return -1;
    }

    // 2: Cria ponteiros para a carta atacante e a carta alvo, inicializando-os como NULL
    Carta* atacante = NULL;
    Carta* alvo     = NULL;

    // 3: Percorre o campo de jogo, realizando o ataque da carta contra o alvo
    for(int i = 0; i < COLS; i++){
        // Verifica se há uma carta na linha do meio do campo para realizar o ataque
        if(campo[ROWS-2][i] != NULL){
            atacante = campo[ROWS-2][i];

            // Verifica se há uma carta a frente (linha do jogador) para realizar o ataque
            if(campo[ROWS-1][i] != NULL){
                alvo = campo[ROWS-1][i];

                printf("[INFO]: oponenteAtaque() [game.c]\n");
                printf("Card [%d] is attacking Card [%d]\n", getID(atacante), getID(alvo));
                printf("CARD [%d] ATK: %d\n", getID(atacante), getAtk(atacante));
                printf("CARD [%d] HP:  %d\n", getID(alvo), getVida(alvo));

                // Verifica se o ataque resultará na morte do alvo ou se ela sobreviverá ao ataque
                // CARTA MORRE
                if(getAtk(atacante) >= getVida(alvo)){
                    printf("Card [%d] killed!\n\n", getID(alvo));
                    removerCarta(campo, alvo);
                    alvo = NULL;
                }
                // CARTA SOBREVIVE
                else{
                    setVida(alvo, getVida(alvo) - getAtk(atacante));
                    printf("Card [%d] injured!\n", getID(alvo));
                    printf("Remaining life: %d\n\n", getVida(alvo));
                }
            }

            // Se não houver carta a frente, o ataque é direcionado ao jogador, reduzindo sua vida
            else{
                printf("[INFO]: oponenteAtaque() [game.c]\n");
                printf("Player's life [%d] reduced by [%d]\n", getVidaJogador(jogador), getAtk(atacante));
                setVidaJogador(jogador, getVidaJogador(jogador) - getAtk(atacante));
                printf("Player's remaining life: [%d]\n\n", getVidaJogador(jogador));
            }
        }
    }
    
    return 0;
}
/* =================================================================================================================== */

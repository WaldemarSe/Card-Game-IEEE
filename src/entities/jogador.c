#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cJSON.h>

#include "jogador.h"
#include "carta.h"

#include "cartainterface.h"

#define MAX_CARTAS 3

typedef struct JogadorStr{
    int vida;

    Lista mao;
    Lista baralho;
} JogadorStr;

Jogador criarJogador(int vida){
    JogadorStr* jogador = (JogadorStr*)malloc(sizeof(JogadorStr));
    
    if(jogador == NULL){
        printf("[ERROR]: criarJogador() [jogador.c]\n");
        printf("Failed to allocate memory for player\n");
        return NULL;
    }

    jogador->vida = vida;

    jogador->mao = criaLista();
    jogador->baralho = criaLista();
    
    return jogador;
}

void setVidaJogador(Jogador jogador, int vida){
    if(jogador == NULL){
        printf("[ERROR]: setVidaJogador() [jogador.c]\n");
        printf("Player is NULL, cannot set life\n");
        return;
    }

    JogadorStr* j = (JogadorStr*)jogador;
    j->vida = vida;
}

int getVidaJogador(Jogador jogador){
    if(jogador == NULL){
        printf("[ERROR]: getVidaJogador() [jogador.c]\n");
        printf("Player is NULL, cannot get life\n");
        return -1;
    }

    JogadorStr* j = (JogadorStr*)jogador;
    return j->vida;
}

Lista getMaoJogador(Jogador jogador){
    if(jogador == NULL){
        printf("[ERROR]: getMaoJogador() [jogador.c]\n");
        printf("Player is NULL, cannot get hand\n");
        return NULL;
    }

    JogadorStr* j = (JogadorStr*)jogador;
    return j->mao;
}

Lista getBaralhoJogador(Jogador jogador){
    if(jogador == NULL){
        printf("[ERROR]: getBaralhoJogador() [jogador.c]\n");
        printf("Player is NULL, cannot get deck\n");
        return NULL;
    }

    JogadorStr* j = (JogadorStr*)jogador;
    return j->baralho;
}

bool carregarBaralho(Jogador jogador, bool playerFlag, const char* caminhoArquivo){
    if(jogador == NULL){
        printf("[ERROR]: carregarBaralho() [jogador.c]\n");
        printf("Player is NULL, cannot load deck\n");
        return false;
    }
    
    JogadorStr* j = (JogadorStr*)jogador;
    
    // Leitura do arquivo JSON
    FILE* file = fopen(caminhoArquivo, "rb");
    if (!file) {
        printf("[ERROR]: carregarBaralho() [jogador.c]\n");
        printf("File not found\n");
        return false;
    }

    // Descobre o tamanho do arquivo
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Aloca memória para o conteúdo + terminador nulo '\0'
    char* buffer = (char*)malloc(length + 1);
    if (buffer) {
        fread(buffer, 1, length, file);
        buffer[length] = '\0';
    }

    fclose(file);

    cJSON* json = cJSON_Parse(buffer);
    free(buffer);

    if (!json || !cJSON_IsArray(json)) {
        printf("[ERROR]: carregarBaralho() [jogador.c]\n");
        printf("Failed to parse JSON\n");
        const char* erro = cJSON_GetErrorPtr();
        if (erro != NULL) {
            printf("Erro de sintaxe no JSON próximo a: %s\n", erro);
        }
        return false;
    }
    
    cJSON *item = NULL; 
    int contador = 0;

    // Itera sobre cada item do array JSON e adiciona à lista do jogador
    cJSON_ArrayForEach(item, json) {
        if (contador >= MAX_CARTAS) break; // Evita estouro de memória no array C

        // Dados da carta
        int id_carta;
        char nome[100] = "";
        int atk;
        int vida;
        char sprite_carta[150] = "";

        cJSON *id = cJSON_GetObjectItemCaseSensitive(item, "id");
        cJSON *name = cJSON_GetObjectItemCaseSensitive(item, "name");
        cJSON *attack = cJSON_GetObjectItemCaseSensitive(item, "attack");
        cJSON *health = cJSON_GetObjectItemCaseSensitive(item, "health");
        cJSON *sprite = cJSON_GetObjectItemCaseSensitive(item, "sprite");

        // Copia os dados para a struct do C
        if (cJSON_IsNumber(id)) id_carta = id->valueint;
        if (cJSON_IsString(name)) strncpy(nome, name->valuestring, 99);
        if (cJSON_IsNumber(attack)) atk = attack->valueint;
        if (cJSON_IsNumber(health)) vida = health->valueint;
        if (cJSON_IsString(sprite)) strncpy(sprite_carta, sprite->valuestring, 149);

        printf("[INFO]: carregarBaralho() [jogador.c]\n");
        printf("Card [%d] loaded: %s (ATK: %d, HP: %d, SPRITE: %s)\n", id_carta, nome, atk, vida, sprite_carta);

        Carta carta = criarCarta(nome, atk, vida, sprite_carta, playerFlag);

        inserirInicio(j->baralho, carta);

        Texture2D txr = LoadTexture(sprite_carta);
        Card_Init((Rectangle){0, 0, 100, 100}, txr);

        contador++;
    }

    cJSON_Delete(json);
    return true;
}

bool comprarCarta(Jogador jogador){
    if(jogador == NULL){
        printf("[ERROR]: comprarCarta() [jogador.c]\n");
        printf("Player is NULL, cannot draw card\n");
        return false;
    }

    JogadorStr* j = (JogadorStr*)jogador;

    if(isListaVazia(j->baralho)){
        printf("[INFO]: comprarCarta() [jogador.c]\n");
        printf("Deck is empty, cannot draw card\n");
        return false;
    }

    Carta carta = removerInicio(j->baralho);
    inserirInicio(j->mao, carta);

    return true;
}

void liberarJogador(Jogador jogador){
    if(jogador == NULL){
        printf("[ERROR]: liberarJogador() [jogador.c]\n");
        printf("Player is NULL, cannot free memory\n");
        return;
    }

    JogadorStr* j = (JogadorStr*)jogador;

    // Libera a memória da mão do jogador
    limparLista(j->mao, freeExtra, killCarta);

    // Libera a memória do baralho do jogador
    limparLista(j->baralho, freeExtra, killCarta);

    // Libera a memória do jogador
    free(j);
}

void embaralharBaralho(Jogador jogador){
    if(jogador == NULL){
        printf("[ERROR]: embaralharBaralho() [jogador.c]\n");
        printf("Player is NULL, cannot shuffle deck\n");
        return;
    }

    JogadorStr* j = (JogadorStr*)jogador;

    // Implementação do algoritmo de embaralhamento (Fisher-Yates)
    int tamanho = listaTamanho(j->baralho);

    for(int i = tamanho - 1; i > 0; i--){
        int jIndex = rand() % (i + 1);

        Item temp = getItemLista(j->baralho, i);
        Item ant = getItemLista(j->baralho, jIndex);

        setItemLista(j->baralho, i, ant);
        setItemLista(j->baralho, jIndex, temp);
    }
}

void printBaralho(Jogador jogador){
    if(jogador == NULL){
        printf("[ERROR]: printBaralho() [jogador.c]\n");
        printf("Player is NULL, cannot print deck\n");
        return;
    }

    JogadorStr* j = (JogadorStr*)jogador;

    printf("[INFO]: printBaralho() [jogador.c]\n");
    printf("Player's Deck:\n");

    percorrerLista(j->baralho, runExtra, printCarta);
}
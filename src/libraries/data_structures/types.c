#include "types.h"

#include <stdio.h>
#include <stdlib.h>

void freeReg(Item item, void* extra){
    UNUSED(extra);
    free(item);
}

void freeExtra(Item item, void* extra){
    void (*fFunc)(Item) = (void (*)(Item))extra;
    fFunc(item);
}

void runExtra(Item item, void* extra){
    void (*runFunc)(Item) = (void (*)(Item))extra;
    runFunc(item);
}

bool checkAllocation(void* var, const char* text){
    // Caso a varia'vel passada for nula, lanca uma mensagem de erro.
    if(var == NULL){
        printf("\n[!] ERRO DE ALOCACAO: %s", text);
        return true;
    }
    return false;
}

void loop(int repeats, loopFunction lFunc, void* extra){
    for(int i = 0; i < repeats; i++){
        lFunc(i, extra);
    }
}

int** mallocMatrix(int* matrix, int rows, int columns) {
    int** m = (int**)malloc(rows * sizeof(int*));
    
    for (int i = 0; i < rows; i++) {
        m[i] = (int*)malloc(columns * sizeof(int));
        
        for (int j = 0; j < columns; j++) {
            m[i][j] = matrix[i * columns + j];
        }
    }
    
    return m;
}
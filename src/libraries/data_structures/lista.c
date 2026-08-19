#include "lista.h"
#include <stdio.h>
#include <string.h>

typedef struct cel{
    Item item;
    struct cel* prox;
    struct cel* ant;
} Celula;

typedef struct Lista{
    Celula* inicio;
    Celula* fim;
    int tamanho;
} listaStr;

Lista criaLista(){
    listaStr* lista = (listaStr*)malloc(sizeof(listaStr));
    if(checkAllocation(lista, "Criacao da lista.")) return NULL;

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
    return lista;
}

static Celula* criaCelula(){
    Celula* celula = (Celula*)malloc(sizeof(Celula));
    if(checkAllocation(celula, "Celula da lista.")) return NULL;
    
    celula->item = NULL;
    celula->prox = NULL;
    celula->ant = NULL;

    return celula;
}

void inserirInicio(Lista lista, Item item){
    if(lista == NULL){
        printf("\n - inserirInicio() -> Lista passada e' nula.");
        return;
    }

    listaStr* l = (listaStr*)lista;

    Celula* nova = criaCelula();
    nova->item = item;

    if (l->inicio == NULL){ // l vazia
        l->inicio = nova;
        l->fim = nova;
        nova->prox = NULL;
        nova->ant = NULL;
    }
    else{
        nova->prox = l->inicio;
        nova->ant = NULL;
        l->inicio->ant = nova;
        l->inicio = nova;
    }

    l->tamanho += 1;
}

void inserirFim(Lista lista, Item item){
    if(lista == NULL){
        printf("\n - inserirFim() -> Lista passada e' nula.");
        return;
    }

    listaStr* l = (listaStr*)lista;

    Celula* nova = criaCelula();
    nova->item = item;

    if (l->inicio == NULL){ // l vazia
        l->inicio = nova;
        l->fim = nova;
        nova->prox = NULL;
        nova->ant = NULL;
    }
    else{
        nova->prox = NULL;
        l->fim->prox = nova;
        nova->ant = l->fim;
        l->fim = nova;
    }

    l->tamanho += 1;
}

Item removerInicio(Lista lista){
    if(lista == NULL){
        printf("\n - removerInicio() -> Lista passada e' nula.");
        return NULL;
    }

    listaStr* l = (listaStr*)lista;

    Celula* cel = l->inicio;
    void* item = cel->item;

    l->inicio = l->inicio->prox;

    if(l->inicio == NULL) l->fim = NULL;
    else l->inicio->ant = NULL;
    
    free(cel);

    l->tamanho -= 1;

    return item;
}

Item removerFim(Lista lista){
    if(lista == NULL){
        printf("\n - removerFim() -> Lista passada e' nula.");
        return NULL;
    }

    listaStr* l = (listaStr*)lista;

    Celula* cel = l->fim;
    void* item = cel->item;

    l->fim = l->fim->ant;

    if (l->fim) l->fim->prox = NULL;
    else l->inicio = NULL;
    
    free(cel);

    l->tamanho -= 1;

    return item;
}

Item remover(Lista lista, compararItens compFunc, Item item){
    if(lista == NULL){
        printf("\n - remover() -> Lista passada e' nula.");
        return NULL;
    }

    if(compFunc == NULL){
        printf("\n - remover() -> Funcao de comparacao nula. -");
        return NULL;
    }

    listaStr* l = (listaStr*)lista;

    Celula* cel = l->inicio;

    if(cel == NULL) return NULL;

    if(compFunc(cel->item, item)){
        l->inicio = cel->prox;

        if (l->inicio) l->inicio->ant = NULL;
        else l->fim = NULL;
        
        void* itemV = cel->item;
        
        free(cel);
        l->tamanho -= 1;
        
        return itemV;
    }

    while(cel->prox != NULL){
        if(compFunc(cel->prox->item, item)){
            Celula* toRemove = cel->prox;
            cel->prox = toRemove->prox;

            if(toRemove->prox) toRemove->prox->ant = cel;
            else l->fim = cel;

            void* ret = toRemove->item;
            
            free(toRemove);
            
            l->tamanho--;
            
            return ret;
        }
        cel = cel->prox;
    }
    
    return NULL;
}

bool isListaVazia(Lista lista){
    if(lista == NULL){
        printf("\n - isListaVazia() -> Lista passada e' nula.");
        return true;
    }

    return ((listaStr*)lista)->inicio == NULL;
}

int listaTamanho(Lista lista){
    if(lista == NULL){
        printf("\n - listaTamanho() -> Lista passada e' nula.");
        return -1;
    }

    return ((listaStr*)lista)->tamanho;
}

void mapTo(Lista from, Lista to, mapFunction mapFunc, copyFunction copyFunc, void* extra){
    if(from == NULL || to == NULL){
        printf("\n - mapTo() -> Lista passada e' nula.");
        return;
    }

    if(mapFunc == NULL){
        printf("\n - mapTo() -> Funcao de mapeamento ou nula. -");
        return;
    }

    listaStr* listaFrom = (listaStr*)from;
    listaStr* listaTo = (listaStr*)to;

    limparLista(listaTo, NULL, NULL);

    Celula* cel = listaFrom->inicio;
    
    while(cel != NULL){
        Item item = mapFunc(cel->item, extra);
        if(item == NULL){
            cel = cel->prox;
            continue;
        }

        if(copyFunc == NULL) inserirFim(listaTo, item);
        else{
            Item newItem = copyFunc(item);
            if(checkAllocation(newItem, "Funcao de copia retornou valor nulo.")) return;
            inserirFim(listaTo, newItem);
        }

        cel = cel->prox;
    }
}

void concatLista(Lista receive, Lista concatFrom, size_t itemSize){
    if(receive == NULL || concatFrom == NULL){
        printf("\n - concatLista() -> Lista passada e' nula.");
        return;
    }

    if(receive == concatFrom){
        printf("\n - concatLista() -> Ambas as listas sao iguais.");
        return;
    }

    listaStr* listaR = (listaStr*)receive;
    listaStr* listaCF = (listaStr*)concatFrom;

    if (listaCF->inicio == NULL) return;

    Celula* atual = listaCF->inicio;

    while (atual != NULL) {
        Item newItem = malloc(itemSize);
        if(checkAllocation(newItem, "Item de concatenacao de listas.")) return;

        memcpy(newItem, atual->item, itemSize);
        inserirFim(listaR, newItem);

        atual = atual->prox;
    }
}

void percorrerLista(Lista lista, runThroughItems runFunc, void* extra) {
    if(lista == NULL){
        printf("\n - percorrerLista() -> Lista passada e' nula.");
        return;
    }

    if(runFunc == NULL){
        printf("\n - percorrerLista() -> Funcao de percursao nula.");
        return;
    }

    listaStr* l = (listaStr*)lista;

    Celula* cel = l->inicio;
    
    while(cel != NULL){
        runFunc(cel->item, extra);
        cel = cel->prox;
    }
}

void percorrerListaReverso(Lista lista, runThroughItems runFunc, void* extra){
        if(lista == NULL){
        printf("\n - percorrerListaReverso() -> Lista passada e' nula.");
        return;
    }

    if(runFunc == NULL){
        printf("\n - percorrerListaReverso() -> Funcao de percursao nula.");
        return;
    }

    listaStr* l = (listaStr*)lista;

    Celula* cel = l->fim;
    
    while(cel != NULL){
        runFunc(cel->item, extra);
        cel = cel->ant;
    }
}

bool isInLista(Lista lista, compararItens compFunc, Item item) {
    if(lista == NULL){
        printf("\n - isInLista() -> Lista passada e' nula.");
        return false;
    }

    if(compFunc == NULL){
        printf("\n - isInLista() -> Funcao de comparacao nula. -");
        return false;
    }

    listaStr* l = (listaStr*)lista;

    Celula* cel = l->inicio;
    
    while(cel != NULL){
        if(compFunc(cel->item, item)){
            return true;
        }
        cel = cel->prox;
    }
    return false;
}

Item getItemLista(Lista lista, int index){
    if(lista == NULL){
        printf("\n - getItemLista() -> Lista passada e' nula.");
        return NULL;
    }

    listaStr* l = (listaStr*)lista;

    if (index < 0 || index >= l->tamanho) return NULL;

    Celula* cel = l->inicio;

    for(int i = 0; (i < index) && (cel != NULL); i++){
        cel = cel->prox;
    }

    return cel->item;
}

int getItemIndexLista(Lista lista, compararItens compFunc, Item item){
    if(lista == NULL){
        printf("\n - getItemIndexLista() -> Lista passada e' nula.");
        return -1;
    }

    if(compFunc == NULL){
        printf("\n - getItemIndexLista() -> Funcao de comparacao nula. -");
        return -1;
    }

    listaStr* l = (listaStr*)lista;

    if (!l) return -1;

    Celula* cel = l->inicio;
    
    int pos = 0;

    while(cel != NULL){
        if(compFunc(cel->item, item)){
            return pos;
        }
        cel = cel->prox;
        pos += 1;
    }

    return -1;
}

void limparLista(Lista lista, freeFunc fFunc, void* extra){
    if(lista == NULL){
        printf("\n - limparLista() -> Lista passada e' nula.");
        return;
    }

    listaStr* l = (listaStr*)lista;

    Celula* atual = l->inicio;
    while (atual != NULL) {
        Celula* temp = atual;
        atual = atual->prox;
        if(fFunc != NULL) fFunc(temp->item, extra);
        free(temp);
    }

    l->inicio = NULL;
    l->fim = NULL;
    l->tamanho = 0;
}

void copyLista(Lista from, Lista to, copyFunction copyFunc){
    if(from == NULL || to == NULL){
        printf("\n - copyLista() -> Lista passada e' nula.");
        return;
    }

    listaStr* f = (listaStr*)from;
    listaStr* t = (listaStr*)to;

    limparLista(t, NULL, NULL);

    Celula* atual = f->inicio;

    while (atual != NULL) {
        Item newItem = copyFunc(atual->item);
        if(checkAllocation(newItem, "Item de copia de listas retornou nulo.")) return;

        inserirFim(to, newItem);

        atual = atual->prox;
    }
}

void destroiLista(Lista lista, freeFunc freeItens, void* extra){
    if(lista == NULL){
        printf("\n - destroiLista() -> Lista passada e' nula.");
        return;
    }

    limparLista(lista, freeItens, extra);
    free(lista);
}
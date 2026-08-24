#include "arvore.h"

#include <stdlib.h>

typedef struct NoStr {
    struct NoStr* esq;
    struct NoStr* dir;
    struct NoStr* pai;
    
    Item item;

    int altura;
} NoStr;

typedef struct ArvoreStr{
    NoStr* raiz;
    int nNos;
} ArvoreStr;

static int getAltura(NoStr* no){
    return (no != NULL) ? no->altura : 0;
}

static void atualizarAlturas(NoStr* no){
    while(no != NULL){
        int altEsq = getAltura(no->esq);
        int altDir = getAltura(no->dir);
        int novaAlt = ((altEsq > altDir) ? altEsq : altDir) + 1;
        
        if(no->altura == novaAlt) break;
        
        no->altura = novaAlt;
        no = no->pai;
    }
}

static NoStr* criaNo(NoStr* pai, Item item){
    NoStr* no = (NoStr*)malloc(sizeof(NoStr));
    no->item = item;

    no->pai = pai;
    no->esq = NULL;
    no->dir = NULL;

    no->altura = 1;

    atualizarAlturas(no->pai);

    return no;
}

Arvore criaArvore(Item item){
    ArvoreStr* arvore = (ArvoreStr*)malloc(sizeof(ArvoreStr));
    
    arvore->raiz = criaNo(NULL, item);
    arvore->nNos = 1;

    return (Arvore)arvore;
}

static void inserirArvoreRec(NoStr* no, compararItens compFunc, Item item){
    if(no == NULL) return;
    
    bool compResult = compFunc(item, no->item);

    if(compResult){
        if(no->dir != NULL) inserirArvoreRec(no->dir, compFunc, item);
        else no->dir = criaNo(no, item);
    }
    else{
        if(no->esq != NULL) inserirArvoreRec(no->esq, compFunc, item);
        else no->esq = criaNo(no, item);
    }
}

void inserirArvore(Arvore arvore, compararItens compFunc, Item item){
    ArvoreStr* a = (ArvoreStr*)arvore;

    if(a->raiz == NULL) return;

    inserirArvoreRec(a->raiz, compFunc, item);
    a->nNos += 1;
}

static void percorrerArvoreRec(NoStr* no, runThroughItems runFunc, void* extra){
    if(no == NULL) return;

    percorrerArvoreRec(no->esq, runFunc, extra);
    runFunc(no->item, extra);
    percorrerArvoreRec(no->dir, runFunc, extra);
}

void percorrerArvore(Arvore arvore, runThroughItems runFunc, void* extra){
    if(arvore == NULL) return;

    ArvoreStr* a = (ArvoreStr*)arvore;

    if(a->raiz == NULL) return;

    percorrerArvoreRec(a->raiz, runFunc, extra);
}

static NoStr* getFilhoMaisDireita(NoStr* no){
    if(no == NULL) return NULL;

    while(no->dir != NULL) no = no->dir;
    return no;
}

static Item removerItemRec(ArvoreStr* arvore, NoStr* no, Item item, compararItens directionFunc, compararItens compFunc, void* extra){
    if(no == NULL) return NULL;

    if(compFunc(item, no->item)){
        // Dois filhos
        if(no->dir != NULL && no->esq != NULL){
            NoStr* maiorFilho = getFilhoMaisDireita(no->esq);
            
            Item itemAux = maiorFilho->item;
            maiorFilho->item = item;
            no->item = itemAux;

            removerItemRec(arvore, no->esq, item, directionFunc, compFunc, extra);
        }
        // Nenhum ou um filho
        else{
            NoStr* noFilho = (no->esq != NULL ? no->esq : no->dir);
            NoStr* noPai = no->pai;

            if(noFilho != NULL) noFilho->pai = noPai;
            
            if(noPai == NULL) arvore->raiz = noFilho;
            else{
                if(noPai->esq == no) noPai->esq = noFilho;
                else noPai->dir = noFilho;

                atualizarAlturas(noPai);
            }

            Item noItem = no->item;
            no->item = NULL;
            free(no);

            arvore->nNos -= 1;

            return noItem;
        }
    }
    else{
        no = (directionFunc(item, no->item) ? no->dir : no->esq);
        removerItemRec(arvore, no, item, directionFunc, compFunc, extra);
    }

    return NULL;
}

Item removerItemArvore(Arvore arvore, Item item, compararItens directionFunc, compararItens compFunc, void* extra){
    if(arvore == NULL) return NULL;

    ArvoreStr* a = (ArvoreStr*)arvore;

    if(a->raiz == NULL) return NULL;

    return removerItemRec(arvore, a->raiz, item, directionFunc, compFunc, extra);
}

static void destroiArvoreRec(NoStr* no, freeFunc fFunc, void* extra){
    if(no == NULL) return;

    destroiArvoreRec(no->esq, fFunc, extra);
    destroiArvoreRec(no->dir, fFunc, extra);
    fFunc(no->item, extra);
    free(no);
}

void destroiArvore(Arvore arvore, freeFunc fFunc, void* extra){
    if(arvore == NULL) return;

    ArvoreStr* a = (ArvoreStr*)arvore;

    if(a->raiz == NULL) return;

    destroiArvoreRec(a->raiz, fFunc, extra);

    free(arvore);
}
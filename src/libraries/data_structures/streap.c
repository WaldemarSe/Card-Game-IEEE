#include "streap.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <time.h>

typedef struct BoundingBox{
    double x1, y1;
    double x2, y2;
} BoundingBox;

typedef struct NodeStr{
    double x, y;        // Chave de busca
    Info info;
    BoundingBox* box;

    int prioridade;

    struct NodeStr* pai;
    struct NodeStr* esq;
    struct NodeStr* dir;
} NodeStr;

typedef struct STreapStr{
    NodeStr* raiz;
    int nRoot;

    double epsilon;
}STreapStr;

// Declaracao de escopo de funcoes.
static void freeNodeSTrp(NodeStr* node, freeFunc fFunc);

STreap createSTrp(double epsilon){
    STreapStr* st = (STreapStr*)malloc(sizeof(STreapStr));
    if(checkAllocation(st, "STreap.")) return NULL;

    st->raiz = NULL;
    st->nRoot = 0;
    st->epsilon = epsilon;

    return (STreap)st;
}

static NodeStr* createNodeSTrp(double x, double y, Info info){
    NodeStr* newNode = (NodeStr*)malloc(sizeof(NodeStr));
    if(checkAllocation(newNode, "Novo node STreap.")) return NULL;

    newNode->box = (BoundingBox*)malloc(sizeof(BoundingBox));
    if(checkAllocation(newNode->box, "Bounding box do novo node da STreap.")){
        free(newNode);
        return NULL;
    }

    newNode->box->x1 = x;
    newNode->box->x2 = x;
    newNode->box->y1 = y;
    newNode->box->y2 = y;

    newNode->pai = NULL;
    newNode->dir = NULL;
    newNode->esq = NULL;

    newNode->info = info;

    newNode->x = x;
    newNode->y = y;

    newNode->prioridade = rand();

    return newNode;
}

static void updateBoundingBox(NodeStr* node){
    if(node == NULL) return;

    node->box->x1 = node->x;
    node->box->x2 = node->x;
    node->box->y1 = node->y;
    node->box->y2 = node->y;

    if(node->esq != NULL){
        node->box->x1 = fmin(node->box->x1, node->esq->box->x1);
        node->box->x2 = fmax(node->box->x2, node->esq->box->x2);
        node->box->y1 = fmin(node->box->y1, node->esq->box->y1);
        node->box->y2 = fmax(node->box->y2, node->esq->box->y2);
    }
    if(node->dir != NULL){
        node->box->x1 = fmin(node->box->x1, node->dir->box->x1);
        node->box->x2 = fmax(node->box->x2, node->dir->box->x2);
        node->box->y1 = fmin(node->box->y1, node->dir->box->y1);
        node->box->y2 = fmax(node->box->y2, node->dir->box->y2);
    }
    return;
}

static void updateBoundingBoxUp(NodeStr* node){
    while(node != NULL){
        updateBoundingBox(node);
        node = node->pai;
    }
}

static void rotateRightSTrp(STreap t, NodeST node){
    if(node == NULL){
        printf("\n - rotateRightSTrp() -> NodeST passado e' nulo.");
        return;
    }

    NodeStr* p = (NodeStr*)node;
    NodeStr* q = p->esq;

    if(q == NULL) return;

    NodeStr* aux = q->dir;

    q->dir = p;
    p->esq = aux;

    q->pai = p->pai;
    p->pai = q;
    if(aux != NULL) aux->pai = p;

    if(q->pai){
        if(q->pai->esq == p) q->pai->esq = q;
        else if(q->pai->dir == p) q->pai->dir = q;
    }
    else{
        STreapStr* st = (STreapStr*)t;
        st->raiz = q;
    }

    updateBoundingBox(p);
    updateBoundingBox(q);
}

static void rotateLeftSTrp(STreap t, NodeST node){
    if(node == NULL){
        printf("\n - rotateLeftSTrp() -> NodeST passado e' nulo.");
        return;
    }

    NodeStr* p = (NodeStr*)node;
    NodeStr* q = p->dir;

    if(q == NULL) return;

    NodeStr* aux = q->esq;

    q->esq = p;
    p->dir = aux;

    q->pai = p->pai;
    p->pai = q;
    if(aux != NULL) aux->pai = p;

    if(q->pai){
        if(q->pai->esq == p) q->pai->esq = q;
        else if(q->pai->dir == p) q->pai->dir = q;
    }
    else{
        STreapStr* st = (STreapStr*)t;
        st->raiz = q;
    }

    updateBoundingBox(p);
    updateBoundingBox(q);
}

static NodeST insertNodeByKeySTrp(STreap t, double x, double y, Info info){
    if(t == NULL){
        printf("\n - insertNodeByKeySTrp() -> Treap passada e' nula. -");
        return NULL;
    }
    
    STreapStr* st = (STreapStr*)t;
    int alturaAtual = 1;

    NodeStr* newNode = createNodeSTrp(x, y, info);
    if(newNode == NULL) return NULL;

    if(st->raiz == NULL){
        st->raiz = newNode;
        return newNode;
    }

    NodeStr* aux = st->raiz;

    // ch1 < ch2, se:
    // (ch1.x < ch2.x)
    //  -- OU --
    // (ch1.x == ch2.x AND ch1.y < ch2.y)
    
    // Verificacao de igualdade: |v - w| <= epsilon.
    while(aux != NULL){
        if((x < aux->x) || ((fabs(x - aux->x) <= st->epsilon) && (y < aux->y))){
            if(aux->esq == NULL){
                aux->esq = newNode;
                newNode->pai = aux;
                break;
            }
            else aux = aux->esq;
        }
        else if(!((fabs(x - aux->x) <= st->epsilon) && (fabs(y - aux->y) <= st->epsilon))){
            if(aux->dir == NULL){
                aux->dir = newNode;
                newNode->pai = aux;
                break;
            }
            else aux = aux->dir;
        }
        else{
            free(newNode->box);
            free(newNode);
            printf("\n -- insertNodeByKeySTrp() -> No' ja' existe na arvore. -- ");
            return NULL;
        }
        alturaAtual += 1;
    }

    updateBoundingBoxUp(newNode);

    return newNode;
}

static void rebalancearSTrp(STreap t, NodeStr* node){
    if(node == NULL){
        printf("\n - rebalancearSTrp() -> NodeST passado e' nulo. -");
        return;
    }

    NodeStr* pai = node->pai;

    if(pai == NULL) return;

    if(node->prioridade < pai->prioridade){
        if(pai->esq == node) rotateRightSTrp(t, pai);
        else rotateLeftSTrp(t, pai);

        rebalancearSTrp(t, node);
    }
}

static bool isInside(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2){
    return (x2 >= x1 && (x2 + w2) <= (x1 + w1) && y2 >= y1 && (y2 + h2) <= (y1 + h1));
}

static bool isOutside(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2){
    return (x2 + w2 < x1 || x2 > x1 + w1 || y2 + h2 < y1 || y2 > y1 + h1);
}

NodeST insertSTrp(STreap t, double x, double y, Info info){
    if(t == NULL){
        printf("\n - insertSTrp() -> Treap passada e' nula. - ");
        return NULL;
    }

    STreapStr* st = (STreapStr*)t;

    NodeStr* newNode = insertNodeByKeySTrp(t, x, y, info);
    if(newNode == NULL) return NULL;

    rebalancearSTrp(t, newNode);
    updateBoundingBoxUp(newNode);
    //updateBoundingBoxDown(st->raiz);
    st->nRoot += 1;

    return newNode;
}

int getPrioridade(NodeST node){
    return ((NodeStr*)node)->prioridade;
}

static void getNodeRegiaoSTrpRec(STreapStr* st, NodeStr* node, double x, double y, double w, double h, Lista resultado){
    if (node == NULL) return;

    if(isInside(x, y, w, h, node->x, node->y, 0, 0)){
        inserirInicio(resultado, node);
    }

    if(node->esq != NULL && !isOutside(x, y, w, h, node->esq->box->x1, node->esq->box->y1, node->esq->box->x2 - node->esq->box->x1, node->esq->box->y2 - node->esq->box->y1)){
        getNodeRegiaoSTrpRec(st, node->esq, x, y, w, h, resultado);
    }

    if(node->dir != NULL && !isOutside(x, y, w, h, node->dir->box->x1, node->dir->box->y1, node->dir->box->x2 - node->dir->box->x1, node->dir->box->y2 - node->dir->box->y1)){
        getNodeRegiaoSTrpRec(st, node->dir, x, y, w, h, resultado);
    }
}

void getNodeRegiaoSTrp(STreap t, double x, double y, double w, double h, Lista resultado){
    if(t == NULL){
        printf("\n - getNodeRegiaoSTrp() -> Treap passada e' nula. -");
        return;
    }

    STreapStr* st = (STreapStr*)t;

    if(st->raiz == NULL){
        printf("\n - getNodeRegiaoSTrp() -> Treap vazia. -");
        return;
    }

    // Nao percorre a arvore se a regiao estiver fora do bounding box da raiz.
    if(isOutside(x, y, w, h, st->raiz->box->x1, st->raiz->box->y1, st->raiz->box->x2 - st->raiz->box->x1, st->raiz->box->y2 - st->raiz->box->y1)) return;

    getNodeRegiaoSTrpRec(st, st->raiz, x, y, w, h, resultado);
}


Info getInfoSTrp(STreap t, NodeST n, double *x, double *y, double *mbbX1, double *mbbY1, double *mbbX2, double *mbbY2){
    UNUSED(t);
    NodeStr* ntr = (NodeStr*)n;
    
    if(x != NULL) *x = ntr->x;
    if(y != NULL) *y = ntr->y;
    if(mbbX1 != NULL) *mbbX1 = ntr->box->x1;
    if(mbbX2 != NULL) *mbbX2 = ntr->box->x2;
    if(mbbY1 != NULL) *mbbY1 = ntr->box->y1;
    if(mbbY2 != NULL) *mbbY2 = ntr->box->y2;

    return ntr->info;
}

static NodeST getNodeSTrpRec(NodeStr* node, double x, double y, double epsilon){
    if(node == NULL) return NULL;
    
    if((x < node->x) || ((fabs(x - node->x) <= epsilon) && (y < node->y))){
        return getNodeSTrpRec(node->esq, x, y, epsilon);
    }
    else if((x > node->x) || ((fabs(x - node->x) <= epsilon) && (y > node->y))){
        return getNodeSTrpRec(node->dir, x, y, epsilon);
    }
    else{
        return node;
    }
}

NodeST getNodeSTrp(STreap t, double xa, double ya){
    STreapStr* st = (STreapStr*)t;
    
    if(st == NULL) return NULL;

    return getNodeSTrpRec(st->raiz, xa, ya, st->epsilon);
}

typedef struct ResourcesClosestNode{
    NodeStr* closest;
    double bestDistance;
    double x;
    double y;
}ResourcesClosestNode;

static double distance_sq_to_mbb(double xa, double ya, BoundingBox* box) {
    double dx = 0.0;
    double dy = 0.0;
    
    if(xa < box->x1) dx = box->x1 - xa;
    else if(xa > box->x2) dx = xa - box->x2;

    if(ya < box->y1) dy = box->y1 - ya;
    else if(ya > box->y2) dy = ya - box->y2;
    
    double distancia = dx*dx + dy*dy;
    return distancia;
}

// Helper function to calculate squared distance between two points (from your existing code)
static double distance(double x1, double y1, double x2, double y2){
    double dx = x1 - x2;
    double dy = y1 - y2;

    double distancia = dx*dx + dy*dy;
    return distancia;
}

static void getClosestNodeSTrpRec(NodeStr* node, void* extra) {
    if(node == NULL) return;
    ResourcesClosestNode* res = (ResourcesClosestNode*)extra;

    double distanciaAtual = distance(res->x, res->y, node->x, node->y);
    if(distanciaAtual < res->bestDistance) {
        res->bestDistance = distanciaAtual;
        res->closest = node;
    }
    
    NodeStr* esq = node->esq;
    NodeStr* dir = node->dir;
    
    double distEsq = DBL_MAX;
    if(esq != NULL) distEsq = distance_sq_to_mbb(res->x, res->y, esq->box);
    
    double distDir = DBL_MAX;
    if(dir != NULL) distDir = distance_sq_to_mbb(res->x, res->y, dir->box);

    if (distEsq < distDir) {
        esq = node->esq;
        dir = node->dir;
    } else {
        esq = node->dir;
        dir = node->esq;
        distEsq = distDir;
        distDir = distEsq;
    }
    
    if(esq != NULL && distEsq <= res->bestDistance) getClosestNodeSTrpRec(esq, res);
    if(dir != NULL && distance_sq_to_mbb(res->x, res->y, dir->box) <= res->bestDistance) getClosestNodeSTrpRec(dir, res);
}

NodeST getClosestNodeSTrp(STreap t, double xa, double ya){
    STreapStr* st = (STreapStr*)t;
    
    if (st == NULL || st->raiz == NULL) return NULL;

    ResourcesClosestNode res = {NULL, DBL_MAX, xa, ya};

    getClosestNodeSTrpRec(st->raiz, &res);

    return res.closest;
}

void updateInfoSTrp(STreap t, NodeST n, Info i){
    UNUSED(t);
    ((NodeStr*)n)->info = i;
}

static void rebalancearDeleteNodeSTrp(STreapStr* st, NodeStr* node){
    if(node == NULL || st == NULL){
        printf("\n - rebalancearDeleteNodeSTrp() -> Uma ou mais informacoes passadas sao nulas. - ");
        return;
    }

    while(node->esq != NULL && node->dir != NULL){
        if(node->esq->prioridade > node->dir->prioridade) rotateRightSTrp(st, node);
        else rotateLeftSTrp(st, node);
    }

    NodeStr* filho = (node->esq) ? node->esq : node->dir;

    if(node->pai != NULL){
        if(node->pai->esq == node) node->pai->esq = filho;
        else node->pai->dir = filho;
    }
    else st->raiz = filho;

    if(filho != NULL){
        filho->pai = node->pai;
        updateBoundingBoxUp(filho);
    }
    else updateBoundingBoxUp(node->pai);
}

Info deleteNodeSTrp(STreap t, NodeST n){
    if(t == NULL || n == NULL){
        printf("\n - deleteNodeSTrp() -> Uma ou mais informacoes passadas sao nulas. -");
        return NULL;
    }

    STreapStr* st = (STreapStr*)t;
    NodeStr* node = ((NodeStr*)n);

    Info i = node->info;

    rebalancearDeleteNodeSTrp(st, node);
    //updateBoundingBoxDown(st->raiz);
    st->nRoot -= 1;

    free(node->box);
    free(node);

    return i;
}

Info removeSTrp(STreap t, double xa, double ya){
    if(t == NULL){
        printf("\n - removeSTrp() -> Treap passada e' nula. -");
        return NULL;
    }

    NodeStr* node = getNodeSTrp(t, xa, ya);

    return deleteNodeSTrp(t, node);
}

static void exportDot(NodeStr* node, FILE* f) {
    if (node == NULL) return;

    fprintf(f, "\"%p\" [shape=record, label=\"{QUADRA| {PONTEIRO | %p} | {X | %.1f} | {Y | %.1f} | {BOUNDING BOX | [%.1f, %.1f, %.1f, %.1f]} }\"];\n",node, node, node->x, node->y, node->box->x1, node->box->y1, node->box->x2, node->box->y2);

    if(node->esq != NULL){
        fprintf(f, "\"%p\" -> \"%p\";\n", node, node->esq);
        exportDot(node->esq, f);
    }

    if(node->dir != NULL){
        fprintf(f, "\"%p\" -> \"%p\";\n", node, node->dir);
        exportDot(node->dir, f);
    }
}

void printSTrp(STreap t, const char *nomeArq){
    STreapStr* st = (STreapStr*)t;
    FILE *f = fopen(nomeArq, "w");

    fprintf(f, "digraph G{\n");
    fprintf(f, "rankdir=TB;\n");
    fprintf(f, "fontname=\"Helvetica\";\n");
    fprintf(f, "node [shape=plaintext, fontname=\"Helvetica\"];\n");

    exportDot(st->raiz, f);
    
    fprintf(f, "}\n");

    fclose(f);
}

void percursoLargura(STreap t, FvisitaNo fVisita, void *aux){
    if(t == NULL){
        printf("\n - percursoLargura() -> Treap passada e' nula. -");
        return;
    }

    if(fVisita == NULL){
        printf("\n - percursoLargura() -> Funcao de visita passada e' nula. -");
        return;
    }

    STreapStr* st = (STreapStr*)t;

    if(st->raiz == NULL){
        printf("\n - percursoLargura() -> Treap vazia. -");
        return;
    }

    // Lista usada como uma fila.
    // (Insercao no comeco e remocao no fim)
    Lista l = criaLista();

    inserirInicio(l, st->raiz);

    while(!isListaVazia(l)){
        NodeStr* node = removerFim(l);

        fVisita(node->info, node->x, node->y, node->box->x1, node->box->y1, node->box->x2, node->box->y2, aux);

        if(node->esq != NULL){
            inserirInicio(l, node->esq);
        }
        if(node->dir != NULL){
            inserirInicio(l, node->dir);
        }
    }
}

static void percursoSimetricoRec(NodeStr* node, FvisitaNo fVisita, void *aux){
    if(node == NULL) return;

    if(node->esq != NULL) percursoSimetricoRec(node->esq, fVisita, aux);
    if(node != NULL) fVisita(node->info, node->x, node->y, node->box->x1, node->box->y1, node->box->x2, node->box->y2, aux);
    if(node->dir != NULL) percursoSimetricoRec(node->dir, fVisita, aux);
}

void percursoSimetrico(STreap t, FvisitaNo fVisita, void *aux){
    if(t == NULL){
        printf("\n - percursoSimetrico() -> Treap passada e' nula. -");
        return;
    }

    if(fVisita == NULL){
        printf("\n - percursoSimetrico() -> Funcao de visita passada e' nula. -");
        return;
    }

    STreapStr* st = (STreapStr*)t;

    percursoSimetricoRec(st->raiz, fVisita, aux);
}

static void percursoProfundidadePreRec(NodeStr* node, FvisitaNo fVisita, void *aux){
    if(node == NULL) return;

    if(node != NULL) fVisita(node->info, node->x, node->y, node->box->x1, node->box->y1, node->box->x2, node->box->y2, aux);
    if(node->esq != NULL) percursoProfundidadePreRec(node->esq, fVisita, aux);
    if(node->dir != NULL) percursoProfundidadePreRec(node->dir, fVisita, aux);
}

void percursoProfundidade(STreap t, FvisitaNo fVisita, void *aux){
    if(t == NULL){
        printf("\n - percursoProfundidade() -> Treap passada e' nula. -");
        return;
    }

    if(fVisita == NULL){
        printf("\n - percursoProfundidade() -> Funcao de visita passada e' nula. -");
        return;
    }

    STreapStr* st = (STreapStr*)t;

    percursoProfundidadePreRec(st->raiz, fVisita, aux);
}

static void freeNodeSTrp(NodeStr* node, freeFunc fFunc){
    if(node == NULL){
        printf("\n - freeNodeSTrp() -> NodeST passado e' nulo. -");
        return;
    }

    if(fFunc != NULL) fFunc(node->info, NULL);
    free(node->box);
    free(node);
}

static void killSTrpRec(NodeStr* node, freeFunc fFunc, void* extra){
    if(node == NULL) return;

    if(node->esq != NULL) killSTrpRec(node->esq, fFunc, extra);
    if(node->dir != NULL) killSTrpRec(node->dir, fFunc, extra);
    if(node != NULL) freeNodeSTrp(node, fFunc);
}

void killSTrp(STreap t, freeFunc fFunc, void* extra){
    if(t == NULL){
        printf("\n - killSTrp() -> Treap passada e' nula. -");
        return;
    }

    STreapStr* st = (STreapStr*)t;

    killSTrpRec(st->raiz, fFunc, extra);
    free(st);
}

////////////////////////

NodeST getStrpRoot(STreap t){
    return ((STreapStr*)t)->raiz;
}

// static int alturaSTrp(NodeStr* node){
//     if(node == NULL) return 0;
    
//     int altEsq = alturaSTrp(node->esq);
//     int altDir = alturaSTrp(node->dir);

//     return ((altDir > altEsq) ? altDir : altEsq) + 1;
// }

// int getAlturaStrp(STreap t){
//     return alturaSTrp(((STreapStr*)t)->raiz);
// }
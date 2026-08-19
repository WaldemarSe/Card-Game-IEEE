#ifndef _GRAPH__
#define _GRAPH__

#include "lista.h"

/*
    Um Grafo direcionado G e' constituido por um conjunto de vertices V e 
    um conjunto de arestas E, denotado por G=(V,E).

    Pode-se associar um dado a arestas e a vertices de G.
    A cada vertice e' associado um nome.

    Existem tambem operacoes que possibilitam percorrer o grafo,
    invocando funcoes quando arestas do grafo 
    sao "descobertas", podendo, inclusive, interromper o percurso.

    Este modulo faz parte de um trabalho de Estrutura de Dados do 
    curso de Ciencia da Computacao da Universidade Estadual de Londrina.
    E' expressamente proibido o uso de ferramentas de IA para a sua implementacao.
    A documentacao deste modulo deve ser melhorada.
*/

typedef void* Graph;
typedef int Node;
typedef void* Edge;
typedef void* Info;

/*
    Invocado quando uma aresta é "descoberta"/"percorrida"/"classificada". 
    Tambem informa os tempos de descoberta e finalizacao
*/
typedef bool (*procEdge)(Graph g, Edge e, int td, int tf, void *extra);

/*
    Invocado quando percurso e' recomecado
*/
typedef bool (*dfsRestarted)(Graph g, void *extra);

/*
    Cria um grafo com, no maximo, "nVert" vertices.
*/
Graph createGraph(int nVert);

/*
    Retorna numero maximo de vertices que grafo g pode conter.
*/
int getMaxNodes(Graph g);

/*
    Retorna numero total de vertices adicionados ao grafo gr.
*/
int getTotalNodes(Graph g);

/*
    Retorna numero total de arestas adicionadas ao grafo gr.
*/
int getTotalEdges(Graph g);

/*
    Adiciona um novo vértice ao grafo "g" com o nome "nome".
*/
Node addNode(Graph g, char* nome, Info info);

/*
    Retorna no' cujo de nome e' "nome". 
*/
Node getNode(Graph g, char* nome);

/*
    Retorna a info de um no' especificado.
*/
Info getNodeInfo(Graph g, Node node);

/*
    Retorna o nome de um no' especificado.
*/
char *getNodeName(Graph g, Node node);

/*
    Atribui info ao no' especificado.
*/
void setNodeInfo(Graph g, Node node, Info info);

/*
    Retorna uma aresta de origem From e destino To com informacao info.
*/
Edge addEdge(Graph g, Node from, Node to, Info info);

/*
    Retorna uma aresta com origem From e destino To.
*/
Edge getEdge(Graph g, Node from, Node to);

/*
    Retorna a origem From da aresta E.
*/
Node getFromNode(Edge e);
  
/*
    Retorna o destino To da aresta E.
*/  
Node getToNode(Edge e);

/*
    Retorna a informacao associada a aresta E.
*/
Info getEdgeInfo(Edge e);

/*
    Atribui a informacao info a aresta E.
*/
void setEdgeInfo(Edge e, Info info);

/*
    Remove a aresta E do grafo g.
*/
void removeEdge(Graph g, Edge e, freeFunc freeEdgeFunc);

/*
    Retorna um valor booleano, true se a origem From e o destino To sao adjacentes, false caso contr'ario.
*/
bool isAdjacent(Graph g, Node from, Node to);

/* 
    Adiciona 'a lista "nosAdjacentes" os nos adjacentes 'a "node".
*/
void adjacentNodes(Graph g, Node node, Lista nosAdjacentes);

/*
    Adiciona 'a lista "arestaAdjacentes" as arestas (x,y), tal que,
    x == node.
*/
void adjacentEdges(Graph g, Node node, Lista arestasAdjacentes);

/*
    Adiciona 'a lista "arestaAdjacentes" as arestas (x,y), tal que,
    y == node.
*/
void adjacentEdgesReverse(Graph g, Node node, Lista arestasAdjacentes);

/*
    Insere na lista "nomesNodes" os nomes atribuidos aos no's do grafo.
*/
void getNodeNames(Graph g, Lista nomesNodes);

/*
    Insere na lista "arestas", as arestas de g.
*/
void getEdges(Graph g, Lista arestas);

/*
    Insera na lista "allInfo", todas as informações guardadas nos vértices do grafo g.
*/
void getAllVerticesInfo(Graph g, Lista allInfo);

// PERCURSO DO GRAFO
/////////////////////////////////////////////////////////////////////////////////////////////////

/*
    Faz percurso em profundidade sobre g, a partir do no' node, classificando 
    as arestas do grafo, invocando a respectiva funcao.
    A busca em profundidade, eventualmente, pode produzir uma floresta.
    newTree e' invocada sempre que o percurso for retomado.
*/
bool dfs(Graph g, Node node, procEdge treeEdge, procEdge forwardEdge, procEdge returnEdge, procEdge crossEdge, dfsRestarted newTree, void *extra);

/*
    Percorre o grafo g em largura, a partir do no' node. discoverNode e' usada
    para a aresta (x,y) usada para "descobrir" o y.
*/
bool bfs(Graph g, Node node, procEdge discoverNode, void *extra);

/*
    Percorre todos os ve'rtices do grafo em ordem de insercao.
*/
void percorrerNodes(Graph g, runThroughItems runFunc, void* extra);

// FREE
/////////////////////////////////////////////////////////////////////////////////////////////////

/*
    Destroi uma aresta e.
*/
void freeAresta(Edge e, void* extra);

/*
    Destroi o grafo g.
*/
void killDG(Graph g, freeFunc freeVerticeFunc, freeFunc freeEdgeFunc);

#endif
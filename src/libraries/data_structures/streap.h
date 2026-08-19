#ifndef _SRB_Tree_H
#define _SRB_Tree_H

#include "lista.h"

/*
  Uma Treap espacial (STreap) e' uma arvore Treap que associa uma coordenada no plano (ancora)
  a uma dada informacao

  A chave de busca e´ a coordenada da ancora.

  A ordem da chave de busca e' definido como, a seguir. Sejam ch1 e ch2 duas chaves de busca.
  Define-se que ch1 < ch2, se:

    * ch1.x < ch2.x    
    OU
    * ch1.x == ch2.x  AND ch1.y < ch2.y

  caso contrario, ch1 == ch2

  Associa-se uma precisao epsilon `a arvore. Esta precisao e' usada para determinar quando dois numeros
  reais (da chave de busca) devem ser considerados como iguais. Assim v == w, se |v - w| <= epsilon.

  Algumas operacoes de busca retornam o no´ da arvore onde uma determinada informacao esta' armazenada. 
  
  Os dados referentes a este no´ podem ser obtidos por outras operacoes, desde que estes nos continuem
  validos. Qualquer remocao posterior faz com que nos (NodeST) retornados previamente devam ser considerados
  invalidos. 
*/

typedef void *STreap; 
typedef void *Info;
typedef void *NodeST;

/**
 * Processa a informacao i associada a um no' da arvore, cuja ancora
 * e' o ponto (x,y), bounding box (mbbX1,mbbY1) -- (mbbX2,mbbY2). 
 * O parametro aux aponta para conjunto de dados 
 * (provavelmente um registro) que sao compartilhados entre as 
 * sucessivas invocacoes a esta funcao.
 */
typedef void (*FvisitaNo) (Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux);

/*
  Retorna uma ´arvore vazia, com precisao epsilon.
  Retorna NULL caso nao tenha conseguido criar a arvore.
*/
STreap createSTrp(double epsilon);

/*
  Insere a informacao info na arvore t, associada a coordenada (x,y).
  Retorna o no´ onde foi inserida a informacao; NULL, caso ja exista informacao com a mesma chave (veja acima)
  inserida.
*/
NodeST insertSTrp(STreap t, double x, double y, Info info);

/*
  Insere na lista resultado os nos da arvore (NodeST) cuja ancora estejam dentro da regiao retangular 
  de ancora (x,y), largura w e altura h.
*/
void getNodeRegiaoSTrp(STreap t, double x, double y, double w, double h, Lista resultado);

/*
  Retorna a informacao associada ao no´ n, sua ancora (xa,ya) e o retangulo envolvente (mbbX1,mbbY1) -- (mbbX2,mbbY2). 
  Este no´ deve ser um no´ valido (veja acima).
*/
Info getInfoSTrp(STreap t, NodeST n, double *x, double *y, double *mbbX1, double *mbbY1, double *mbbX2, double *mbbY2);

/*
  Retorna o no da arvore associado a ancora (xa,ya) e o retangulo envolvente; NULL, se tal ancora nao existir.
*/
NodeST getNodeSTrp(STreap t, double xa, double ya);

/*
  Retorna o no da arvore associado a ancora (xa,ya) mais pro'xima e o retangulo envolvente; NULL, se tal ancora nao existir.
*/
NodeST getClosestNodeSTrp(STreap t, double xa, double ya);

/*
  Altera a informacao associada ao no n que deve ser existente e valido. 
  A ancora  deste no nao sao alterado.
*/
void updateInfoSTrp(STreap t, NodeST n, Info i);

/*
  Remove o no' n da arvore, portanto, o no' n  deve ser considerado invalido.
  Retorna a informacao que estava associada a tal no'.
*/
Info deleteNodeSTrp(STreap t, NodeST n);

/*
  Remove o no' da arvore cuja chave e´ a coordenada (xa,ya). 
  Qualquer no' da arvore retornado por operacoes anteriores
  deve ser considerado invalido.
  Retorna a informacao que estava associada a tal no' (ou NULL, se nao encontrado).
*/
Info removeSTrp(STreap t, double xa, double ya);

/*
  "Desenha" (no formato dot) a arvore no arquivo nomeArq.
  Veja: https://graphviz.org/
*/
void printSTrp(STreap t, const char *nomeArq);

/*
  As proximas operacoes percorrem a arvore em largura/profundidade/simetrico.
  Invoca a funcao fVisita (veja descricao acima) em cada no´ visitado
*/

/////////////////////////////////////////////////////////////////////////////////////////////////

// Percorre a a'rvore em largura.
void percursoLargura(STreap t, FvisitaNo fVisita, void *aux);

// Percorre a a'rvore em simetria.
void percursoSimetrico(STreap t, FvisitaNo fVisita, void *aux);

// Percorre a a'rvore em profundidade.
void percursoProfundidade(STreap t, FvisitaNo fVisita, void *aux);

/////////////////////////////////////////////////////////////////////////////////////////////////

// FREE

/*
  Desaloca todos os recursos usados pela arvore t.
*/
void killSTrp(STreap t, freeFunc fFunc, void* extra);

// DEBUG FUNCS
///////////////////////

NodeST getStrpRoot(STreap t);

int getAlturaStrp(STreap t);

int getPrioridade(NodeST node);

#endif
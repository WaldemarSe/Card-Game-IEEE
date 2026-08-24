#ifndef _Arvore_h_
#define _Arvore_h_

#include <stdbool.h>

#include "types.h"

/**
 * Cabeçalho dedicado 'a estrutura "Arvore" que tem como princi'pio
 * a organizacao hierarquica dos dados, permitindo a busca,
 * insercao e remocao eficiente de elementos atraves de uma
 * estrutura ramificada.
 */

typedef void* Arvore;

/**
 * @brief Cria uma a'rvore com raiz definida.
 * @param item Item a ser armazenado na raiz da a'rvore.
 * @return Retorna um ponteiro para a estrutura de a'rvore criada.
 */
Arvore criaArvore(Item item);

/**
 * @brief Insere um novo item na a'rvore de acordo com a funcao de comparacao.
 * @param arvore Ponteiro para a estrutura da a'rvore.
 * @param compFunc Funcao que define a precedencia para o posicionamento do item.
 * @param item Item a ser inserido.
 * @return Não ha' retorno de algum valor.
 */
void inserirArvore(Arvore arvore, compararItens compFunc, Item item);

/**
 * @brief Faz o percurso sime'trico da a'rvore, executando a funcao externa para cada item.
 * @param arvore Ponteiro para a estrutura da a'rvore.
 * @param runFunc Funcao a ser executada em cada item visitado.
 * @param extra Ponteiro para dados adicionais para a funcao runFunc.
 * @return Não ha' retorno de algum valor.
 */
void percorrerArvore(Arvore arvore, runThroughItems runFunc, void* extra);

/**
 * @brief Remove um item especifico da a'rvore.
 * @param arvore Ponteiro para a estrutura da a'rvore.
 * @param item Referencia do item a ser localizado e removido.
 * @param directionFunc Funcao que orienta a busca (esquerda ou direita) na a'rvore.
 * @param compFunc Funcao que valida se o item encontrado e' o alvo da remocao.
 * @param extra Ponteiro para dados adicionais necessarios a's funcoes de comparacao.
 * @return Retorna o item removido ou NULL caso o item nao seja encontrado.
 */
Item removerItemArvore(Arvore arvore, Item item, compararItens directionFunc, compararItens compFunc, void* extra);

/**
 * @brief Libera toda a memoria da a'rvore e de seus itens.
 * @param arvore Ponteiro para a estrutura da a'rvore a ser destruida.
 * @param fFunc Funcao responsavel por liberar a memoria de cada item.
 * @param extra Ponteiro para dados adicionais necessarios a' funcao fFunc.
 * @return Não ha' retorno de algum valor.
 */
void destroiArvore(Arvore arvore, freeFunc fFunc, void* extra);

#endif
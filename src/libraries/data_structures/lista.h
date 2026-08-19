#ifndef _Lista_h_
#define _Lista_h_

#include <stdbool.h>
#include <stdlib.h>

#include "types.h"

/**
 * Cabeçalho dedicado 'a estrura "Lista" que tem como princi'pio
 * a insercao e remocao de qualquer elemento em qualquer posicao
 * dentro da estrutura.
*/

typedef void* Lista;

/**
 * @brief Cria uma lista gene'rica.
 * @return Retorna a lista criada caso houve sucesso na criação, NULL caso contrário.
 */
Lista criaLista();

/**
 * @brief Insere no início da lista.
 * @param lista Lista genérica escolhida para inserção.
 * @param item Ponteiro para um tipo qualquer de estrutura/variável na qual será inserida na lista.
 * @return Não há retorno de algum valor.
 */
void inserirInicio(Lista lista, Item item);

//void inserirMeio(Lista, Item, Item);

/**
 * @brief Insere no fim da lista.
 * @param lista Lista genérica escolhida para inserção.
 * @param item Ponteiro para um tipo qualquer de estrutura/variável na qual será inserida na lista.
 * @return Não há retorno de algum valor.
 */
void inserirFim(Lista lista, Item item);

/**
 * @brief Remove o primeiro item da lista.
 * @param lista Lista genérica escolhida para remoção do item.
 * @return Retorna o primeiro item da lista caso encontrado, NULL caso contrário.
 */
Item removerInicio(Lista lista);

/**
 * @brief Remove o último item da lista.
 * @param lista Lista genérica escolhida para remoção do item.
 * @return Retorna o último item da lista caso encontrado, NULL caso contrário.
 */
Item removerFim(Lista lista);

/**
 * @brief Remove o item especfiicado da lista.
 * @param lista Lista genérica escolhida para remoção do item.
 * @param compFunc Função de comparação entre dois itens.
 * @param item Ponteiro para o item que será removido da lista.
 * @return Retorna o item removido caso encontrado, NULL caso contrário.
 */
Item remover(Lista lista, compararItens compFunc, Item item);

/**
 * @brief Verifica de a lista especificada está vazia.
 * @param lista Lista genérica para verificação.
 * @return Retorna Verdadeiro (True) caso a lista esteja vazia, Falso (False) caso contrário.
 */
bool isListaVazia(Lista lista);

/**
 * @brief Verifica o tamanho da lista especificada.
 * @param lista Lista genérica para verificação.
 * @return Retorna o tamanho da lista.
 */
int listaTamanho(Lista lista);

/**
 * @brief Mapeia os itens de uma lista para uma outra depois de aplicada uma dada função.
 * 
 * AVISO: RECOMENDADO LIMPAR A LISTA 'TO' ANTES DE MAPEAR!
 * @param from Lista genérica da origem dos itens de mapeamento.
 * @param to Lista genérica de destino dos itens de mapeamento.
 * @param mapFunc Ponteiro de função que aplica uma operação qualquer nos itens.
 * @param copyFunc Ponteiro de função que retorna uma co'pia do item a ser inserido na nova lista, caso seja nulo, compartilha a memo'ria entre as listas.
 * @param extra Ponteiro para um valor/estrutura qualquer usado para auxiliar o processamento da função mapFunc
 * @return Não há retorno de algum valor.
 */
void mapTo(Lista from, Lista to, mapFunction mapFunc, copyFunction copyFunc, void* extra);

/**
 * @brief Concatena duas listas.
 * @param receive Lista genérica que conterá os itens de ambas as listas.
 * @param concatFrom Lista genérica que será concatenada à lista receive.
 * @param itemSize Tamanho em bytes de um item armazenado na lista concatFrom.
 * @return Não há retorno de algum valor.
 */
void concatLista(Lista receive, Lista concatFrom, size_t itemSize);

/**
 * @brief Percorre a lista fornecida e aplica uma dada função à cada item da lista.
 * @param lista Lista genérica para percorrer.
 * @param runFunc Ponteiro de uma função qualquer que recebe cada um dos itens da lista.
 * @param extra Ponteiro para um valor/estrutura qualquer usado para auxiliar o processamento da função runFunc.
 * @return Não há retorno de algum valor.
 */
void percorrerLista(Lista lista, runThroughItems runFunc, void* extra);

/**
 * @brief Percorre a lista fornecida na ordem inversa e aplica uma dada função à cada item da lista.
 * @param lista Lista genérica para percorrer inversamente.
 * @param runFunc Ponteiro de uma função qualquer que recebe cada um dos itens da lista.
 * @param extra Ponteiro para um valor/estrutura qualquer usado para auxiliar o processamento da função runFunc.
 * @return Não há retorno de algum valor.
 */
void percorrerListaReverso(Lista lista, runThroughItems runFunc, void* extra);

/**
 * @brief Verifica se um dado elemento está contido na lista fornecida.
 * @param lista Lista genérica para verificação.
 * @param compFunc Ponteiro de uma função de comparação de dois itens.
 * @param item Item usado para comparar se ele está contido na lista.
 * @return Retorna Verdadeiro (True) caso o item esteja na lista, Falso (False) caso contrário.
 */
bool isInLista(Lista lista, compararItens compFunc, Item item);

/**
 * @brief Percorre a lista fornecida até o index do dado elemento de 0 ate' tam-1.
 * @param lista Lista genérica para percorrer.
 * @param index Inteiro usado para indicar a posição do item.
 * @return Retorna o item posicionado no index fornecido, NULL caso o index seja inva'lido.
 */
Item getItemLista(Lista lista, int index);

/**
 * @brief Busca e retorna o index do item da lista que satisfaz a funcao de comparacao, o index va'lido esta' entre
 * 0 e tam-1.
 * @param lista Lista gene'rica para busca.
 * @param compFunc Funcao de comparacao que define a condicao de igualdade.
 * @param item Item usado como referencia para busca da posicao.
 * @return Retorna a posicao do item encontrado caso exista, -1 caso contrário.
 */
int getItemIndexLista(Lista lista, compararItens compFunc, Item item);

/**
 * @brief Limpa todos os elementos da lista especificada.
 * @param lista Lista genérica para limpeza.
 * @param freeFunc Ponteiro para uma funcao para liberar a memoria dos itens armazenados na lista. Caso seja nulo, nao libera os itens.
 * @param extra Ponteiro para um item auxiliar a ser passada para a funcao freeFunc caso necessa'rio.
 * @return Não há retorno de algum valor.
 */
void limparLista(Lista lista, freeFunc fFunc, void* extra);

/**
 * @brief Copia os itens de uma lista para uma outra lista.
 * 
 * AVISO: RECOMENDADO LIMPAR A LISTA 'TO' ANTES DE COPIAR!
 * @param from Lista gene'rica para cópia dos itens.
 * @param to Lista genérica para destino das co'pias da lista from.
 * @param copyFunc Ponteiro de função que retorna uma co'pia do item a ser inserido na nova lista.
 * @return Nao ha' retorno de algum valor.
 */
void copyLista(Lista from, Lista to, copyFunction copyFunc);

/**
 * @brief Destroi a lista passada.
 * @param lista Lista genérica para ser destruida.
 * @param freeFunc Ponteiro para uma funcao para liberar a memoria dos itens armazenados na lista. Caso seja nulo, nao libera os itens.
 * @param extra Ponteiro para um item auxiliar a ser passada para a funcao freeFunc caso necessa'rio.
 * @return Não há retorno de algum valor.
 */
void destroiLista(Lista l, freeFunc freeItens, void* extra);

#endif
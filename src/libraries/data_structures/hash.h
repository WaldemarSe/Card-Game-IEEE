#ifndef _HASH_h_
#define _HASH_h_

#include <stdbool.h>

#include "types.h"

/**
 * Mo'dulo especializado para a implementacao da tabela de espalhamento (Hash Table).
 * 
 * Uma tabela de espalhamento tem por principal funcao a associacao de dois valores,
 * na tabela implementada, ela possui a associacao entre nome-valor.
 * Sendo:
 * Nome, uma String;
 * Valor, um ponteiro para um dado qualquer.
 */

typedef void* Hash;

/**
 * @brief Cria uma tabela Hash (espalhamento).
 * @param tam Tamanho da tabela 'a ser criada.
 * @param gerarPrimo Valor booleano: True -> Gera uma tabela de tamanho de pro'ximo primo ao valor tam (recomendado), False -> Gera uma tabela de tamanho tam.
 * @param fPreenchimento Valor decimal (de 0 'a 1) que representa o fator ma'ximo de preenchimento da tabela.
 * @return Retorna um ponteiro para a tabela criada.
 */
Hash criaHash(int tam, bool gerarPrimo, double fPreenchimento);

/**
 * @brief Insere uma nova informacao na tabela Hash especificada.
 * 
 * AVISO: Caso a tabela ultrapasse o fator de preenchimento estabelecido, e' alocada uma nova tabela com o pro'ximo primo do dobro do espaco anterior.
 * @param hash Tabela hash a ser inserida um valor novo.
 * @param nome String a ser associada ao valor.
 * @param valor Ponteiro para um valor a ser associado ao nome especificado.
 * @return Nao ha' retorno de algum valor.
 */
void inserirHash(Hash hash, const char* nome, Item valor);

/**
 * @brief Pega o valor associado ao nome na tabela Hash especificada.
 * @param hash Tabela hash a ser buscada o valor.
 * @param nome String a ser buscada dentro da tabela.
 * @return Retorna um ponteiro para o valor associado ao nome.
 */
Item getHashValue(Hash hash, const char* nome);

/**
 * @brief Remove o valor associado ao nome na tabela Hash especificada.
 * @param hash Tabela hash a ser removida o valor.
 * @param nome String a ser buscada dentro da tabela para remocao.
 * @return Retorna um ponteiro para o valor associado ao nome.
 */
Item removeHashValue(Hash hash, const char* nome);

/**
 * @brief Destroi a tabela Hash especificada.
 * @param hash Tabela hash a ser destrui'da.
 * @param fFunc Ponteiro para um funcao de liberacao para os valores inseridos na tabela.
 * @param extra Ponteiro para um item auxiliar a ser passada para a funcao freeFunc caso necessa'rio.
 * @return Nao ha' retorno de algum valor.
 */
void destroiHash(Hash hash, freeFunc fFunc, void* extra);

// DEBUG FUNCTIONS

void imprimirHash(Hash hash, printFunc pFunc);

#endif
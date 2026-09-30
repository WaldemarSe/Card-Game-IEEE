#ifndef _TextObject_h_
#define _TextObject_h_

#include <stdbool.h>
#include <raylib.h>

#include <delimiters.h>

/**
 * Cabecalho destinado 'a manipulacao de visualizacao de textos pela bilbioteca gra'fica 'raylib'.
 * 
 * O mo'dulo disponinliza um tipo TextObject, no qual oferece modificacoes de recursos do
 * texto para melhor manipulacao de strings dentro do DrawText do raylib.
 */

typedef void* TextObject;

/**
 * @brief Cria uma instancia de um objeto de texto.
 * @param text A string inicial que o objeto ira' conter.
 * @return Retorna o objeto de texto criado, ou NULL caso falhe.
 */
TextObject Text_Init(const char* text);

/**
 * @brief Cria uma co'pia profunda de um objeto de texto existente.
 * @param txtObj O objeto de texto original a ser copiado.
 * @return Retorna uma nova instancia de TextObject com os mesmos atributos.
 */
TextObject Text_Copy(TextObject txtObj);

/**
 * @brief Altera a string de conteu'do do objeto de texto.
 * @param txtObj O objeto de texto a ser modificado.
 * @param text A nova string a ser atribuida ao objeto.
 * @return Nao ha' retorno de algum valor.
 */
void Text_Set(TextObject txtObj, const char* text);

/**
 * @brief Define o tamanho da fonte para a renderizacao do texto.
 * @param txtObj O objeto de texto a ser modificado.
 * @param fontSize O novo tamanho da fonte em pixels.
 * @return Nao ha' retorno de algum valor.
 */
void Text_SetFontSize(TextObject txtObj, int fontSize);

/**
 * @brief Define o preenchimento (padding) do retangulo delimitador do texto.
 * @param txtObj O objeto de texto a ser modificado.
 * @param padding O valor de preenchimento a ser aplicado.
 * @return Nao ha' retorno de algum valor.
 */
void Text_SetRecPadding(TextObject txtObj, float padding);

/**
 * @brief Escala o objeto de texto proporcionalmente.
 * @param txtObj O objeto de texto a ser modificado.
 * @param scaling O fator de escala (ex: 2.0 para dobrar de tamanho).
 * @return Nao ha' retorno de algum valor.
 */
void Text_Scale(TextObject txtObj, float scaling);

/**
 * @brief Define a posicao absoluta do texto no espaco 2D.
 * @param txtObj O objeto de texto a ser modificado.
 * @param position Vetor Vector2 contendo as coordenadas X e Y.
 * @return Nao ha' retorno de algum valor.
 */
void Text_SetPosition(TextObject txtObj, Vector2 position);

/**
 * @brief Define a cor do texto.
 * @param txtObj O objeto de texto a ser modificado.
 * @param color A nova cor do texto.
 * @return Nao ha' retorno de algum valor.
 */
void Text_SetColor(TextObject txtObj, Color color);

/**
 * @brief Verifica se um ponto especifico esta' sobre a a'rea do texto.
 * @param txtObj O objeto de texto para verificacao.
 * @param point O ponto (Vector2) a ser testado (ex: posicao do mouse).
 * @return Retorna true se o ponto estiver dentro do retangulo do texto, false caso contra'rio.
 */
bool Text_IsPointOverText(TextObject txtObj, Vector2 point);

/**
 * @brief Move o texto com base em um deslocamento relativo.
 * @param txtObj O objeto de texto a ser movido.
 * @param delta O vetor de deslocamento a ser somado 'a posicao atual.
 * @return Nao ha' retorno de algum valor.
 */
void Text_MoveDelta(TextObject txtObj, Vector2 delta);

/**
 * @brief Renderiza o objeto de texto na tela.
 * @param txtObj O objeto de texto a ser desenhado.
 * @return Nao ha' retorno de algum valor.
 */
void Text_Draw(TextObject txtObj);

/**
 * @brief Obtém o identificador u'nico do objeto de texto.
 * @param txtObj O objeto de texto escolhido.
 * @return Retorna o valor inteiro correspondente ao ID.
 */
int Text_getId(TextObject txtObj);

/**
 * @brief Obtém o retangulo delimitador (Bounding Box) do texto.
 * @param txtObj O objeto de texto escolhido.
 * @return Retorna um retangulo que delimita o texto.
 */
Rectangle Text_getRectangle(TextObject txtObj);

/**
 * @brief Pega o tamanho do texto do textObject passado;
 * @param txtObj O objeto de texto escolhido.
 * @return Retorna o tamanho da string de texto do objeto.
 */
int Text_getTextLength(TextObject txtObj);

/**
 * @brief Pega o tamanho (espacial) do textObject passado;
 * @param txtObj O objeto de texto escolhido.
 * @return Retorna o tamanho (largura) do texto do objeto.
 */
float Text_getLength(TextObject txtObj);

/**
 * @brief Pega a string do texto do textObject passado;
 * @param txtObj O objeto de texto escolhido.
 * @return Retorna uma string contendo o conteu'do de texto do objeto.
 */
const char* Text_getText(TextObject txtObj);

/**
 * @brief Obtém o valor da borda atual do objeto.
 * @param txtObj O objeto de texto escolhido.
 * @return Retorna o valor do padding.
 */
float Text_getPadding(TextObject txtObj);

/**
 * @brief Libera a memoria alocada pelo objeto de texto criado.
 * @param txtObj O objeto de texto 'a ser liberado.
 * @return Nao ha' retorno de algum valor.
 */
void Text_Free(TextObject txtObj);

/**
 * @brief Libera todas as instancias de memoria alocadas pelos objetos de texto criados.
 * @return Nao ha' retorno de algum valor.
 */
void Text_FreeAll();

#endif
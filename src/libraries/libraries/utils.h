#ifndef _Utils_h_
#define _Utils_h_

#include <raylib.h>
#include <stddef.h>
#include <stdbool.h>

#include <types.h>
#include <hash.h>

// Minimal WinAPI cursor declarations (Windows only)
typedef void* HCURSOR;
typedef void* HINSTANCE;
typedef const wchar_t* LPCWSTR;   // wide string (Windows uses UTF-16)

__declspec(dllimport) HCURSOR __stdcall LoadCursorW(HINSTANCE hInstance, LPCWSTR lpCursorName);
__declspec(dllimport) HCURSOR __stdcall SetCursor(HCURSOR hCursor);

// Predefined system cursor IDs
#define IDC_ARROW   ((LPCWSTR)32512)
#define IDC_HAND    ((LPCWSTR)32649)
#define IDC_SIZEALL ((LPCWSTR)32646)

#define TO_STRING(variable) #variable

/**
 * @brief Aguarda por um determinado período e sinaliza a passagem do intervalo.
 * @param intervalo O tempo em segundos a ser esperado.
 * @return Retorna true se o intervalo foi atingido, false caso contra'rio.
 */
bool wait(double intervalo);

/**
 * @brief Normaliza um valor de ponto flutuante para o inteiro mais proximo.
 * @param value O valor original em float.
 * @return Retorna o valor normalizado como inteiro.
 */
int normalize(float value);

/**
 * @brief Retorna um valor dentro do intervalo especificado conforme value.
 * @param value Valor a ser restringido.
 * @param minBound Limite inferior.
 * @param maxBound Limite Superior.
 * @return Retorna o valor dentro do intervalo especificado.
 */
int clamp(int value, int minBound, int maxBound);

/**
 * @brief Retorna um valor de ponto flutuante dentro do intervalo especificado conforme value.
 * @param value Valor a ser restringido.
 * @param minBound Limite inferior.
 * @param maxBound Limite Superior.
 * @return Retorna o valor de ponto flutuante dentro do intervalo especificado.
 */
float fclamp(float value, float minBound, float maxBound);

/**
 * @brief Desenha uma seta na tela entre dois pontos.
 * @param start Coordenada de origem da seta.
 * @param end Coordenada de destino da seta (ponta).
 * @param headLength Comprimento da cabeca da seta.
 * @param headWidth Largura da cabeca da seta.
 * @param backOffset Deslocamento da seta em relacao ao ponto final.
 * @param color A cor utilizada para a seta.
 * @return Nao ha' retorno de algum valor.
 */
void DrawArrow(Vector2 start, Vector2 end, float headLength, float headWidth, float backOffset, Color color);

/**
 * @brief Calcula a coordenada central de um retangulo.
 * @param rectangle O retangulo de referencia.
 * @return Retorna a coordenada correspondente ao centro do retângulo.
 */
Vector2 getRectCenter(Rectangle rectangle);

/**
 * @brief Reduz o tamanho do retangulo igualmente em todos os lados (reducao centralizada).
 * @param rectangle O retangulo a ser reduzido.
 * @param factor O fator de reducao (0 <= factor <= 1)
 * @return Retorna um retangulo reduzido.
 */
Rectangle reduceRecSizeEvenly(Rectangle rectangle, float factor);

Rectangle increaseRecSizeEvenly(Rectangle rectangle, float factor);

/**
 * @brief Pega o angulo entre dois pontos no plano.
 * @param v1 Ponto 1 (origem do angulo).
 * @param v2 Ponto 2 (destino do angulo).
 * @return Retorna o angulo dos dois pontos.
 */
float getVector2Angle(Vector2 v1, Vector2 v2);

/**
 * @brief Definição de tipo para funções de interpolação.
 * * @param t O tempo normalizado (valor entre 0 e 1).
 * @return Retorna o valor da função no instante t (valor entre 0 e 1).
 */
typedef float (*interpolationFunction)(float t);

///////////////////////////////////////////
/* FUNCOES DE INTERPOLACAO PRE-DEFINIDAS */
///////////////////////////////////////////

float linearFunction(float t);

float easeInFunction(float t);

float easeOutFunction(float t);

float quadraticFunction(float t);

float rootFunction(float t);

float easeInOutFunction(float t);

float easeInOutCubic(float t);

float easeInOutQuint(float t);

float easeInOutCirc(float t);

float easeInOutBack(float t);

float easeOutBounce(float t);

float easeOutBack(float t);

float bellFunction(float t);

///////////////////////////////////////////

/**
 * Gerenciamento de memoria pela tabela Hash para as instancias de
 * todas as bibliotecas simplificadas do Raylib (libraries).
 */

void createAndInsertInstance(Hash* hash, int id, Item item);

Item removeInstance(Hash hash, int id);

#endif
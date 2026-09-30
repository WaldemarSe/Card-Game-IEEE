#ifndef _MathGraph_h_
#define _MathGraph_h_

#include <stdbool.h>
#include <raylib.h>

#include "utils.h"

/**
 * Cabecalho destinado 'a visualizacao e manipulacao de graficos matematicos.
 * * O modulo permite a renderizacao de graficos baseados em funcoes de interpolacao,
 * facilitando a exibicao de curvas e dados dentro de um quadro (frame) especifico.
 */

typedef void* MathGraph;

/**
 * @brief Inicializa uma instancia de um grafico matema'tico.
 * @param interFunc Funcao de interpolacao que define o comportamento da curva.
 * @param numPoints Quantidade de pontos a serem calculados para a renderizacao.
 * @param frame Retangulo que define a area de exibicao do grafico na tela.
 * @param lineThickness Espessura da linha utilizada para desenhar o grafico.
 * @return Retorna o objeto MathGraph criado, ou NULL caso ocorra erro.
 */
MathGraph MathGraph_Init(interpolationFunction interFunc, int numPoints, Rectangle frame, float lineThickness);

/**
 * @brief Redimensiona a a'rea de exibicao do grafico.
 * @param mathGraph O objeto de grafico a ser modificado.
 * @param frame O novo retangulo que definira os limites de exibicao.
 * @return Nao ha' retorno de algum valor.
 */
void MathGraph_Resize(MathGraph mathGraph, Rectangle frame);

/**
 * @brief Altera a quantidade de pontos processados pelo grafico.
 * @param mathGraph O objeto de gra'fico a ser modificado.
 * @param points O novo numero de pontos para detalhamento da curva.
 * @return Nao ha' retorno de algum valor.
 */
void MathGraph_Points(MathGraph mathGraph, int points);

/**
 * @brief Renderiza o gra'fico matematico na tela.
 * @param mathGraph O objeto de grafico a ser desenhado.
 * @return Nao ha' retorno de algum valor.
 */
void MathGraph_Draw(MathGraph mathGraph);

/**
 * @brief Libera a memoria alocada pelo objeto de mathGraph criado.
 * @param mathGraph O objeto de grafico 'a ser liberado.
 * @return Nao ha' retorno de algum valor.
 */
void MathGraph_Free(MathGraph mathGraph);

/**
 * @brief Libera toda a memoria alocada para os objetos de graficos criados.
 * @return Nao ha' retorno de algum valor.
 */
void MathGraph_FreeAll();

#endif
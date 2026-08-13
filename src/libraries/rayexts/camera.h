#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <raylib.h>

/**
 * Cabecalho destinado ao gerenciamento de visualizacao e transformacao de camera.
 * O modulo abstrai a Camera2D do raylib, permitindo manipulacoes de zoom,
 * movimento e conversao de coordenadas entre espacos de mundo e tela.
 */

typedef void* MyCamera;

/**
 * @brief Inicializa uma instancia personalizada de camera.
 * @param position Coordenada inicial da camera.
 * @param offset Deslocamento em relacao 'a posicao.
 * @param zoomBaseFactor Fator de escala inicial (1.0 para padrao).
 * @return Retorna o objeto MyCamera criado, ou NULL caso ocorra erro.
 */
MyCamera cameraInit(Vector2 position, Vector2 offset, float zoomBaseFactor);

/**
 * @brief Converte um ponto do espaco de mundo para o espaco da camera.
 * @param camera O objeto de camera escolhido.
 * @param point O ponto no espaco global a ser convertido.
 * @return Retorna a coordenada correspondente 'a posicao relativa 'a camera.
 */
Vector2 getPointOnCamera(MyCamera camera, Vector2 point);

/**
 * @brief Move a camera com um delta.
 * @param camera O objeto de camera a ser movido.
 * @param delta O vetor (x, y) de deslocamento.
 * @param zoomProportional Se verdadeiro, o movimento sera escalonado pelo zoom atual.
 * @return Nao ha' retorno de algum valor.
 */
void cameraMove(MyCamera camera, Vector2 delta, bool zoomProportional);

/**
 * @brief Move a camera para um posicao.
 * @param camera O objeto de camera a ser movido.
 * @param delta O vetor (x, y) de posicao.
 * @return Nao ha' retorno de algum valor.
 */
void cameraSetPosition(MyCamera camera, Vector2 position);

/**
 * @brief Calcula o deslocamento de um ponto corrigido pelo zoom da camera.
 * @param camera O objeto de camera para referencia.
 * @param delta O vetor de deslocamento original.
 * @return Retorna a coordenada com o deslocamento ajustado para a escala da camera.
 */
Vector2 getCameraPointDelta(MyCamera camera, Vector2 delta);

/**
 * @brief Altera o zoom da camera.
 * @param camera O objeto de camera 'a ser modificado.
 * @param factor O multiplicador de escala 'a ser aplicado.
 * @return Nao ha' retorno de algum valor.
 */
void cameraZoom(MyCamera camera, float factor);

Rectangle cameraGetRec(MyCamera camera);

void cameraSetRec(MyCamera camera, Rectangle rec);

Vector2 cameraGetOffset(MyCamera camera);

float cameraGetZoom(MyCamera camera);

/**
 * @brief Inicia o modo de renderizacao 2D da camera.
 * Deve ser chamado antes de desenhar os objetos que seguem a camera.
 * @param camera O objeto de camera escolhido.
 * @return Nao ha' retorno de algum valor.
 */
void openCamera(MyCamera camera);

/**
 * @brief Finaliza o modo de renderizacao 2D da camera.
 * Restaura o sistema de coordenadas padrao da tela.
 * @param camera O objeto de camera escolhido.
 * @return Nao ha' retorno de algum valor.
 */
void closeCamera(MyCamera camera);

/**
 * @brief Libera a memoria alocada para o objeto de camera criado.
 * @param camera O objeto de camera a ser liberado.
 * @return Nao ha' retorno de algum valor.
 */
void cameraFree(MyCamera camera);

/**
 * @brief Libera toda a memoria alocada para os objetos de camera criados.
 * @return Nao ha' retorno de algum valor.
 */
void cameraFreeAll();

#endif
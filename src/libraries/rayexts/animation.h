#ifndef _Animation_h_
#define _Animation_h_

#include "utils.h"
#include <delimiters.h>

/**
 * Cabecalho destinado ao gerenciamento e execucao de animacoes de transformacao.
 * O modulo permite a composicao de diferentes tipos de animacoes (posicao, escala e frames)
 * em um unico objeto, oferecendo controle sobre o tempo e funcoes de interpolacao.
 */

typedef void* Animation;

/**
 * @brief Inicializa uma instancia de um gerenciador de animacoes.
 * @return Retorna o objeto Animation criado com todos os componentes nulos.
 */
Animation Animation_Init();

/////////////////////////////////////////////////////////
// INITS PARA TODOS
/////////////////////////////////////////////////////////

/**
 * @brief Adiciona um componente de animacao de posicao ao objeto.
 * @param animation O objeto de animacao a ser modificado.
 * @param interFunc Funcao de interpolacao para o movimento.
 * @return Nao ha retorno de algum valor.
 */
void Animation_AddPositionAnimation(Animation animation, interpolationFunction interFunc);

/**
 * @brief Adiciona um componente de animacao de escala ao objeto.
 * @param animation O objeto de animacao a ser modificado.
 * @param rectangle O retangulo inicial de referencia para a escala.
 * @param interFunc Funcao de interpolacao para o redimensionamento.
 * @return Nao ha retorno de algum valor.
 */
void Animation_AddScaleAnimation(Animation animation, Rectangle rectangle, interpolationFunction interFunc);

/**
 * @brief Adiciona um componente de animacao por frames (sprite animation).
 * @param animation O objeto de animacao a ser modificado.
 * @param amountOfFrames Quantidade total de quadros da animacao.
 * @param framesSpeed Velocidade da troca de quadros (frames por segundo).
 * @param frameDelta A distancia de um frame ao outro em pixels.
 * @return Nao ha retorno de algum valor.
 */
void Animation_AddFramesAnimation(Animation animation, int amountOfFrames, float framesSpeed, float frameDelta);

/////////////////////////////////////////////////////////
// POSITION
/////////////////////////////////////////////////////////

/**
 * @brief Define um objetivo de movimento para a animacao de posicao.
 * @param animation O objeto de animacao escolhido.
 * @param finalPoint Coordenada de destino final.
 * @param duration Tempo em segundos para completar o percurso.
 * @return Nao ha retorno de algum valor.
 */
void Animation_MoveTo(Animation animation, Vector2 finalPoint, float duration);

/**
 * @brief Atualiza o estado logico da animacao de posicao.
 * @param animation O objeto de animacao a ser processado.
 * @param deltaTime Tempo decorrido desde o ultimo frame.
 * @return Nao ha retorno de algum valor.
 */
void Animation_UpdatePosition(Animation animation, float deltaTime);

/**
 * @brief Verifica se a animacao de posicao esta em execucao.
 * @param animation O objeto de animacao de referencia.
 * @return Retorna true se houver um deslocamento ativo, false caso contrario.
 */
bool Animation_PositionIsAnimating(Animation animation);

/////////////////////////////////////////////////////////
// RESIZE
/////////////////////////////////////////////////////////

/**
 * @brief Define um objetivo de redimensionamento para a animacao de escala.
 * @param animation O objeto de animacao escolhido.
 * @param scaleTo Fator de escala final desejado.
 * @param duration Tempo em segundos para completar a transicao.
 * @return Nao ha retorno de algum valor.
 */
void Animation_Resize(Animation animation, float scaleTo, float duration);

/**
 * @brief Atualiza o estado logico da animacao de escala.
 * @param animation O objeto de animacao a ser processado.
 * @param deltaTime Tempo decorrido desde o ultimo frame.
 * @return Nao ha retorno de algum valor.
 */
void Animation_UpdateScale(Animation animation, float deltaTime);

/**
 * @brief Verifica se a animacao de escala esta em execucao.
 * @param animation O objeto de animacao de referencia.
 * @return Retorna true se houver um redimensionamento ativo, false caso contrario.
 */
bool Animation_ScaleIsAnimating(Animation animation);

/**
 * @brief Forca a finalizacao imediata da animacao de escala, definindo-a para o estado final.
 * @param animation O objeto de animacao a ser modificado.
 * @return Nao ha retorno de algum valor.
 */
void Animation_EndResize(Animation animation);

/////////////////////////////////////////////////////////
// FRAMES
/////////////////////////////////////////////////////////

/**
 * @brief Atualiza o contador de tempo e a troca de quadros (frames) da animacao.
 * @param animation O objeto de animacao a ser processado.
 * @param deltaTime Tempo decorrido desde o ultimo frame.
 * @return Nao ha retorno de algum valor.
 */
void Animation_UpdateFrames(Animation animation, float deltaTime);

/**
 * @brief Inverte a ordem de reproducao dos frames da animacao.
 * @param animation O objeto de animacao a ser modificado.
 * @return Nao ha retorno de algum valor.
 */
void Animation_ReverseFrames(Animation animation);

/**
 * @brief Verifica se a animacao por frames esta em execucao.
 * @param animation O objeto de animacao de referencia.
 * @return Retorna true se a troca de quadros estiver ativa.
 */
bool Animation_FramesIsAnimating(Animation animation);

/**
 * @brief Reinicia a contagem de frames para o quadro inicial (zero).
 * @param animation O objeto de animacao a ser modificado.
 * @return Nao ha retorno de algum valor.
 */
void Animation_ResetFrames(Animation animation);

/**
 * @brief Define ou redefine as propriedades de uma animacao de frames existente.
 * @param animation O objeto de animacao a ser modificado.
 * @param amountOfFrames Nova quantidade total de quadros.
 * @param frameDelta Novo deslocamento em pixels entre frames.
 * @param framesSpeed Nova velocidade de reproducao.
 * @return Nao ha retorno de algum valor.
 */
void Animation_SetFrames(Animation animation, int amountOfFrames, float frameDelta, float framesSpeed);

/**
 * @brief Calcula a coordenada X ou Y do frame atual para uso em Source Rectangles.
 * @param animation O objeto de animacao escolhido.
 * @return Retorna o valor em pixels correspondente ao frame atual.
 */
float Animation_GetFrameCoord(Animation animation);

/////////////////////////////////////////////////////////
// UPDATE DE TODOS
/////////////////////////////////////////////////////////

/**
 * @brief Atualiza todos os componentes de animacao inicializados (posicao, escala e frames).
 * @param animation O objeto de animacao a ser processado.
 * @param deltaTime Tempo decorrido desde o ultimo frame.
 * @return Nao ha retorno de algum valor.
 */
void Animation_UpdateAll(Animation animation, float deltaTime);

/**
 * @brief Define manualmente a posicao atual da animacao.
 * @param animation O objeto de animacao a ser modificado.
 * @param position Nova coordenada de posicao.
 * @return Nao ha retorno de algum valor.
 */
void Animation_SetPosition(Animation animation, Vector2 position);

/**
 * @brief Obtem a coordenada de posicao atual da animacao.
 * @param animation O objeto de animacao escolhido.
 * @return Retorna a coordenada correspondente a posicao atual.
 */
Vector2 Animation_GetPosition(Animation animation);

/**
 * @brief Define manualmente o retangulo de escala da animacao.
 * @param animation O objeto de animacao a ser modificado.
 * @param rectangle Estrutura com as novas dimensoes.
 * @return Nao ha retorno de algum valor.
 */
void Animation_SetRectangle(Animation animation, Rectangle rectangle);

/**
 * @brief Obtem o retangulo de escala atual da animacao.
 * @param animation O objeto de animacao escolhido.
 * @return Retorna o retangulo correspondente ao estado atual de escala.
 */
Rectangle Animation_GetScale(Animation animation);

/**
 * @brief Altera a funcao de interpolacao do movimento de posicao.
 * @param animation O objeto de animacao a ser modificado.
 * @param interFunc Nova funcao de interpolacao (Ex: easeInOut, linear).
 * @return Nao ha retorno de algum valor.
 */
void Animation_SetPositionFunction(Animation animation, interpolationFunction interFunc);

/**
 * @brief Altera a funcao de interpolacao do redimensionamento de escala.
 * @param animation O objeto de animacao a ser modificado.
 * @param interFunc Nova funcao de interpolacao.
 * @return Nao ha retorno de algum valor.
 */
void Animation_SetScaleFunction(Animation animation, interpolationFunction interFunc);

/////////////////////////////////////////////////////////
// FREE's
/////////////////////////////////////////////////////////

/**
 * @brief Libera a memoria alocada para o objeto de animacao criado.
 * @param animation O objeto de animacao a ser liberado.
 * @return Nao ha retorno de algum valor.
 */
void Animation_Free(Animation animation);

/**
 * @brief Libera toda a memoria alocada para a lista global de animacoes criadas.
 * @return Nao ha retorno de algum valor.
 */
void Animation_FreeAll();

#endif
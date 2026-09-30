#ifndef _ANIMATEDBUTTON_h_
#define _ANIMATEDBUTTON_h_

#include <stdbool.h>
#include <raylib.h>

/**
 * Cabecalho destinado ao gerenciamento de botoes com suporte a animacoes fluidas.
 * O modulo estende as funcionalidades de interface, adicionando comportamentos
 * dinamicos como feedback visual de redimensionamento e transicoes de estado.
 */

typedef void* AnimatedButton;

/**
 * @brief Inicializa uma instancia de botao animado com parametros de escala e velocidade.
 * @param text O conteudo textual a ser exibido no botao.
 * @param fontsize O tamanho da fonte do texto.
 * @param position A coordenada (x, y) inicial do botao na tela.
 * @param textFill Cor do texto em estado normal.
 * @param border Cor da borda do botao.
 * @param textHover Cor do texto durante a interacao.
 * @param fillHover Cor de preenchimento durante a interacao.
 * @param resizeRatio Fator de escala para a animacao (ex: 1.1 para aumentar 10%).
 * @param speedAnim Velocidade da transicao da animacao.
 * @return Retorna o objeto AnimatedButton criado, ou NULL caso ocorra erro.
 */
AnimatedButton AnimatedButton_Init(const char* text, int fontsize, Vector2 position, Color textFill, Color border, Color textHover, Color fillHover, float resizeRatio, float speedAnim);

/**
 * @brief Verifica se o botao foi pressionado pelo mouse no frame atual.
 * @param button O objeto botao a ser verificado.
 * @return Retorna true se houver interacao de clique descendente.
 */
bool AnimatedButton_isPressedByMouse(AnimatedButton button);

/**
 * @brief Verifica se o botao foi solto pelo mouse, confirmando a acao de clique.
 * @param button O objeto botao a ser verificado.
 * @return Retorna true se o botao do mouse foi liberado sobre a area do botao.
 */
bool AnimatedButton_isReleasedByMouse(AnimatedButton button);

/**
 * @brief Dispara o gatilho visual da animacao do botao.
 * @param button O objeto botao que executara a animacao.
 * @return Nao ha retorno.
 */
void AnimatedButton_PlayAnimation(AnimatedButton button);

/**
 * @brief Executa um feedback visual imediato (geralmente uma resposta rapida ao toque).
 * @param button O objeto botao a receber o feedback.
 * @return Nao ha retorno.
 */
void AnimatedButton_Feedback(AnimatedButton button);

/**
 * @brief Atualiza os estados logicos e quadros da animacao baseados no tempo.
 * @param button O objeto botao a ser atualizado.
 * @param deltaTime O tempo decorrido desde o ultimo frame (GetFrameTime).
 * @return Nao ha retorno.
 */
void AnimatedButton_Update(AnimatedButton button, float deltaTime);

/**
 * @brief Renderiza o botao animado na tela com suas transformacoes atuais.
 * @param button O objeto botao a ser desenhado.
 * @return Nao ha retorno.
 */
void AnimatedButton_Draw(AnimatedButton button);

/**
 * @brief Libera a memoria alocada para o objeto de botao animado.
 * @param button O objeto botao a ser liberado.
 * @return Nao ha retorno.
 */
void AnimatedButton_Free(AnimatedButton button);

#endif
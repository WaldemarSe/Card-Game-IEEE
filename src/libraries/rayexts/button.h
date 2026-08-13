#ifndef _Button_h_
#define _Button_h_

#include "utils.h"
#include "delimiters.h"

/**
 * Cabecalho destinado ao gerenciamento de elementos de interface do tipo botao.
 * O mo'dulo permite a criacao, customizacao visual, deteccao de interacao
 * e renderizacao de botoes retangulares com suporte a estados de hover.
 */

typedef void* Button;

/**
 * @brief Inicializa uma instancia de botao com propriedades visuais e de texto.
 * @param text O conteudo textual a ser exibido no botao.
 * @param fontsize O tamanho da fonte do texto.
 * @param position A coordenada (x, y) inicial do botao na tela.
 * @param textFill Cor do texto em estado normal.
 * @param border Cor da borda do botao.
 * @param textHover Cor do texto quando o mouse esta sobre o botao.
 * @param fillHover Cor de preenchimento quando o mouse esta sobre o botao.
 * @return Retorna o objeto Button criado, ou NULL caso ocorra erro.
 */
Button Button_Init(const char* text, int fontsize, Vector2 position, Color textFill, Color border, Color textHover, Color fillHover);

/**
 * @brief Redimensiona o botao com base em um fator de escala.
 * @param button O objeto botao a ser escalonado.
 * @param scale Fator de multiplicacao para as dimensoes do botao.
 * @return Nao ha retorno.
 */
void Button_Scale(Button button, float scale);

/**
 * @brief Ajusta as dimensoes do retangulo do botao para envolver o texto atual.
 * @param button O objeto botao a ser ajustado.
 * @return Nao ha retorno.
 */
void Button_FitSizeToTextsize(Button button);

/**
 * @brief Ajusta o tamanho da fonte para que o texto caiba nas dimensoes atuais do botao.
 * @param button O objeto botao a ser ajustado.
 * @return Nao ha retorno.
 */
void Button_FitTextsizeToSize(Button button);

/**
 * @brief Define uma nova posicao para o botao no espaco da tela.
 * @param button O objeto botao a ser movido.
 * @param position O novo vetor de posicao (x, y).
 * @return Nao ha retorno.
 */
void Button_SetPosition(Button button, Vector2 position);

/**
 * @brief Define diretamente a area retangular (posicao e dimensao) do botao.
 * @param button O objeto botao a ser modificado.
 * @param rec Estrutura Rectangle com os novos valores de retangulo.
 * @return Nao ha retorno.
 */
void Button_SetRec(Button button, Rectangle rec);

/**
 * @brief Obtem a area de colisao e desenho do botao.
 * @param button O objeto botao de referencia.
 * @return Retorna o Rectangle correspondente aos limites do botao.
 */
Rectangle Button_GetRec(Button button);

/**
 * @brief Verifica se um ponto especifico esta sobre a area do botao.
 * @param button O objeto botao para o teste.
 * @param point O ponto (geralmente a posicao do mouse) a ser testado.
 * @return Retorna true se o ponto estiver colidindo com o botao, false caso contrario.
 */
bool Button_isHovering(Button button, Vector2 point);

/**
 * @brief Verifica se o botao foi clicado pelo botao esquerdo do mouse.
 * @param button O objeto botao a ser testado.
 * @return Retorna true se o mouse estiver sobre o botao e o clique ocorrer.
 */
bool Button_isPressedByMouse(Button button);

/**
 * @brief Realiza o desenho do botao e de seu texto no buffer de tela atual.
 * @param button O objeto botao a ser renderizado.
 * @return Nao ha retorno.
 */
void Button_Draw(Button button);

/**
 * @brief Libera a memoria alocada para o objeto de botao.
 * @param button O objeto botao a ser destruido.
 * @return Nao ha retorno.
 */
void Button_Free(Button button);

#endif
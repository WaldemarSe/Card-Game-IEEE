#ifndef _ImageObject_h_
#define _ImageObject_h_

#include <raylib.h>
#include <delimiters.h>

/**
 * Cabecalho destinado 'a manipulacao e exibicao de texturas e imagens.
 * O mo'dulo encapsula as funcionalidades de carregamento, transformacao e 
 * desenho de texturas da biblioteca raylib, permitindo o controle de posicao, 
 * escala, rotacao e a'reas de origem/destino (pro).
 */

typedef void* ImageObject;

/**
 * @brief Inicializa um objeto de imagem a partir de um arquivo.
 * @param filename Caminho para o arquivo de imagem no disco.
 * @return Retorna o objeto ImageObject criado, ou NULL caso o carregamento falhe.
 */
ImageObject Image_Init(const char* filename);

/**
 * @brief Adiciona a propriedade de nine-slicing 'a uma imagem.
 * 
 * NOTA: Slicing usa a propriedade 'source', use setSource primeiro se nao deseja usar a imagem completa como slicing.
 * 
 * @param img O objeto de imagem a ser adicionada a propriedade.
 * @param leftPadding Borda esquerda.
 * @param topPadding Borda acima.
 * @param rightPadding Borda direita.
 * @param bottomPadding Borda abaixo.
 * @return Nao ha' retorno de algum valor.
 */
void Image_AddSlicing(ImageObject img, int leftPadding, int topPadding, int rightPadding, int bottomPadding);

/**
 * @brief Define a posicao do objeto de imagem no espaco 2D.
 * @param img O objeto de imagem a ser modificado.
 * @param position Coordenadas X e Y para o posicionamento.
 * @return Nao ha' retorno de algum valor.
 */
void Image_SetPosition(ImageObject img, Vector2 position);

/**
 * @brief Define a cor de sobreposicao para a renderizacao da imagem.
 * @param img O objeto de imagem a ser modificado.
 * @param color Estrutura Color (ex: WHITE para cor original).
 * @return Nao ha' retorno de algum valor.
 */
void Image_SetColor(ImageObject img, Color color);

/**
 * @brief Define o fator de escala do objeto de imagem.
 * @param img O objeto de imagem a ser modificado.
 * @param scale Fator multiplicador de tamanho (1.0 para tamanho original).
 * @return Nao ha' retorno de algum valor.
 */
void Image_ApplyScale(ImageObject img, float scale);

/**
 * @brief Define o angulo de rotacao da imagem.
 * @param img O objeto de imagem a ser modificado.
 * @param rotation Angulo em graus.
 * @return Nao ha' retorno de algum valor.
 */
void Image_SetRotation(ImageObject img, float rotation);

/**
 * @brief Define o retangulo de destino para o desenho da imagem.
 * @param img O objeto de imagem a ser modificado.
 * @param destination Retangulo que define a a'rea onde a imagem sera' desenhada na tela.
 * @return Nao ha' retorno de algum valor.
 */
void Image_SetDestination(ImageObject img, Rectangle destination);

/**
 * @brief Define a a'rea de origem (recorte) da textura original.
 * @param img O objeto de imagem a ser modificado.
 * @param source Retangulo que define a parte da textura a ser utilizada.
 * @return Nao ha' retorno de algum valor.
 */
void Image_SetSource(ImageObject img, Rectangle source);

/**
 * @brief Altera a textura do objeto carregando um novo arquivo.
 * @param img O objeto de imagem a ser modificado.
 * @param filename Caminho do novo arquivo de imagem.
 * @param replaceSource Se verdadeiro, redefine o retangulo de origem para o tamanho total da nova imagem.
 * @param replaceDestination Se verdadeiro, redefine o retangulo de destino para o tamanho total da nova imagem.
 * @return Nao ha' retorno de algum valor.
 */
void Image_SetTexture(ImageObject img, const char* filename, bool replaceSource, bool replaceDestination);

/**
 * @brief Define o ponto de origem para transformacoes como rotacao e escala.
 * @param img O objeto de imagem a ser modificado.
 * @param origin Vetor de origem relativo ao retangulo de destino.
 * @return Nao ha' retorno de algum valor.
 */
void Image_SetOrigin(ImageObject img, Vector2 origin);

/**
 * @brief Ajusta o tamanho da imagem para caber em dimensoes especi'ficas.
 * @param img O objeto de imagem a ser modificado.
 * @param size Dimensoes de largura e altura desejadas.
 * @return Nao ha' retorno de algum valor.
 */
void Image_FitToSize(ImageObject img, Vector2 size);

/**
 * @brief Ajusta o tamanho da imagem para ocupar as dimensoes atuais da tela.
 * @param img O objeto de imagem a ser modificado.
 * @return Nao ha' retorno de algum valor.
 */
void Image_FitToScreenSize(ImageObject img);

/**
 * @brief Obte'm a posicao atual do objeto de imagem.
 * @param img O objeto de imagem escolhido.
 * @return Retorna as coordenadas atuais da imagem.
 */
Vector2 Image_GetPosition(ImageObject img);

/**
 * @brief Obte'm o retangulo de destino atual do objeto de imagem.
 * @param img O objeto de imagem escolhido.
 * @return Retorna o retangulo de destino da imagem.
 */
Rectangle Image_GetDestination(ImageObject img);

/**
 * @brief Obte'm a cor de sobreposicao atual do objeto.
 * @param img O objeto de imagem escolhido.
 * @return Retorna a cor aplicada na imagem.
 */
Color Image_GetColor(ImageObject img);

/**
 * @brief Obte'm o angulo de rotacao atual do objeto.
 * @param img O objeto de imagem escolhido.
 * @return Retorna o angulo em graus.
 */
float Image_GetRotation(ImageObject img);

/**
 * @brief Obte'm o nome ou caminho da textura atualmente carregada.
 * @param img O objeto de imagem escolhido.
 * @return Retorna uma string com o nome do arquivo de textura.
 */
const char* Image_GetTextureName(ImageObject img);

/**
 * @brief Obte'm o ponto de origem atual do objeto.
 * @param img O objeto de imagem escolhido.
 * @return Retorna o ponto de origem da imagem.
 */
Vector2 Image_GetOrigin(ImageObject img);

/**
 * @brief Cria uma co'pia independente de um objeto de imagem.
 * @param img O objeto de imagem original a ser copiado.
 * @return Retorna uma nova instancia de ImageObject com os mesmos atributos.
 */
ImageObject Image_Copy(ImageObject img);

/**
 * @brief Renderiza a imagem na tela.
 * @param img O objeto de imagem a ser desenhado.
 * @return Nao ha' retorno de algum valor.
 */
void Image_Draw(ImageObject img);

/**
 * @brief Renderiza a imagem na tela com os retangulos passados.
 * @param img O objeto de imagem a ser desenhado.
 * @param source Fonte da imagem principal (crop).
 * @param destination Local de desenho no plano desejado.
 * @return Nao ha' retorno de algum valor.
 */
void Image_DrawManually(ImageObject img, Rectangle source, Rectangle destination);

/**
 * @brief Remove a propriedade de nine-slicing do objeto de imagem.
 * @param img O objeto de image a ser removida a propriedade.
 * @return Nao ha' retorno de algum valor.
 */
void Image_RemoveSlicing(ImageObject img);

/**
 * @brief Libera a memoria alocada para o objeto de imagem.
 * @param img O objeto de imagem a ser liberado.
 * @return Nao ha' retorno de algum valor.
 */
void Image_Free(ImageObject img);

/**
 * @brief Libera todas as instancias de memoria alocadas para os objetos de imagens criados.
 * @return Nao ha' retorno de algum valor.
 */
void Image_FreeAll();

#endif
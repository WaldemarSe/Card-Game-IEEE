#include "screen.h"

#include <stdio.h>

#include "jogador.h"

/** TELA DE TESTE
 * 
 * Pode ser usada livremente, mas lembre-se de desmarcar na hora de fazer commit para evitar conflitos depois.
 * NOTA:    Variáveis usadas em múltiplas função devem ser declaradas como estáticas globalmente.
 * 
 * INIT:    Serve para inicalização de variáveis.
 * 
 * UPDATE:  Itens que requerem atualizações constantes (por frame), por ex: verificação de vida > 0.
 * 
 * DRAW:    Atualiza todo frame para desenhar na tela (caso deseje testar prints, coloque no INIT ou com um
 *              [if(keypressed(...) printf();] no UPDATE.).
 * 
 * UNLOAD:  Liberação de variáveis alocadas.
*/

// Exemplo de variável estática global para ser acessada em múltiplas partes do arquivo.
static Jogador j = NULL;

static void Init(Game game){
    Jogador j = criarJogador(10);

    bool suc = carregarBaralho(j, true, "./assets/data/cartas.json");
    if(!suc) printf("\n\nErro ao carregar baralho :(\n\n");

    embaralharBaralho(j);

    printBaralho(j);
}

static void Update(Game game, float deltaTime){
}

static void Draw(Game game, float deltaTime){
}

static void Unload(Game game){
}

Screen TestScreen = { Init, Update, Draw, Unload };
# Bibliotecas (Raylib)

Repositório especializado em funções úteis para o desenvolvimento de projetos baseados em Raylib (C-lang).<br>
Este apresenta um conjunto de funções para criação de objetos de imagem, câmera, animação, _slider_, botões, etc. também, está presente algumas estruturas de dados como lista, árvore binária, fila de prioridade, tabela hash, etc.

## Pré-requisitos

Raylib e GCC.

* A instalação do **Raylib** pode ser feita [aqui](https://www.raylib.com).
* A instalação do **GCC** pode ser feita [aqui](https://sourceforge.net/projects/gcc-win64/).

## Como utilizar

1. Extrair Bibliotecas para o mesmo ambiente da pasta do projeto alvo.
2. Mover os arquivos Makefile e CMD para um nível abaixo da árvore de pastas.
3. Criar uma subpasta _src_ no projeto alvo com arquivos fonte.
4. Executar o CMD presente no repositório.
5. Compilar o projeto usando o comando ``` make DIR=./nomeDoProjeto ```.
6. Executar o programa com ``` ./nomeDoProjeto/nomeDoProjeto ```.

> [!IMPORTANT]
> Talvez o compilador reclame de _imports_ do raylib e algumas dependências. Para resolver, basta incluir os _paths_ presentes no ```c_cpp_properties``` do repositório no _Include Path_ do compilador

## Exemplo de utilização

Seguindo os passos especificados no tópico anterior, a estrutura final de pastas deve ser conforme apresentada na imagem a seguir.

![Imagem de exemplo da estrutura final do projeto com a biblioteca.](/assets/exemplo-estrutura.PNG)

Após a organização da estrutura, é possível utilizar as funções presentes com a inclusão padrão da linguagem (por exemplo, ``` #include <animation.h> ```).

Com isso em mente, um exemplo de código utilizando a biblioteca segue da seguinte forma, por exemplo:
```
#include <direct.h>
#include <time.h>
#include <stdlib.h>

#include <raylib.h>
#include <raymath.h>

#include <animation.h>
#include <Delimiters.h>
#include <utils.h>

int main(){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Exemplo");
    SetTargetFPS(60);

    _chdir(GetApplicationDirectory());

    srand(time(NULL));

    Vector2 c = CENTER;
    float cRadius = 20.0f;

    Animation a = Animation_Init();
    Animation_AddPositionAnimation(a, easeInOutCubic);
    Animation_AddScaleAnimation(a, (Rectangle){0, 0, cRadius, cRadius}, easeInOutCubic);

    Vector2 finalPoint = Vector2Zero();
    float scale = 1.0f;

    while(!WindowShouldClose()){
        float deltaTime = GetFrameTime();

        if(wait(0.5f)){
            Animation_SetPosition(a, c);

            finalPoint.x = rand() % (SCREEN_WIDTH - (int)(cRadius * 4)) + cRadius * 2;
            finalPoint.y = rand() % (SCREEN_HEIGHT - (int)(cRadius * 4)) + cRadius * 2;
            scale = ((float)(rand() % 400) / 100.0f) + 0.1f;

            Animation_MoveTo(a, finalPoint, 0.5f);
            Animation_Resize(a, scale, 0.5f);
        }

        Animation_UpdateAll(a, deltaTime);

        c = Animation_GetPosition(a);
        cRadius = Animation_GetScale(a).width;

        BeginDrawing();
            ClearBackground(BLACK);
        
            DrawCircleV(c, cRadius, WHITE);
        EndDrawing();
    }

    CloseWindow();
    Animation_Free(a);

    return 0;
}
```

O código acima inclui a biblioteca _animation_ e algumas outras para representação de um ponto se movendo na tela. Este é um exemplo bem simples de utilização apenas para completude de caso de uso.
A saída do código mostrado está logo abaixo.

![Imagem de saída do código acima.](/assets/exemplo-output.gif)

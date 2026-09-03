# Card-Game-IEEE
`Ramo Estudantil IEEE UEL`
> Projeto de Jogo de cartas do curso de Ciência da Computação no ano 2026. 
A ideia do projeto é criar um jogo eletrônico de cartas, explorando a criatividade dos membros na definição das regras, mecânicas e do visual do jogo.

**SUPERVISORES**:
Marco 
Nicolas de Oliveira

**MEMBROS**:
Aluísio de Oliveira Barbosa
André Felipe Ijiri Ribeiro
Bruna Yokoshiro
Caio Sweiver de Carvalho
Eduardo Fernandes Lanza
João Santos
Waldemar Serafim Neto

---

## Branches

Fluxo de manutenção das branches:

* **Main:** A branch `main` **não** deve receber nenhum merge direto das branches auxiliares. Deve ser realizado uma revisão do código para averiguar se a o objetivo foi devidamente concluído sem capotar o projeto principal;
* **Pull Request:** O *pull request* deve ser realizado para a brach `Waldemar` para que verificações possam ser realizadas antes do *merge* com a `main`;
* **Merge Administrativo:** O merge final para a branch `main` será realizado exclusivamente por uma única pessoa designada;

---

## Commits
> **[Créditos](https://github.com/GabrielPaduan/Treino_Exato/blob/main/README.md)**

Será adoto a especificação do **[Conventional Commits](https://www.conventionalcommits.org/pt-br/v1.0.0/)**.

### Regras Gerais
* **Idioma:** O idioma padrão adotado para as mensagens de commit é o **Português (PT-BR)**.
* **Clareza e Contexto:** Cada `push` deve ser composto por commits **atômicos e devidamente descritivos**. Evite commits genéricos como *"alterações"*, especificando claramente o que foi feito.

### Estrutura do Commit

Ao realizar um commit, seguir a estrutura a seguir:

```text
<tipo>(<escopo>): <descrição>
```

### Tipos de Commits permitidos

| Tipo | Descrição | Exemplo de Uso |
| :--- | :--- | :--- |
| **`feat`** | Adiciona uma nova funcionalidade ao projeto. | Criação de uma nova tela ou rota de API. |
| **`fix`** | Corrige um bug ou comportamento indesejado. | Resolução de um erro de cálculo ou layout quebrado. |
| **`docs`** | Alterações exclusivas na documentação. | Atualização do `README.md` ou diagramas UML. |
| **`refactor`** | Refatoração de código (não adiciona feature nem corrige bug). | Melhoria de performance ou reorganização de pastas. |
| **`style`** | Mudanças de formatação (espaços, ponto e vírgula, indentação). | Aplicação de regras do Prettier ou ESLint. |
| **`test`** | Adição ou correção de testes automatizados. | Criação de testes unitários para um controller. |
| **`chore`** | Tarefas de manutenção, dependências ou build. | Atualização de pacotes (ex: via Yarn). |

### Exemplos Práticos

**Correto:**
> `feat(login): adicionar validação de e-mail no formulário`

> `fix(api): corrigir erro 500 na rota de cadastro de aluno`

> `docs: criar diagrama de sequência da página inicial`

> `chore: atualizar dependência do react-router-dom`

**Incorreto:**
> `atualização na tela de login` *(Falta tipo e formatação)*

> `fix(login) corrigido erro` *(Falta os dois pontos e a descrição está vaga)*

> `feat: Adicionado novas tabelas` *(Verbo conjugado no passado e letra maiúscula na descrição)*

---

## Compilação

### Pré-requisitos
1. Ter o [MinGW](https://sourceforge.net/projects/mingw/) instalado e configurado para o PATH do sistema.
2. Ter o [Raylib](https://www.raylib.com/) instalado apropriadamente.

### Compilando o programa
1. Executar o terminal presente no diretório raiz do repositório: `Raylib(CMD)`.
2. Navegar até o diretório atual através do comando `cd`, por exemplo: `cd "C:\Users\Admin\Documents\Github\Card-Game-IEEE"`.
3. Executar o comando `make`.

Se os passos foram seguidos corretamente, um executável `cardGame.exe` será incluído na raiz do arquivo.

---

## Clean

Seguindo os passos presentes na seção de compilação...

Basta executar o comando `make clean` para remover todos os arquivos-objeto criados a partir de um comando `make`.

---

## Valgrind

Seguindo os passos presentes na seção de compilação...

Executar: `"valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./ted -e ../entradas/ -f t1.geo -v t3.via -q consultas/t2.qry -o ../saidas/"`

---

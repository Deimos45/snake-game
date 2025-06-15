
## 🐍 Jogo da Cobrinha Simples em C 🐍

Este é um jogo da cobrinha básico, baseado em console, implementado em C. Ele possui um tamanho de mapa personalizável, jogabilidade clássica da cobrinha e compatibilidade entre plataformas para a limpeza do console.

---

## Recursos

- 🎮 **Jogabilidade Clássica da Cobrinha:** Controle uma cobra, coma frutas para crescer e evite bater nas paredes ou em você mesmo.  
- 🗺️ **Tamanho do Mapa Personalizável:** Defina a largura e a altura do tabuleiro do jogo (dentro dos limites).  
- 🏆 **Controle de Pontuação:** Sua pontuação é exibida no final de cada jogo, baseada no número de frutas comidas.  
- 💻 **Compatibilidade com Plataformas:** Suporte tanto para Windows (`cls`) quanto Linux (`clear`) para limpeza da tela.

---

##  Primeiros Passos

###  Pré-requisitos

- Um compilador C (como GCC).  
- Para Linux: você precisará do arquivo `kbhitlinux.h` e da funcionalidade `getch()`, que pode ser tratada por bibliotecas como **ncurses**.  

---

### Compilação

**Salve o código como:** `snake_game.c`  

###  No Windows:
```bash
gcc snake_game.c -o snake_game.exe
```

###  No Linux:
> Certifique-se de ter `kbhitlinux.h` no mesmo diretório.

```bash
gcc snake_game.c kbhitlinux.h -o snake_game -lncurses
```
> Obs.: Caso tenha erro com `getch()` ou `kbhit()`, instale o ncurses:  
```bash
sudo apt-get install libncurses-dev
```

---

##  Executando o Jogo

### No Windows:
```bash
./snake_game.exe
```

### No Linux:
```bash
./snake_game
```

---

## Como Jogar

- **Configuração inicial:**  
Informe o tamanho do mapa (mínimo **10x10**, máximo **50x50**).

- **Controles:**  
`W` = Cima  
`A` = Esquerda  
`S` = Baixo  
`D` = Direita  

- **Objetivo:**  
Controle a cobra (`O`) para comer a fruta (`*`).  
Cada fruta faz sua cobra crescer e sua pontuação aumentar.

- **Perde se:**  
- Bater na parede (`#`)  
- Bater no próprio corpo  

- **Vence se:**  
Preencher todo o mapa com o corpo da cobra.

---

## Configurações no Código

No arquivo `snake_game.c`, você pode ajustar:  
- `SnakeInitialSize` → Tamanho inicial da cobra (padrão: **3**)  
- `maxSizeX`, `maxSizeY` → Limite máximo do mapa (**50x50**)  

---

## Estrutura do Código

- **`struct Segment`** → Cada pedaço da cobra (lista duplamente encadeada).  
- **`struct Snake`** → Representa a cobra completa (cabeça, cauda, direção e tamanho).  

### Funções Principais:
- **`clearW()` / `clearL()`** → Limpa o console (Windows/Linux).  
- **`CreateSnake()`** → Cria a cobra.  
- **`AddSegment()`** → Adiciona um segmento na cauda.  
- **`InitializeSnake()`** → Inicializa a cobra na posição inicial.  
- **`ResetSnake()`** → Limpa a cobra atual da memória.  
- **`ResetMap()`** → Prepara o mapa e reinicia a cobra.  
- **`SpawnFruit()`** → Gera uma fruta em posição aleatória.  
- **`MoveSnake()`** → Move a cobra, trata colisões, crescimento e retorno do status do jogo.  
- **`ShowMap()`** → Exibe o mapa no console.  
- **`UpdateSnakeDirection()`** → Atualiza a direção da cobra com base no input.  
- **`GetKeyDown()`** → Captura as teclas pressionadas.  
- **`main()`** → Loop principal que gerencia o jogo.

---

## Divirta-se jogando e hackeando o código! 🎉

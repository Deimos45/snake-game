#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define LINHAS 20
#define COLUNAS 30
#define CRESCIMENTO_INICIAL 3

typedef struct Segmento {
    int x, y;
    struct Segmento *proximo;
} Segmento;

typedef struct {
    Segmento *cabeca;
    Segmento *cauda;
    int direcaoX;
    int direcaoY;
} Cobra;

void inicializarTabuleiro(char tabuleiro[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (i == 0 || i == LINHAS - 1 || j == 0 || j == COLUNAS - 1) {
                tabuleiro[i][j] = '#'; // Parede
            } else {
                tabuleiro[i][j] = ' '; // Espaço livre
            }
        }
    }
}
void gerarFruta(char tabuleiro[LINHAS][COLUNAS]) {
    int x, y;
    do {
        // Gera posições aleatórias dentro dos limites válidos
        x = 1 + rand() % (LINHAS - 2);
        y = 1 + rand() % (COLUNAS - 2);
    } while(tabuleiro[x][y] != ' '); // Garante posição vazia
    
    tabuleiro[x][y] = '*'; // Coloca a fruta
}

void exibirTabuleiro(char tabuleiro[LINHAS][COLUNAS]) {
    system("clear"); // limpa o terminal (use "cls" no Windows)
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            printf("%c", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void inicializarCobra(Cobra *cobra) {
    cobra->cabeca = malloc(sizeof(Segmento));
    cobra->cabeca->x = LINHAS / 2;
    cobra->cabeca->y = COLUNAS / 2;
    cobra->cabeca->proximo = NULL;
    cobra->cauda = cobra->cabeca;
    cobra->direcaoX = 0;
    cobra->direcaoY = 1; // Direita

    // Crescimento inicial
    for (int i = 1; i < CRESCIMENTO_INICIAL; i++) {
        Segmento *novo = malloc(sizeof(Segmento));
        novo->x = cobra->cabeca->x;
        novo->y = cobra->cabeca->y - i;
        novo->proximo = NULL;
        cobra->cauda->proximo = novo;
        cobra->cauda = novo;
    }
}

void atualizarTabuleiroComCobra(char tabuleiro[LINHAS][COLUNAS], Cobra *cobra) {
    Segmento *atual = cobra->cabeca;
    while (atual != NULL) {
        tabuleiro[atual->x][atual->y] = 'O';
        atual = atual->proximo;
    }
}

int main() {
    srand(time(NULL));

    char tabuleiro[LINHAS][COLUNAS];
    Cobra cobra;

    inicializarTabuleiro(tabuleiro);
    gerarFruta(tabuleiro);
    inicializarCobra(&cobra);
    atualizarTabuleiroComCobra(tabuleiro, &cobra);

    // Simulação de jogo (por enquanto só exibe o mesmo tabuleiro 5 vezes)
    for (int i = 0; i < 5; i++) {
        exibirTabuleiro(tabuleiro);
        sleep(1); // Espera 1 segundo
    }

    return 0;
}
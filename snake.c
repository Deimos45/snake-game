#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LINHAS 20
#define COLUNAS 30

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
    
    tabuleiro[x][y] = 'F'; // Coloca a fruta
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

int main() {
    char tabuleiro[LINHAS][COLUNAS];
    inicializarTabuleiro(tabuleiro);

    // Simulação de jogo (por enquanto só exibe o mesmo tabuleiro 5 vezes)
    for (int i = 0; i < 5; i++) {
        exibirTabuleiro(tabuleiro);
        sleep(1); // Espera 1 segundo
    }

    return 0;
}
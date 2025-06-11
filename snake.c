#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>
#include <fcntl.h>

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

char tabuleiro[LINHAS][COLUNAS];
int frutaX = 0, frutaY = 0; // posição da fruta

// Entrada de teclado não bloqueante (Linux)
int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

char getKey() {
    if (kbhit())
        return getchar();
    return '\0';
}

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
    do {
        frutaX = 1 + rand() % (LINHAS - 2);
        frutaY = 1 + rand() % (COLUNAS - 2);
    } while (tabuleiro[frutaX][frutaY] != ' ');
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
    cobra->direcaoY = 1; 

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


int moverCobra(Cobra *cobra, char tabuleiro[LINHAS][COLUNAS]) {
    int novaX = cobra->cabeca->x + cobra->direcaoX;
    int novaY = cobra->cabeca->y + cobra->direcaoY;

    if (tabuleiro[novaX][novaY] == '#' || tabuleiro[novaX][novaY] == 'O') {
        return 0; // colisão
    }

    Segmento *novo = malloc(sizeof(Segmento));
    novo->x = novaX;
    novo->y = novaY;
    novo->proximo = cobra->cabeca;
    cobra->cabeca = novo;

    int comeu = (novaX == frutaX && novaY == frutaY);
    if (!comeu) {
        Segmento *atual = cobra->cabeca;
        while (atual->proximo != cobra->cauda) {
            atual = atual->proximo;
        }
        free(cobra->cauda);
        cobra->cauda = atual;
        cobra->cauda->proximo = NULL;
    } else {
        gerarFruta(tabuleiro);
    }

    return 1;
}

void atualizarDirecao(Cobra *cobra, char tecla) {
    switch (tecla) {
        case 'w': if (cobra->direcaoX != 1) { cobra->direcaoX = -1; cobra->direcaoY = 0; } break;
        case 's': if (cobra->direcaoX != -1) { cobra->direcaoX = 1; cobra->direcaoY = 0; } break;
        case 'a': if (cobra->direcaoY != 1) { cobra->direcaoX = 0; cobra->direcaoY = -1; } break;
        case 'd': if (cobra->direcaoY != -1) { cobra->direcaoX = 0; cobra->direcaoY = 1; } break;
    }
}

int main() {
    srand(time(NULL));
    Cobra cobra;
    inicializarTabuleiro(tabuleiro);
    gerarFruta(tabuleiro);
    inicializarCobra(&cobra);

    while (1) {
        char tecla = getKey();
        if (tecla) {
            atualizarDirecao(&cobra, tecla);
        }

        inicializarTabuleiro(tabuleiro);          // limpa o tabuleiro
        tabuleiro[frutaX][frutaY] = '*';          // desenha a fruta

        if (!moverCobra(&cobra, tabuleiro)) {
            printf("Game Over!\n");
            break;
        }

        atualizarTabuleiroComCobra(tabuleiro, &cobra);
        exibirTabuleiro(tabuleiro);
        usleep(150000);
    }

    return 0;
}
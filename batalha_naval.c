#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_TABULEIRO 10
#define NUM_NAVIOS 5

typedef struct {
    int x, y;
    int afundado;
} Navio;

void introducao() {
    puts("Bem-vindo ao Batalha Naval");
    printf("\nVocê é um almirante que tem a missão de derrubar as embarcações inimigas\n");
    printf("Que vença o melhor!\n");
    printf("--------------------------------------------------------------------------------\n\n");
}

void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int mostrarErrosAcertos) {
    printf("\nTabuleiro:\n\n");
    printf("  ");
    for (int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
        printf("%d ", coluna + 1);
    }
    printf("\n");
    for (int linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
        printf("%d ", linha + 1);
        for (int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
            if (tabuleiro[linha][coluna] == 0) {
                printf("~ ");
            } else if (tabuleiro[linha][coluna] == 1) {
                printf("N ");
            } else if (tabuleiro[linha][coluna] == -1) {
                if (mostrarErrosAcertos) {
                    printf("X ");
                } else {
                    printf("~ ");
                }
            } else if (tabuleiro[linha][coluna] == -2) {
                if (mostrarErrosAcertos) {
                    printf("O ");
                } else {
                    printf("~ ");
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int x, int y) {
    if (tabuleiro[x][y] == 0) {
        tabuleiro[x][y] = 1;
        return 1;
    } else {
        return 0;
    }
}

int efetuarTiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int x, int y) {
    if (tabuleiro[x][y] == 1) {
        tabuleiro[x][y] = -2;
        return 1;
    } else if (tabuleiro[x][y] == 0) {
        tabuleiro[x][y] = -1;
        return 0;
    } else {
        return -1;
    }
}

int verificarVitoria(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 1) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    introducao();
    srand(time(NULL));

    int tabuleiroJogador1[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int tabuleiroJogador2[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int tirosJogador1[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int tirosJogador2[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiroJogador1[i][j] = 0;
            tabuleiroJogador2[i][j] = 0;
            tirosJogador1[i][j] = 0;
            tirosJogador2[i][j] = 0;
        }
    }

    printf("Jogador 1, posicione seus navios (x y):\n");
    for (int i = 0; i < NUM_NAVIOS; i++) {
        int x, y;
        printf("Navio %d: ", i + 1);
        scanf("%d %d", &x, &y);
        if (posicionarNavio(tabuleiroJogador1, x, y) == 0) {
            printf("\nPosição ocupada. Tente novamente.\n");
            i--;
            
        }
    }

    printf("\nJogador 2, posicione seus navios (x y):");
    for (int i = 0; i < NUM_NAVIOS; i++) {
        int x, y;
        printf("Navio %d: ", i + 1);
        scanf("%d %d", &x, &y);
        if (posicionarNavio(tabuleiroJogador2, x, y) == 0) {
            printf("\nPosição ocupada. Tente novamente.\n");
            i--;
           
        }
    }

    int jogadorAtual = 1;
    while (1) {
        printf("Tabuleiro do Jogador %d:\n", jogadorAtual);
        exibirTabuleiro(jogadorAtual == 1 ? tirosJogador1 : tirosJogador2, 1);

        int x, y;
        printf("\nJogador %d, efetue seu tiro (x y): ", jogadorAtual);
        scanf("%d %d", &x, &y);

        int resultado = efetuarTiro(jogadorAtual == 1 ? tabuleiroJogador2 : tabuleiroJogador1, x, y);

        if (resultado == 1) {
            printf("Tiro certo!\n");
        } else if (resultado == 0) {
            printf("Tiro errado\n");
        } else {
            printf("Você já atingiu essa posição. Tente novamente.\n");
        }

        if (verificarVitoria(jogadorAtual == 1 ? tabuleiroJogador2 : tabuleiroJogador1)) {
            printf("Jogador %d venceu!\n", jogadorAtual);
            break;
        }

        if (jogadorAtual == 1) {
            jogadorAtual = 2;
        } else {
            jogadorAtual = 1;
        }
    }

    return 0;
}

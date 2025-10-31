#include <stdio.h>

#define TAM 10 // Tamanho fixo do tabuleiro
#define NAVIO 3
#define AGUA 0
#define HABILIDADE 5

// Função para inicializar o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para exibir o tabuleiro formatado
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n   ");
    for (int j = 0; j < TAM; j++)
        printf("%2d ", j);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para posicionar navio horizontal
void posicionarNavioHorizontal(int tabuleiro[TAM][TAM], int linha, int coluna, int tamanho) {
    if (coluna + tamanho <= TAM) {
        for (int j = coluna; j < coluna + tamanho; j++) {
            tabuleiro[linha][j] = NAVIO;
        }
    }
}

// Função para posicionar navio vertical
void posicionarNavioVertical(int tabuleiro[TAM][TAM], int linha, int coluna, int tamanho) {
    if (linha + tamanho <= TAM) {
        for (int i = linha; i < linha + tamanho; i++) {
            tabuleiro[i][coluna] = NAVIO;
        }
    }
}

// Função para posicionar navio diagonal principal (↘)
void posicionarNavioDiagonalPrincipal(int tabuleiro[TAM][TAM], int linha, int coluna, int tamanho) {
    if (linha + tamanho <= TAM && coluna + tamanho <= TAM) {
        for (int i = 0; i < tamanho; i++) {
            tabuleiro[linha + i][coluna + i] = NAVIO;
        }
    }
}

// Função para posicionar navio diagonal secundária (↙)
void posicionarNavioDiagonalSecundaria(int tabuleiro[TAM][TAM], int linha, int coluna, int tamanho) {
    if (linha + tamanho <= TAM && coluna - tamanho >= -1) {
        for (int i = 0; i < tamanho; i++) {
            tabuleiro[linha + i][coluna - i] = NAVIO;
        }
    }
}

// Função genérica para aplicar uma habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[5][5], int origemLinha, int origemColuna, int tamanho) {
    int offset = tamanho / 2; // Centro da matriz da habilidade

    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (habilidade[i][j] == 1) {
                int linha = origemLinha + (i - offset);
                int coluna = origemColuna + (j - offset);

                // Verifica se está dentro dos limites do tabuleiro
                if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM) {
                    // Marca a área de efeito no tabuleiro
                    if (tabuleiro[linha][coluna] == AGUA)
                        tabuleiro[linha][coluna] = HABILIDADE;
                }
            }
        }
    }
}

// Cria habilidade em forma de cone apontando para baixo
void criarHabilidadeCone(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            habilidade[i][j] = (j >= 2 - i && j <= 2 + i) ? 1 : 0;
        }
    }
}

// Cria habilidade em forma de cruz
void criarHabilidadeCruz(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            habilidade[i][j] = (i == 2 || j == 2) ? 1 : 0;
        }
    }
}

// Cria habilidade em forma de octaedro (losango)
void criarHabilidadeOctaedro(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int dist = abs(2 - i) + abs(2 - j);
            habilidade[i][j] = (dist <= 2) ? 1 : 0;
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // ================================
    // 1️⃣ POSICIONANDO OS 4 NAVIOS
    // ================================
    int tamanhoNavio = 3;

    // Navios horizontais e verticais
    posicionarNavioHorizontal(tabuleiro, 1, 1, tamanhoNavio);
    posicionarNavioVertical(tabuleiro, 4, 7, tamanhoNavio);

    // Navios diagonais
    posicionarNavioDiagonalPrincipal(tabuleiro, 6, 0, tamanhoNavio);
    posicionarNavioDiagonalSecundaria(tabuleiro, 0, 9, tamanhoNavio);

    printf("\n=== TABULEIRO COM NAVIOS (INCLUINDO DIAGONAIS) ===\n");
    exibirTabuleiro(tabuleiro);

    // ================================
    // 2️⃣ CRIANDO AS HABILIDADES
    // ================================
    int cone[5][5];
    int cruz[5][5];
    int octaedro[5][5];

    criarHabilidadeCone(cone);
    criarHabilidadeCruz(cruz);
    criarHabilidadeOctaedro(octaedro);

    // ================================
    // 3️⃣ APLICANDO HABILIDADES NO TABULEIRO
    // ================================
    aplicarHabilidade(tabuleiro, cone, 2, 3, 5);
    aplicarHabilidade(tabuleiro, cruz, 7, 7, 5);
    aplicarHabilidade(tabuleiro, octaedro, 5, 3, 5);

    printf("\n=== TABULEIRO COM HABILIDADES APLICADAS ===\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}

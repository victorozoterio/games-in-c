#include <stdio.h>  // Biblioteca para funções de entrada e saída (printf, scanf)
#include <string.h> // Biblioteca para manipulação de strings (strlen, strcmp)
#include <stdlib.h> // Biblioteca para funções utilitárias (system())

// Declarações das funções do Jogo da Forca
void jogarForca();

// Declarações das funções do Ligue 4
void jogarLig4();
void inicializarTabuleiro(char tabuleiro[6][7]);
void imprimirTabuleiro(char tabuleiro[6][7]);
int celulaVazia(char tabuleiro[6][7], int linha, int coluna);
int soltarDisco(char tabuleiro[6][7], int linha, int coluna, char disco);
int verificarVencedor(char tabuleiro[6][7], char disco);

// Função para desenhar a forca
void desenhaForca(int tentativas) {
    switch (tentativas) {
        case 6:
            printf("\n");
            printf("-----    \n");
            printf("|   |   \n");
            printf("|       \n");
            printf("|       \n");
            printf("|       \n");
            printf("|       \n");
            printf("========\n");
            break;
        case 5:
            printf("\n");
            printf("-----    \n");
            printf("|   |   \n");
            printf("|   O   \n");
            printf("|       \n");
            printf("|       \n");
            printf("|       \n");
            printf("========\n");
            break;
        case 4:
            printf("\n");
            printf("-----    \n");
            printf("|   |   \n");
            printf("|   O   \n");
            printf("|   |   \n");
            printf("|       \n");
            printf("|       \n");
            printf("========\n");
            break;
        case 3:
            printf("\n");
            printf("-----    \n");
            printf("|   |   \n");
            printf("|   O   \n");
            printf("|  /|   \n");
            printf("|       \n");
            printf("|       \n");
            printf("========\n");
            break;
        case 2:
            printf("\n");
            printf("-----    \n");
            printf("|   |   \n");
            printf("|   O   \n");
            printf("|  /|\\  \n");
            printf("|       \n");
            printf("|       \n");
            printf("========\n");
            break;
        case 1:
            printf("\n");
            printf("-----    \n");
            printf("|   |   \n");
            printf("|   O   \n");
            printf("|  /|\\  \n");
            printf("|  /    \n");
            printf("|       \n");
            printf("========\n");
            break;
        case 0:
            printf("\n");
            printf("-----    \n");
            printf("|   |   \n");
            printf("|   O   \n");
            printf("|  /|\\  \n");
            printf("|  / \\  \n");
            printf("========\n");
            printf("GAME OVER!\n");
            break;
    }
}

// Função para limpar a tela
void limparTela() {
    #ifdef _WIN32
        system("cls");  // Para Windows
    #else
        system("clear");  // Para Linux/macOS
    #endif
}

int main() {
    int escolha;
    const char* marrom = "\033[38;2;139;87;66m";
    const char* verde = "\033[0;92m";
    const char* reset = "\033[0m";

    while (1) {
        limparTela();
        
        printf("   _______\n");
        printf("   |.---.|\n");
        printf("   ||___||\n");
        printf("   |+  .'|\n");
        printf("   | _ _ |  QuantIT\n");
        printf("   |_____/  %s=======%s\n", marrom, reset);
        
        // Exibe o menu de escolha
        printf("%s", verde);
        printf("\n==========================\n");
        printf("%s", reset);
        printf("       MENU DE JOGOS      \n");
        printf("%s", verde);
        printf("==========================\n\n");
        printf("%s", reset);
        printf("1. Jogo da Forca\n");
        printf("2. Ligue 4\n");
        printf("3. Sair\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                jogarForca();
                break;
            case 2:
                jogarLig4();
                break;
            case 3:
                printf("Saindo do programa. Ate a proxima!\n");
                exit(0);
            default:
                printf("Opção invalida! Tente novamente.\n");
        }
    }

    return 0;
}

void jogarForca() {
    char palavra[50]; // Palavra a ser adivinhada
    char letra, letrasErradas[6];
    int tamanho, tentativas = 6, erros = 0;
    char palavraAdivinhada[tamanho + 1]; // Mantém o progresso do jogador
    char letrasTentadas[26] = {0};  // Array para controlar todas as letras já tentadas
    const char* vermelho = "\033[31m";
    const char* verde = "\033[0;92m";
    const char* reset = "\033[0m";
    limparTela();
    
    // Solicita ao usuário que digite a palavra a ser adivinhada
    printf("Digite a palavra a ser adivinhada: ");
    scanf("%s", palavra);
    
    tamanho = strlen(palavra); // Obtém o tamanho da palavra
    
    // Inicializa a palavraAdivinhada com underscores
    for (int i = 0; i < tamanho; i++) {
        palavraAdivinhada[i] = '_';
    }
    palavraAdivinhada[tamanho] = '\0'; // Adiciona '\0' no final da string para indicar seu término.

    // Loop principal do jogo, executado enquanto o número de tentativas for maior que 0 e a palavra não estiver completamente adivinhada
    while (tentativas > 0 && strcmp(palavraAdivinhada, palavra) != 0) {
        limparTela(); // Limpa a tela a cada iteração

        // Exibe a palavra oculta e o número de tentativas restantes
        printf("%s", verde);
        printf("\n========================\n");
        printf("%s", reset);
        printf("     Jogo da Forca        \n");
        printf("%s", verde);
        printf("========================\n");
        printf("%s", reset);
        printf("\nPalavra: %s\n", palavraAdivinhada);
        printf("Tentativas restantes: %d\n", tentativas);
        desenhaForca(tentativas); // Desenha a forca de acordo com as tentativas restantes

        // Se houver letras erradas, exibe-as
        if (erros > 0) {
            printf("Letras erradas: ");
            for (int i = 0; i < erros; i++) {
                printf("%c ", letrasErradas[i]);
            }
            printf("\n");
        }

        // Solicita ao usuário que digite uma letra
        printf("Digite uma letra: ");
        scanf(" %c", &letra);

        // Verifica se a letra já foi tentada
        if (letrasTentadas[letra - 'a']) {
            printf("Voce ja digitou essa letra! Tente outra.\n");
            printf("Pressione Enter para continuar...");
            getchar();  // Consome o Enter (\n) deixado no buffer pelo scanf
            getchar();  // Aguarda o usuário pressionar Enter novamente para continuar
            continue;
        }

        letrasTentadas[letra - 'a'] = 1; // Marca a letra como tentada
        
        // Procura pela letra na palavra
        int acertou = 0;
        for (int i = 0; i < tamanho; i++) {
            if (palavra[i] == letra) {
                palavraAdivinhada[i] = letra;  // Substitui o underscore pela letra correta
                acertou = 1;
            }
        }

        // Se a letra não foi encontrada na palavra, é considerada errada
        if (!acertou) {
            printf("Letra incorreta!\n");
            letrasErradas[erros] = letra;  // Armazena a letra errada
            erros++;  // Incrementa o número de erros
            tentativas--;  // Decrementa o número de tentativas restantes
            printf("Pressione Enter para continuar.");
            getchar();  // Consome o Enter do scanf
            getchar();  // Espera por um novo Enter
        }

        // Se as tentativas chegarem a zero, o jogador perdeu
        if (tentativas == 0) {
            limparTela();
            printf("%s", vermelho);
            desenhaForca(tentativas);
            printf("%s", reset);
            printf("\nVoce perdeu! A palavra era: %s\n", palavra);
            printf("Pressione Enter para voltar ao menu principal.\n");
            getchar();
            break;
        }
    }

    // Se o jogador adivinhar a palavra corretamente
    if (strcmp(palavraAdivinhada, palavra) == 0) {
        printf("\nParabens! Voce adivinhou a palavra: %s\n", palavra);
        printf("Pressione Enter para voltar ao menu principal.\n");
        getchar();
        getchar();
    }
}

void jogarLig4() {
    char tabuleiro[6][7];
    int linha, coluna;
    int jogadorAtual = 1;
    int jogoGanho = 0;
    char disco;

    inicializarTabuleiro(tabuleiro);

    while (jogoGanho == 0) {
        limparTela();
        
        const char* verde = "\033[0;92m";
        const char* reset = "\033[0m";
        printf("%s", verde);
        printf("\n==================\n");
        printf("%s", reset);
        printf("     Ligue 4        \n");
        printf("%s", verde);
        printf("==================\n");
        printf("%s", reset);
        
        imprimirTabuleiro(tabuleiro);
        
        if (jogadorAtual == 1) {
            disco = 'X';
            printf("Vez do Jogador 1 (X)\n");
        } else {
            disco = 'O';
            printf("Vez do Jogador 2 (O)\n");
        }

        printf("Informe uma linha (1-6) e uma coluna (1-7): ");
        scanf("%d %d", &linha, &coluna);

        if (linha < 1 || linha > 6 || coluna < 1 || coluna > 7) {
            printf("Entrada invalida. Pressione Enter para continuar e escolha uma linha entre 1-6 e uma coluna entre 1-7.\n");
            getchar();
            getchar();
            continue;
        }

        linha = linha - 1; // Outra opção seria linha -= 1
        coluna = coluna - 1; // Ou coluna -= 1

        if (celulaVazia(tabuleiro, linha, coluna)) {
            soltarDisco(tabuleiro, linha, coluna, disco);
        } else {
            printf("Celula ja ocupada! Pressione Enter para continuar e escolha outra.\n");
            getchar();
            getchar();
            continue;
        }

        if (verificarVencedor(tabuleiro, disco)) {
            limparTela();
            imprimirTabuleiro(tabuleiro);
            printf("%sJogador %d venceu!%s\n", verde, jogadorAtual, reset);
            jogoGanho = 1;
            printf("Pressione Enter para voltar ao menu principal.\n");
            getchar();
            getchar();
            break;
        }

        if (jogadorAtual == 1) {
        jogadorAtual = 2;
        } else {
            jogadorAtual = 1;
}
    }
}

// Código auxiliar para o Ligue 4
void inicializarTabuleiro(char tabuleiro[6][7]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            tabuleiro[i][j] = '.';
        }
    }
}

void imprimirTabuleiro(char tabuleiro[6][7]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int celulaVazia(char tabuleiro[6][7], int linha, int coluna) {
    return tabuleiro[linha][coluna] == '.';
}

int soltarDisco(char tabuleiro[6][7], int linha, int coluna, char disco) {
    tabuleiro[linha][coluna] = disco;
    return 1;
}

int verificarVencedor(char tabuleiro[6][7], char disco) {
    for (int linha = 0; linha < 6; linha++) {
        for (int coluna = 0; coluna < 7 - 3; coluna++) {
            if (tabuleiro[linha][coluna] == disco && tabuleiro[linha][coluna + 1] == disco &&
                tabuleiro[linha][coluna + 2] == disco && tabuleiro[linha][coluna + 3] == disco) {
                return 1;
            }
        }
    }

    for (int coluna = 0; coluna < 7; coluna++) {
        for (int linha = 0; linha < 6 - 3; linha++) {
            if (tabuleiro[linha][coluna] == disco && tabuleiro[linha + 1][coluna] == disco &&
                tabuleiro[linha + 2][coluna] == disco && tabuleiro[linha + 3][coluna] == disco) {
                return 1;
            }
        }
    }

    for (int linha = 3; linha < 6; linha++) {
        for (int coluna = 0; coluna < 7 - 3; coluna++) {
            if (tabuleiro[linha][coluna] == disco && tabuleiro[linha - 1][coluna + 1] == disco &&
                tabuleiro[linha - 2][coluna + 2] == disco && tabuleiro[linha - 3][coluna + 3] == disco) {
                return 1;
            }
        }
    }

    for (int linha = 3; linha < 6; linha++) {
        for (int coluna = 3; coluna < 7; coluna++) {
            if (tabuleiro[linha][coluna] == disco && tabuleiro[linha - 1][coluna - 1] == disco &&
                tabuleiro[linha - 2][coluna - 2] == disco && tabuleiro[linha - 3][coluna - 3] == disco) {
                return 1;
            }
        }
    }

    return 0;
}
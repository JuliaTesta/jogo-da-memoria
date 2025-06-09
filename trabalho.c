/*
    Projeto: Jogo da Memória
    
    Membros do grupo:
    - Pedro Henrique Trindade
    - Isabela Maria
    - Julia Testa Matos
    
    Descrição: 
    O jogo consiste em um tabuleiro 4x4 com pares de números aleatórios ocultos.
    O jogador deve encontrar os pares com no máximo 10 tentativas.
    Ao final, pode optar por salvar seu placar em um arquivo de texto.

    Observações:
    - O código foi estruturado em funções para melhor modularização.
    - Comentários explicam principalmente partes de lógica mais complexa (como geração aleatória, verificação de acertos, manipulação de arquivos).
*/

#include <stdio.h> 
#include <stdlib.h>
#include <time.h>        // Para geração de números aleatórios baseada no tempo
#include <windows.h>    // Para funções como Sleep(), system("cls") e Beep()
#include <direct.h>     // Para obter o diretório onde o arquivo será salvo
#include <string.h>     // Para a função strlen()


// Definições de constantes
#define TAM 4        // Tamanho do tabuleiro (4x4)
#define COORD 5     // Tamanho usado na visualização com coordenadas (não usado diretamente no código)
#define PARES 8     // Total de pares no jogo (8 pares -> 16 posições)

// Definições de cores ANSI para tons claros e vibrantes
#define RESET       "\x1b[0m"
#define BRIGHT_BLUE "\x1b[94m"
#define BRIGHT_MAGENTA "\x1b[95m"
#define BRIGHT_CYAN "\x1b[96m"
#define BRIGHT_WHITE "\x1b[97m"
#define BRIGHT_GREEN "\x1b[92m"
#define BRIGHT_YELLOW "\x1b[93m"
#define BRIGHT_RED "\x1b[91m"

// Cores de fundo (bg) - Mantidas para referência, mas não aplicadas diretamente nos printf
#define BG_LIGHT_CYAN "\x1b[106m"
#define BG_LIGHT_YELLOW "\x1b[103m"
#define BG_LIGHT_MAGENTA "\x1b[105m"
#define BG_LIGHT_BLUE "\x1b[104m"
#define BG_LIGHT_GREEN "\x1b[102m"


// Protótipos das funções
void gerarTabuleiro(int tabuleiro[TAM][TAM]);
void mostrarTabuleiro(int tabuleiro[TAM][TAM], int tempo);
void mostrarTabuleiroOculto(int ponto, int chutes);
int verificar_acerto(int tabuleiro[TAM][TAM], int x1, int y1, int x2, int y2);
void salvarPlacar(int ponto, int erro);
void jogoDaMemoria();
void mostrarRegras();
int mostrarMenu();
void limparBuffer();

//----------------------------------------------
// Função Mostrar Menu: 
// Gera a tela inical do jogo, com a opção de iniciá-lo ou sair
//----------------------------------------------
int mostrarMenu(){
    int opcao;
    
    printf("\n\n");

    printf("         ░░░░░██╗░█████╗░░██████╗░░█████╗░  ██████╗░░█████╗░\n");
    printf("         ░░░░░██║██╔══██╗██╔════╝░██╔══██╗  ██╔══██╗██╔══██╗\n");
    printf("         ░░░░░██║██║░░██║██║░░██╗░██║░░██║  ██║░░██║███████║\n");
    printf("         ██╗░░██║██║░░██║██║░░╚██╗██║░░██║  ██║░░██║██╔══██║\n");
    printf("         ╚█████╔╝╚█████╔╝╚██████╔╝╚█████╔╝  ██████╔╝██║░░██║\n");
    printf("         ░╚════╝░░╚════╝░░╚═════╝░░╚════╝░  ╚═════╝░╚═╝░░╚═╝\n" RESET);
    printf("\n");
    printf("         " BRIGHT_CYAN "███╗░░░███╗███████╗███╗░░░███╗░█████╗░██████╗░██╗░█████╗░\n");
    printf("         " BRIGHT_CYAN "████╗░████║██╔════╝████╗░████║██╔══██╗██╔══██╗██║██╔══██╗\n");
    printf("         " BRIGHT_CYAN "██╔████╔██║█████╗░░██╔████╔██║██║░░██║██████╔╝██║███████║\n");
    printf("         " BRIGHT_CYAN "██║╚██╔╝██║██╔══╝░░██║╚██╔╝██║██║░░██║██╔══██╗██║██╔══██║\n");
    printf("         " BRIGHT_CYAN "██║░╚═╝░██║███████╗██║░╚═╝░██║╚█████╔╝██║░░██║██║██║░░██║\n");
    printf("         " BRIGHT_CYAN "╚═╝░░░░░╚═╝╚══════╝╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝╚═╝╚═╝░░╚═╝\n" RESET);
    
    printf("\n ");

    printf("          ＥＳＣＯＬＨＡ ＵＭＡ ＯＰＣＡＯ\n\n" RESET);
    printf("          " BRIGHT_GREEN "1-  𝐈𝐍𝐈𝐂𝐈𝐀𝐑 𝐉𝐎𝐆𝐎\n" RESET);
    printf("          " BRIGHT_RED "2-  𝐒𝐀𝐈𝐑\n" RESET);
    printf("          " BRIGHT_MAGENTA "3 - 𝐑𝐄𝐆𝐑𝐀𝐒 ✍(◔◡◔)\n" RESET);
    printf("          " BRIGHT_WHITE ""); // Inicia a cor para o scanf
    scanf("          %d", &opcao);
    printf(RESET ""); // Reseta a cor após o scanf

    return opcao; //retorna a opção escolhida
}

//----------------------------------------------
//Função Mostrar Regras:
//----------------------------------------------
void mostrarRegras(){
    system("cls");
    

    printf("\n\n");

    printf("             " BRIGHT_YELLOW "░█▀▀█ ░█▀▀▀ ░█▀▀█ ░█▀▀█ ─█▀▀█ ░█▀▀▀█\n");
    printf("             " BRIGHT_YELLOW "░█▄▄▀ ░█▀▀▀ ░█─▄▄ ░█▄▄▀ ░█▄▄█ ─▀▀▀▄▄\n");
    printf("             " BRIGHT_YELLOW "░█─░█ ░█▄▄▄ ░█▄▄█ ░█─░█ ░█─░█ ░█▄▄▄█\n" RESET);

    printf("\n\n");

    printf("    ╔══════════════════════════════════════════════════════════════════╗\n");
    printf("    ║ " BRIGHT_CYAN "1. O tabuleiro é 4x4 com 8 pares de números.                     ║\n");
    printf("    ║ " BRIGHT_CYAN "2. O objetivo é encontrar todos os pares com até 10 tentativas.  ║\n");
    printf("    ║ " BRIGHT_CYAN "3. Em cada tentativa, escolha duas coordenadas para revelar.     ║\n");
    printf("    ║ " BRIGHT_CYAN "4. Se os números forem iguais, você marca ponto.                 ║\n");
    printf("    ║ " BRIGHT_CYAN "5. Se forem diferentes, perde uma tentativa.                     ║\n");
    printf("    ║ " BRIGHT_CYAN "6. O jogo termina ao achar todos os pares ou acabar tentativas.  ║\n");
    printf("    ║ " BRIGHT_CYAN "7. Você pode salvar seu placar em um arquivo .txt no final.      ║\n");
    printf("    ╚══════════════════════════════════════════════════════════════════╝\n\n" RESET);

    printf( "Pressione qualquer tecla para voltar ao menu...\n");
    system("pause > nul"); //Espera pressionar tecla

    system("cls");
}

int main() {
    SetConsoleOutputCP(65001); // Suporte a acentuação UTF-8 no Windows console
    int opcao; 

    do{
        opcao = mostrarMenu(); //Recebe o valor retornado (escolha do jogador) e armazena na variável opção

    switch (opcao){
    case 1: {
        system("cls"); // Limpa a tela antes de reiniciar 
        char jogarNovamente;

    do {
        jogoDaMemoria(); // Inicia o jogo

        limparBuffer();
        printf(BRIGHT_BLUE "\nDeseja jogar novamente? (s/n): " RESET);
        scanf(" %c", &jogarNovamente);
        system("cls"); // Limpa a tela antes de reiniciar

    } while (jogarNovamente == 's' || jogarNovamente == 'S');
        break;
    }
    
    case 2:
       
        printf(BRIGHT_RED "Saindo do Jogo...\n" RESET);
        Sleep(1500);
        system("cls");
        break;

    case 3: 
        mostrarRegras();
        limparBuffer();
        break;

    default:
        printf(BRIGHT_RED "Opção inválida.\n" RESET);
        getchar(); //espera apertar tecla
        Sleep(1500);
        system("cls");
        break;
    }
    
} while (opcao !=2);
return 0; 

}

//----------------------------------------------
// Função: gerarTabuleiro
// Gera 8 pares de números aleatórios e os embaralha
//----------------------------------------------
void gerarTabuleiro(int tabuleiro[TAM][TAM]) {
    int valores[TAM*TAM]; 
    int usados[10] = {0}; // Controla quantas vezes cada número foi usado
    int paresGerados = 0, idx = 0;

    srand(time(NULL)); // Semente aleatória baseada no tempo

    // Geração dos pares
    while (paresGerados < PARES) {
        int num = rand() % 10; // Número de 0 a 9
        if (usados[num] < 2) { //Se o indice do vetor usados[1] (por exemplo) estiver com valor 2 então ele não seria usado.
            valores[idx++] = num;
            valores[idx++] = num;
            usados[num] = 2;
            paresGerados++;
        }
    }

    // Embaralhamento Fisher-Yates
    for (int i = TAM * TAM - 1; i > 0; i--) {
        int j = rand() % (i + 1); //garante que j estará entre 0 e i
        int temp = valores[i]; //Salva temporariamente o valor da posição
        valores[i] = valores[j]; //Coloca o valor da posição j na posição i
        valores[j] = temp; //Finaliza a troca colocando o valor original de i na posição j
    }

    // Preenchimento do tabuleiro com os valores embaralhados
    idx = 0;
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = valores[idx++];
        }
    }
}

//----------------------------------------------
// Função: mostrarTabuleiro
// Mostra o tabuleiro com os números por alguns segundos
//----------------------------------------------
void mostrarTabuleiro(int tabuleiro[TAM][TAM], int tempo) {
    
    printf("============================================\n");
    printf("        " BRIGHT_YELLOW "𝑻𝑨𝑩𝑼𝑳𝑬𝑰𝑹𝑶 4 𝑿 4 ( 𝑴𝑬𝑴𝑶𝑹𝑰𝒁𝑬❗)\n" RESET);         
    printf("============================================\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf(BRIGHT_MAGENTA "[%d] " RESET, tabuleiro[i][j]); // Números do tabuleiro em magenta vibrante
        }
        printf("\n"); // Nova linha
    }

    printf("\n Você tem %d segundos para memorizar...\n\n", tempo);
    for (int i = 1; i < 5; i++) {
        printf("        O tabuleiro será apagado em %i\n", i);
        Sleep(1000); // Espera 1 segundo entre cada contagem
        
    }

    system("cls"); // Limpa a tela após o tempo
}

//----------------------------------------------
// Função: mostrarTabuleiroOculto
// Exibe um tabuleiro com coordenadas e a pontuação atual
//----------------------------------------------
void mostrarTabuleiroOculto(int ponto, int chutes) {
    
    printf("============================================\n");
    printf("    " BRIGHT_YELLOW "𝑇𝐴𝐵𝑈𝐿𝐸𝐼𝑅𝑂 𝑂𝐶𝑈𝐿𝑇𝑂 𝐶𝑂𝑀 𝐶𝑂𝑂𝑅𝐷𝐸𝑅𝑁𝐴𝐷𝐴𝑆:\n" RESET);
    printf("============================================\n");

    // Cabeçalho com números das colunas
    printf("    " BRIGHT_CYAN); // Cor para os números das colunas
    for (int i = 1; i <= TAM; i++) {
        printf(" %2d ", i);
    }
    printf("\n" RESET);
    
    // Corpo do tabuleiro com coordenadas e símbolos ocultos
    for (int i = 0; i < TAM; i++) {
        printf(" %2d " RESET, i + 1); // Números das linhas
        for (int j = 0; j < TAM; j++) {
            printf(BRIGHT_BLUE "[*] " RESET); // Símbolos ocultos em azul vibrante
        }
        printf("\n" RESET);
    }

    printf("\n [🎮 𝙏𝙀𝙉𝙏𝘼𝙏𝙄𝙑𝘼𝙎 𝙍𝙀𝙎𝙏𝘼𝙉𝙏𝙀𝙎 ] " BRIGHT_RED "%d | [🌟 𝙋𝙊𝙉𝙏𝙊𝙎 ] " BRIGHT_GREEN "%d\n" RESET, chutes, ponto);
}

//----------------------------------------------
// Função: verificar_acerto
// Verifica se os valores nas duas coordenadas são iguais
//Se x1 ou y1 forem menores que 0 ou maiores/iguais a TAM, o jogador digitou coordenadas inválidas.
//----------------------------------------------
int verificar_acerto(int tabuleiro[TAM][TAM], int x1, int y1, int x2, int y2) {
      return tabuleiro[x1][y1] == tabuleiro[x2][y2];
}
    
//----------------------------------------------
// Função: salvarPlacar
// Permite salvar a pontuação do jogador em um arquivo .txt
//----------------------------------------------
void salvarPlacar(int ponto, int erro) {            
    
    printf("𝐏𝐚𝐫𝐚 𝐬𝐚𝐥𝐯𝐚𝐫 𝐬𝐞𝐮 𝐩𝐥𝐚𝐜𝐚𝐫 𝐝𝐢𝐠𝐢𝐭𝐞 𝟏, 𝐜𝐚𝐬𝐨 𝐧𝐚̃𝐨 𝐪𝐮𝐞𝐢𝐫𝐚 𝐝𝐢𝐠𝐢𝐭𝐞 𝟐: ");
    int salvar;
    scanf("%d", &salvar);
    limparBuffer(); 
    
    if (salvar == 1) {
        system("cls");
        

        FILE *dadosJogador = fopen("jogomemoria2025.txt", "a");//Dessa forma (Sem nenhum diretório indicado), o .txt será gerado no diretório do executável
        if (dadosJogador == NULL) {
            printf(BRIGHT_RED "Erro ao abrir arquivo.\n" RESET);
            return;
        }

        char nome[255];
        printf(BRIGHT_BLUE "Digite o nome do jogador:\n" RESET);
        scanf(" %[^\n]", nome); // Lê nome com espaços

        // Grava os dados no arquivo
        fprintf(dadosJogador, "Nome: %s\n", nome);
        fprintf(dadosJogador, "Pontos: %d\n", ponto);
        fprintf(dadosJogador, "Erros: %d\n\n", erro);

        char cwd[1024];
        _getcwd(cwd, sizeof(cwd)); // Obtém o diretório atual
        printf(BRIGHT_GREEN "Arquivo salvo em: %s\\jogomemoria2025.txt\n" RESET, cwd);

        fclose(dadosJogador);
    }
}

//----------------------------------------------
// Função principal do jogo: jogoDaMemoria
// Controla a lógica de tentativas, entrada do jogador e chamada das funções auxiliares
//----------------------------------------------
void jogoDaMemoria() {
    int tabuleiro[TAM][TAM];
    int ponto = 0, erro = 0, chutes = 10;
    int x1, y1, x2, y2;

    gerarTabuleiro(tabuleiro); // Gera o tabuleiro com os pares aleatórios
    mostrarTabuleiro(tabuleiro, 5); // Mostra o tabuleiro por 5 segundos

    // Loop principal do jogo
    while (chutes > 0 && ponto < PARES) {
        Sleep(1000);
        mostrarTabuleiroOculto(ponto, chutes);

        // Entrada do jogador
        printf(BRIGHT_BLUE "Coordenadas do 1º número (linha coluna): " RESET);
        if (scanf("%d %d", &x1, &y1) != 2) { //Verifica se foram digitados dois números inteiros
            printf(BRIGHT_RED "Entrada inválida. Tente novamente.\n" RESET); //Erro de digitação, ex: 'e' ou ';'
            limparBuffer(); 
            Sleep(1500);
            system("cls");
            continue;
        }
        
        printf(BRIGHT_BLUE "Coordenadas do 2º número (linha coluna): " RESET);
        if (scanf("%d %d", &x2, &y2) != 2) {
            printf(BRIGHT_RED "Entrada inválida. Tente novamente.\n" RESET); 
            limparBuffer();
            Sleep(1500);
            system("cls");
            continue;
        }
       
        // Ajuste de coordenadas (usuário digita de 1 a 4)
        x1--; y1--;
        x2--; y2--;

        // Validação das coordenadas
        if (x1 < 0 || x1 >= TAM || y1 < 0 || y1 >= TAM ||
            x2 < 0 || x2 >= TAM || y2 < 0 || y2 >= TAM ||
            (x1 == x2 && y1 == y2)) {
            printf(BRIGHT_RED " (ㆆ_ㆆ) Coordenadas inválidas ou repetidas. Tente novamente.\n" RESET); //Erro de jogo, ex: '15'
           
            Sleep(1500); //Espera  jogador ver o resultado e limpa a tela
            system("cls");
            continue;
        }

        // Verificação do acerto
        if (verificar_acerto(tabuleiro, x1, y1, x2, y2)) {
            printf(BRIGHT_GREEN " (>‿◠)✌ Par correto! [%d] == [%d]\n" RESET, tabuleiro[x1][y1], tabuleiro[x2][y2]);
            ponto++;
            chutes--;
            Beep(750, 300); // Som para acerto
        } else {
            printf(BRIGHT_RED " ( ˘︹˘ ) Errou! [%d] != [%d]\n" RESET, tabuleiro[x1][y1], tabuleiro[x2][y2]);
            erro++;
            chutes--;
        }
        Sleep(1500);
        system("cls");
    }

    // Mensagem final
    system("color F0"); // Fundo branco
    if (ponto == PARES) {
        printf(BRIGHT_GREEN "\n (っ＾▿＾) Parabéns! Você encontrou todos os pares!\n" RESET);
    } else {
        printf(BRIGHT_MAGENTA "\n  (•◡•)    Fim de jogo. Você fez %d ponto(s).\n" RESET, ponto);
    }

    // Mostra o tabuleiro completo no final
    printf(BRIGHT_CYAN "\nTabuleiro completo:\n\n" RESET);
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("[%d] " RESET, tabuleiro[i][j]); // Números do tabuleiro em branco
        }
        printf("\n" RESET); // Nova linha
    }

    system("cls"); // Limpa a tela antes de reiniciar


//Placar

    printf("      " BRIGHT_MAGENTA "██████╗░░█████╗░███╗░░██╗████████╗██╗░░░██╗░█████╗░░█████╗░░█████╗░░█████╗░\n");
    printf("      " BRIGHT_MAGENTA "██╔══██╗██╔══██╗████╗░██║╚══██╔══╝██║░░░██║██╔══██╗██╔══██╗██╔══██╗██╔══██╗\n");
    printf("      " BRIGHT_MAGENTA "██████╔╝██║░░██║██╔██╗██║░░░██║░░░██║░░░██║███████║██║░░╚═╝███████║██║░░██║\n");
    printf("      " BRIGHT_MAGENTA "██╔═══╝░██║░░██║██║╚████║░░░██║░░░██║░░░██║██╔══██║██║░░██╗██╔══██║██║░░██║\n");
    printf("      " BRIGHT_MAGENTA "██║░░░░░╚█████╔╝██║░╚███║░░░██║░░░╚██████╔╝██║░░██║╚█████╔╝██║░░██║╚█████╔╝\n");
    printf("      " BRIGHT_MAGENTA "╚═╝░░░░░░╚════╝░╚═╝░░╚══╝░░░╚═╝░░░░╚═════╝░╚═╝░░╚═╝░╚════╝░╚═╝░░╚═╝░╚════╝░\n\n" RESET);
    
printf("      " BRIGHT_GREEN "ＡＣＥＲＴＯＳ: %d\n " RESET,ponto);
printf("      " BRIGHT_RED "ＥＲＲＯＳ: %d\n " RESET,erro);

    salvarPlacar(ponto, erro); // Pergunta se o jogador quer salvar o placar
}

void limparBuffer() {
    int c; //armazena temporariamente os caracteres lidos
    while ((c = getchar()) != '\n' && c != EOF) { }
}
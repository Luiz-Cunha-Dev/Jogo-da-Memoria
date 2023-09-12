#include <stdio.h> // printf e scanf
#include <stdlib.h> // função de gerar numeros aleatorios
#include <time.h> // gerar a semente para a função rand (usando a hora atual)
#include <unistd.h> // função sleep
#include <locale.h> // acentuação e caracteres especiais
#include <windows.h> // função system

#define TAMANHO_TABULEIRO 4
#define TOTAL_CONJUNTOS 8

int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
int tabuleiroExibido[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
int acertos = 0;
int erros = 0;
int cor = 7, res;
	

void mostrarCartas(){
	int i, j;
	for(i = 0; i < TAMANHO_TABULEIRO; i++){
		for(j = 0; j < TAMANHO_TABULEIRO; j++){
		tabuleiroExibido[i][j] = 1;
	}
	}
}

void esconderCartas(){
		int i, j;
		for(i = 0; i < TAMANHO_TABULEIRO; i++){
		for(j = 0; j < TAMANHO_TABULEIRO; j++){
		tabuleiroExibido[i][j] = 0;
	}
	}
}

// Função para gerar números aleatórios de 0 a 7
int gerarNumeroAleatorio() {
    return rand() % 8;
}

// Função para inicializar o tabuleiro com pares de números aleatórios
void inicializarTabuleiro() {
    int i, j, k;
    int contadorConjuntos[TOTAL_CONJUNTOS] = {0};

    srand(time(NULL));

    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            do {
                k = gerarNumeroAleatorio();	
                
            } while (contadorConjuntos[k] >= 2);

            tabuleiro[i][j] = k;
            contadorConjuntos[k]++;
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro() {
    int i, j;

    printf("\n\n");

    // Exibir numeração das colunas
    printf("    ");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("  %d          ", j + 1);
    }
    printf("\n");

    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        // Exibir numeração das linhas

        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiroExibido[i][j]) {
                printf("   _______   ");
            } else {
                printf("   _______   ");
            }
        }
        printf("\n");

        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiroExibido[i][j]) {
                printf("  |       |  ");
            } else {
                printf("  |       |  ");
            }
        }
        printf("\n");	

        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiroExibido[i][j] && j == 0) {
                printf("%d |   %i   |  ", i+1, tabuleiro[i][j]);
            } else if (!tabuleiroExibido[i][j] && j == 0) {
                printf("%d |   %c   |  ", i+1, 63);
            }
            
			if (tabuleiroExibido[i][j] && j != 0) {
                printf("  |   %i   |  ", tabuleiro[i][j]);
            } else if (!tabuleiroExibido[i][j] && j != 0) {
                printf("  |   %c   |  ", 63);
            }
        }
        printf("\n");

        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiroExibido[i][j]) {
                printf("  |       |  ");
            } else {
                printf("  |       |  ");
            }
        }
        printf("\n");

        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiroExibido[i][j]) {
                printf("   TTTTTTT   ");
            } else {
                printf("   TTTTTTT   ");
            }
        }
        printf("\n");
    }
}

// Função para revelar uma carta do tabuleiro
void revelarCarta(int linha, int coluna) {
    tabuleiroExibido[linha][coluna] = 1;
}

// Função para ocultar uma carta do tabuleiro
void ocultarCarta(int linha, int coluna) {
    tabuleiroExibido[linha][coluna] = 0	;
}

// Função para verificar se as coordenadas são válidas
int coordenadasValidas(int linha, int coluna) {
    return linha >= 0 && linha < TAMANHO_TABULEIRO && coluna >= 0 && coluna < TAMANHO_TABULEIRO;
}

// Função para verificar se duas cartas são iguais
int cartasSaoIguais(int linha1, int coluna1, int linha2, int coluna2) {
	if(linha1 == linha2 && coluna1 == coluna2){
		return 0;
	}
    return tabuleiro[linha1][coluna1] == tabuleiro[linha2][coluna2];
}

//Função que exibe a apresentação
void apresentacao() {
    char* textoAscii =
    	"\n"
        "        __                                     __                   __  ___                                     _\n"
        "       / /  ____    ____ _  ____          ____/ /  ____ _          /  |/  /  ___    ____ ___   ____    _____   (_)  ____ _\n"
        "  __  / /  / __ \\  / __ `/ / __ \\        / __  /  / __ `/         / /|_/ /  / _ \\  / __ `__ \\ / __ \\  / ___/  / /  / __ `/\n"
        " / /_/ /  / /_/ / / /_/ / / /_/ /       / /_/ /  / /_/ /         / /  / /  /  __/ / / / / / // /_/ / / /     / /  / /_/ /\n"
        " \\____/   \\____/  \\__, /  \\____/        \\__,_/   \\__,_/         /_/  /_/   \\___/ /_/ /_/ /_/ \\____/ /_/     /_/   \\__,_/\n"
        "                 /____/\n\n";

    printf("%s", textoAscii);
}


void perguntaCor() {
    printf("                                        **************************************\n");
    	printf("\n                                          1 - Fundo branco e texto vermelho\n");
    	printf("                                          2 - Fundo preto e texto lilás\n");
    	printf("                                          3 - Fundo preto e texto verde\n");
    	printf("                                          4 - Fundo cinza e texto branco\n");
        printf("                                          5 - Fundo preto e texto verde água\n\n");
        printf("                                        **************************************\n");
        printf("\n  Entre com número da opção: ");
        scanf("%d", &cor);
        mudarCor(cor);
        
    	system("cls");
    
    	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n                                             AGUARDE SEU JOGO COMEÇARA EM BREVE... \n");
    	sleep(3);
    	system("cls");
}

void mudarCor(int cor){
	    if(cor == 1){
            system("color 74");
        }else if(cor == 2){
            system ("color 0D");
        }else if(cor == 3){
            system ("color 02");
        }else if(cor == 4){
            system ("color 87");
        }else if(cor == 5){
            system ("color 0B");
        }else{
        	system("color 07");
		}
}

void efeitoColorido(){
	int i = 0;
	
	while(i<2){
		system("color 01");
        usleep(300000); //0,3 segundos ou 300.000 microsegundos
        system("color 02");
        usleep(300000);
        system("color 03");
        usleep(300000);
        system("color 04");
        usleep(300000);
        system("color 05");
        usleep(300000);
        system("color 06");
        usleep(300000);
		i++;
	}
        mudarCor(cor);
	}

int main() {
	system("title Jogo da Memoria");
	setlocale(LC_ALL,"");
    int linha1, coluna1, linha2, coluna2;
    char nome[50];
    int salvarPontos = 0;
    

    do {
        acertos = 0;
        erros = 0;
        inicializarTabuleiro();
        apresentacao();
        efeitoColorido();

         
		printf("                                        *************************************");
		printf("\n\n                                         Deseja continuar com a cor padrão ?");
		printf("\n\n                                                     1-SIM  2-NÃO        \n\n");
		printf("                                        *************************************\n");
		scanf("%i",&res);
		system("cls");
		
		if(res==2){
			apresentacao();
			perguntaCor();
		}
		
    	apresentacao();
    	printf("               ***********************************************************************************************\n");
        printf("                   Regras:\n");
        printf("                   1. Memorize os números exibidos no tabuleiro.\n");
        printf("                   2. Digite as coordenadas das cartas para encontrá-las.\n");
        printf("                   3. Se as cartas forem iguais, você ganha pontos.\n");
        printf("                   4. Se as cartas forem diferentes, você perde pontos.\n");
        printf("                   5. O jogo termina quando todas as cartas forem encontradas ou se tiver mais de 10 erros.\n\n");
        printf("               ***********************************************************************************************\n");

        printf("\nDigite seu nome: ");
        scanf("%s", nome);

		
        printf("\nPrepare-se! O tabuleiro será exibido por 5 segundos.\n");
        sleep(3);
        system("cls");
        mostrarCartas();
        exibirTabuleiro();
        sleep(5);
        esconderCartas();
        system("cls");

        while (acertos < TOTAL_CONJUNTOS && erros <= 10) {
        	printf("\n                Acertos: %d  Erros: %d\n", acertos, erros);
        	            
            exibirTabuleiro();

            printf("\nDigite a linha da primeira carta: ");
            scanf("%d", &linha1);

            printf("Digite a coluna da primeira carta: ");
            scanf("%d", &coluna1);

            linha1--;
            coluna1--;

            if (coordenadasValidas(linha1, coluna1) && !tabuleiroExibido[linha1][coluna1]) {
                revelarCarta(linha1, coluna1);
                system("cls");
                exibirTabuleiro();

                printf("\nDigite a linha da segunda carta: ");
                scanf("%d", &linha2);

                printf("Digite a coluna da segunda carta: ");
                scanf("%d", &coluna2);

                linha2--;
                coluna2--;

                if (coordenadasValidas(linha2, coluna2) && !tabuleiroExibido[linha2][coluna2]) {
                    revelarCarta(linha2, coluna2);
                    system("cls");
                    exibirTabuleiro();

                    if (cartasSaoIguais(linha1, coluna1, linha2, coluna2)) {
                    	printf("%c", 7);
                    	printf("\033[32m"); // Altera a cor do texto para verde
                        printf("\n     Parabéns, você encontrou um par de cartas!\n");
                        acertos++;
                        sleep(1);  // Aguarda 1 segundo
                    } else {
                    	printf("\033[31m"); // Altera a cor do texto para vermelho
                        printf("\n     As cartas são diferentes! Tente novamente.\n");
                        ocultarCarta(linha1, coluna1);
                        ocultarCarta(linha2, coluna2);
                        erros++;
                        sleep(1);  // Aguarda 1 segundo
                    }
                    
                    sleep(3);

					mudarCor(cor);
                    system("cls");
                } else {
                	system("cls");
                    printf("\nCoordenadas inválidas ou carta já revelada! Tente novamente.\n");
                    ocultarCarta(linha1, coluna1);
                }
            } else {
            	system("cls");
                printf("\nCoordenadas inválidas ou carta já revelada! Tente novamente.\n");
            }
        }

        if (acertos == TOTAL_CONJUNTOS) {
            apresentacao();
            printf("                                            Parabéns! Você venceu o jogo!\n");
            printf("                                    *********************************************\n");
            printf("                                                     .-=========-.\n");
    		printf("                                                     \\'-=======-'/\n");
    		printf("                                                     _|   .=.   |_ \n");
    		printf("                                                    ((|         |))\n");
    		printf("                                                     \\|   /|\\   |/\n");
    		printf("                                                      \\__ '`' __/\n");
    		printf("                                                        _`) (`_\n");
    		printf("                                                      _/_______\\_\n");
    		printf("                                                     /___________\\\n");
    		printf("                                    *********************************************\n\n");
        } else {
            apresentacao();
    		printf("                                            /|  /|  ---------------------------\n");
    		printf("                                            ||__||  |                         |\n");
    		printf("                                           /   O O\\__         Você perdeu!    |\n");
    		printf("                                          /          \\       Tente novamente  |\n");
    		printf("                                         /      \\     \\                       |\n");
    		printf("                                        /   _    \\     \\ ----------------------\n");
    		printf("                                       /    |\\____\\     \\      ||\n");
    		printf("                                      /     | | | |\\____/      ||\n");
    		printf("                                     /       \\| | | |/ |     __||\n");
    		printf("                                    /  /  \\   -------  |_____| ||\n");
    		printf("                                   /   |   |           |       --|\n");
    		printf("                                   |   |   |           |_____  --|\n");
    		printf("                                   |  |_|_|_|          |     \\----\n");
    		printf("                                   /\\                  |\n");
    		printf("                                  / /\\        |        /\n");
    		printf("                                 / /  |       |       |\n");
    		printf("                             ___/ /   |       |       |\n");
    		printf("                            |____/    c_c_c_C/ \\C_c_c_c\n\n\n");
        }

        printf("Pontuação final: Acertos: %d  Erros: %d\n", acertos, erros);

        printf("\nDeseja salvar seus pontos? (1 - Sim, 2 - Não): ");
        scanf("%d", &salvarPontos);

        if (salvarPontos == 1) {
            FILE *arquivo = fopen("jogomemoria2023.txt", "a");

            if (arquivo != NULL) {
                fprintf(arquivo, "Jogador: %s | Acertos: %d | Erros: %d\n", nome, acertos, erros);
                fclose(arquivo);
            }
        }
        printf("\nDeseja jogar novamente? (1 - Sim, 2 - Não): ");
        scanf("%d", &salvarPontos);
        system("cls");

    } while (salvarPontos == 1);

   return 0;
}

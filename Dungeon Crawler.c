#include <stdio.h>
#include <stdlib.h>

int main(){
	
	int i;
	int j;
	int tela = 0;
	int escolha;
	
	char fase1 [10][10];
	char fase2 [20][20];
	char fase3 [40][40];
	
	int move;
	int pos_playerX = 1, pos_playerY = 1;
	char player = '&';
	
	
	// Inicializando as matrizes
  	for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            if (i == 0 || i == 9 || j == 0 || j == 9) {
                fase1[i][j] = '*';
            } else {
                fase1[i][j] = ' ';
            }
        }
    }
	
	// Laço do menu principal
	
	while(tela == 0){
		
		system("cls");
		printf("Silas, O Lobo \n1-Jogar\n2-Tutorial\n3-Sair\n");
		escolha = getch();
		
		if(escolha =='1'){
			system("cls");
			printf ("Em uma noite escura,");
			system("pause");

			tela = 1;
			system("cls");
		}
		
		else if(escolha=='2'){
		system ("cls");	
		printf(
		"Ok, aqui vao algumas instrucoes:\n\n"
		"O jogo e do estilo aventura onde o objetivo e o jogador conseguir passar as 3 fases.\n"
		"Em cada fase,o jogador deve se movimentar para pegar uma chave e abir uma porta fechada.\n\n"
		"Aqui estao os seguintes comandos que o jogador deve usar para completar as missoes:\n\n"
		"W: o jogador movimenta uma unidade para cima\n"
		"A: O jogador movimenta uma unidade para esquerda\n"
		"S: O jogador movimenta uma unidade para baixo\n"
		"D: O jogador movimenta uma unidade para direita\n"
		"I: O jogador interage com o objeto que esta em cima\n ");
		system("pause");
		}
		
		else if(escolha=='3'){
		system("cls");
		printf("Os uivos ecoam pela floresta enquanto voce se afasta. Ate a proxima lua cheia, corajoso aventureiro.");
		return 0;
		}
		else{
			printf("la ele 1000x kkkkk. kkkk do bora bill \n kkk la eleeeeeee \n kkkkk... \nklkkkkkk!!! la ele :)\n");
			system("pause");
		}
	}
	
	while (tela == 1){
		
		for (i = 0; i < 10; i++){
			for (j = 0; j < 10; j++){
				if (i == pos_playerY && j == pos_playerX){
					fase1[i][j] = player;
				}
				printf("%c", fase1[i][j]);
			}
			printf("\n");
		}
		
		fase1[pos_playerY][pos_playerX] = ' ';
		
		move = getch();
		
		if (move == 'w'&& pos_playerY - 1 != 0 && pos_playerY - 1 != 9){
			pos_playerY--;	
		}
		if (move == 's'&& pos_playerY + 1 != 0 && pos_playerY + 1 != 9){
			pos_playerY++;
		}
		if (move == 'a'&& pos_playerX - 1 != 0 && pos_playerX - 1 != 9){
			pos_playerX--;
		}
		if (move == 'd'&& pos_playerX + 1 != 0 && pos_playerX + 1 != 9){
			pos_playerX++;	
		}
		system("cls");
	}
	
	return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main(){
	
	int menu = 1;
	int rm = 9;
	char escolha;
	char fase1 [10][10];
	char fase2 [20][20];
	char fase3 [40][40];
	
	char player='&';
	
	// Laço do menu principal
	
	while(menu > 0){
		
		system("cls");
		printf("Silas, O Lobo \n1-Jogar\n2-Tutorial\n3-Sair\n");
		scanf(" %c", &escolha);
		
		if(escolha =='1'){
			system("cls");
			printf ("Historia do lobo silas\n");
			system("pause");
			menu = 0;
			rm = 1;
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
		printf("Os uivos ecoam pela floresta enquanto você se afasta. Ate a proxima lua cheia, corajoso aventureiro.");
		return 0;
		}
	}
	while (rm == 1){
		// Aqui deve começar a primeira fase, ainda por fazer.
		printf("placeholder");
		system("pause");
		}
		
}

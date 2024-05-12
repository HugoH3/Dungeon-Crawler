#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Variáveis Globais (constantes)
const char PLAYER_CHAR = '&';
const char KEY_CHAR = '@';
const char MONSTER_CHAR = 'X';
const char CLOSED_DOOR = 'D';
const char OPENED_DOOR = '=';

// Função de inicializar as matrizes, criando as paredes da fase

void levelWalls (int xLimit, int yLimit, char level[xLimit][yLimit]){
    level[xLimit][yLimit];
    for (int x = 0; x < xLimit; x++) {
        for (int y = 0; y < yLimit; y++) {
            if (x == 0 || x == xLimit - 1 || y == 0 || y == yLimit - 1) {
                level[x][y] = '*';
            } else {
                level[x][y] = ' ';
            }
        }
    } 
}

int main() {
    srand(time(NULL));

    // Declaração de variavéis 
    int screen = 0;
    int choice;

    int key_pressed;
    int playerX = 1, playerY = 1;
    int monsterX = 6, monsterY = 6;
    int monstermov;
    int coord_X, coord_Y;
    
    int playerHasKey = 0;

    // Inicializando matrizes

    char level1[10][10];
    char level2[20][20];
    char level3[40][40];
    levelWalls(10,10, level1);
    levelWalls(20,20, level2);


    // Main menu loop
    while (screen == 0) {
        system("cls");
        printf("Silas, The Wolf\n1-Play\n2-Tutorial\n3-Exit\n");
        choice = getch();

        if (choice == '1') {
            system("cls");

            // Todo: Adicionar introdução da história aqui
            printf(
                "Em uma noite de lua cheia na floresta dos afogados\n"
                "Silas anda solitario. "    
            );
            system("pause");
            screen = 1;
            system("cls");
        } else if (choice == '2') {
            system("cls");
            printf(
                "Alright, here are some instructions:\n\n"
                "The game is an adventure where the player must pass 3 levels.\n"
                "In each level, the player must move to collect a key and open a closed door.\n\n"
                "Use the following commands to complete the missions:\n\n"
                "W: Move one unit up\n"
                "A: Move one unit left\n"
                "S: Move one unit down\n"
                "D: Move one unit right\n"
                "I: Interact with the object on top\n");
            system("pause");
            
        } else if (choice == '3') {
            system("cls");
            printf("The howls echo through the forest as you depart. Until the next full moon, brave adventurer.");
            return 0;
        } else {
            printf("Press a valid key!\n");
            system("pause");
        }
    }

    // Level 1 loop
    while (screen == 1){
        monstermov = rand()%4;
        if (monstermov == 0 && monsterX - 1 != 0 && monsterX - 1 != 9){
            monsterX--;
        }
        if (monstermov == 1 && monsterX + 1 != 0 && monsterX + 1 != 9){
            monsterX++;
        }
        if (monstermov == 2 && monsterY - 1 != 0 && monsterY - 1 != 9){
            monsterY--;
        }
        if (monstermov == 3 && monsterY + 1 != 0 && monsterY + 1 != 9){
            monsterY++;
        }
        level1[monsterX][monsterY] = MONSTER_CHAR;

        if (playerHasKey == 0) {
            level1[9][5] = CLOSED_DOOR;
            level1[5][5] = KEY_CHAR;
        } else {
            level1[9][5] = OPENED_DOOR;
        }


        // Loop principal do jogo
        for (coord_X = 0; coord_X < 10; coord_X++) {
            for (coord_Y = 0; coord_Y < 10; coord_Y++) {
                if (coord_X == playerX && coord_Y == playerY) {
                    level1[coord_X][coord_Y] = PLAYER_CHAR;
                }
                printf("%c", level1[coord_X][coord_Y]);
            }
            printf("\n");
        }
    
        level1[playerX][playerY] = ' ';
        level1[monsterX][monsterY] = ' ';

        key_pressed = getch();

        // Todo: Transformar isso em uma função
        if (key_pressed == 'w' && playerX - 1 != 0 && playerX - 1 != 9) {
            playerX--;
        }
        if (key_pressed == 's' && playerX + 1 != 0 && playerX + 1 != 9) {
            playerX++;
        }
        if (key_pressed == 'a' && playerY - 1 != 0 && playerY - 1 != 9) {
            playerY--;
        }
        if (key_pressed == 'd' && playerY + 1 != 0 && playerY + 1 != 9) {
            playerY++;
        }
        if (key_pressed == 'i' && playerY == 5 && playerX == 5) {
            playerHasKey = 1;
        }
        if (playerX == monsterX  && playerY == monsterX) {
            system("cls");
            printf("Silas died, poor thing. But he can try again by pressing any key.\n\n");
            system("pause");
            playerY = 1;
            playerX = 1;
            playerHasKey = 0;
        }
        if (playerX == 8 && playerY == 5 && playerHasKey == 1 && key_pressed == 's'){
            screen = 2;
            system("cls");
            system("pause");
            playerX = 1, playerY = 1;
        }
        system("cls");
    }
    

    // Todo: Corrigir tela se imprimindo infinitamente
    while (screen == 2){

         for (coord_X = 0; coord_X < 20; coord_X++) {
            for (coord_Y = 0; coord_Y < 20; coord_Y++) {
                if (coord_X == playerX && coord_Y == playerY) {
                    level2[coord_X][coord_Y] = PLAYER_CHAR;
                }
                printf("%c", level2[coord_X][coord_Y]);
            }
            printf("\n");
        }
        level1[playerX][playerY] = ' ';
    }
    key_pressed = getch();
    

    return 0;
}
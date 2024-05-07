#include <stdio.h>
#include <stdlib.h>

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

    // Declaração de variavéis 
    int screen = 0;
    int choice;

    int key_pressed;
    int playerX = 1, playerY = 1;
    int coord_X, coord_Y;


    char player = '&';
    char key = '@';
    int playerHasKey = 0;
    char CLOSED_DOOR = 'D';
    char OPENED_DOOR = '=';

    char PLAYER_CHAR = '&';
    char KEY_CHAR = '@';
    char MONSTER_CHAR = 'X';

    // Inicializando matrizes

    char level1[10][10];
    levelWalls(10,10, level1);

    // Main menu loop
    while (screen == 0) {
        system("cls");
        printf("Silas, The Wolf\n1-Play\n2-Tutorial\n3-Exit\n");
        choice = getch();

        if (choice == '1') {
            system("cls");

            // Todo: Adicionar introdução da história aqui
            printf("Silas");
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
    while (screen == 1) {
        level1[6][6] = MONSTER_CHAR;

        if (playerHasKey == 0) {
            level1[9][5] = CLOSED_DOOR;
        } else {
            level1[9][5] = OPENED_DOOR;
        }

        if (playerHasKey == 0) {
            level1[5][5] = KEY_CHAR;
        }

        for (coord_X = 0; coord_X < 10; coord_X++) {
            for (coord_Y = 0; coord_Y < 10; coord_Y++) {
                if (coord_X == playerY && coord_Y == playerX) {
                    level1[coord_X][coord_Y] = PLAYER_CHAR;
                }
                printf("%c", level1[coord_X][coord_Y]);
            }
            printf("\n");
        }

        level1[playerY][playerX] = ' ';

        key_pressed = getch();

        // Todo: Transformar isso em uma função
        if (key_pressed == 'w' && playerY - 1 != 0 && playerY - 1 != 9) {
            playerY--;
        }
        if (key_pressed == 's' && playerY + 1 != 0 && playerY + 1 != 9) {
            playerY++;
        }
        if (key_pressed == 'a' && playerX - 1 != 0 && playerX - 1 != 9) {
            playerX--;
        }
        if (key_pressed == 'd' && playerX + 1 != 0 && playerX + 1 != 9) {
            playerX++;
        }
        if (key_pressed == 'i' && playerX == 5 && playerY == 5) {
            playerHasKey = 1;
        }
        if (playerX == 6 && playerY == 6) {
            system("cls");
            printf("Silas died, poor thing. But he can try again by pressing any key.\n\n");
            system("pause");
            playerX = 1;
            playerY = 1;
            playerHasKey = 0;
        }
        system("cls");
    }

    return 0;
}
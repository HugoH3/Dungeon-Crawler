#include <stdio.h>
#include <stdlib.h>

int main() {
    // Declare Variables
    int i;
    int j;
    int screen = 0;
    int choice;

    char level1[10][10];
    char level2[20][20];
    char level3[40][40];

    int move;
    int playerX = 1, playerY = 1;

    char player = '&';
    char key = '@';
    int playerHasKey = 0;
    char CLOSED_DOOR = 'D';
    char OPENED_DOOR = '=';

    char PLAYER_CHAR = '&';
    char KEY_CHAR = '@';
    char MONSTER_CHAR = 'X';

    // Initialize matrices
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            if (i == 0 || i == 9 || j == 0 || j == 9) {
                level1[i][j] = '*';
            } else {
                level1[i][j] = ' ';
            }
        }
    }

    // Main menu loop
    while (screen == 0) {
        system("cls");
        printf("Silas, The Wolf\n1-Play\n2-Tutorial\n3-Exit\n");
        choice = getch();

        if (choice == '1') {
            system("cls");
            printf("On a dark night,");
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

        for (i = 0; i < 10; i++) {
            for (j = 0; j < 10; j++) {
                if (i == playerY && j == playerX) {
                    level1[i][j] = PLAYER_CHAR;
                }
                printf("%c", level1[i][j]);
            }
            printf("\n");
        }

        level1[playerY][playerX] = ' ';

        move = getch();

        if (move == 'w' && playerY - 1 != 0 && playerY - 1 != 9) {
            playerY--;
        }
        if (move == 's' && playerY + 1 != 0 && playerY + 1 != 9) {
            playerY++;
        }
        if (move == 'a' && playerX - 1 != 0 && playerX - 1 != 9) {
            playerX--;
        }
        if (move == 'd' && playerX + 1 != 0 && playerX + 1 != 9) {
            playerX++;
        }
        if (move == 'i' && playerX == 5 && playerY == 5) {
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


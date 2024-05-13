#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Variáveis Globais
const char PLAYER_CHAR = '&';
const char KEY_CHAR = '@';
const char MONSTER_CHAR = 'X';
const char MONSTER2_CHAR = 'V';
const char CLOSED_DOOR = 'D';
const char OPENED_DOOR = '=';
const char SPIKE_CHAR = '#';
const char BUTTON_CHAR = 'O';

char key_pressed;
int playerX = 1, playerY = 1;
int monsterX, monsterY;
int player_has_key;
int keyX, keyY;
int screen = 0;
int coord_X, coord_Y;
int lifes;
int button_pressed;

// Funções do Jogo
void playerMovement(char key_pressed, int limit)
{
    if (key_pressed == 'q')
    {
        screen = 0;
        main();
    }
    if (key_pressed == 'w' && playerX - 1 != 0 && playerX - 1 != limit)
    {
        playerX--;
    }
    if (key_pressed == 's' && playerX + 1 != 0 && playerX + 1 != limit)
    {
        playerX++;
    }
    if (key_pressed == 'a' && playerY - 1 != 0 && playerY - 1 != limit)
    {
        playerY--;
    }
    if (key_pressed == 'd' && playerY + 1 != 0 && playerY + 1 != limit)
    {
        playerY++;
    }
}
void levelWalls(int xLimit, int yLimit, char level[xLimit][yLimit])
{
    for (int x = 0; x < xLimit; x++)
    {
        for (int y = 0; y < yLimit; y++)
        {
            if (x == 0 || x == xLimit - 1 || y == 0 || y == yLimit - 1)
            {
                level[x][y] = '*';
            }
            else
            {
                level[x][y] = ' ';
            }
        }
    }
}
void print_level(int xLimit, int yLimit, char level[xLimit][yLimit])
{
    for (coord_X = 0; coord_X < xLimit; coord_X++)
    {
        for (coord_Y = 0; coord_Y < yLimit; coord_Y++)
        {
            printf("%c", level[coord_X][coord_Y]);
        }
        printf("\n");
    }
}
void gameOver(char level[20][20]) 
{
    if (level[playerX][playerY] == SPIKE_CHAR || playerX == monsterX && playerY == monsterY) {
        system("cls");
        playerY = 1;
        playerX = 1;
        player_has_key = 0;
        lifes--;

        if (lifes == 0) {
            printf(
                "|You can hear Silas howl one last time\n"
                "|He failed to find his friend, and now he's trapped inside, forever\n"
                "|Memento Mori.\n"
            );
            system("pause");
            screen = 0;
            main();
        }
        printf("|C'mon Silas, are you even trying?\n|Lifes left: %d\n\n", lifes);

        system("pause");
    }
}
int main()
{
    lifes = 3;
    srand(time(NULL));

    // Declaração de variavéis

    int choice;

    int monstermov;

    // Inicializando matrizes
    char level1[10][10];

    char level2[20][20];
    // char level3[40][40];
    levelWalls(10, 10, level1);
    levelWalls(20, 20, level2);

    // Loop do Menu
    while (screen == 0)
    {
        system("cls");
        printf("Silas, The Wolf\n1-Play\n2-Tutorial\n3-Exit\n");
        choice = getch();

        if (choice == '1')
        {
            system("cls");

            // Todo: Adicionar introdução da história aqui
            printf(
                "|Once upon a time, our hero Silas was wandering in the lost woods\n"
                "|He was looking for his friend, Charlie, that has misteriously disappered 3 nights before.\n"
                "|While walking through the fog, he sees a trail of fur that took him into a dark cave\n"
                "|As he goes inside, a shadow can be seem jumping around randomly next to a key\n"
                "|The creature was blind, but dangerous.\n"
            );

            system("pause");
            screen = 1;
            system("cls");
        }
        else if (choice == '2')
        {
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
        }
        else if (choice == '3')
        {
            system("cls");
            printf("The howls echo through the forest as you depart. Until the next full moon, brave adventurer.");
            return 0;
        }
        else
        {
            printf("Press a valid key!\n");
            system("pause");
        }
    }

    // Level 1 loop
    while (screen == 1)
    {
        monsterX = 6;
        monsterY = 6;
        keyX = 5;
        keyY = 5;

        monstermov = rand() % 4;
        if (monstermov == 0 && monsterX - 1 != 0 && monsterX - 1 != 9)
        {
            monsterX--;
        }
        if (monstermov == 1 && monsterX + 1 != 0 && monsterX + 1 != 9)
        {
            monsterX++;
        }
        if (monstermov == 2 && monsterY - 1 != 0 && monsterY - 1 != 9)
        {
            monsterY--;
        }
        if (monstermov == 3 && monsterY + 1 != 0 && monsterY + 1 != 9)
        {
            monsterY++;
        }

        level1[monsterX][monsterY] = MONSTER_CHAR;
        if (player_has_key == 0)
        {
            level1[9][5] = CLOSED_DOOR;
            level1[keyX][keyY] = KEY_CHAR;
        }
        if (player_has_key == 1)
        {
            level1[9][5] = OPENED_DOOR;
            level1[keyX][keyY] = ' ';
        }

        level1[playerX][playerY] = PLAYER_CHAR;
        print_level(10, 10, level1);

        level1[playerX][playerY] = ' ';
        level1[monsterX][monsterY] = ' ';

        key_pressed = getch();
        playerMovement(key_pressed, 9);

        if (playerX == keyX && playerY == keyY && key_pressed == 'i')
        {
            player_has_key = 1;
        }

        gameOver(level1);

        // Checando posição do player, se ele estiver em cima da porta aberta e apertar 's', avança
        if (playerX == 8 && playerY == 5 && player_has_key == 1 && key_pressed == 's')
        {
            screen = 2;
            system("cls");
            printf(
                "|Silas manages to escape the creature, the door behind him closes, there's no going back now.\n"
                "|He finds more clues about his friend Charlie, he's now closer than ever!\n"
                "|Silas senses a dark presence as he enters the next room.\n"
                "|It's a Fabiliraryanalizerichardugo, a monster that can only be summoned by skilled wizards\n"
                "|This monster follows his target until he gets close enough to absorb all energy\n"
            );
            system("pause");
            playerX = 1, playerY = 1;
            player_has_key = 0;
        }
        system("cls");
    }

    // Loop da Fase 2
    while (screen == 2)
    {   
        // Declarando posições iniciais dos objetos

        monsterX = 10;
        monsterY = 17;
        keyX = 2;
        keyY = 8;
        
        // Lógica do botão, ele tenha sido pressionado, os espinhos envolta da chave sumirão
        if (button_pressed == 0)
        {
            level2[keyX-1][keyY] = SPIKE_CHAR;
            level2[keyX+1][keyY] = SPIKE_CHAR;
            level2[keyX][keyY-1] = SPIKE_CHAR;
            level2[keyX][keyY+1] = SPIKE_CHAR;
            level2[12][12] = BUTTON_CHAR;
        }
        else
        {
            level2[keyX-1][keyY] = ' ';
            level2[keyX+1][keyY] = ' ';
            level2[keyX][keyY-1] = ' ';
            level2[keyX][keyY+1] = ' ';
        }
        if (player_has_key == 0)
        {
            level2[19][5] = CLOSED_DOOR;
            level2[keyX][keyY] = KEY_CHAR;
        }
        else
        {
            level2[19][5] = OPENED_DOOR;
        }


        monstermov = rand() % 2;    
        if (monstermov == 0) 
        {
            if (playerY < monsterY && monsterY - 1 != 0) {
                monsterY--;
            } else if (playerY > monsterY && monsterY + 1 != 19) {
                monsterY++;
            }
        } 
        else 
        {
            if (playerX < monsterX && monsterX - 1 != 0) {
                monsterX--;
            } else if (playerX > monsterX && monsterX + 1 != 19) {
                monsterX++;
            }
        }

        // Colocando o player e monstro
        level2[playerX][playerY] = PLAYER_CHAR;
        level2[monsterX][monsterY] = MONSTER2_CHAR;

        print_level(20, 20, level2);

        if (playerX == 12 && playerY == 12)
        {
            button_pressed = 1;
            printf("The Key is now safe to grab!\n");
        }

        level2[playerX][playerY] = ' ';
        level2[monsterX][monsterY] = ' ';
        key_pressed = getch();

        if (playerX == keyX && playerY == keyY && key_pressed == 'i')
        {
            player_has_key = 1;
            level2[19][5] = OPENED_DOOR;
        }
        if (playerX == 18 && playerY == 5 && player_has_key == 1 && key_pressed == 's'){
            system("cls");
            screen = 3;
            printf("|The story of Silas does not end here. Come back soon. \n");
            system("pause");
        }
        playerMovement(key_pressed, 19);
        gameOver(level2);
        system("cls");

    }

    return 0;
}

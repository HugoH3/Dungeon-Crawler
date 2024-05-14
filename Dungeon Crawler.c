#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

// Definindo as constantes
const char PLAYER_CHAR = '&';
const char KEY_CHAR = '@';
const char MONSTER_CHAR = 'X';
const char MONSTER2_CHAR = 'V';
const char CLOSED_DOOR = 'D';
const char OPENED_DOOR = '=';
const char SPIKE_CHAR = '#';
const char BUTTON_CHAR = 'O';
const char WALL_CHAR = '*';
const char EMPTY_SPACE = ' ';

// Definindo variáveis globais

char map[40][40];
// char level3[40][40]

char key_pressed;
int playerX = 1, playerY = 1;
int monsterX, monsterY;
int player_has_key;
int keyX, keyY;
int x, y;
int monstermov;
int button_pressed;
int screen;

// Funções do Jogo
void monsterMovement(int limit){
    monstermov = rand()%4;
        if (monstermov == 0 && monsterX - 1 != 0 && monsterX - 1 != limit)
        {
            monsterX--;
        }
        else if (monstermov == 1 && monsterX + 1 != 0 && monsterX + 1 != limit)
        {
            monsterX++;
        }
        else if (monstermov == 2 && monsterY - 1 != 0 && monsterY - 1 != limit)
        {
            monsterY--;
        }
        else if (monstermov == 3 && monsterY + 1 != 0 && monsterY + 1 != limit)
        {
            monsterY++;
        }
}
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
    map[playerX][playerY] = PLAYER_CHAR;
}
void levelWalls(int limit)
{
    for (int x = 0; x < limit; x++)
    {
        for (int y = 0; y < limit; y++)
        {
            // Definindo onde devem ficar as paredes e onde devem ter espaços vazios
            if (x == 0 || x == limit - 1 || y == 0 || y == limit - 1)
            {
                map[x][y] = WALL_CHAR;
            }
            else
            {
                map[x][y] = EMPTY_SPACE;
            }
        }
    }
}
void print_level(int limit)
{
    // Imprimindo o level
    for (x = 0; x < limit; x++)
    {
        for (y = 0; y < limit; y++)
        {
            printf("%c", map[x][y]);
        }
        printf("\n");
    }
}
void gameOver() 
{
    if (map[playerX][playerY] == SPIKE_CHAR || 
        map[playerX][playerY] == MONSTER_CHAR || 
        map[playerX][playerY] == MONSTER2_CHAR) 
    {
        int lives = 3;
        system("cls");
        playerY = 1;
        playerX = 1;
        player_has_key = 0;
        lives--;
        
        if (lives == 0) 
        {
            printf(
                "|You can hear Silas howl one last time\n"
                "|He failed to find his friend, and now he's trapped inside, forever\n"
                "|Memento Mori.\n"
            );
            system("pause");

            lives = 3;
            screen = 0;
            mainMenu();
        }
        printf("|C'mon Silas, are you even trying?|\n|Lifes left: %d|\n\n", lives);

        system("pause");
    }
}
void mainMenu()
{
system("cls");
    printf("Silas, The Wolf\n1-Play\n2-Tutorial\n3-Exit\n");

    key_pressed = getch();

    if (key_pressed == '1')
    {
        system("cls");

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
    else if (key_pressed == '2')
    {
        system("cls");
        printf(
            "Alright, here are some instructions:\n\n"
            "The game is an adventure where the player must pass 3 levels.\n"
            "In each map, the player must move to collect a key and open a closed door.\n\n"
            "Use the following commands to complete the missions:\n\n"
            "W: Move one unit up\n"
            "A: Move one unit left\n"
            "S: Move one unit down\n"
            "D: Move one unit right\n"
            "I: Interact with the object on top\n");
        system("pause");
    }
    else if (key_pressed == '3')
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
int main()
{
    srand(time(NULL));
    mainMenu();

    while (screen == 1)
    {
        levelWalls(10);
        monsterX = 7;
        monsterY = 8;
        keyX = 5;
        keyY = 5;
        
        monsterMovement(10);
        gameOver();
        
        map[playerX][playerY] = PLAYER_CHAR;
        if (player_has_key == 0)
        {
            map[9][5] = CLOSED_DOOR;
            map[keyX][keyY] = KEY_CHAR;
        }
        if (player_has_key == 1)
        {
            map[9][5] = OPENED_DOOR;
            map[keyX][keyY] = EMPTY_SPACE;
        }
    
        print_level(10);
        
        map[playerX][playerY] = EMPTY_SPACE;
        map[monsterX][monsterY] = EMPTY_SPACE;

        key_pressed = getch();
        playerMovement(key_pressed, 9);

        if (playerX == keyX && playerY == keyY && key_pressed == 'i')
        {
            player_has_key = 1;
        }

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
        }
        system("cls");
    }

    // Loop da Fase 2
    while (screen == 2)
    {   
        levelWalls(20);

        // Declarando posições iniciais dos objetos

        monsterX = 10;
        monsterY = 17;
        keyX = 2;
        keyY = 8;
        
        // Lógica do botão, ele tenha sido pressionado, os espinhos envolta da chave sumirão
        if (button_pressed == 0)
        {
            map[keyX-1][keyY] = SPIKE_CHAR;
            map[keyX+1][keyY] = SPIKE_CHAR;
            map[keyX][keyY-1] = SPIKE_CHAR;
            map[keyX][keyY+1] = SPIKE_CHAR;
            map[12][12] = BUTTON_CHAR;
        }
        else
        {
            map[keyX-1][keyY] = EMPTY_SPACE;
            map[keyX+1][keyY] = EMPTY_SPACE;
            map[keyX][keyY-1] = EMPTY_SPACE;
            map[keyX][keyY+1] = EMPTY_SPACE;
        }
        if (player_has_key == 0)
        {
            map[19][5] = CLOSED_DOOR;
            map[keyX][keyY] = KEY_CHAR;
        }
        else
        {
            map[19][5] = OPENED_DOOR;
        }

        // Colocando o player e monstro
        map[playerX][playerY] = PLAYER_CHAR;
        map[monsterX][monsterY] = MONSTER2_CHAR;

        print_level(20);

        if (playerX == 12 && playerY == 12)
        {
            button_pressed = 1;
            printf("The Key is now safe to grab!\n");
        }

        map[playerX][playerY] = EMPTY_SPACE;
        map[monsterX][monsterY] = EMPTY_SPACE;
        key_pressed = getch();

        if (playerX == keyX && playerY == keyY && key_pressed == 'i')
        {
            player_has_key = 1;
            map[19][5] = OPENED_DOOR;
        }
        if (playerX == 18 && playerY == 5 && player_has_key == 1 && key_pressed == 's'){
            system("cls");
            screen = 3;
            printf("|The story of Silas does not end here. Come back soon. \n");
            system("pause");
        }
        
        playerMovement(key_pressed, 19);
        gameOver();
        system("cls");

    }

    return 0;
}

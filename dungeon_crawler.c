#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <math.h>
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

// Declarando variáveis globais

char map[40][40];

int player_has_key = 0;
char key_pressed;
int playerX = 1, playerY = 1;
int monsterX, monsterY;
int monster2X, monster2Y;
int doorX, doorY;
int keyX, keyY;
int player_has_key;
int button_pressed;
int screen;
int lives;


// Funções do Jogo
void placeKeyAndDoor()
{
    // Interação do player pra pegar a chave
    if (player_has_key == 0)
    {
        map[doorX][doorY] = CLOSED_DOOR;
        map[keyX][keyY] = KEY_CHAR;
    }
    else
    {
        map[doorX][doorY] = OPENED_DOOR;
        map[keyX][keyY] = EMPTY_SPACE;  
    }
}
void placeMonster(int limit)
{
    int monsterDirection = rand()%4;

    // Colisão com as paredes e objetos

    // Todo: Nao deixar sobrescrever a chave
    if (monsterDirection == 0 && monsterX - 1 > 0)
    {
        monsterX--;
    }
    else if (monsterDirection == 1 && monsterX + 1 < limit)
    {
        monsterX++;
    }
    else if (monsterDirection == 2 && monsterY - 1 > 0)
    {
        monsterY--;
    }
    else if (monsterDirection == 3 && monsterY + 1 < limit)
    {
        monsterY++;
    }
}
void placeMonster2(int limit)
{
    int difX = playerX - monsterX;
    int difY = playerY - monsterY;

    if (abs(difX) > abs(difY) && playerX < monster2X && monster2X - 1 > 0)
    {
        monster2X--;
    }
    else if (abs(difX) > abs(difY) && playerX > monster2X && monster2X + 1 < limit)
    {
        monster2X++;
    }
    else if (abs(difX) < abs(difY) && playerX < monster2X && monster2Y - 1 > 0)
    {
        monster2Y--;
    }
    else if (abs(difX) < abs(difY) && playerX < monster2X && monster2Y + 1 < limit)
    {
        monster2Y++;
    }
}
void playerInteractions(int limit)
{
    if (key_pressed == 'q')
    {
        screen = 0;
        main();
    }
    if (key_pressed == 'w' && playerX - 1 > 0)
    {
        playerX--;
    }
    if (key_pressed == 's' && playerX + 1 < limit)
    {
        playerX++;
    }
    if (key_pressed == 'a' && playerY - 1 > 0 )
    {
        playerY--;
    }
    if (key_pressed == 'd' && playerY + 1 < limit)
    {
        playerY++;  
    }
    if (key_pressed == 'i' && map[playerX][playerY] == map[keyX][keyY])
    {
        player_has_key = 1;
    }
}
void levelWalls(int level_size)
{
    for (int x = 0; x < level_size; x++)
    {
        for (int y = 0; y < level_size; y++)
        {
            // Definindo onde devem ficar as paredes e onde devem ter espaços vazios
            if (x == 0 || x == level_size - 1 || y == 0 || y == level_size - 1)
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
void print_level(int level_size)
{
    // Imprimindo o level
    for (int x = 0; x < level_size; x++)
    {
        for (int y = 0; y < level_size; y++)
        {
            printf("%c", map[x][y]);
        }
        printf("\n");
    }
    map[playerX][playerY] = EMPTY_SPACE;
    map[monsterX][monsterY] = EMPTY_SPACE;
}
void checkColision(int limit) 
{   
    if(map[playerX][playerY] == MONSTER_CHAR)
    {
        // Todo: Consertar sistema de vidas
        if (lives == 0) 
        {
            printf
            (
                "|You can hear Silas howl one last time\n"
                "|He failed to find his friend, and now he's trapped inside, forever\n"
                "|Memento Mori.\n"
            );
            system("cls");
            system("pause");
        }
        else
        {
            playerY = 1;
            playerX = 1; 
            player_has_key = 0;
            lives--;
            monsterX = 5+rand()%(limit - 5);
            monsterY = 5+rand()%(limit - 5);
            system("cls");
            printf("|C'mon Silas, are you even trying?|\n|Lifes left: %d|\n\n", lives);
            system("pause");
            system("cls");
        }
    } 
}
void mainMenu()
{
    while(screen == 0)
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
            system("exit");
        }
        else
        {
            printf("Press a valid key!\n");
            system("pause");
        }
    }
}
int main()
{
    srand(time(NULL));
    mainMenu();

    // Transição entre o menu e a fase 1

    lives = 3;
    monsterX = 4;
    monsterY = 4;
    keyX = 5;
    keyY = 5;
    doorX = 9;
    doorY = 6;
    playerX = 1;
    playerY = 1;

    while (screen == 1)
    {   
        // Alocando objetos dentro do mapa
        levelWalls(10);
        playerInteractions(9);
        placeMonster(9);    
        placeKeyAndDoor();
        map[playerX][playerY] = PLAYER_CHAR;
        map[monsterX][monsterY] = MONSTER_CHAR;
        
        checkColision(9);
        
        printf("POSITION: %d %d\n", playerX, playerY);
        printf("MONSTER: %d %d\n", monsterX, monsterY);
        printf("KEY: %d %d\n", keyX, keyY);
        printf("CHAR IN POSITION: %c\n", map[playerX][playerY]);
        print_level(10);
        if (map[playerX+1][playerY] == OPENED_DOOR)
        {
            printf("Press 'i' to enter the next room");
            if (key_pressed == 'i')
            {
                screen++;
                break;
            }
        }
        key_pressed = getch();

        system("cls");
    }

    // Transição entre a Fase 1 e a Fase 2
    system("cls");
    printf
    (
        "|Silas manages to escape the creature, the door behind him closes, there's no going back now.\n"
        "|He finds more clues about his friend Charlie, he's now closer than ever!\n"
        "|Silas senses a dark presence as he enters the next room.\n"
        "|It's a Fabiliraryanalizerichardugo, a monster that can only be summoned by skilled wizards\n"
        "|This monster follows his target until he gets close enough to absorb all energy\n"
    );

    system("pause");


    player_has_key = 0;
    doorX = 19;
    doorY = 8;
    keyX = 7;
    keyY = 9;
    monster2X = 8;
    monster2Y = 9;

    // Inicio da Fase 2
    while (screen == 2)
    {   
        system("cls");
        levelWalls(20);
        playerInteractions(19);
        placeMonster(19);
        placeMonster2(19);
        placeKeyAndDoor();

        printf("POSITION: %d %d\n", playerX, playerY);
        printf("MONSTER2: %d %d\n");
        printf("KEY: %d %d\n", keyX, keyY);
        printf("CHAR IN POSITION: %c\n", map[playerX][playerY]);

        map[playerX][playerY] = PLAYER_CHAR;
        map[monster2X][monster2Y] = MONSTER2_CHAR;
        checkColision(19);

        // Colocando o botão
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
            map[16-1][10] = EMPTY_SPACE;
            map[16+1][10] = EMPTY_SPACE;
            map[16][10-1] = EMPTY_SPACE;
            map[16][10+1] = EMPTY_SPACE;
        }

        print_level(20);

        if (playerX == 12 && playerY == 12)
        {
            button_pressed = 1;
            printf("The Key is now safe to grab!\n");
        }

        if (playerX == 19 && playerY == 9 && player_has_key == 1 && key_pressed == 's'){
            system("cls");
            screen = 3;
            printf("|The story of Silas does not end here. Come back soon. \n");
            system("pause");
        }
        key_pressed = getch();
        
        system("cls");
    } 

    return 0;
}

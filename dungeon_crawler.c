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
const char PORTAL_CHAR = '>';

// Declarando variáveis globais

char map[40][40];

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
int buttonX, buttonY;

// Funções do Jogo
void placeSpikesAndButton()
{   

    if(button_pressed == 0)
    {
        map[keyX+1][keyY] = SPIKE_CHAR;
        map[keyX-1][keyY] = SPIKE_CHAR;
        map[keyX][keyY+1] = SPIKE_CHAR;
        map[keyX][keyY-1] = SPIKE_CHAR;
    }
    if (playerX == buttonX && playerY == buttonY && button_pressed == 0)
    {
        button_pressed = 1;
        printf("The Key is now safe to grab!\n");
    }

}
void placeKeyAndDoor()
{
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

    // Colisão com as paredes
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
void placeMonster2()
{
    int difX = playerX - monster2X;
    int difY = playerY - monster2Y;

    if (abs(difX) > abs(difY) && playerX < monster2X)
    {
        monster2X--;
    }
    else if (abs(difX) > abs(difY) && playerX > monster2X)
    {
        monster2X++;
    }
    else if (abs(difX) < abs(difY) && playerY < monster2Y)
    {
        monster2Y--;
    }
    else if (abs(difX) < abs(difY) && playerY > monster2Y)
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
    if (key_pressed == 'i' && keyX == playerX && keyY == playerY)
    {
        player_has_key = 1;
    }
    // Todo: Consertar player pegando chave em qualquer canto
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
    if(map[playerX][playerY] == MONSTER2_CHAR || map[playerX][playerY] == MONSTER_CHAR || map[playerX][playerY] == SPIKE_CHAR)
    {
        // Todo: Consertar sistema de vidas
        playerY = 1;
        playerX = 1; 
        player_has_key = 0;
        button_pressed = 0;
        lives--;
        monsterX = 5+rand()%(limit - 5);
        monsterY = 5+rand()%(limit - 5);
        monster2X = 1;
        monster2Y = 1;
        system("cls");
        printf("|C'mon Silas, are you even trying?|\n|Lifes left: %d|\n\n", lives);
        system("pause");
        system("cls");

        if (lives == 0) 
        {
            printf
            (
                "|You can hear Silas howl one last time\n"
                "|He failed to find his friend, and now he's trapped inside, forever\n"
                "|Memento Mori.\n"
            );
            system("pause");
            system("cls");
            screen = 0;
            main();
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
            printf
                (
                "Alright, here are some instructions:\n\n"
                "The game is an adventure where the player must pass 3 levels.\n"
                "In each map, the player must move to collect a key and open a closed door.\n\n"
                "Use the following commands to complete the missions:\n\n"
                "W: Move one unit up\n"
                "A: Move one unit left\n"
                "S: Move one unit down\n"
                "D: Move one unit right\n"
                "I: Interact with the object on top\n"
                "Q: Return to main menu"
                );
            system("pause");
        }
        else if (key_pressed == '3')
        {
            system("cls");
            printf("The howls echo through the forest as you depart. Until the next full moon, brave adventurer.");
            exit(0);
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
    player_has_key = 0;

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
        
        print_level(10);

        if (map[playerX+1][playerY] == OPENED_DOOR)
        {
            printf("Press 'i' to enter the next room\n");
            if (key_pressed == 'i')
            {
                player_has_key = 0;
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

    // Reinicializando variaveis
    playerX = 1;
    playerY = 1;
    button_pressed = 0;
    doorX = 19;
    doorY = 8;
    keyX = 7;
    keyY = 9;
    monsterX = 9;
    monsterY = 15;
    monster2X = 1;
    monster2Y = 1;
    buttonX = 10;
    buttonY = 10;
    player_has_key = 0;
    
    // Inicio da Fase 2
    while (screen == 2)
    {  
        system("cls");
        levelWalls(20);
        playerInteractions(19);
        placeMonster(19);
        placeKeyAndDoor();
        
        // Colocando objetos no mapa
        map[buttonX][buttonY] = BUTTON_CHAR;
        map[playerX][playerY] = PLAYER_CHAR;
        placeSpikesAndButton(10, 10);
        if (button_pressed == 1)
        {
            placeMonster2();
            map[monster2X][monster2Y] = MONSTER2_CHAR;
        }
        map[monsterX][monsterY] = MONSTER_CHAR;
        checkColision(19);

        print_level(20);

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
    // Transição entre a Fase 2 e a Fase 3
    
    system("cls");
    printf
    (
        "|Silas manages enters the final room, finding the great detroyer.\n"
        "|- The destroyer i knew you kidnapped my Friend!\n"
        "|- I will let him free if you help me test my new portals. \n"
        "|I'll give you 505 rupees also. \n"
        "|- Erm... what the sigma? Okay then.\n"
        "|- We can eat cake at Henry's after this is over too. "
    );


    system("pause");

    // Reinicializando variáveis
    playerX = 1;
    playerY = 1;
    button_pressed = 0;
    doorX = 39;
    doorY = 20;
    keyX = 30;
    keyY = 17;
    monsterX = 9;
    monsterY = 15;
    monster2X = 1;
    monster2Y = 1;
    buttonX = 30;
    buttonY = 30;
    player_has_key = 0;

    // Começando a fase 3
    while (screen == 3)
    {
        system("cls");
        levelWalls(40);
        playerInteractions(39);
        placeMonster(39);
        placeKeyAndDoor();
        
        map[buttonX][buttonY] = BUTTON_CHAR;
        map[playerX][playerY] = PLAYER_CHAR;
        placeSpikesAndButton();
        if (button_pressed == 1)
        {
            placeMonster2();
            map[monster2X][monster2Y] = MONSTER2_CHAR;
        }
        map[monsterX][monsterY] = MONSTER_CHAR;
        checkColision(39);

        map[9][27] = PORTAL_CHAR;
        map[30][10] = PORTAL_CHAR;

        if (playerX == 9 && playerY == 27) 
        {
            playerX = 30;
            playerY = 10;
        }
        else if (playerX == 30 && playerY == 10) 
        {
            playerX = 9;
            playerY = 27;
        }


        print_level(40);

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
    system("cls");
    printf
    (
    "|After the rescue, Destroyer, Charlie and Silas go to Henry's house to eat cake\n"
    "|There was no cake. But they had fun. \n"
    "|The end.\n"
    );

    system("pause");
    system("cls");
    printf("Thanks for Playing.\nMade by: 3H & Analice\nSpecial Thanks: Silas\n'Vi Veri Veniversum Vivus Vici'");
    system("pause");
    
    return 0;
}

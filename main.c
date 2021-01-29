/*
   Juego de BattleShip programado en C.

   Autor : Naoki Nakao
   Fecha :
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.c>

/* Directivas de preprocesador */

#define TRUE      1
#define FALSE     0
#define DELAY   500

#define DIMENSION            10
#define MAX_SHIPS             5
#define EMPTY             FALSE
#define PLAYER              219
#define COMPUTER             67
#define PLAYER_SHIP_DOWN     88
#define COMPUTER_SHIP_DOWN   33

#define UP      72
#define DOWN    80
#define RIGHT   77
#define LEFT    75
#define ENTER   13
#define ESC     27

#define SEP        3
#define OCEAN   BLUE

/* Prototipos de función */

void showBattleground(int [][DIMENSION]);

int main()
{
    // matriz 10x10 para representar el juego
    int battleground[DIMENSION][DIMENSION] = {{0}};

    showBattleground(battleground);


    return 0;
}

/*
   Función    : showBattleground
   Argumentos : battleground[][DIMENSION] (matriz que representa el óceano).
   Onjetivo   : mostrar en pantalla el terreno de juego.
   Retrono    : ---
*/
void showBattleground(int battleground[][DIMENSION])
{
   int row, col, pos_x = 15, pos_y = 5;

   for (row = 0; row < DIMENSION; row++)
   {
      for (col = 0; col < DIMENSION; col++)
      {
         textbackground(OCEAN);
         gotoxy(pos_x+col*SEP, pos_y+row);
         printf(" %d ", battleground[row][col]);
      }
   }

   return;
}















































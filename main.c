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

#define SEP                    3
#define CURSOR_COLOR   LIGHTGRAY
#define OCEAN               BLUE

/* Prototipos de función */

void showBattleground(int [][DIMENSION]);
void setColor(int, int);
void defaultColor();

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
         setColor(OCEAN, OCEAN);
         gotoxy(pos_x+col*SEP, pos_y+row);
         printf(" %c ", battleground[row][col]);
      }
   }

   defaultColor();

   return;
}

/*
   Función    : setColor
   Argumentos : int text (color del texto).
                int background (color del fondo).
   Onjetivo   : cambiar el color del texto y del fondo.
   Retrono    : ---
*/
void setColor(int text, int background)
{
   textcolor(text);
   textbackground(background);
   return;
}

/*
   Función    : defaultColor
   Argumentos : ---
   Onjetivo   : restablecer los colores por defecto.
   Retrono    : ---
*/
void defaultColor()
{
   setColor(WHITE, BLACK);
   return;
}















































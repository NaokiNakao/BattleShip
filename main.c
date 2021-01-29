/*
   Juego de BattleShip programado en C.

   Autor : Naoki Nakao
   Fecha :
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.c>
#include <time.h>

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
#define SPACE   32

#define SEP      3

#define CURSOR_COLOR   LIGHTGRAY
#define OCEAN_COLOR         BLUE

/* Prototipos de función */

void cursorMovement(int [][DIMENSION]);
void showBattleground(int [][DIMENSION], int, int);
void setColor(int, int);
void defaultColor();

int main()
{
    gotoxy(21, 1);
    printf("--- Battleship ---");

    // matriz 10x10 para representar el juego
    int battleground[DIMENSION][DIMENSION] = {{0}};

    cursorMovement(battleground);

    return 0;
}

/*
   Función    : cursorMovement
   Argumentos : battleground[][DIMENSION] (matriz que representa el óceano)
   Onjetivo   : controlar la secuencia de juego.
   Retorno    : ---
*/
void cursorMovement(int battleground[][DIMENSION])
{
   char key;
   int pos_x = 0, pos_y = 0;

   _setcursortype(FALSE);

   while (TRUE)
   {
      showBattleground(battleground, pos_y, pos_x);

      // validando teclas presionadas
      do {
         key = getch();
      } while (key != UP && key != RIGHT && key != LEFT &&
               key != DOWN && key != ENTER && key != ESC && key != SPACE);

      // flecha arriba presionada
      if (key == UP)
      {
         pos_y--;
         if (pos_y < 0) pos_y = DIMENSION-1;
      }
      // flecha abajo presionada
      else if (key == DOWN)
      {
         pos_y++;
         if (pos_y == DIMENSION) pos_y = 0;
      }
      // flecha derecha presionada
      else if (key == RIGHT)
      {
         pos_x++;
         if (pos_x == DIMENSION) pos_x = 0;
      }
      // flecha izquierda presionada
      else if (key == LEFT)
      {
         pos_x--;
         if (pos_x < 0) pos_x = DIMENSION-1;
      }
   }
}

/*
   Función    : showBattleground
   Argumentos : int battleground[][DIMENSION] (matriz que representa el óceano)
                int select_row (fila seleccionada).
                int select_col (columna seleccionada).
   Onjetivo   : mostrar en pantalla el terreno de juego.
   Retrono    : ---
*/
void showBattleground(int battleground[][DIMENSION], int select_row, int select_col)
{
   int row, col, pos_x = 15, pos_y = 5;

   for (row = 0; row < DIMENSION; row++)
   {
      for (col = 0; col < DIMENSION; col++)
      {
         // diferenciando la casilla seleccionada del resto
         if (select_row == row && select_col == col)
            setColor(CURSOR_COLOR, CURSOR_COLOR);
         else
            setColor(OCEAN_COLOR, OCEAN_COLOR);

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















































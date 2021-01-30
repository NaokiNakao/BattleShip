/*
   Juego de Battleship programado en C.

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
#define INI_X   21
#define INI_Y    1

#define CURSOR_COLOR   LIGHTGRAY
#define OCEAN_COLOR         BLUE
#define SHIP_COLOR        YELLOW
#define FAILLED_COLOR        RED

/* Prototipos de función */

void cursorMovement(int [][DIMENSION]);
void showBattleground(int [][DIMENSION], int, int);
void setColor(int, int);
void defaultColor();

int main()
{
    _setcursortype(FALSE);

    while (TRUE)
    {
       gotoxy(INI_X, INI_Y);
       printf("--- Battleship ---");
       gotoxy(INI_X-9, INI_Y+2);
       printf("Presione cualquier tecla para iniciar.");
       getch();

       // matriz 10x10 para representar el juego
       int battleground[DIMENSION][DIMENSION] = {{0}};

       cursorMovement(battleground);
    }

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
   int pos_x = 0, pos_y = 0, player_ships = MAX_SHIPS,
       computer_ships = MAX_SHIPS, ready = FALSE;

   do
   {
      showBattleground(battleground, pos_x, pos_y);

      // actualizando en pantalla la cantidad de barcos
         gotoxy(INI_X-13, INI_Y+17);
         printf("Tus barcos : %d | Barcos de la computadora : %d",
                player_ships, computer_ships);

      // validando teclas presionadas
      do {
         key = getch();
      } while (key != UP && key != RIGHT && key != LEFT &&
               key != DOWN && key != ENTER && key != ESC && key != SPACE);

      // flecha arriba presionada
      if (key == UP)
      {
         pos_x--;
         if (pos_x < 0) pos_x = DIMENSION-1;
      }
      // flecha abajo presionada
      else if (key == DOWN)
      {
         pos_x++;
         if (pos_x == DIMENSION) pos_x = 0;
      }
      // flecha derecha presionada
      else if (key == RIGHT)
      {
         pos_y++;
         if (pos_y == DIMENSION) pos_y = 0;
      }
      // flecha izquierda presionada
      else if (key == LEFT)
      {
         pos_y--;
         if (pos_y < 0) pos_y = DIMENSION-1;
      }
      // el jugador presiona la tecla ENTER
      else if (key == ENTER)
      {
         // la variable "ready" indica si el jugador se encuentra preparando
         // los barcos o si ya está jugando contra la computadora
         if (ready)
         {

         }
         else
         {
            // posicionando barcos del jugador
            if (battleground[pos_x][pos_y] == EMPTY)
            {
               battleground[pos_x][pos_y] = PLAYER;
               player_ships--;
            }
            else
            {
               battleground[pos_x][pos_y] = EMPTY;
               player_ships++;
            }
         }
      }
   } while (key != ESC);
}

/*
   Función    : showBattleground
   Argumentos : int battleground[][DIMENSION] (matriz que representa el océano)
                int select_row (fila seleccionada).
                int select_col (columna seleccionada).
   Onjetivo   : mostrar en pantalla el terreno de juego.
   Retrono    : ---
*/
void showBattleground(int battleground[][DIMENSION], int select_row, int select_col)
{
   int row, col, pos_x = INI_X-6, pos_y = INI_Y+4;

   for (row = 0; row < DIMENSION; row++)
   {
      for (col = 0; col < DIMENSION; col++)
      {
         // diferenciando la casilla seleccionada del resto
         if (select_row == row && select_col == col)
            setColor(CURSOR_COLOR, CURSOR_COLOR);

         // diferenciando la casilla con barco del jugador
         else if (battleground[row][col] == PLAYER)
            setColor(SHIP_COLOR, OCEAN_COLOR);

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















































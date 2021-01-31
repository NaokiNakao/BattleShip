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

#define SEP            3
#define INI_X         15
#define INI_Y          1
#define MAX_X         80
#define INSTR_LINE    INI_Y+2
#define SHIP_DEP_X    40
#define SHIP_DEP_Y     7

#define CURSOR_COLOR   LIGHTGRAY
#define OCEAN_COLOR         BLUE
#define SHIP_COLOR        YELLOW
#define FAILLED_COLOR        RED

#define START    1
#define PREP     2
#define READY    3
#define ATTACK   4

/* Prototipos de función */

void game(int [][DIMENSION]);
void showBattleground(int [][DIMENSION], int, int);
void setColor(int, int);
void defaultColor();
void clearLine(int, int);
void instruction(int);
void placeComputerShip(int [][DIMENSION], int);

int main()
{
    _setcursortype(FALSE);

    while (TRUE)
    {
       gotoxy(INI_X, INI_Y);
       printf("--- Battleship ---");
       instruction(START);
       getch();

       // matriz 10x10 para representar el juego
       int battleground[DIMENSION][DIMENSION] = {{0}};

       game(battleground);
    }

    return 0;
}

/*
   Función    : game
   Argumentos : battleground[][DIMENSION] (matriz que representa el óceano)
   Onjetivo   : controlar la secuencia de juego.
   Retorno    : ---
*/
void game(int battleground[][DIMENSION])
{
   char key;
   int pos_x = 0, pos_y = 0, player_ships = MAX_SHIPS,
       computer_ships = MAX_SHIPS, ready = FALSE,
       computer_placing = FALSE, temp;

   clearLine(START, INSTR_LINE);

   do
   {

      // imprimiendo mensaje de instrucción para el jugador
      if (ready)
         instruction(ATTACK);
      else if (player_ships > EMPTY)
         instruction(PREP);
      else if (player_ships == EMPTY)
         instruction(READY);

      showBattleground(battleground, pos_x, pos_y);

      // actualizando en pantalla la cantidad de barcos
      gotoxy(INI_X-13, INI_Y+17);
      printf("Tus barcos : %d | Barcos de la computadora : %d",
             player_ships, computer_ships);

      // validando teclas presionadas
      do {
         if (computer_placing == TRUE) break;
         key = getch();
      } while (key != UP && key != RIGHT && key != LEFT && key != DOWN &&
               key != ENTER && key != ESC && key != SPACE);

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
               if (player_ships > EMPTY)
               {
                  battleground[pos_x][pos_y] = PLAYER;
                  player_ships--;

                  if (player_ships == EMPTY)
                     clearLine(START, INSTR_LINE);
               }
            }
            else
            {
               temp = player_ships;
               battleground[pos_x][pos_y] = EMPTY;
               player_ships++;

               // detectar si el jugador quiere modificar los barcos
               // después de haber colocado todos
               if (temp == EMPTY && player_ships > EMPTY)
                  clearLine(START, INSTR_LINE);
            }
         }
      }
      // el jugador ya ha confirmado el lugar de los 5 barcos
      else if (key == SPACE && player_ships == EMPTY && ready == FALSE)
         computer_placing = TRUE;

      // colocando los barcos de la computadora
      if (computer_placing == TRUE)
      {
         if (computer_ships > EMPTY)
         {
            placeComputerShip(battleground, computer_ships);
            computer_ships--;
         }
         else
         {
            Sleep(DELAY);
            ready = TRUE;
            computer_placing = FALSE;
            clearLine(START, INSTR_LINE);

            // borrando líneas de desplegadas
            for (int count = 0; count <= MAX_SHIPS; count++)
            {
               gotoxy(SHIP_DEP_X, SHIP_DEP_Y+count);
               clearLine(SHIP_DEP_X, SHIP_DEP_Y+count);
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
   Retorno    : ---
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
   Retorno    : ---
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

/*
   Función    : clearLine
   Argumentos : int line (línea a borrar).
   Onjetivo   : borrar línea especificada.
   Retorno    : ---
*/
void clearLine(int x, int y)
{
   gotoxy(x, y);

   for (int i = 1; i <= MAX_X; i++)
      printf(" ");

   return;
}

/*
   Función    : instruction
   Argumentos : command (especifica la instrucción actual).
   Onjetivo   : imprimir en pantalla lo que debe hacer el jugador.
   Retorno    : ---
*/
void instruction(int command)
{
   // comenzar el juego
   if (command == START)
   {
      gotoxy(INI_X-9, INSTR_LINE);
      printf("Presione cualquier tecla para iniciar.");
   }
   // colocar barcos
   else if (command == PREP)
   {
      gotoxy(INI_X, INSTR_LINE);
      printf("Coloque sus barcos.");
   }
   // barcos ya colocados
   else if (command == READY)
   {
      gotoxy(INI_X-9, INSTR_LINE);
      printf("Presione barra espaciadora para iniciar.");
   }
   // indicando ataque
   else if (command == ATTACK)
   {
      gotoxy(INI_X-2, INSTR_LINE);
      printf("Intente hundir un barco.");
   }

   return;
}

/*
   Función    : placeComputerShip
   Argumentos : int battleground[][DIMENSION] (matriz que representa el óceano)
                int count (cantidad de barcos)
   Onjetivo   : colocar los barcos de la computadora.
   Retorno    : ---
*/
void placeComputerShip(int battleground[][DIMENSION], int count)
{
   int row, col;

   gotoxy(SHIP_DEP_X, SHIP_DEP_Y);
   printf("Computadora desplegando barcos:");

   // generando una casilla aleatoria para colocar barco
   do {
      row = rand() % DIMENSION;
      col = rand() % DIMENSION;
   } while (battleground[row][col] != EMPTY);

   battleground[row][col] = COMPUTER;
   Sleep(DELAY);
   gotoxy(SHIP_DEP_X, SHIP_DEP_Y+MAX_SHIPS-count+1);
   printf("Barco %d desplegado...", MAX_SHIPS - count + 1);

   return;
}

















































/*
   Juego de Battleship programado en C.

   Autor : Naoki Nakao
   Fecha :
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.c>
#include <string.h>
#include <time.h>

/* Directivas de preprocesador */

#define TRUE      1
#define FALSE     0
#define DELAY   500

#define DIMENSION            10
#define MAX_SHIPS             5
#define PLAYER_INDEX          1
#define COMPUTER_INDEX        0
#define EMPTY             FALSE
#define PLAYER              219
#define COMPUTER             67
#define PLAYER_SHIP_DOWN     35
#define COMPUTER_SHIP_DOWN   33
#define FAILLED              88
#define COMPUTER_FAIL        70

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
#define RESULT_LINE   INI_Y+14
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
void showBattleground(int [][DIMENSION], int, int, int);
void setColor(int, int);
void defaultColor();
void clearLine(int, int);
void instruction(int);
void placePlayerShip(int [][DIMENSION], int [], int, int);
void placeComputerShip(int [][DIMENSION], int);
void playerGuess(int [][DIMENSION], int [], int, int);
void resultPlayer(int);
void computerGuess(int [][DIMENSION], int []);
void resultComputer(int);
void winner(int []);

int main()
{
   srand(time(NULL));

   while (TRUE)
   {
      _setcursortype(FALSE);
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
   int pos_x = 0, pos_y = 0, ships[] = {MAX_SHIPS, MAX_SHIPS},
       ready = FALSE, computer_placing = FALSE, temp, game_over = FALSE;

   clearLine(START, INSTR_LINE);

   while (TRUE)
   {
      _setcursortype(FALSE);

      // imprimiendo mensaje de instrucción para el jugador
      if (ready)
         instruction(ATTACK);
      else if (ships[PLAYER_INDEX] > EMPTY)
         instruction(PREP);
      else if (ships[PLAYER_INDEX] == EMPTY)
         instruction(READY);

      showBattleground(battleground, pos_x, pos_y, ready);

      // actualizando en pantalla la cantidad de barcos
      gotoxy(INI_X-13, INI_Y+17);
      printf("Tus barcos : %d | Barcos de la computadora : %d",
             ships[PLAYER_INDEX], ships[COMPUTER_INDEX]);

      // terminando el juego si hay ganador
      if (game_over)
      {
         winner(ships);
         break;
      }

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
            // barco hundido, no se puede jugar en esa posición
            if (battleground[pos_x][pos_y] == PLAYER_SHIP_DOWN ||
                battleground[pos_x][pos_y] == COMPUTER_SHIP_DOWN)
            {
               gotoxy(INI_X-4, RESULT_LINE);
               printf("Ya se hundi%c un barco aqu%c", 162, 161);
               continue;
            }
            playerGuess(battleground, ships, pos_x, pos_y);
            if (!ships[COMPUTER_INDEX] || !ships[PLAYER_INDEX])
               game_over = TRUE;

            if (!game_over)
            {
               Sleep(DELAY*3);
               computerGuess(battleground, ships);
               if (!ships[PLAYER_INDEX] || !ships[COMPUTER_INDEX])
                  game_over = TRUE;
            }
         }
         else
            placePlayerShip(battleground, ships, pos_x, pos_y);
      }
      // el jugador ya ha confirmado el lugar de los 5 barcos
      else if (key == SPACE && ships[PLAYER_INDEX] == EMPTY && ready == FALSE)
         computer_placing = TRUE;

      // opción de salir
      else if (key == ESC)
      {
         _setcursortype(30);
         gotoxy(SHIP_DEP_X, SHIP_DEP_Y);
         printf("%cDesea salir? (S)i (N)o : ", 168);

         do {
            key = toupper(getch());
         } while (key != 'S' && key != 'N');

         if (key == 'S')
         {
            clrscr();
            clearLine(START, INI_Y+17);
            break;
         }
         else
         {
            clearLine(SHIP_DEP_X, SHIP_DEP_Y);
            continue;
         }
      }

      // colocando los barcos de la computadora
      if (computer_placing == TRUE)
      {
         if (ships[COMPUTER_INDEX] > EMPTY)
         {
            placeComputerShip(battleground, ships[COMPUTER_INDEX]);
            ships[COMPUTER_INDEX]--;
         }
         else
         {
            Sleep(DELAY);
            ready = TRUE;
            computer_placing = FALSE;
            ships[PLAYER_INDEX] = MAX_SHIPS;
            ships[COMPUTER_INDEX] = MAX_SHIPS;
            clearLine(START, INSTR_LINE);

            // borrando líneas de desplegadas
            for (int count = 0; count <= MAX_SHIPS; count++)
            {
               gotoxy(SHIP_DEP_X, SHIP_DEP_Y+count);
               clearLine(SHIP_DEP_X, SHIP_DEP_Y+count);
            }
         }
      }
   }

   return;
}

/*
   Función    : showBattleground
   Argumentos : int battleground[][DIMENSION] (matriz que representa el océano)
                int select_row (fila seleccionada).
                int select_col (columna seleccionada).
                int flag (indica si se deben esconder el caracter del jugador.
   Onjetivo   : mostrar en pantalla el terreno de juego.
   Retorno    : ---
*/
void showBattleground(int matrix[][DIMENSION],int sel_row,int sel_col,int flag)
{
   int row, col, pos_x = INI_X-6, pos_y = INI_Y+4;

   for (row = 0; row < DIMENSION; row++)
   {
      for (col = 0; col < DIMENSION; col++)
      {
         // diferenciando la casilla seleccionada del resto
         if (sel_row == row && sel_col == col)
            setColor(CURSOR_COLOR, CURSOR_COLOR);

         // diferenciando la casilla con barco del jugador
         //else if (matrix[row][col] == PLAYER && !flag)
         else if (matrix[row][col] == PLAYER)
            setColor(SHIP_COLOR, OCEAN_COLOR);

         else if (matrix[row][col] == COMPUTER)
            setColor(SHIP_COLOR, OCEAN_COLOR);

         else if (matrix[row][col] == PLAYER_SHIP_DOWN)
            setColor(SHIP_COLOR, OCEAN_COLOR);

         else if (matrix[row][col] == COMPUTER_SHIP_DOWN)
            setColor(SHIP_COLOR, OCEAN_COLOR);

         else if (matrix[row][col] == FAILLED)
            setColor(FAILLED_COLOR, OCEAN_COLOR);

         else if (matrix[row][col] == COMPUTER_FAIL)
            setColor(SHIP_COLOR, OCEAN_COLOR);

         else
            setColor(OCEAN_COLOR, OCEAN_COLOR);

         gotoxy(pos_x+col*SEP, pos_y+row);
         printf(" %c ", matrix[row][col]);
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
   Función    : placePlayerShip
   Argumentos : int matrix[][DIMENSION] (matriz que representa el óceano)
                int ships[] (arreglo que contiene la cantidad de barcos)
                int row (fila seleccionada)
                int col (columna seleccionada)
   Onjetivo   : colocar barco del jugador.
   Retorno    : ---
*/
void placePlayerShip(int matrix[][DIMENSION], int ships[], int row, int col)
{
   int temp;

   if (matrix[row][col] == EMPTY)
   {
      if (ships[PLAYER_INDEX] > EMPTY)
      {
         matrix[row][col] = PLAYER;
         ships[PLAYER_INDEX]--;

         if (ships[PLAYER_INDEX] == EMPTY)
            clearLine(START, INSTR_LINE);
      }
   }
   else
   {
      // detectar si el jugador quiere modificar los barcos
      // después de haber colocado todos
      temp = ships[PLAYER_INDEX];
      matrix[row][col] = EMPTY;
      ships[PLAYER_INDEX]++;

      if (temp == EMPTY && ships[PLAYER_INDEX] > EMPTY)
         clearLine(START, INSTR_LINE);
   }

   return;
}

/*
   Función    : placeComputerShip
   Argumentos : int matrix[][DIMENSION] (matriz que representa el óceano)
                int count (cantidad de barcos)
   Onjetivo   : colocar los barcos de la computadora.
   Retorno    : ---
*/
void placeComputerShip(int matrix[][DIMENSION], int count)
{
   int row, col;

   gotoxy(SHIP_DEP_X, SHIP_DEP_Y);
   printf("Computadora desplegando barcos:");

   // generando una casilla aleatoria para colocar barco
   do {
      row = rand() % DIMENSION;
      col = rand() % DIMENSION;
   } while (matrix[row][col] != EMPTY);

   matrix[row][col] = COMPUTER;
   Sleep(DELAY);
   gotoxy(SHIP_DEP_X, SHIP_DEP_Y+MAX_SHIPS-count+1);
   printf("Barco %d desplegado...", MAX_SHIPS - count + 1);

   return;
}

/*
   Función    : playerGuess
   Argumentos : int matrix[][DIMENSION] (matriz que representa el óceano)
                int ships[] (arreglo que contiene la cantidad de barcos)
                int row (fila seleccionada)
                int col (columna seleccionada)
   Onjetivo   : verificar el resultado en intento del jugador.
   Retorno    : ---
*/
void playerGuess(int matrix[][DIMENSION], int ships[], int row, int col)
{
   // el jugador adivinó las coordenadas de un barco de la computadora
   if (matrix[row][col] == COMPUTER)
   {
      resultPlayer(COMPUTER);
      matrix[row][col] = COMPUTER_SHIP_DOWN;
      ships[COMPUTER_INDEX]--;
   }
   // el jugador ingresó las coordanadas de su propio barco
   else if (matrix[row][col] == PLAYER)
   {
      resultPlayer(PLAYER);
      matrix[row][col] = PLAYER_SHIP_DOWN;
      ships[PLAYER_INDEX]--;
   }
   // el jugador no adivina ningún barco
   else if (matrix[row][col] == EMPTY ||
            matrix[row][col] == COMPUTER_FAIL)
   {
      resultPlayer(EMPTY);
      matrix[row][col] = FAILLED;
   }

   return;
}

/*
   Función    : resultPlayer
   Argumentos : int command (indicará el mensaje del resultado de la jugada)
   Onjetivo   : imprimir en pantalla el resultado de la jugada del jugador
   Retorno    : ---
*/
void resultPlayer(int command)
{
   clearLine(START, RESULT_LINE);

   if  (command == COMPUTER)
   {
      gotoxy(INI_X-5, RESULT_LINE);
      printf("%cBoom!%cHas hundido el barco!", 173, 173);
   }
   else if (command == PLAYER)
   {
      gotoxy(INI_X-8, RESULT_LINE);
      printf("Oh no, hundiste tu propio barco :(");
   }
   else if (command == EMPTY)
   {
      gotoxy(INI_X-2, RESULT_LINE);
      printf("%cLo siento, fallaste!", 173);
   }

   return;
}

/*
   Función    : computerGuess
   Argumentos : int matrix[][DIMENSION] (matriz que representa el óceano)
                int ships[] (arreglo que contiene la cantidad de barcos)
   Onjetivo   : hacer jugada de la computadora
   Retorno    : ---
*/
void computerGuess(int matrix[][DIMENSION], int ships[])
{
   int row, col;

   // generando jugada de la computadora en una casilla
   // en la cual no haya jugado
   do {
      row = rand() % DIMENSION;
      col = rand() % DIMENSION;
   } while (matrix[row][col] == COMPUTER_FAIL);

   // la computadora adivina coordenadas de un barco del jugador
   if (matrix[row][col] == PLAYER)
   {
      resultComputer(PLAYER);
      matrix[row][col] = PLAYER_SHIP_DOWN;
      ships[PLAYER_INDEX]--;
   }
   // la computadora adivina coordenadas su propio barco
   else if (matrix[row][col] == COMPUTER)
   {
      resultComputer(COMPUTER);
      matrix[row][col] = COMPUTER_SHIP_DOWN;
      ships[COMPUTER_INDEX]--;
   }
   // la computadora no acertó ningún barco
   else if (matrix[row][col] == EMPTY)
   {
      resultComputer(EMPTY);
      matrix[row][col] = COMPUTER_FAIL;
   }
}

/*
   Función    : resultComputer
   Argumentos : int command (indicará el mensaje del resultado de la jugada)
   Onjetivo   : imprimir en pantalla el resultado de computadora
   Retorno    : ---
*/
void resultComputer(int command)
{
   clearLine(START, RESULT_LINE);

   if (command == PLAYER)
   {
      gotoxy(INI_X-11, RESULT_LINE);
      printf("%cLa computadora hundi%c uno de sus barcos!", 173, 162);
   }
   else if (command == COMPUTER)
   {
      gotoxy(INI_X-13, RESULT_LINE);
      printf("%cLa computadora hundi%c una de sus propias naves!", 173, 162);
   }
   else if (command == EMPTY)
   {
      gotoxy(INI_X-5, RESULT_LINE);
      printf("%cLa computadora ha fallado!", 173);
   }
}

/*
   Función    : winner
   Argumentos : int ships[] (arreglo que contiene la cantidad de barcos)
   Onjetivo   : detectar ganador e indicar en pantalla
   Retorno    : ---
*/
void winner(int ships[])
{
   clearLine(START, INSTR_LINE);

   // si el jugador ganó
   if (!ships[COMPUTER_INDEX])
   {
      gotoxy(INI_X-2, INSTR_LINE);
      printf("%cFelicidades, ganaste!", 173);
   }
   // si la computadora ganó
   if (!ships[PLAYER_INDEX])
   {
      gotoxy(INI_X-7, INSTR_LINE);
      printf("La computadora ha ganado el juego");
   }

   gotoxy(SHIP_DEP_X, SHIP_DEP_Y);
   printf("Presiona cualquier tecla");
   getch();
   clrscr();
   clearLine(START, INI_Y+17);

   return;
}

















































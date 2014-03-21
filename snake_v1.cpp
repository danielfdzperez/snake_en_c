#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h> //Se usa para _fpurge
#include <time.h> //se usa para utilizar random
#include <ncurses.h> 

#define FILAS 20
#define COLUMNAS 20
#define EXIT 27

int movimiento(int respuesta_anterior){
	int respuesta;
	//coge los caracteres introducidos por el usuario
	halfdelay(5);
	respuesta = getch();//coge los caracteres
	if(respuesta != KEY_UP && respuesta != KEY_LEFT && respuesta != KEY_RIGHT && respuesta != KEY_DOWN && respuesta != EXIT)
	    respuesta = respuesta_anterior;
	else
	    respuesta_anterior = respuesta;
	return respuesta;
    }

void movimiento_usuario(int direccion, int pos_usuario[][2], char tablero[][COLUMNAS]){
    switch(direccion){
	case KEY_RIGHT:
	    tablero[pos_usuario[2][0]][pos_usuario[2][1]] = ' ';
	    for(int copiar = 2; copiar>0; copiar--){
		for(int c_pos = 0; c_pos<2; c_pos++)
		    pos_usuario[copiar][c_pos] = pos_usuario[copiar-1][c_pos];
		tablero[pos_usuario[copiar][0]][pos_usuario[copiar][1]] = 'x';
	    }

	    pos_usuario[0][1]++; 
	    tablero[pos_usuario[0][0]][pos_usuario[0][1]] = 'x';

	    break;

	    case KEY_LEFT:
	    tablero[pos_usuario[2][0]][pos_usuario[2][1]] = ' ';
	    for(int copiar = 2; copiar>0; copiar--){
		for(int c_pos = 0; c_pos<2; c_pos++)
		    pos_usuario[copiar][c_pos] = pos_usuario[copiar-1][c_pos];
		tablero[pos_usuario[copiar][0]][pos_usuario[copiar][1]] = 'x';
	    }

	    pos_usuario[0][1]--; 
	    tablero[pos_usuario[0][0]][pos_usuario[0][1]] = 'x';

	    break;

	    case KEY_UP:
	    tablero[pos_usuario[2][0]][pos_usuario[2][1]] = ' ';
	    for(int copiar = 2; copiar>0; copiar--){
		for(int c_pos = 0; c_pos<2; c_pos++)
		    pos_usuario[copiar][c_pos] = pos_usuario[copiar-1][c_pos];
		tablero[pos_usuario[copiar][0]][pos_usuario[copiar][1]] = 'x';
	    }

	    pos_usuario[0][0]--; 
	    tablero[pos_usuario[0][0]][pos_usuario[0][1]] = 'x';

	    break;

	    case KEY_DOWN:
	    tablero[pos_usuario[2][0]][pos_usuario[2][1]] = ' ';
	    for(int copiar = 2; copiar>0; copiar--){
		for(int c_pos = 0; c_pos<2; c_pos++)
		    pos_usuario[copiar][c_pos] = pos_usuario[copiar-1][c_pos];
		tablero[pos_usuario[copiar][0]][pos_usuario[copiar][1]] = 'x';
	    }

	    pos_usuario[0][0]++; 
	    tablero[pos_usuario[0][0]][pos_usuario[0][1]] = 'x';

	    break;
    }

}

void imprimir_tablero(char tablero[][COLUMNAS]){
    clear();
    for(int fila = 0; fila<FILAS; fila++){
	for(int col=0; col<COLUMNAS; col++)
	    printw("%c",tablero[fila][col]);
	printw("\n");
    }
    refresh();
}
int main(int argc, char *argv[]){


    initscr();//comenzar ncurses
    raw();
    keypad(stdscr, TRUE);//permite usar las flechas
    noecho();

    char tablero[FILAS][COLUMNAS];
    int pos_usuario[5][2];
    int direccion;

    pos_usuario[0][0] = 5;//fila
    pos_usuario[0][1] = 3;//columna
    pos_usuario[1][0] = 5;//fila
    pos_usuario[1][1] = 4;//columna
    pos_usuario[2][0] = 5;//fila
    pos_usuario[2][1] = 5;//columna

    //rellenar el tablero
    for(int fila = 0; fila<FILAS; fila++)
	for(int col=0; col<COLUMNAS; col++)
	    if(col == 0 || col == COLUMNAS-1 || fila == 0 || fila == FILAS-1)
		tablero[fila][col] = 'H';
	    else
		tablero[fila][col] = ' ';
    //posiciones de la serpiente
    tablero[pos_usuario[0][0]][pos_usuario[0][1]] = 'x';
    tablero[pos_usuario[1][0]][pos_usuario[1][1]] = 'x';
    tablero[pos_usuario[2][0]][pos_usuario[2][1]] = 'x';

    do{
	direccion = movimiento(direccion);//captura el movimiento del usuario
	movimiento_usuario(direccion, pos_usuario, tablero);//mueve al usuario
	imprimir_tablero(tablero);
    }while(direccion != EXIT);

    getch();
    endwin();
    return EXIT_SUCCESS;
}

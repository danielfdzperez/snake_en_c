#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h> //Se usa para _fpurge
#include <time.h> //se usa para utilizar random
#include <ncurses.h> 

#define FILAS 20
#define COLUMNAS 20
#define EXIT 27
#define CARACTER 'x'

void posicion_inicial(int pos_usuario[][2]){

    pos_usuario[0][0] = 5;//fila
    pos_usuario[0][1] = 3;//columna
    pos_usuario[1][0] = 5;//fila
    pos_usuario[1][1] = 4;//columna
    pos_usuario[2][0] = 5;//fila
    pos_usuario[2][1] = 5;//columna

}

void comida_aleatoria(char tablero[][COLUMNAS]){

    int posicion_aleatoria[2];
    bool posicion_encontrada = false;
    do{
	posicion_aleatoria[1] = random() % COLUMNAS;//columna
	posicion_aleatoria[0] = random() % FILAS;//fila

	if(tablero[posicion_aleatoria[0]][posicion_aleatoria[1]] != 'x' && 
		tablero[posicion_aleatoria[0]][posicion_aleatoria[1]] != 'H'){
	    posicion_encontrada = true;
	    tablero[posicion_aleatoria[0]][posicion_aleatoria[1]] = '#';
	}

    }while(posicion_encontrada != true);

}

void inicializar_tablero(char tablero[][COLUMNAS], int pos_usuario[][2]){
    //rellenar el tablero
    for(int fila = 0; fila<FILAS; fila++)
	for(int col=0; col<COLUMNAS; col++)
	    if(col == 0 || col == COLUMNAS-1 || fila == 0 || fila == FILAS-1)
		tablero[fila][col] = 'H';
	    else
		tablero[fila][col] = ' ';
    //posiciones de la serpiente
    tablero[pos_usuario[0][0]][pos_usuario[0][1]] = CARACTER;
    tablero[pos_usuario[1][0]][pos_usuario[1][1]] = CARACTER;
    tablero[pos_usuario[2][0]][pos_usuario[2][1]] = CARACTER;
    comida_aleatoria(tablero);
}

int movimiento(int respuesta_anterior){
    int respuesta;
    //coge los caracteres introducidos por el usuario
    halfdelay(3);
    respuesta = getch();//coge los caracteres
    if(respuesta != KEY_UP && respuesta != KEY_LEFT && respuesta != KEY_RIGHT && respuesta != KEY_DOWN && respuesta != EXIT)
	respuesta = respuesta_anterior;
    else
	respuesta_anterior = respuesta;
    return respuesta;
}

void movimiento_usuario(int direccion, int pos_usuario[][2], char tablero[][COLUMNAS], bool *comido, int *longitud){
    switch(direccion){
	case KEY_RIGHT:
	    if(tablero[pos_usuario[0][0]][pos_usuario[0][1] + 1] == '#'){
		*comido = true;
		(*longitud)++;
	    }
	    else
		tablero[pos_usuario[*longitud][0]][pos_usuario[*longitud][1]] = ' ';

	    for(int copiar = *longitud; copiar>0; copiar--){
		for(int c_pos = 0; c_pos<2; c_pos++)
		    pos_usuario[copiar][c_pos] = pos_usuario[copiar-1][c_pos];
		tablero[pos_usuario[copiar][0]][pos_usuario[copiar][1]] = CARACTER;
	    }

	    pos_usuario[0][1]++; 
	    tablero[pos_usuario[0][0]][pos_usuario[0][1]] = CARACTER;

	    break;

	case KEY_LEFT:
	    if(tablero[pos_usuario[0][0]][pos_usuario[0][1] - 1] == '#'){
		*comido = true;
		(*longitud)++;
	    }
	    else
		tablero[pos_usuario[*longitud][0]][pos_usuario[*longitud][1]] = ' ';

	    for(int copiar = *longitud; copiar>0; copiar--){
		for(int c_pos = 0; c_pos<2; c_pos++)
		    pos_usuario[copiar][c_pos] = pos_usuario[copiar-1][c_pos];
		tablero[pos_usuario[copiar][0]][pos_usuario[copiar][1]] = CARACTER;
	    }
	    pos_usuario[0][1]--; 
	    tablero[pos_usuario[0][0]][pos_usuario[0][1]] = CARACTER;

	    break;

	case KEY_UP:
	    if(tablero[pos_usuario[0][0] - 1][pos_usuario[0][1]] == '#'){
		*comido = true;
		(*longitud)++;
	    }
	    else
		tablero[pos_usuario[*longitud][0]][pos_usuario[*longitud][1]] = ' ';

	    for(int copiar = *longitud; copiar>0; copiar--){
		for(int c_pos = 0; c_pos<2; c_pos++)
		    pos_usuario[copiar][c_pos] = pos_usuario[copiar-1][c_pos];
		tablero[pos_usuario[copiar][0]][pos_usuario[copiar][1]] = CARACTER;
	    }
	    pos_usuario[0][0]--; 
	    tablero[pos_usuario[0][0]][pos_usuario[0][1]] = CARACTER;

	    break;

	case KEY_DOWN:
	    if(tablero[pos_usuario[0][0] + 1][pos_usuario[0][1]] == '#'){
		*comido = true;
		(*longitud)++;
	    }
	    else
		tablero[pos_usuario[*longitud][0]][pos_usuario[*longitud][1]] = ' ';

	    for(int copiar = *longitud; copiar>0; copiar--){
		for(int c_pos = 0; c_pos<2; c_pos++)
		    pos_usuario[copiar][c_pos] = pos_usuario[copiar-1][c_pos];
		tablero[pos_usuario[copiar][0]][pos_usuario[copiar][1]] = CARACTER;
	    }

	    pos_usuario[0][0]++; 
	    tablero[pos_usuario[0][0]][pos_usuario[0][1]] = CARACTER;

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
    int pos_usuario[100][2],
	longitud = 2;//la longitud de la serpiente.
    int direccion;
    bool comido = false;//determina si se ha comido o no comida
    srand(time(NULL));

    direccion = KEY_RIGHT;
    posicion_inicial(pos_usuario);

    inicializar_tablero(tablero, pos_usuario);

    do{
	if(comido == true){
	    comida_aleatoria(tablero);
	    comido = false;
	}
	direccion = movimiento(direccion);//captura el movimiento del usuario
	movimiento_usuario(direccion, pos_usuario, tablero, &comido, &longitud);//mueve al usuario
	imprimir_tablero(tablero);
    }while(direccion != EXIT);

    getch();
    endwin();
    return EXIT_SUCCESS;
}

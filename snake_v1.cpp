#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h> //Se usa para _fpurge
#include <time.h> //se usa para utilizar random
#include <ncurses.h> 

#define FILAS 20
#define COLUMNAS 20
#define EXIT 27
#define CARACTER 'x'
#define CABEZA '<'

void posicion_inicial(int pos_usuario[][2]){

    pos_usuario[0][0] = 5;//fila
    pos_usuario[0][1] = 5;//columna
    pos_usuario[1][0] = 5;//fila
    pos_usuario[1][1] = 4;//columna
    pos_usuario[2][0] = 5;//fila
    pos_usuario[2][1] = 3;//columna

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
    tablero[pos_usuario[0][0]][pos_usuario[0][1]] = CABEZA;
    tablero[pos_usuario[1][0]][pos_usuario[1][1]] = CARACTER;
    tablero[pos_usuario[2][0]][pos_usuario[2][1]] = CARACTER;
    comida_aleatoria(tablero);
}

int movimiento(int respuesta_anterior, int velocidad){
    int respuesta;
    //coge los caracteres introducidos por el usuario
    halfdelay(velocidad);
    respuesta = getch();//coge los caracteres
    if(respuesta != KEY_UP && respuesta != KEY_LEFT && respuesta != KEY_RIGHT && respuesta != KEY_DOWN && respuesta != EXIT)
	respuesta = respuesta_anterior;
    else
	respuesta_anterior = respuesta;
    return respuesta;
}

void movimiento_usuario(int direccion, int pos_usuario[][2], char tablero[][COLUMNAS], bool *comido, int *longitud, bool *muerto){
    switch(direccion){
	case KEY_RIGHT:
	    if(tablero[pos_usuario[0][0]][pos_usuario[0][1] + 1] == '#'){
		*comido = true;
		(*longitud)++;
	    }
	    else
		if(tablero[pos_usuario[0][0]][pos_usuario[0][1] + 1] == 'H' || 
		   tablero[pos_usuario[0][0]][pos_usuario[0][1] + 1] == CARACTER){
		    *muerto = true;
		    break;
		}
		else
		    tablero[pos_usuario[*longitud][0]][pos_usuario[*longitud][1]] = ' ';

	    for(int copiar = *longitud; copiar>0; copiar--){
		for(int c_pos = 0; c_pos<2; c_pos++)
		    pos_usuario[copiar][c_pos] = pos_usuario[copiar-1][c_pos];
		tablero[pos_usuario[copiar][0]][pos_usuario[copiar][1]] = CARACTER;
	    }

	    pos_usuario[0][1]++; 
	    tablero[pos_usuario[0][0]][pos_usuario[0][1]] = CABEZA;

	    break;

	case KEY_LEFT:
	    if(tablero[pos_usuario[0][0]][pos_usuario[0][1] - 1] == '#'){
		*comido = true;
		(*longitud)++;
	    }
	    else
		if(tablero[pos_usuario[0][0]][pos_usuario[0][1] - 1] == 'H' || 
			tablero[pos_usuario[0][0]][pos_usuario[0][1] - 1] == CARACTER){
		    *muerto = true;
		    break;
		}
		else
		    tablero[pos_usuario[*longitud][0]][pos_usuario[*longitud][1]] = ' ';

	    for(int copiar = *longitud; copiar>0; copiar--){
		for(int c_pos = 0; c_pos<2; c_pos++)
		    pos_usuario[copiar][c_pos] = pos_usuario[copiar-1][c_pos];
		tablero[pos_usuario[copiar][0]][pos_usuario[copiar][1]] = CARACTER;
	    }
	    pos_usuario[0][1]--; 
	    tablero[pos_usuario[0][0]][pos_usuario[0][1]] = CABEZA;

	    break;

	case KEY_UP:
	    if(tablero[pos_usuario[0][0] - 1][pos_usuario[0][1]] == '#'){
		*comido = true;
		(*longitud)++;
	    }
	    else
		if(tablero[pos_usuario[0][0] - 1][pos_usuario[0][1]] == 'H' || 
			tablero[pos_usuario[0][0] - 1][pos_usuario[0][1]] == CARACTER){
		    *muerto = true;
		    break;
		}
		else
		    tablero[pos_usuario[*longitud][0]][pos_usuario[*longitud][1]] = ' ';

	    for(int copiar = *longitud; copiar>0; copiar--){
		for(int c_pos = 0; c_pos<2; c_pos++)
		    pos_usuario[copiar][c_pos] = pos_usuario[copiar-1][c_pos];
		tablero[pos_usuario[copiar][0]][pos_usuario[copiar][1]] = CARACTER;
	    }
	    pos_usuario[0][0]--; 
	    tablero[pos_usuario[0][0]][pos_usuario[0][1]] = CABEZA;

	    break;

	case KEY_DOWN:
	    if(tablero[pos_usuario[0][0] + 1][pos_usuario[0][1]] == '#'){
		*comido = true;
		(*longitud)++;
	    }
	    else
		if(tablero[pos_usuario[0][0] + 1][pos_usuario[0][1]] == 'H' || 
			tablero[pos_usuario[0][0] + 1][pos_usuario[0][1]] == CARACTER){
		    *muerto = true;
		    break;
		}
		else
		    tablero[pos_usuario[*longitud][0]][pos_usuario[*longitud][1]] = ' ';

	    for(int copiar = *longitud; copiar>0; copiar--){
		for(int c_pos = 0; c_pos<2; c_pos++)
		    pos_usuario[copiar][c_pos] = pos_usuario[copiar-1][c_pos];
		tablero[pos_usuario[copiar][0]][pos_usuario[copiar][1]] = CARACTER;
	    }

	    pos_usuario[0][0]++; 
	    tablero[pos_usuario[0][0]][pos_usuario[0][1]] = CABEZA;

	    break;
    }

}
void muro_aleatorio(char tablero[][COLUMNAS]){

    int posicion_aleatoria[2];
    bool posicion_encontrada = false;
    do{
	posicion_aleatoria[1] = random() % COLUMNAS;//columna
	posicion_aleatoria[0] = random() % FILAS;//fila

	if(tablero[posicion_aleatoria[0]][posicion_aleatoria[1]] != CARACTER && 
		tablero[posicion_aleatoria[0]][posicion_aleatoria[1]] != 'H' &&
		tablero[posicion_aleatoria[0]][posicion_aleatoria[1]] != '#' &&
		tablero[posicion_aleatoria[0]][posicion_aleatoria[1]] != CABEZA){

	    posicion_encontrada = true;
	    tablero[posicion_aleatoria[0]][posicion_aleatoria[1]] = 'H';
	}

    }while(posicion_encontrada != true);

}

void imprimir_tablero(char tablero[][COLUMNAS], int nivel){
    clear();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);

    for(int fila = 0; fila<FILAS; fila++){
	for(int col=0; col<COLUMNAS; col++)
	    if(tablero[fila][col] != CARACTER && tablero[fila][col] != CABEZA && tablero[fila][col]!= '#'){
		attron(COLOR_PAIR(3));
		printw("%c",tablero[fila][col]);
		attroff(COLOR_PAIR(3));
	    }

	    else
		if(tablero[fila][col] == CARACTER){
		    attron(COLOR_PAIR(1));
		    printw("%c",tablero[fila][col]);
		    attroff(COLOR_PAIR(1));
		}
		else
		    if(tablero[fila][col] == CABEZA){
			attron(COLOR_PAIR(2));
			printw("%c",tablero[fila][col]);
			attroff(COLOR_PAIR(2));
		    }
		    else{
			attron(COLOR_PAIR(4));
			printw("%c",tablero[fila][col]);
			attroff(COLOR_PAIR(4));
		    }


	printw("\n");
    }
    printw("\tNivel: %i\n", nivel);
    refresh();
}
int main(int argc, char *argv[]){


    initscr();//comenzar ncurses
    raw();
    keypad(stdscr, TRUE);//permite usar las flechas
    noecho();

    char opcion;
    char tablero[FILAS][COLUMNAS];
    int pos_usuario[100][2],
	longitud;//la longitud de la serpiente.
    int direccion,
	velocidad,
	siguiente_nivel,
	nivel;
    bool comido,//determina si se ha comido o no comida
	 muerto;//determina si esta muerto o vivo.
    srand(time(NULL));

    do{
	direccion = KEY_RIGHT;
	posicion_inicial(pos_usuario);

	inicializar_tablero(tablero, pos_usuario);
        
	nivel = 1;
	longitud = 2;
	comido = false;
	muerto = false;
	velocidad = 3;
	siguiente_nivel = 0;
	do{
	    imprimir_tablero(tablero, nivel);

	    if(comido == true){
		comida_aleatoria(tablero);
		comido = false;
		siguiente_nivel ++;

		if(nivel > 9)
		    for(int veces_pinta=0; veces_pinta<nivel/10; veces_pinta++)
			muro_aleatorio(tablero);

		if(siguiente_nivel == 5){
		    nivel ++;

		    if(velocidad > 0)
			velocidad--;
		    if(nivel > 4)
			muro_aleatorio(tablero);
		    siguiente_nivel = 0;
		}
	    }
	    direccion = movimiento(direccion, velocidad);//captura el movimiento del usuario
	    movimiento_usuario(direccion, pos_usuario, tablero, &comido, &longitud, &muerto);//mueve al usuario
	    //imprimir_tablero(tablero);
	}while(direccion != EXIT && muerto != true);
	printw("\tGAME OVER\n"
		"\t¿Jugar de nuevo? s/n");
	refresh();
	__fpurge(stderr);
	opcion = getch();
    }while(opcion != 'n');
    endwin();
    return EXIT_SUCCESS;
}

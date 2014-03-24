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

enum TipoOpcion { normal, extremo, puntuaciones, salir};

//muestra el menu
enum TipoOpcion menu(){

    clear();
    int opcion;
    
    printw("\t\tSNAKE\n"
	    "\t1-Partida normal\n"
	    "\t2-Parida extrema\n"
	    "\t3-Puntuaciones\n"
	    "\t4-salir\n"
	    "Tu opcion: ");
    refresh();
    opcion = getch() - '1';
    __fpurge(stdin);

    return (enum TipoOpcion) opcion;

}
//establece la posicion inicial de la serpiente
void posicion_inicial(int pos_usuario[][2]){

    pos_usuario[0][0] = 5;//fila
    pos_usuario[0][1] = 5;//columna
    pos_usuario[1][0] = 5;//fila
    pos_usuario[1][1] = 4;//columna
    pos_usuario[2][0] = 5;//fila
    pos_usuario[2][1] = 3;//columna

}
//genera una posicion aleatoria para la comida
void comida_aleatoria(char tablero[][COLUMNAS]){
    //comprueba que no hay nada en la posicion donde se creara la comida y si no hay nada la genera
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
//inicializa la matriz del tablero
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
//captura el movimiento del usuario
int movimiento(int respuesta_anterior, int velocidad){
    int respuesta;
    //coge los caracteres introducidos por el usuario
    halfdelay(velocidad);//si no introduce nada el usuario en x tiempo se introduce solo
    respuesta = getch();//coge los caracteres
    //compara que la respuesta es correcta
    if(respuesta != KEY_UP && respuesta != KEY_LEFT && respuesta != KEY_RIGHT && respuesta != KEY_DOWN && respuesta != EXIT)
	//si lo es la respuesta sera la misma que la anterior
	respuesta = respuesta_anterior;
    else
	//sino la respuesta anterior sera la respuesta
	respuesta_anterior = respuesta;
    return respuesta;
}
//mueve la serpiente por la matriz
void movimiento_usuario(int direccion, int pos_usuario[][2], char tablero[][COLUMNAS], bool *comido, int *longitud, bool *muerto){
    //escoge el movimiento en funcion de la respuesta del usuario
    switch(direccion){
	case KEY_RIGHT:
	    //si el siguiente movimiento es comida
	    if(tablero[pos_usuario[0][0]][pos_usuario[0][1] + 1] == '#'){
		*comido = true;//se indica que se comio la comida
		(*longitud)++;//se alarga la serpiente
	    }
	    else
		//se comprueba si el siguiente movimiento es la propia serpiente o el muro
		if(tablero[pos_usuario[0][0]][pos_usuario[0][1] + 1] == 'H' || 
		   tablero[pos_usuario[0][0]][pos_usuario[0][1] + 1] == CARACTER){
		    *muerto = true;//se indica que la serpiente ha muerto
		    break;//se rompe el bucle
		}
		else
		    //se borra el ultimo caracter de la serpiente
		    tablero[pos_usuario[*longitud][0]][pos_usuario[*longitud][1]] = ' ';

	    //copia la posicion desde la ultima posicion de la serpiete hasta la 2.
	    for(int copiar = *longitud; copiar>0; copiar--){
		for(int c_pos = 0; c_pos<2; c_pos++)
		    pos_usuario[copiar][c_pos] = pos_usuario[copiar-1][c_pos];
		tablero[pos_usuario[copiar][0]][pos_usuario[copiar][1]] = CARACTER;
	    }
            
	    pos_usuario[0][1]++;//actualiza la posicion de la cabeza 
	    tablero[pos_usuario[0][0]][pos_usuario[0][1]] = CABEZA;//asigna al tablero la posicion de la cabeza

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
//genera posicion aleatoria para el muro
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
//imprime el tablero por pantalla
void imprimir_tablero(char tablero[][COLUMNAS], int nivel){
    clear();
    
    init_pair(1, COLOR_GREEN, COLOR_BLACK);//asigna el color que se le dara
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);

    for(int fila = 0; fila<FILAS; fila++){
	for(int col=0; col<COLUMNAS; col++)
	    //se le pone color al muro
	    if(tablero[fila][col] != CARACTER && tablero[fila][col] != CABEZA && tablero[fila][col]!= '#'){
		attron(COLOR_PAIR(3));//asigna el color
		printw("%c",tablero[fila][col]);
		attroff(COLOR_PAIR(3));//fin asignacion del color
	    }

	    else
		//se le pone color al cuerpo de la serpiente
		if(tablero[fila][col] == CARACTER){
		    attron(COLOR_PAIR(1));
		    printw("%c",tablero[fila][col]);
		    attroff(COLOR_PAIR(1));
		}
		else
		    //se le pone color a la cabeza
		    if(tablero[fila][col] == CABEZA){
			attron(COLOR_PAIR(2));
			printw("%c",tablero[fila][col]);
			attroff(COLOR_PAIR(2));
		    }
		    else{
			//se le pone color a la comida
			attron(COLOR_PAIR(4));
			printw("%c",tablero[fila][col]);
			attroff(COLOR_PAIR(4));
		    }


	printw("\n");
    }
    printw("\tNivel: %i\n", nivel);//imprime el nivel por el que va el usuario
    refresh();
}
//muestra las mejores puntuaciones
void mostrar_puntuaciones(){
    clear();
    printw("No disponible actualmente\n");
    refresh();
    getch();

}
//el bucle y todas las variables de la partida
void partida(int nivel_minimo, int dividir, int velocidad_minima){
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
    do{
	direccion = KEY_RIGHT;
	posicion_inicial(pos_usuario);

	inicializar_tablero(tablero, pos_usuario);

	nivel = 1;
	longitud = 2;
	comido = false;
	muerto = false;
	velocidad = velocidad_minima;
	siguiente_nivel = 0;
	do{
	    imprimir_tablero(tablero, nivel);

	    if(comido == true){
		comida_aleatoria(tablero);
		comido = false;
		siguiente_nivel ++;

		if(nivel > nivel_minimo)
		    for(int veces_pinta=0; veces_pinta<nivel/dividir; veces_pinta++)
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
	}while(direccion != EXIT && muerto != true);

	printw("\tGAME OVER\n"
		"\t¿Jugar de nuevo? s/n");
	refresh();

	__fpurge(stdin);
	opcion = getchar();
	__fpurge(stdin);
    }while(opcion != 'n');
}

int main(int argc, char *argv[]){


    initscr();//comenzar ncurses
    raw();
    keypad(stdscr, TRUE);//permite usar las flechas
    noecho();
    start_color();//inicia que se permita imprimir color
    srand(time(NULL));

    //opciones para determinar si la partida es en extremo o normal
    int dividir,
	nivel_minimo,
	velocidad_minima;

    enum TipoOpcion opcion;
    do{
	switch(opcion = menu()){
	    case normal:
		dividir = 10;
		nivel_minimo = 9;
		velocidad_minima = 3;
		partida(nivel_minimo, dividir, velocidad_minima);
		break;
	    case extremo:
		dividir = 1;
		nivel_minimo = 1;
		velocidad_minima = 1;
		partida(nivel_minimo, dividir, velocidad_minima);
		break;
	    case puntuaciones:
		mostrar_puntuaciones();
		break;
	}
    }while(opcion != salir);

    endwin();//fin ncurses
    return EXIT_SUCCESS;
}

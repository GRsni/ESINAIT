#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "estructura.h"
#include "entrada&salida.h"
#include "partida.h"
#include "menu_principal.h"

/** \brief Inicializa las variables de control de programa y carga la informacion de ficheros
 *
 * \return No devuelve nada
 *
 */

void inicializa_variables() {
    srand(time(0));
    total_jugadores=0;
    num_jugadores_activos=0;
    total_objetos=0;
    cargar_estructuras();
}

int main() {
    int salir=0;
    inicializa_variables();
//    entrar();
    guardar_partida();
//    do {
//        while(partida_en_progreso==0) {
//            iniciar_sesion();
//        }
//        game_loop();
//        finalizar_partida();
//    } while(salir==0);
    return 0;
}





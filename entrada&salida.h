#ifndef ENTRADA_SALIDA
#define ENTRADA_SALIDA
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "estructura.h"

int contar_linea_fichero(char *);
void cargar_struct_objetos();
void cargar_struct_mochila(jugador *);
void copiar_objeto(objeto*, objeto*);
void cargar_struct_jugadores();
void cargar_struct_tormenta();
void cargar_struct_posiciones();
void cargar_struct_juego();
void cargar_estructuras();

void mostrar();

void guardar_posiciones();
void guardar_objetos();
void guardar_configuracion();
void guardar_usuarios();
void guardar_tormenta();
void guardar_mochila();
void guardar_partida();

#endif // ENTRADA_SALIDA


#ifndef PARTIDA
#define PARTIDA

#include "estructura.h"

void game_loop();

void randomizar_posiciones();

void menu_partida(jugador *, int *);
int ver_mochila(jugador *);
char* actualizar_objeto_seleccionado(jugador *);
void usar_objeto();
void mover_jugador(jugador *, int*);
void objetos_cercanos(jugador *);
void oponentes_cercanos(jugador *, int v[]);
void ver_posicion_actual(jugador *);
void ver_tormenta();
void actualizar_tormenta();

int* establecer_orden();
int* reune_indices_jugadores();

void eliminar_objeto_mochila(jugador *);
void eliminar_jugador(jugador *);

void usar_objeto(jugador *,int indices []);

int jugadores_restantes(int *);
void actualizar_ganador(jugador *);
int finalizar_turno(int *);
void finalizar_partida();


#endif // PARTIDA


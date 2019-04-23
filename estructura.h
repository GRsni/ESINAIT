#ifndef ESTRUCTURA_H_INCLUDED
#define ESTRUCTURA_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Objeto {
    char identificadorobjeto[10];
    char descripcion[20];
    char tipo[20];
    int coste;
    float alcance;
    int dano;
    int cantidad;
} objeto;


typedef struct Jugador{
    char sobrenombre[50];
    char nombre[50];
    int nivel;
    int vida;
    int escudo;
    char estado[4];//0:offline, 1:Online, 2:Bloqueado, 3:En juego, 4:En espera, 5:Eliminado
    int cartera;
    int np;
    int ng;
    short int admin; //1=ADMIN, 0=NO ADMIN
    char contrasena[50];
    int num_objetos;
    int obj_seleccionado;
    objeto *mochila;
    float x, y;
} jugador;


typedef struct Tormenta{
    float x, y, diametro;
    int tiempo;
} fase_tormenta;


typedef struct Posiciones_mapa{
    char nombre_elemento[50], tipo[20];
    float x, y;
}posicion_mapa;


typedef struct Juego {
    float radio;
    float alcance_recoger;
    float rango_arma_base;
    int cartera_defecto;
    int jugadores_min;
    float tamano_paso;
    int tamano_mochila;
    int numero_partidas_por_nivel;
    int numero_acciones_por_turno;
    int numero_fases;
    int numero_posiciones;
    int turnos_de_partida;
    fase_tormenta *tormentas;
    int fase_actual;
    posicion_mapa *posiciones;
    int objetos_en_mapa;
} juego;

juego *objeto_juego;

jugador *jugadores;
int total_jugadores;
int num_jugadores_activos;
int num_jug_muertos;

int partida_en_progreso;

objeto *objetos;
int total_objetos;






#endif // ESTRUCTURA_H_INCLUDED

#include <math.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265

/** \brief Animacion de barra de carga de partida
 *
 * \return No devuelve nada
 *
 */

void barra_de_carga() {
    int counter=0, bloques=0, i;

    while(bloques<20) {
        if(counter==INT_MAX/100) {
            system("cls");
            printf("Cargando partida\n[");
            for(i=0; i<19; i++) {
                printf("%c", i<bloques?'#':' ');
            }
            puts("]");
            bloques++;
            counter=0;
        }
        counter++;

    }
    puts("PARTIDA CARGADA");
    system("pause");
    system("cls");

}

/** \brief Funcion de angulo aleatorio
 *
 * \return Devuelve un valor entre 0 y PI * 2
 *
 */

float angulo_aleatorio() {
    return (rand()%6283)/1000.0;
}

/** \brief Funcion de radio aleatorio
 *
 * \param r Entero limite superior
 * \return Devuelve un valor entre 0 y r
 *
 */

int radio_aleatorio(int r) {
    return rand()%( r);
}

/** \brief Calcula la distancia euclidea entre dos pares de coordenadas
 *
 * \param orX Real origen X
 * \param orY Real origen Y
 * \param destX Real destino X
 * \param destY Real destino Y
 * \return Devuelve la distancia entre los dos puntos
 *
 */

float distancia(float orX, float orY, float destX, float destY) {
    float a=pow(destX-orX, 2), b=pow(destY-orY, 2);
    return sqrt(a+b);
}

/** \brief Compara la cadena selec con op1 y op2
 *
 * \param *selec Cadena de caracteres a comprobar
 * \param *op1 Cadena opcion 1
 * \param *op2 Cadena opcion 2
 * \return Devuelve 1 si selec es o op1 o op2, 0 en caso contrario
 *
 */

int compara_palabra(char* selec, char* op1, char* op2){
    int out=0;
    if(strcmp(selec, op1)==0||strcmp(selec, op2)==0){
        out=1;
    }
    return out;
}

/** \brief Elimina el salto de linea de una cadena
 *
 * \param *c1 Puntero a cadena a modificar
 * \return No devuelve nada, modifica por referencia
 *
 */

void correcionM(char *c1) {
    int i,longc;
    longc=strlen(c1);
    for(i=0; i<longc; i++) {
        if(c1[i]=='\n')
            c1[i]='\0';
    }
}

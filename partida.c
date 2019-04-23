#include <limits.h>
#include <math.h>
#include "partida.h"
#include "estructura.h"
#include "entrada&salida.h"
#include "menu_principal.h"
#include "utilidad.h"


/** \brief Funcion de partida, contiene el bucle del juego
 *
 * \return No devuelve nada
 *
 */

void game_loop() {
    int i=0;
    partida_en_progreso=1;
    num_jug_muertos=0;
    objeto_juego->turnos_de_partida=0;
    int *orden_jugadores=establecer_orden();
    randomizar_posiciones(orden_jugadores);
//    barra_de_carga();
    while(partida_en_progreso==1) {
        for(i=0; i<num_jugadores_activos; i++) {
            if(strcmp(jugadores[orden_jugadores[i]].estado, "GO")!=0) {

                menu_partida(&jugadores[orden_jugadores[i]], orden_jugadores);
                partida_en_progreso=jugadores_restantes(orden_jugadores);
            }
            if(partida_en_progreso==0) {
                break;
            }
        }
        if(partida_en_progreso==1) {
            partida_en_progreso=finalizar_turno(orden_jugadores);
        }
    }
    printf("Volviendo al menu principal.\n");
}



//################################################
//  FUNCIONES DE MENU DE PARTIDA
//################################################

/** \brief Menu de partida para los jugadores
 *
 * \param *jug Puntero a jugador
 * \param *indices Vector de indices de jugadores activos
 * \return No devuelve nada
 *
 */

void menu_partida(jugador *jug, int *indices) {
    int selector, acciones=objeto_juego->numero_acciones_por_turno, cambio;
    char *nom_objeto_en_mano=actualizar_objeto_seleccionado(jug);

    while(acciones>0&&strcmp(jug->estado, "GO")!=0) {
        nom_objeto_en_mano=actualizar_objeto_seleccionado(jug);
        system("cls");
        do {
            fflush(stdin);
            printf("Turno de %s\n", jug->sobrenombre);
            printf("[Vida]: %d\n[Escudo]: %d\n\n\n", jug->vida, jug->escudo);
            printf("Acciones restantes: %d\n\n\n", acciones);
            printf("1-Ver mochila\n");
            printf("2-Usar objeto en mano [%s]\n", nom_objeto_en_mano);
            printf("3-Mover jugador\n");
            printf("4-Ver objetos cercanos\n");
            printf("5-Ver oponentes cercanos\n");
            printf("6-Ver posicion actual\n");
            printf("7-Ver posicion de la tormenta\n");
            printf("8-Finalizar turno\n");
            printf("9-Volver al menu principal\n");
            printf("Elige la opcion: ");
            scanf("%d", &selector);
        } while(selector<1||selector>10);
        puts("");
        switch(selector) {
        case 1:
            cambio=ver_mochila(jug);
            if(cambio==1) {
                acciones--;
            }

            break;
        case 2:
            usar_objeto(jug, indices);
            break;
        case 3:
            mover_jugador(jug, indices);
            acciones--;
            break;
        case 4:
            objetos_cercanos(jug);
            break;
        case 5:
            oponentes_cercanos(jug, indices);
            break;
        case 6:
            ver_posicion_actual(jug);
            break;
        case 7:
            ver_tormenta();
            break;
        case 8:
            acciones=0;
            printf("Has acabado tu turno.\n");
            break;
        case 9:
            menu_usuarios(jug);
            break;
        case 10:
            guardar_posiciones();
        }
        system("pause");
        system("cls");
    }
}


/** \brief Muestra la mochila del jugador
 *
 * \param *jug Puntero a jugador
 * \return Devuelve 1 si se ha cambiado el objeto en mano, 0 si no
 *
 */

int ver_mochila(jugador *jug) {
    int i, selector, out=0;
    char palabra[10];
    printf("[MOCHILA DE %s]\n", jug->sobrenombre);
    if(jug->num_objetos>0) {
        printf("Tienes %d objetos: \n\n", jug->num_objetos);
        for(i=0; i<jug->num_objetos; i++) {
            printf("ITEM [%d]\n", i+1);
            printf("%s: %s\nTIPO: %s\n", jug->mochila[i].descripcion, jug->mochila[i].identificadorobjeto, jug->mochila[i].tipo);
            if(strcmp(jug->mochila[i].tipo, "arma")==0) {
                printf("MUNICION: %d\n\n", jug->mochila[i].cantidad);
            } else {
                printf("CANTIDAD: %d\n\n", jug->mochila[i].cantidad);
            }
        }
        do {
            printf("Quieres escoger un objeto?[si/no]: ");
            scanf("%s", palabra);
        } while(compara_palabra(palabra, "si", "no")==0);
        if(strcmp(palabra, "si")==0) {
            do {
                printf("Escribe el numero para seleccionar un objeto: ");
                scanf("%d", &selector);
                fflush(stdin);
            } while(selector<1||selector>jug->num_objetos);
            jug->obj_seleccionado=selector-1;
            printf("Has cogido el objeto %s\n\n", jug->mochila[jug->obj_seleccionado].identificadorobjeto);
            out=1;
        } else {
            printf("No has cambiado tu objeto en mano\n");
        }
    } else {
        printf("No tienes objetos en la mochila.\n");

    }
    return out;
}


/** \brief Muestra por pantalla la posicion actual del jugador
 *
 * \param *jug Puntero a jugador
 * \return No devuelve nada
 *
 */

void ver_posicion_actual(jugador * jug) {
    printf("Tu posicion actual es:\nX: %f, Y: %f\n\n", jug->x, jug->y);
}

/** \brief Funcion para moverse por el mapa de juego
 *
 * \param *jug Puntero a jugador
 * \param *indices Vector de indices de jugadores activos
 * \return No devuelve nada
 *
 */

void mover_jugador(jugador *jug, int *indices) {
    int mover, valida=0;
    char selector[4];
    float base_x=jug->x, base_y=jug->y, paso=objeto_juego->tamano_paso, nuevo_x=base_x, nuevo_y=base_y;
    fase_tormenta tAux=objeto_juego->tormentas[objeto_juego->fase_actual];

    do {
        printf("Tu posicion es: (%.2f,%.2f)\n", jug->x, jug->y);
        puts("Selecciona una posicion para moverse:");
        printf("Pulsa 1 para desplazarte hacia el norte:(%.2f, %.2f)\n", base_x, base_y+paso);
        printf("Pulsa 2 para desplazarte hacia la oeste:(%.2f, %.2f)\n", base_x-paso, base_y);
        printf("Pulsa 3 para desplazarte hacia la este:(%.2f, %.2f)\n", base_x+paso, base_y);
        printf("Pulsa 4 para desplazarte hacia sur:(%.2f, %.2f)\n", base_x, base_y-paso);
        printf("Pulsa 5 para desplazarte hacia noreste:(%.2f, %.2f)\n", base_x+.707*paso, base_y+.707*paso);
        printf("Pulsa 6 para desplazarte hacia noroeste:(%.2f, %.2f)\n", base_x-.707*paso, base_y+.707*paso);
        printf("Pulsa 7 para desplazarte hacia sureste:(%.2f, %.2f)\n", base_x-.707*paso, base_y+.707*paso);
        printf("Pulsa 8 para desplazarte hacia suroeste:(%.2f, %.2f)\n", base_x-.707*paso, base_y-.707*paso);
        printf("Eleccion: ");
        scanf("%d",&mover);
        switch(mover) {
        case 1:
            nuevo_y+=paso;
            break;

        case 2:
            nuevo_x-=paso;
            break;

        case 3:
            nuevo_x+=paso;
            break;

        case 4:
            nuevo_y-=paso;
            break;

        case 5:
            nuevo_x+=.707*paso;
            nuevo_y+=.707*paso;
            break;

        case 6:
            nuevo_x-=.707*paso;
            nuevo_y+=.707*paso;
            break;

        case 7:
            nuevo_x+=.707*paso;
            nuevo_y-=.707*paso;
            break;

        case 8:
            nuevo_x-=.707*paso;
            nuevo_y-=.707*paso;
            break;
        }

        if(distancia(nuevo_x, nuevo_y, tAux.x, tAux.y)>tAux.diametro/2) {
            printf("CUIDADO: EN ESTA POSICION ESTAS FUERA DEL OJO DE LA TORMENTA\n\n");
            puts("Quieres moverte a otro sitio?");
            scanf("%s", selector);
            if(compara_palabra(selector, "si", "no")==1) {
                if(strcmp(selector, "no")==0) {
                    puts("Has sido eliminado");
                    eliminar_jugador(jug);
                    valida=1;
                }
            }
        } else {
            valida=1;
        }
    } while(valida==0);

    jug->x=nuevo_x;
    jug->y=nuevo_y;
}

/** \brief Muestra los objetos en alcance del jugador, y permite cogerlos
 *
 * \param *jug Puntero a jugador
 * \return No devuelve nada
 *
 */

void objetos_cercanos(jugador *jug) {
    int i=0;
    int existir=0;
    char objeto_selec[20];
    int decision=0;
    int indice_objeto_mochila=0;
    posicion_mapa *p_aux;
    objeto objeto_aux;


    for(i=0; i<objeto_juego->numero_posiciones; i++) {//imprimir los objetos en el mapa al alcance del jugador
        p_aux=&objeto_juego->posiciones[i];
        if(strcmp(p_aux->tipo, "Objeto")==0) {
            if((distancia(jug->x, jug->y, p_aux->x, p_aux->y))<objeto_juego->alcance_recoger) {
                printf("-El objeto %s esta a tu alcance.\n\n",p_aux->nombre_elemento);
                existir=1;
            }
        }
    }
    if(existir==0) {
        puts("No hay ningun objeto a su alcance.");
    } else {
        puts("Desea recoger un objeto?");
        printf("Escribe el nombre del objeto que quieres recoger o NO para salir: ");
        scanf("%s", objeto_selec);
        correcionM(objeto_selec);
        if(strcmp(objeto_selec, "NO")!=0) {
            for(i=0; i<objeto_juego->numero_posiciones; i++) { //busca la posicion_mapa elegida
                if(strcmp(objeto_selec, objeto_juego->posiciones[i].nombre_elemento)==0&&
                        distancia(jug->x, jug->y, objeto_juego->posiciones[i].x, objeto_juego->posiciones[i].y)<objeto_juego->alcance_recoger) {
                    p_aux=&objeto_juego->posiciones[i];
                }
            }
            for(i=0; i<total_objetos; i++) {//carga en objeto_aux el objeto correspondiente de la lista completa
                if(strcmp(objeto_selec, objetos[i].identificadorobjeto)==0) {
                    objeto_aux=objetos[i];
                    if(strcmp(objeto_aux.tipo, "arma")==0) {
                        objeto_aux.cantidad=10;
                    } else {
                        objeto_aux.cantidad=1;
                    }
                }
            }
            for(i=0; i<jug->num_objetos; i++) { //comprueba si el jugador tiene ese mismo objeto en la mochila
                if(strcmp(objeto_aux.identificadorobjeto, jug->mochila[i].identificadorobjeto)==0) {
                    jug->mochila[i].cantidad+=objeto_aux.cantidad;//combina el inventario y sale de la funcion
                    return;
                }
            }
            //si no es un objeto de la mochila
            if(jug->num_objetos==objeto_juego->tamano_mochila) {//comprueba si la mochila esta llena
                puts("Su mochila esta llena.");
                puts("¿Desea reemplazar algun objeto?");
                puts("Pulse 1 para SI, pulse 0 para NO : ");
                scanf("%d", &decision);
                if(decision==1) {//muestra los objetos de la mochila
                    puts("Sus objetos actuales son estos: \n\n");
                    for(i=0; i<jugadores->num_objetos; i++) {
                        printf("[%d]%s x%d \n\n",i+1, jug->mochila[i].identificadorobjeto, jug->mochila[i].cantidad);
                    }
                    printf("Que objeto desea soltar en el mapa[1-%d]: ", jug->num_objetos);
                    scanf("%d", &indice_objeto_mochila);
                    indice_objeto_mochila--;

                    strcpy(p_aux->nombre_elemento, jug->mochila[indice_objeto_mochila].identificadorobjeto);
                    copiar_objeto(&objeto_aux, &jug->mochila[indice_objeto_mochila]);
                } else {
                    puts("No ha intercambiado ningun objeto");
                    return;
                }
            } else {
                copiar_objeto(&objeto_aux, &jug->mochila[jug->num_objetos]);
                jug->num_objetos++;
                p_aux->x=30000;
                p_aux->y=30000;
            }
            printf("Has cogido el objeto %s\n", objeto_aux.identificadorobjeto);
        }
    }

}


/** \brief Muestra los oponentes en rango del jugador
 *
 * \param *jug Puntero a jugador
 * \param indices[] Vector de indices de jugadores activos
 * \return No devuelve nada
 *
 */

void oponentes_cercanos(jugador *jug, int indices[]) {
    int i=0;
    int existe=0;
    float rango_arma=0;
    if(jug->obj_seleccionado==-1) {
        rango_arma=objeto_juego->rango_arma_base;
    } else {
        rango_arma=jug->mochila[jug->obj_seleccionado].alcance;
    }
    for(i=0; i<num_jugadores_activos; i++) {
        if(strcmp(jug->sobrenombre, jugadores[indices[i]].sobrenombre)!=0) {//no comprobar jugador consigo mismo
            float dist=distancia(jug->x,jug->y,jugadores[indices[i]].x,jugadores[indices[i]].y);
            if(dist<rango_arma) {
                if(dist==1) {
                    printf("El jugador %s esta visible a %.2f metro\n\n",jugadores[indices[i]].sobrenombre, dist);
                } else {
                    printf("El jugador %s esta visible a %.2f metros\n\n",jugadores[indices[i]].sobrenombre, dist);
                }
                existe=1;
            }
        }
    }
    if(existe==0) {
        puts("Ningun jugador esta a su alcance");
    }
}


/** \brief Muestra la posicion actual de la tormenta
 *
 * \param *jug Puntero a jugador
 * \return No devuelve nada
 *
 */

void ver_tormenta(jugador *jug) {
    int f_actual=objeto_juego->fase_actual;
    fase_tormenta t=objeto_juego->tormentas[objeto_juego->fase_actual];
    int turnos=t.tiempo/60;

    printf("El centro de la tormenta esta en: [%.2f, %.2f]\n", t.x, t.y);
    printf("El radio de la tormenta es %.1f\n", t.diametro/2);
    if(f_actual<objeto_juego->numero_fases-1) {
        printf("Queda%c %d turno%c para que la tormenta se mueva a:\n", turnos==1?32:110, turnos, turnos==1?32:115);
        printf("[%.2f,%.2f], con radio: %.1f\n\n", objeto_juego->tormentas[f_actual+1].x, objeto_juego->tormentas[f_actual+1].y,
               objeto_juego->tormentas[f_actual+1].diametro/2);
    }
    return;
}

/** \brief Permite usar el objeto seleccionado, para disparar o curarse
 *
 * \param *jug Puntero a jugador
 * \param indices[] Vector de indices de jugadores activos
 * \return No devuelve nada
 *
 */

void usar_objeto(jugador *jug,int indices []) {

    int j,w=0,i,existe, obj_selec;
    float rango_arma;
    char c;
    char nick[10];

    obj_selec=jug->obj_seleccionado;
    system("cls");


    if(obj_selec!=-1) {

        c=jug->mochila[obj_selec].tipo[1];

    } else {
        c='r';//porque es la pistola por defecto
    }

    switch(c) {

    case 'r':


        //mostrar oponentes

        if(obj_selec==-1) {
            rango_arma=objeto_juego->rango_arma_base;
        } else {
            rango_arma=jug->mochila[obj_selec].alcance;
        }
        printf("%f\n", rango_arma);

        for(i=0; i<num_jugadores_activos; i++) {
            if(strcmp(jug->sobrenombre, jugadores[indices[i]].sobrenombre)!=0) {//no comprobar jugador consigo mismo
                if((distancia(jug->x,jug->y,jugadores[indices[i]].x,jugadores[indices[i]].y))<rango_arma) {
                    printf("Los jugadores visibles son  %s \n\n",jugadores[indices[i]].sobrenombre);
                    existe=1;
                }
            }
        }

        if(existe==0) {
            puts("Ningun jugador esta a su alcance");
            system("pause");
            system("cls");
            return;
        }
        printf("Selecciona un jugador: ");
        fgets(nick,50,stdin);
        fflush(stdin);

        for(j=0; j<num_jugadores_activos; j++) {
            if(strcmp(nick,jugadores[j].sobrenombre)==0) {
                printf("\nJugador comprobado\n");
                w=j;

            }
        }


        //actualizar oponentes/matar=adquirir experiencia



        if(obj_selec!=-1) {
            jug->mochila[obj_selec].cantidad-=2;
            if(jugadores[w].escudo==0) {
                jugadores[w].vida=jugadores[w].vida-jug->mochila[obj_selec].dano;
            } else {
                jugadores[w].escudo=jugadores[w].escudo-jug->mochila[obj_selec].dano;
                if(jugadores[w].escudo<0) {
                    int resto=abs(jugadores[w].escudo);
                    jugadores[w].vida-=resto;
                    jugadores[w].escudo=0;
                }
            }

        } else {
            if(jugadores[w].escudo==0) {
                jugadores[w].vida=jugadores[w].vida-10;
            } else {
                jugadores[w].escudo=jugadores[w].escudo-10;
                if(jugadores[w].escudo<0) {
                    int resto=abs(jugadores[w].escudo);
                    jugadores[w].vida-=resto;
                    jugadores[w].escudo=0;
                }

            }

        }
        if(jugadores[w].escudo<0) {
            jugadores[w].escudo=0;
        }

        if(jugadores[w].vida<=0) {
            eliminar_jugador(jug);
        }

        break;

    case 'c':

        if((strcmp("botiquin",jug->mochila[obj_selec].descripcion)==0)||(strcmp("venda",jug->mochila[obj_selec].descripcion)==0)) {

            jug->vida=jug->vida+jug->mochila[obj_selec].dano;

            if(jug->vida>100) {
                jug->vida=100;
            }

            jug->mochila[obj_selec].cantidad--;


            printf("Tu salud a aumentado, ahora tienes %i",jug->vida);


        } else {

            jug->escudo=jug->escudo+jug->mochila[obj_selec].dano;

            if(jug->escudo>100) {
                jug->escudo=100;
            }

            printf("Tu escudo a aumentado, ahora tienes %i",jug->escudo);

            jug->mochila[obj_selec].cantidad--;


        }

        break;

    default:

        printf("\nLas skins no se pueden usar, estan equipadas automaticamente\n");

        break;


    }

    if(jug->mochila[obj_selec].cantidad==0) {
        eliminar_objeto_mochila(jug);
        jug->obj_seleccionado=-1;
    }
}

//################################################
//  FUNCIONES AUXILIARES DE PARTIDA
//################################################

/** \brief Actualiza el objeto seleccionado del jugador
 *
 * \param *jug Puntero a jugador
 * \return Devuelve el nombre del nuevo objeto seleccionado
 *
 */

char* actualizar_objeto_seleccionado(jugador *jug) {
    char *nom;
    if(jug->obj_seleccionado==-1) {
        nom="Pistola normal";
    } else {
        nom=jug->mochila[jug->obj_seleccionado].identificadorobjeto;
    }
    return nom;
}


/** \brief Reune los indices de los jugadores activos en partida
 *
 * \return Devuelve un vector de enteros de indices
 *
 */

int* reune_indices_jugadores() {
    int index=0, i;
    int tam_vector=objeto_juego->jugadores_min;
    int *indices=(int*)malloc(tam_vector*sizeof(int));

    if(indices==NULL) {
        printf("ERROR al cargar el vector de orden\nEn funcion: establecer_orden()\n");
    } else {
        for(i=0; i<total_jugadores; i++) {
            if(strcmp(jugadores[i].estado, "EE")==0) {
                num_jugadores_activos++;
                strcpy(jugadores[i].estado, "EJ");
                if(index<tam_vector) {
                    indices[index]=i;
                    index++;
                } else {
                    tam_vector++;
                    indices=(int *)realloc(indices, tam_vector*sizeof(int));
                    indices[index]=i;
                    index++;
                }
            }
        }
    }
    return indices;
}


/** \brief Crea el orden aleatorio de los jugadores activos
 *  @see reune_indices_jugadores()
 * \return Devuelve un vector de enteros
 *
 */

int* establecer_orden() {
    int *indices=reune_indices_jugadores();
    int cambiados=0;
    int *orden_jugadores=(int *)malloc(num_jugadores_activos*sizeof(int));

    if(orden_jugadores==NULL) {
        puts("ERROR al cargar el vector orden_jugadores\nEn la funcion establecer_orden()");
        exit(1);
    } else {
        while(cambiados<num_jugadores_activos) {
            int index=rand()%num_jugadores_activos;
            if(indices[index]!=-1) {
                orden_jugadores[cambiados]=indices[index];
                indices[index]=-1;
                cambiados++;
            }
        }
    }
    return orden_jugadores;
}

/** \brief Establece las posiciones iniciales de los jugadores al inicio del juego
 *
 * \param *indices Vector de indices de jugadores activos
 * \return No devuelve nada
 *
 */

void randomizar_posiciones(int * indices) {
    float espacio_vital=objeto_juego->radio/100;
    int i, j;
    for(i=0; i<num_jugadores_activos; i++) {
        short int pos_valida=1;
        do {
            float angulo=angulo_aleatorio();
            int radio=radio_aleatorio((int)objeto_juego->radio);
            float x=radio*cos(angulo);
            float y=radio*sin(angulo);
            for(j=0; j<num_jugadores_activos && pos_valida==1; j++) {
                if(i!=j) {
                    float destX=jugadores[indices[j]].x;
                    float destY=jugadores[indices[j]].y;
                    if(distancia(x, y, destX, destY)<espacio_vital) {
                        pos_valida=0;
                    }
                }
            }
            if(pos_valida==1) {
                jugadores[indices[i]].x=x;
                jugadores[indices[i]].y=y;
            }

        } while(pos_valida==0);
    }
}

/** \brief Actualiza las fases de la tormenta a cada ronda
 *
 * \return No devuelve nada
 *
 */

void actualizar_tormenta() {
    if(objeto_juego->fase_actual<objeto_juego->numero_fases-1) {
        objeto_juego->tormentas[objeto_juego->fase_actual].tiempo-=60;
        if(objeto_juego->tormentas[objeto_juego->fase_actual].tiempo<=0) {
            objeto_juego->fase_actual++;
        }
    }
}

/** \brief Comprueba cuantos jugadores activos quedan
 *
 * \param *indices Vector de indices de jugadores activos
 * \return Devuelve 1 si quedan varios, 0 si solo queda uno
 *
 */

int jugadores_restantes(int *indices) {
    int out=1, count=0, i, index=0;
    for(i=0; i<num_jugadores_activos; i++) {
        if(strcmp(jugadores[indices[i]].estado, "GO")!=0) {
            count++;
            index=indices[i];
        }
    }
    if(count==1) {
        printf("El juego ha acabado.\nEL GANADOR ES: %s\n", jugadores[index].sobrenombre);
        printf("Ha ganado 50 monedas\n");
        actualizar_ganador(&jugadores[index]);
        out=0;
    }
    return out;
}

/** \brief Actualiza el perfil del jugador ganador
 *
 * \param *jug Puntero a jugador
 * \return No devuelve nada, modifica por referencia
 *
 */
void actualizar_ganador(jugador *jug) {
    jug->ng++;
    jug->cartera+=50;
    if(jug->ng>jug->nivel*objeto_juego->numero_partidas_por_nivel) {
        printf("Has subido de nivel: %d -> %d", jug->nivel, jug->nivel+1);
        printf("Has recibido %d monedas", jug->nivel*50);
        jug->nivel++;
        jug->cartera+=jug->nivel*50;
    }
    system("pause");
    system("cls");
    return;
}

/** \brief Elimina el objeto de la mochila del jugador
 *
 * \param *jug Puntero a jugador
 * \return No devuelve nada
 *
 */

void eliminar_objeto_mochila(jugador *jug) {
    int y;

    y=jug->obj_seleccionado;


    jug->mochila[y].alcance=0;
    jug->mochila[y].cantidad=0;
    jug->mochila[y].coste=0;
    jug->mochila[y].dano=0;
    strcpy(jug->mochila[y].descripcion,"0");
    strcpy(jug->mochila[y].identificadorobjeto,"0");
    strcpy(jug->mochila[y].tipo,"0");

    printf("\nObjeto eliminado\n");

}

/** \brief Elimina el jugador de la partida
 *
 * \param *jug Puntero a jugador
 * \return No devuelve nada
 *
 */

void eliminar_jugador(jugador *jug) {
    strcpy(jug->estado, "GO");
    num_jug_muertos++;
}

/** \brief Comprobaciones de final de ronda(actualizacion de tormenta y recuento de jugadores)
 *
 * \param *indices Vector de indices de jugadores activos
 * \return Devuelve 1 si la partida continua, 0 si no
 *
 */

int finalizar_turno(int *indices) {
    int i, continua=1;
    fase_tormenta tAux=objeto_juego->tormentas[objeto_juego->fase_actual];

    actualizar_tormenta();
    printf("Fin de la ronda %d\n\n", objeto_juego->turnos_de_partida);

    for(i=0; i<num_jugadores_activos; i++) { //itera sobre todos los jugadores en partida
        if(strcmp(jugadores[indices[i]].estado, "GO")!=0) {  //selecciona los jugadores aun vivos
            continua=jugadores_restantes(indices); //comprueba si solo queda un jugador vivo
            if(continua==1) { //si quedan varios jugadores, comprueba si esta fuera de la tormenta
                if(distancia(jugadores[indices[i]].x, jugadores[indices[i]].y, tAux.x, tAux.y)>tAux.diametro/2) {
                    printf("El jugador %s estaba fuera de la tormenta y ha sido eliminado\n\n", jugadores[indices[i]].sobrenombre);
                    eliminar_jugador(&jugadores[indices[i]]); //elimina el jugador fuera de la tormenta
                }
            } else {
                break;
            }
        }
    }

    objeto_juego->turnos_de_partida++;
    return continua;
}


/** \brief Reinicia la configuracion del juego y guarda la informacion en los ficheros
 *
 * \return No devuelve nada
 *
 */

void finalizar_partida(){
    int i=0;
    for(i=0; i<num_jugadores_activos; i++){
        if(compara_palabra(jugadores[i].estado, "EJ", "GO")==1){
            strcpy(jugadores[i].estado, "ON");
        }
    }
    objeto_juego->turnos_de_partida=0;
    objeto_juego->fase_actual=0;
    num_jugadores_activos=0;
    num_jug_muertos=0;
    guardar_partida();
}


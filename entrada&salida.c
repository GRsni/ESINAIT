#include "entrada&salida.h"
#include "utilidad.h"

/** \brief Cuenta el numero de lineas que tiene un fichero
 *
 * \param *nombre Cadena de caracteres, nombre del fichero a leer
 * \return Devuelve el numero de lineas del fichero
 *
 */
int contar_linea_fichero(char *nombre) {
    printf("AQUI contar linea fichero %s\n", nombre);
    char aux=0;
    int cont=1;
    FILE *f;
    f=fopen(nombre,"r");
    if(f==NULL) {

        printf("Ha ocurrido un error al abrir el fichero PRIMERO\n");
        exit(1);
    }
    while (aux!=EOF) {
        aux=fgetc(f);
        if(aux=='\n') {
            cont++;
        }
    }
    fclose(f);
    return cont;

}


/** \brief Copia la informacion de un objeto en otro por referencia
 *
 * \param *origen Puntero a objeto
 * \param *destino Puntero a objeto
 * \return No devuelve nada
 *
 */
void copiar_objeto(objeto *origen, objeto *destino) {
    strcpy(destino->identificadorobjeto, origen->identificadorobjeto);
    strcpy(destino->tipo, origen->tipo);
    strcpy(destino->descripcion, origen->descripcion);

    destino->dano=origen->dano;
    destino->coste=origen->coste;
    destino->alcance=origen->alcance;
    return;
}


/** \brief Carga el vector de objetos mochila del jugador por referencia
 *
 * \param *jug Puntero a jugador
 * \return No devuelve nada
 *
 */
void cargar_struct_mochila(jugador *jug) {
    int cont_objetos=0, i;
    FILE *f;
    char *token, linea[100];

    f=fopen("mochila.txt", "r");
    if(f==NULL) {
        printf("ERROR al abrir el archivo mochila en la funcion cargar_struct_mochila()\n");
        exit(1);
    } else {
        while(!feof(f)) {
            fgets(linea, 100, f);
            token=strtok(linea, "/");
            if(strcmp(token, jug->sobrenombre)==0) { //check if item bag nick matches any player's nick
                token=strtok(NULL, "/");
                for(i=0; i<total_objetos; i++) {
                    if(strcmp(token, objetos[i].identificadorobjeto)==0) { //item name matches item in whole list
                        copiar_objeto(&objetos[i], &jug->mochila[cont_objetos]);
                        token=strtok(NULL, "/");
                        jug->mochila[cont_objetos].cantidad=atoi(token);
                        jug->num_objetos++;
                        cont_objetos++;
                    }
                }
            }

        }
    }
}


/** \brief Carga la informacion de los jugadores desde el fichero "jugadores.txt"
 *
 * \return No devuelve nada
 *
 */

void cargar_struct_jugadores() {

    int N=0;
    int n=0;
    char c;
    char linea[100];
    char *token;
    FILE *f;
    N=contar_linea_fichero("usuarios.txt");
    total_jugadores=N;

    printf("numero de jugadores:%d\n", N);
    jugadores=(jugador*)malloc(N*sizeof(jugador));

    f=fopen("usuarios.txt","a+");

    if(f==NULL) {

        printf("\n Ha ocurrido un error al abrir el fichero");
        exit(1);
    } else {

        c=fgetc(f);
        if(c!=EOF) {
            //Q=contar_linea_fichero()
            rewind(f);

            do {
                fgets(linea,100,f);
                if(strcmp(linea,"\0")) {
                    token=strtok(linea,"/");
                    strcpy(jugadores[n].sobrenombre,token);

                    token=strtok(NULL,"/");
                    strcpy(jugadores[n].nombre,token);

                    token=strtok(NULL,"/");
                    jugadores[n].nivel=atoi(token);

                    token=strtok(NULL,"/");
                    jugadores[n].vida=atoi(token);

                    token=strtok(NULL,"/");
                    jugadores[n].escudo=atoi(token);

                    token=strtok(NULL,"/");
                    strcpy(jugadores[n].estado, token);

                    token=strtok(NULL,"/");
                    jugadores[n].cartera=atoi(token);

                    token=strtok(NULL,"/");
                    jugadores[n].np=atoi(token);

                    token=strtok(NULL,"/");
                    jugadores[n].ng=atoi(token);

                    token=strtok(NULL,"/");
                    jugadores[n].admin=strcmp(token, "ADM")==0?1:0;

                    token=strtok(NULL,"\n");
                    strcpy(jugadores[n].contrasena,token);

                    jugadores[n].obj_seleccionado=-1;

                    jugadores[n].x=LONG_MAX;
                    jugadores[n].y=LONG_MAX;

                    jugadores[n].num_objetos=0;
                    jugadores[n].mochila=(objeto*)calloc(objeto_juego->tamano_mochila, sizeof(objeto));
                    cargar_struct_mochila(&jugadores[n]);


                    n++;
                }

            } while(n<N);

        }

        fclose(f);
        system("cls");

    }
    return;
}


/** \brief Carga la informacion de todos los objetos desde el fichero "objetos.txt"
 *
 * \return No devuelve nada
 *
 */

void cargar_struct_objetos() {

    int N=0;
    int n=0;
    char c;
    char linea[100];
    char *token;

    FILE *f;
    N=contar_linea_fichero("objetos.txt");
    total_objetos=N;

    objetos=(objeto*)malloc(N*sizeof(objeto));

    f=fopen("objetos.txt","a+");

    if(f==NULL) {

        printf("\n Ha ocurrido un error al abrir el fichero");
        exit(1);
    } else {

        c=fgetc(f);
        if(c!=EOF) {
            //    Q=contar_linea_fichero();
            rewind(f);
            do {
                fgets(linea,100,f);

                if(strcmp(linea,"\0")) {
                    token=strtok(linea,"/");
                    strcpy(objetos[n].identificadorobjeto,token);

                    token=strtok(NULL,"/");
                    strcpy(objetos[n].descripcion,token);

                    token=strtok(NULL,"/");
                    strcpy(objetos[n].tipo,token);

                    token=strtok(NULL,"/");
                    objetos[n].coste=atoi(token);;

                    token=strtok(NULL,"/");
                    objetos[n].alcance=atof(token);;

                    token=strtok(NULL,"/");
                    objetos[n].dano=atoi(token);;
                    objetos[n].cantidad=0;

                    n++;

                }

            } while(N!=n);

        }

        fclose(f);
        system("cls");
    }
    return;
}


/** \brief Carga la informacion del juego desde los archivos
 *
 * \return No devuelve nada
 *
 */

void cargar_struct_juego() {
    FILE *f;
    char linea[200];
    char *token;
    objeto_juego=(juego*)malloc(sizeof(juego));

    f=fopen("configuracion.txt", "r");
    if(f==NULL) {
        printf("ERROR al abrir el archivo de configuracion\n");
        exit(1);
    } else {
        fgets(linea, 200, f);
        puts(linea);
        token=strtok(linea, "/");
        objeto_juego->radio=atof(token);

        token=strtok(NULL, "/");
        objeto_juego->alcance_recoger=atoi(token);


        token=strtok(NULL, "/");
        objeto_juego->rango_arma_base=atof(token);
        printf("%f", objeto_juego->rango_arma_base);

        token=strtok(NULL, "/");
        objeto_juego->cartera_defecto=atoi(token);

        token=strtok(NULL, "/");
        objeto_juego->jugadores_min=atoi(token);

        token=strtok(NULL, "/");
        objeto_juego->tamano_paso=atof(token);

        token=strtok(NULL, "/");
        objeto_juego->tamano_mochila=atoi(token);

        token=strtok(NULL, "/");
        objeto_juego->numero_partidas_por_nivel=atoi(token);

        token=strtok(NULL, "/");
        objeto_juego->numero_acciones_por_turno=atoi(token);

        fclose(f);

        cargar_struct_tormenta();
        cargar_struct_posiciones();

        objeto_juego->fase_actual=0;
    }


}

/** \brief Carga las fases de la tormenta desde el archivo "tormenta.txt"
 *
 *  \return No devuelve nada
 *
 */

void cargar_struct_tormenta() {
    int N=0;
    int n=0;
    char c;
    char linea[100];
    char *token;

    FILE *f;
    N=contar_linea_fichero("tormenta.txt");

    objeto_juego->numero_fases=N;

    objeto_juego->tormentas=(fase_tormenta*)malloc(N*sizeof(fase_tormenta));

    f=fopen("tormenta.txt","a+");

    if(f==NULL) {

        printf("\n Ha ocurrido un error al abrir el fichero");
        exit(1);
    } else {

        c=fgetc(f);
        if(c!=EOF) {
            //    Q=contar_linea_fichero();
            rewind(f);
            do {
                fgets(linea,100,f);

                if(strcmp(linea,"\0")) {

                    token=strtok(linea,"/");
                    objeto_juego->tormentas[n].x=atoi(token);;

                    token=strtok(NULL,"/");
                    objeto_juego->tormentas[n].y=atoi(token);;

                    token=strtok(NULL,"/");
                    objeto_juego->tormentas[n].diametro=atoi(token);;

                    token=strtok(NULL,"/");
                    objeto_juego->tormentas[n].tiempo=atoi(token);;

                    n++;

                }

            } while(N!=n);

        }

        fclose(f);
        system("cls");
    }
    return;
}

/** \brief Carga el vector de posiciones en el mapa desde el fichero "posiciones.txt"
 *
 * \return No devuelve nada
 *
 */

void cargar_struct_posiciones() {

    int N=0;
    int n=0;
    char c;
    char linea[100];
    char *token;

    FILE *f;
    N=contar_linea_fichero("mapa.txt");

    objeto_juego->numero_posiciones=N;
    objeto_juego->objetos_en_mapa=0;
    objeto_juego->posiciones=(posicion_mapa*)malloc(N*sizeof(posicion_mapa));

    f=fopen("mapa.txt","a+");

    if(f==NULL) {

        printf("\n Ha ocurrido un error al abrir el fichero");
        exit(1);
    } else {

        c=fgetc(f);
        if(c!=EOF) {
            //    Q=contar_linea_fichero();
            rewind(f);
            do {
                fgets(linea,100,f);

                if(strcmp(linea,"\0")) {
                    token=strtok(linea,"/");
                    strcpy(objeto_juego->posiciones[n].tipo,token);
                    if(strcmp(token, "Objeto")==0) {
                        objeto_juego->objetos_en_mapa++;
                    }

                    token=strtok(NULL,"/");
                    strcpy(objeto_juego->posiciones[n].nombre_elemento,token);

                    token=strtok(NULL,"/");
                    objeto_juego->posiciones[n].x=atof(token);

                    token=strtok(NULL,"/");
                    objeto_juego->posiciones[n].y=atof(token);

                    n++;
                }

            } while(N!=n);
        }

        fclose(f);
        system("cls");
    }
    return;
}

/** \brief Muestra toda la informacion cargada en el sistema
 *
 * \return No deuvelve nada
 *
 */

void mostrar() {
    int i, j;
    int Q=contar_linea_fichero("usuarios.txt");
    for(i=0; i<Q; i++) {
        printf("nick: %s\n",jugadores[i].sobrenombre);
        fflush(stdin);

        printf("nombre: %s\n",jugadores[i].nombre);
        fflush(stdin);

        printf("nivel: %d\n",jugadores[i].nivel);
        fflush(stdin);

        printf("vida: %d\n",jugadores[i].vida);
        fflush(stdin);

        printf("contrasena: %s\n",jugadores[i].contrasena);
        fflush(stdin);

        printf("admin: %d\n", jugadores[i].admin);
        fflush(stdin);

        printf("Estado: %s\n", jugadores[i].estado);
        fflush(stdin);

        for(j=0; j<jugadores[i].num_objetos; j++) {
            printf("%s, ", jugadores[i].mochila[j].identificadorobjeto);
            printf("%s, ", jugadores[i].mochila[j].descripcion);
            printf("%s, ", jugadores[i].mochila[j].tipo);
            printf("cantidad: %d ", jugadores[i].mochila[j].cantidad);
            printf("coste: %d ", jugadores[i].mochila[j].coste);
            puts("");
        }
        puts("");
    }
    puts("LISTA DE OBJETOS");
    for(i=0; i<total_objetos; i++) {
        printf("%s/%s daño %d\n", objetos[i].identificadorobjeto, objetos[i].descripcion, objetos[i].dano);
    }
    printf("tamaño mapa: %f\n", objeto_juego->radio);
    printf("rango_arma_base: %f\n", objeto_juego->rango_arma_base);
    puts("\nPosiciones tormenta:");
    for(i=0; i<objeto_juego->numero_fases; i++) {
        printf("pos x: %f, pos y: %f, con diametro: %f\n", objeto_juego->tormentas[i].x,
               objeto_juego->tormentas[i].y, objeto_juego->tormentas[i].diametro);
    }
    puts("\nPosiciones en el mapa:");
    for(i=0; i<objeto_juego->numero_posiciones; i++) {
        posicion_mapa p=objeto_juego->posiciones[i];
        printf("%s: %s en %.2f %.2f\n", p.tipo, p.nombre_elemento, p.x, p.y);
    }
    system("pause");
    return;
}


/** \brief Llamada a las funciones de carga de datos
 *
 * \return No devuelve nada
 *
 */
void cargar_estructuras() {
    cargar_struct_juego();
    cargar_struct_objetos();
    cargar_struct_jugadores();
    mostrar();
}


/** \brief Llamada a las funciones de guardado en ficheros
 *
 * \return  No devuelve nada
 *
 */
void guardar_partida() {

    guardar_configuracion();
    guardar_mochila();
    guardar_objetos();
    guardar_posiciones();
    guardar_tormenta();
    guardar_usuarios();

}

/** \brief Guarda el vector de posiciones en el fichero
 *
 * \return No devuelve nada
 *
 */
void guardar_posiciones() {
    int i;
    FILE *f=fopen("mapa.txt", "w+");
    if(f==NULL) {
        puts("ERROR al abrir el fichero mapa.txt en la funcion guardar_struct_posiciones");
    } else {
        for(i=0; i<total_jugadores; i++) {
            if(strcmp(jugadores[i].estado, "EJ")==0) {
                fprintf(f, "Jugador/%s/%f/%f\n", jugadores[i].sobrenombre, jugadores[i].x, jugadores[i].y);
            }
        }
        for(i=0; i<objeto_juego->numero_posiciones; i++) {
            posicion_mapa p=objeto_juego->posiciones[i];
            if(strcmp(p.tipo, "Objeto")==0) {
                if(distancia(p.x, p.y, 0, 0)<objeto_juego->radio) {
                    fprintf(f, "Objeto/%s/%f/%f", p.nombre_elemento, p.x, p.y);
                    if(i<objeto_juego->numero_posiciones-1) {
                        fprintf(f, "\n");
                    }
                }
            }
        }
        fclose(f);
    }
}

/** \brief Guarda el vector de jugadores en el fichero
 *
 * \return No devuelve nada
 *
 */
void guardar_usuarios() {


    FILE *f;
    int i=0,N=0;
    N=total_jugadores;

    f=fopen("usuarios.txt","w");

    if(f==NULL) {

        printf("\nERROR en la funcion guardar_usuarios al abrir el fichero\n");
    } else {

        for(i=0; i<N; i++) {

            fwrite(jugadores[i].sobrenombre,1,strlen(jugadores[i].sobrenombre),f);
            fputc('/',f);
            fwrite(jugadores[i].nombre,1,strlen(jugadores[i].nombre),f);
            fputc('/',f);
            fprintf(f,"%i",jugadores[i].nivel);
            fputc('/',f);
            fprintf(f,"%i",jugadores[i].vida);
            fputc('/',f);
            fprintf(f,"%i",jugadores[i].escudo);
            fputc('/',f);;
            fputc('/',f);
            fwrite(jugadores[i].estado,1,strlen(jugadores[i].estado),f);
            fputc('/',f);
            fprintf(f,"%i",jugadores[i].cartera);
            fputc('/',f);
            fprintf(f,"%i",jugadores[i].np);
            fputc('/',f);
            fprintf(f,"%i",jugadores[i].ng);
            fputc('/',f);
            if(jugadores[i].admin==1) {
                fwrite("ADM",1,3,f);
                fputc('/',f);
            } else {
                fwrite("JDG",1,3,f);
                fputc('/',f);
            }

            fwrite(jugadores[i].contrasena,1,strlen(jugadores[i].contrasena),f);
            fputc('\n',f);

        }

        fclose(f);
    }
}
/** \brief Guarda la configuracion del juego en el fichero
 *
 * \return No devuelve nada
 *
 */


void guardar_configuracion() {

    FILE *f;
    int i=0;


    f=fopen("configuracion.txt","w");

    if(f==NULL) {
        printf("\nHa ocurrido un error al abrir el fichero\n");
        exit(1);
    }

    fprintf(f,"%f",objeto_juego[i].radio);
    fputc('/',f);
    fprintf(f,"%f",objeto_juego[i].alcance_recoger);
    fputc('/',f);
    fprintf(f,"%f",objeto_juego[i].rango_arma_base);
    fputc('/',f);
    fprintf(f,"%i",objeto_juego[i].cartera_defecto);
    fputc('/',f);
    fprintf(f,"%i",objeto_juego[i].jugadores_min);
    fputc('/',f);
    fprintf(f,"%f",objeto_juego[i].tamano_paso);
    fputc('/',f);
    fprintf(f,"%i",objeto_juego[i].tamano_mochila);
    fputc('/',f);
    fprintf(f,"%i",objeto_juego[i].numero_partidas_por_nivel);
    fputc('/',f);
    fprintf(f,"%i",objeto_juego[i].numero_acciones_por_turno);
    fputc('\n',f);

    fclose(f);
}



/** \brief Guarda las mochilas de los jugadores en el fichero
 *
 * \return  No devuelve nada
 *
 */

void guardar_mochila() {


    FILE *f;
    int j=0,i=0,N=0,M=0;
    N=total_jugadores;

    f=fopen("mochila.txt","w");

    if(f==NULL) {

        printf("\nHa ocurrido un error al abrir el fichero\n");
        exit(1);
    }

    for(i=0; i<N; i++) {
        M=jugadores[i].num_objetos;
        for(j=0; j<M; j++) {
            fwrite(jugadores[i].sobrenombre,1,strlen(jugadores[i].sobrenombre),f);
            fputc('/',f);
            fwrite(jugadores[i].mochila[j].identificadorobjeto,1,strlen(jugadores[i].mochila[j].identificadorobjeto),f);
            fputc('/',f);
            fprintf(f,"%i",jugadores[i].mochila[j].cantidad);
            fputc('\n',f);
        }

    }

    fclose(f);
}

/** \brief Guarda las posiciones de la tormenta en el fichero
 *
 * \return No devuelve nada
 *
 */


void guardar_tormenta() {


    FILE *f;
    int i=0,N=0;

    N=contar_linea_fichero("tormenta.txt");

    f=fopen("tormenta.txt","w");

    if(f==NULL) {

        printf("\nHa ocurrido un error al abrir el fichero\n");
        exit(1);
    }

    for(i=0; i<N; i++) {

        fprintf(f,"%f",objeto_juego->tormentas[i].x);
        fputc('/',f);
        fprintf(f,"%f",objeto_juego->tormentas[i].y);
        fputc('/',f);
        fprintf(f,"%f",objeto_juego->tormentas[i].diametro);
        fputc('/',f);
        fprintf(f,"%i",objeto_juego->tormentas[i].tiempo);
        fputc('\n',f);

    }

    fclose(f);
}


/** \brief Guarda la lista de objetos en el fichero
 *
 * \return No devuelve nada
 *
 */


void guardar_objetos() {


    FILE *f;
    int i=0,N=0;

    N=total_objetos;

    f=fopen("objetos.txt","w");

    if(f==NULL) {

        printf("\nHa ocurrido un error al abrir el fichero\n");
        exit(1);
    }

    for(i=0; i<N; i++) {

        fwrite(objetos[i].identificadorobjeto,1,strlen(objetos[i].identificadorobjeto),f);
        fputc('/',f);
        fwrite(objetos[i].descripcion,1,strlen(objetos[i].descripcion),f);
        fputc('/',f);
        fwrite(objetos[i].tipo,1,strlen(objetos[i].tipo),f);
        fputc('/',f);
        fprintf(f,"%i",objetos[i].coste);
        fputc('/',f);
        fprintf(f,"%f",objetos[i].alcance);
        fputc('/',f);
        fprintf(f,"%i",objetos[i].dano);
        fputc('\n',f);

    }

    fclose(f);
}




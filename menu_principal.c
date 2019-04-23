#include "menu_principal.h"
#include <stdio.h>
#include "utilidad.h"
#include "estructura.h"
#include "entrada&salida.h"
#include "partida.h"

/** \brief Funcion de inicio de programa
 *
 * \return No devuelve nada
 *
 */

void entrar() {

    int d;

    printf("\tBienvenido a ESINAIT \n 1.Entrar en el sistema\n 0.Salir del sistema\n");
    scanf("%d",&d);

    if(d==1) {
        iniciar_sesion();
    } else {
        exit(1);
    }

}

/** \brief Inicio de sesion de cada usuario
 *
 * \return No devuelve nada
 *
 */

void iniciar_sesion() {

    int c;

    printf(" 1.Cuenta existente\n ");
    printf(" 2.Crear un usuario nuevo\n");
    printf("\t Su eleccion:");
    scanf("%i",&c);


    do {
        switch(c) {
        case 1:
            comprobar_jugador();
            break;
        case 2:
            crear_usuario();
            break;
        //return 0;
        default:
            printf("Opcion no valida");
        }
    } while(c<1 || c>2);


}

/** \brief Funcion para crear perfil nuevo
 *
 * \return No devuelve nada, modifica por referencia el vector de jugadores
 *
 */

void crear_usuario() {
    char contra[50];
    char contra1[50];
    int comprobante=0;
    int N=0;
    N=contar_linea_fichero("usuarios.txt");
    N=N+1;
    jugadores=(jugador*)malloc(N*sizeof(jugador));
    puts("Bienvenido a Esinait, rellene los datos para crear su cuenta");

    puts("Introduzca su nick de juego; ");
    fflush(stdin);
    fgets(jugadores[N].sobrenombre,50,stdin);
    correcionM(jugadores[N].sobrenombre);


    puts("Introduzca su nombre completo: ");
    fflush(stdin);
    fgets(jugadores[N].nombre,50,stdin);
    correcionM(jugadores[N].nombre);


    while(comprobante==0) {
        puts("Introduzca su contraseña: ");
        fflush(stdin);
        fgets(contra,50,stdin);
        correcionM(contra);
        puts("Repita la contraseña: ");
        fflush(stdin);
        fgets(contra1,50,stdin);
        correcionM(contra1);

        if(strcmp(contra,contra1)==0) {
            strcpy(jugadores[N].contrasena,contra);
            comprobante=1;
        } else {
            puts("La contraseña no coincide");
        }
    }

    jugadores[N].nivel=1;
    printf("Su nivel actual es %d por ser un nuevo usuario\n\n",jugadores[N].nivel);

    jugadores[N].vida=100;
    printf("Su vida actual es de %d por ser un nuevo usuario\n\n",jugadores[N].vida);

    jugadores[N].escudo=0;
    printf("Su escudo actual es de %d por ser un nuevo usuario\n\n",jugadores[N].escudo);

    strcpy(jugadores[N].estado,"OFF");
    printf("Al ser un nuevo usuario, su estado preterminado es %s \n\n",jugadores[N].estado);

    jugadores[N].cartera=0;
    printf("Sus monedas actuales son %d debido a ser un nuevo usuario \n\n",jugadores[N].cartera);

    jugadores[N].np=0;

    jugadores[N].ng=0;

    jugadores[N].admin=0;
    menu_usuarios(&jugadores[N]);
}



/** \brief Comprueba la informacion de inicio del jugador
 *
 * \return No devuelve nada
 *
 */

void comprobar_jugador() {

    int N=0;
    int i=0;
    int j=0;
    int decision=0;
    int comprobar=0;
    char contra[50];
    char nom[50];
    int intentos=2;
    N=contar_linea_fichero("usuarios.txt");
    while(comprobar==0) {
        i=0;
        puts("Introduzca su nombre de usuario: ");
        fflush(stdin);
        fgets(nom,50,stdin);
        correcionM(nom);
        printf("%s \n\n",jugadores[i].sobrenombre);


        while((i<N)&&(comprobar==0)) {
            correcionM(jugadores[i].sobrenombre);
            if(strcmp(jugadores[i].sobrenombre,nom)==0) {
                j=i;
                comprobar=1;
                printf("%d \n\n",comprobar);
            } else {
                i++;
            }
        }
        if(comprobar==0) {

            puts("Usuario No encontrado porfavor intentelo de nuevo");
            puts("Pulse 1 para volver a la pantalla inicial");
            scanf("%d",&decision);
            fflush(stdin);
            if(decision==1) {
                system("cls");
            }
        }
    }


    comprobar=0;

    while((comprobar==0)&&(intentos>=0)) {
        puts("Introduzca su contrasena: ");
        fflush(stdin);
        fgets(contra,50,stdin);
        correcionM(contra);
        comprobar=0;
        printf("%s",jugadores[j].contrasena);
        if(strcmp(jugadores[j].contrasena,contra)==0) {
            comprobar=1;
            puts("Contrasena correcta, bienvenido\n\n");
        } else {
            puts("Contrasena incorrecta, vuelva a intentarlo\n");
            printf("Le quedan %d intentos",intentos);
            intentos--;
        }

    }
    if(jugadores[j].admin==1) {
        menu_administrador(&jugadores[j]);
    } else {
        menu_usuarios(&jugadores[j]);
    }

}

/** \brief Menu de control del administrador
 *
 * \param *jug Puntero a jugador
 * \return No devuelve nada
 *
 */

void menu_administrador(jugador *jug) {

    int decision;
    int comprobar=0;
    char decision1[20];
    int i=0;
    int N=0;
    int j=0;
    N=contar_linea_fichero("usuarios.txt");

    //printf("%s",jug->sobrenombre);
    printf("\n\tMenu-Administrador\n");
    printf("--------------------------\n");

    puts("OPCIONES DEL ADMINISTRADOR : ");
    puts("¿Que desea hacer?\n\n");
    puts(" 1.Editar un perfil");
    puts(" 2.Empezar la partida: ");
    puts(" 3.Eliminar jugador");
    puts(" 4.Editar configuracion");
    puts(" 5.Editar objetos");

    puts("OPCIONES USUARIO");
    printf(" 6.Cambiar de usuario\n");
    printf(" 7.Jugar/Continuar Partida\n");
    printf(" 8.Comprar objetos\n");
    printf(" 9.Ver perfil\n");
    printf(" 10.Salir del sistema\n");
    printf("\n\t Su eleccion:");

    scanf("%d",&decision);

    switch (decision) {
    case 1:
        editar_usuario();
        break;
    case 2:
        game_loop(); //Se inicia la partida
        break;
    case 3:
        puts("Introduce el nickname el jugador al que quiere eliminar");
        fflush(stdin);
        fgets(decision1,50,stdin);
        correcionM(decision1);
        for(i=0; i<N; i++) {
            if(strcmp(decision1,jugadores[i].sobrenombre)==0) {
                j=i;
                i=N;
                comprobar=1;
            }
        }

        if(comprobar==1) {




            strcpy(jugadores[j].sobrenombre,jugadores[N-1].sobrenombre);

            strcpy(jugadores[j].nombre,jugadores[N-1].nombre);

            jugadores[j].nivel=jugadores[N-1].nivel;

            jugadores[j].vida=jugadores[N-1].vida;

            jugadores[j].escudo=jugadores[N-1].escudo;

            strcpy(jugadores[j].estado,jugadores[N-1].estado);

            jugadores[j].cartera=jugadores[N-1].cartera;

            jugadores[j].np=jugadores[N-1].np;

            jugadores[j].ng=jugadores[N-1].ng;

            jugadores[j].admin=jugadores[N-1].admin;

            strcpy(jugadores[j].contrasena,jugadores[N-1].contrasena);

            N--;





            jugadores=(jugador*)realloc(jugadores,N*sizeof(jugador));
        } else {
            puts("Ese jugador no existe");
        }
        puts("ANTES DE ESTPO");
        menu_administrador(&jugadores[j]);

        break;
    case 4:
        editar_configuracion();
        break;
    case 5:
        editar_objetos();
        break;

    case 6:
        iniciar_sesion();
        break;

    case 7:
        printf("Usted esta en espera");
        strcpy(jug->estado, "EE");
        num_jugadores_activos++;
        menu_administrador(&jugadores[j]);
        break;

    case 8:
        comprar_objeto(jug);

        break;

    case 9:
        ver_perfil(jug);
        break;

    case 10:
        printf(" Saliendo...");
        entrar();
        break;

    default:
        printf("\nOpcion no valida\n");
        break;
    }

}

/** \brief Menu de edicion de usuarios para el administrador
 *
 * \return No devuelve nada
 *
 */

void editar_usuario() {

    int comprobacion=0;
    char decision[50];
    char cambiarP[50];
    int cambiarN;
    int decision1=0;
    int decision2=0;
    int N=0;
    int j=0;
    int i=0;


    N=contar_linea_fichero("usuarios.txt");

    while(comprobacion==0) {
        puts("Introduzca el nick del jugador del cual quiere editar su perfil: ");
        fflush(stdin);
        fgets(decision,50,stdin);
        correcionM(decision);
        while((comprobacion==0)&&(i<N)) {
            if(strcmp(jugadores[i].sobrenombre,decision)==0) {
                comprobacion=1;
                j=i;
            } else {
                // printf("%d",i);
                i++;
            }
        }

        if(comprobacion==0) {
            puts("Ese jugador no existe\n\n");
            puts("Pulse 1 para introducir otro usuario");
            puts("Pulse cualquier otro boton para volver al menu administrador");
            scanf("%d",&decision1);
            if(decision1!=1) {
                menu_administrador(&jugadores[j]);

            }
        }
    }

    printf("Introduzca el campo que quiere modificar del jugador %s \n\n",jugadores[j].sobrenombre);
    puts("Pulse 1 para editar el nick");
    puts("Pulse 2 para editar el nombre");
    puts("Pulse 3 para editar el nivel");
    puts("Pulse 4 para editar la vida");
    puts("Pulse 5 para editar el escudo");
    puts("Pulse 6 para editar el estado");
    puts("Pulse 7 para editar la cartera");
    puts("Pulse 8 para editar el numero partida jugadas");
    puts("Pulse 9 para editar el numero partida ganadas");
    puts("Pulse 10 para editar el rol");
    puts("Pulse 11 para editar la contraseña");
    scanf("%d",&decision2);

    switch(decision2) {
    case 1:
        printf("El nick actual es %s \n\n",jugadores[j].sobrenombre);
        puts("Introduzca el nuevo nick del jugador: ");
        fflush(stdin);
        fgets(cambiarP,50,stdin);
        correcionM(cambiarP);
        strcpy(jugadores[j].sobrenombre,cambiarP);
        printf("El nuevo valor del nickname es %s \n\n",jugadores[j].sobrenombre);

        editar_usuario();

    case 2:
        printf("El nombre actual es %s \n\n",jugadores[j].nombre);
        puts("Introduzca el nuevo nombre del jugador: ");
        fflush(stdin);
        fgets(cambiarP,50,stdin);
        correcionM(cambiarP);
        strcpy(jugadores[j].nombre,cambiarP);
        printf("El nuevo valor del nombre es %s \n\n",jugadores[j].nombre);

        editar_usuario();

    case 3:
        printf("El nivel actual es %d \n\n",jugadores[j].nivel);
        puts("Introduzca el nuevo nivel del jugador: ");
        scanf("%d",&cambiarN);
        jugadores[j].nivel=cambiarN;
        printf("El nuevo nivel del jugador es %d \n\n",jugadores[j].nivel);

        editar_usuario();

    case 4:
        printf("La vida actual es %d \n\n",jugadores[j].vida);
        puts("Introduzca la nueva vida del jugador: ");
        scanf("%d",&cambiarN);
        jugadores[j].vida=cambiarN;
        printf("La nueva vida del jugador es %d \n\n",jugadores[j].vida);

        editar_usuario();

    case 5:
        printf("El escudo actual del escudo es %d \n\n",jugadores[j].escudo);
        puts("Introduzca el nuevo escudo del jugador: ");
        scanf("%d",&cambiarN);
        jugadores[j].escudo=cambiarN;
        printf("El nuevo escudo del jugador es %d \n\n",jugadores[j].escudo);

        editar_usuario();

    case 6:
        printf("El estado actual es %s \n\n",jugadores[j].estado);
        puts("Introduzca el nuevo estado del jugador: ");
        fflush(stdin);
        fgets(cambiarP,50,stdin);
        correcionM(cambiarP);
        strcpy(jugadores[j].estado,cambiarP);
        printf("El nuevo estado es %s \n\n",jugadores[j].estado);


        editar_usuario();

    case 7:
        printf("El valor actual de la cartera es %d \n\n",jugadores[j].cartera);
        puts("Introduzca el nuevo valor de la cartera del jugador: ");
        scanf("%d",&cambiarN);
        jugadores[j].cartera=cambiarN;
        printf("El nuevo valor de la cartera es es %d \n\n",jugadores[j].cartera);

        editar_usuario();

    case 8:
        printf("El numero de partidas jugadas es %d \n\n",jugadores[j].np);
        puts("Introduzca el nuevo valor de partidas jugadas por el jugador: ");
        scanf("%d",&cambiarN);
        jugadores[j].np=cambiarN;
        printf("El numero de partidas jugadas por el jugador es %d \n\n",jugadores[j].np);

        editar_usuario();

    case 9:
        printf("El numero de partidas ganadas es %d \n\n",jugadores[j].ng);
        puts("Introduzca el nuevo valor de partidas ganadas por el jugador: ");
        scanf("%d",&cambiarN);
        jugadores[j].ng=cambiarN;
        printf("El nuumero de partidas ganadas por el jugador es %d \n\n",jugadores[j].ng);

        editar_usuario();

    case 10:
        puts("1 para administrador, 0 para usuario corriente");
        printf("El rol del usuario es %d \n\n",jugadores[j].admin);
        puts("Introduzca el nuevo rol del jugador: ");
        scanf("%d",&cambiarN);
        jugadores[j].admin=cambiarN;
        printf("El nuevo rol del jugador es %d \n\n",jugadores[j].admin);

        editar_usuario();

    case 11:
        printf("La contraseña actual es %s \n\n",jugadores[j].contrasena);
        puts("Introduzca la nueva contraseña del jugador: ");
        fflush(stdin);
        fgets(cambiarP,50,stdin);
        correcionM(cambiarP);
        strcpy(jugadores[j].contrasena,cambiarP);
        printf("La nueva contraseña es %s \n\n",jugadores[j].contrasena);

        editar_usuario();

    default:
        editar_usuario();

    }

}


/** \brief Menu de control para los usuarios
 *
 * \param *jug Puntero a jugador
 * \return No devuelve nada
 *
 */

void menu_usuarios(jugador *jug) {

    int c;

    printf("%s",jug->sobrenombre);
    printf("\n\tMenu-Usuarios\n");
    printf("--------------------------\n");

    if(strcmp(jug->estado,"EJ")!=0) {
        printf(" 1.Cambiar de usuario\n");
    } else {
        printf(" 1.#Opcion bloqueada durante la partida#\n");
    }

    if(strcmp(jug->estado,"EJ")!=0) {
        printf(" 2.Jugar partida\n");
    } else {
        printf(" 2.Continuar partida\n");
    }


    if(strcmp(jug->estado,"EJ")!=0) {
        printf(" 3.Comprar Objeto\n");
    } else {
        printf(" 3.#Opcion bloqueada durante la partida#\n");
    }

    printf(" 4.Ver perfil\n");

    if(strcmp(jug->estado,"EJ")!=0) {
        printf(" 5.Salir del sistema\n");
    } else {
        printf(" 5.#Opcion bloqueada durante la partida#\n");
    }

    printf("\n\t Su eleccion:");

    if(strcmp(jug->estado,"EJ")!=0) {
        scanf("%d",&c);
    } else {
        do {
            scanf("%d",&c);
        } while(c!=5 || c!=3 || c!=1);
    }

    do {
        switch(c) {

        case 1:
            iniciar_sesion();
            break;
        case 2:
            printf("\n Todavia no hecha\n");
            strcpy(jug->estado, "EE");
            num_jugadores_activos++;
            break;
        case 3:
            comprar_objeto(jug);
            break;
        case 4:
            ver_perfil(jug);
            break;
        case 5:
            printf(" Saliendo...");
            //volver a entrar
            break;
        default:
            printf("\nOpcion no valida\n");
            break;

        }
    } while(c<1 && c>5);
}


/** \brief Muestra por pantalla la informacion de perfil del usuario
 *
 * \param *jug Puntero a jugador
 * \return No devuelve nada
 *
 */
void ver_perfil(jugador *jug) {

    system("cls");

    printf("\tTu perfil:\n");
    printf("Nick: %s\n",jug->sobrenombre);
    printf("Nombre: %s\n",jug->nombre);
    printf("Contrasena: %s\n",jug->contrasena);
    printf("Cartera: %i monedas\n",jug->cartera);
    printf("Estado: %s\n",jug->estado);
    printf("Vida: %i",jug->vida);
    printf("Escudo: %i\n",jug->escudo);
    printf("Nivel: %i\n",jug->nivel);
    printf("Numero de partidas ganadas: %i\n",jug->ng);
    printf("Numero de aprtidas jugadas: %i\n",jug->np);
    printf("Numero de objetos de la mochila: %i\n",jug->num_objetos);

    printf("\n");
    system("pause");
}

/** \brief Muestra la tienda para comprar objetos
 *
 * \param *jug Puntero a jugador
 * \return No devuelve nada
 *
 */


void comprar_objeto(jugador *jug) {
    int j,N,k,NM,W,n=1,y,z,comp,comp2;
    char p;
    char id[10],u[10],c[2],c2[2];

    N=total_objetos;

    system("cls");

    printf("\t\nBIENVENIDO A LA TIENDA\n");
    printf("\n");

    for(j=0; j<N; j++) {

        printf("%i. %s\t",j+1,objetos[j].identificadorobjeto);

        if(j==4) {
            printf("\n");
        }
    }

    printf("\n\nDesea comprar alguno de estos objetos?[si/no]: ");
    scanf("%s",c);

    comp=compara_palabra(c,"si","Si");


    //Datos estaticos pre bucle

    NM=jug->num_objetos;

    W=0;


    do {
        if(comp==1) {

            printf("\n\nIndica el identificador del objeto: ");
            scanf("%s",id);
            fflush(stdin);

            //Buscamos el objeto k = objeto
            for(k=0; k<=N; k++) {

                //objeto existe
                if(strcmp(id,objetos[k].identificadorobjeto)==0) {

                    if(objetos[k].coste<=jug->cartera) {

                        //Lugar donde se repite el objeto= Y

                        for(y=0; y<objeto_juego[0].tamano_mochila; y++) {

                            if(strcmp(id,jug->mochila[y].identificadorobjeto)==0) {

                                W=1;//Esta repetidp

                                printf("\nEl objeto ''%s''esta repetido",objetos[k].descripcion);

                                jug->cartera=jug->cartera-objetos[k].coste; //pierdes dinero al comprar el objeto

                                if(strcmp("arma",jug->mochila[y].tipo)==0) {

                                    printf(" y adquiere 20 mas de municion\n");


                                    jug->mochila[y].cantidad=jug->mochila[y].cantidad+20;

                                } else {
                                    printf(" y acumulas 1 mas\n");

                                    jug->mochila[y].cantidad++;


                                }

                            }

                        }


                        //No esta repetido W=si se repite o no 1/0
                        if(W==0) {
                            if(objeto_juego[0].tamano_mochila>=jug->num_objetos) {
                                //con espacio

                                printf("\nEl objeto ''%s'' sera añadido a su mochila\n",objetos[k].descripcion);

                                jug->cartera=jug->cartera-objetos[k].coste;

                                NM=jug->num_objetos;

                                strcpy(jug->mochila[NM].identificadorobjeto,objetos[k].identificadorobjeto);
                                strcpy(jug->mochila[NM].descripcion,objetos[k].descripcion);
                                jug->mochila[NM].alcance=objetos[k].alcance;
                                jug->mochila[NM].coste=objetos[k].coste;
                                jug->mochila[NM].dano=objetos[k].dano;
                                strcpy(jug->mochila[NM].tipo,objetos[k].tipo);
                                jug->mochila[NM].cantidad=objetos[k].cantidad;

                                printf("//Objeto añadido con exito//\n");
                            } else {
                                //Mochila llena
                                printf("\nSu mochila esta llena\n¿Desea comprar el objeto sustituyendolo por uno suyo?[s/n]:");
                                scanf("%c",&p);

                                switch(p) {
                                //Si sustituimos
                                case 's' :
                                    //Muestra tus objetos = j
                                    for(j=0; j<jug->num_objetos; j++) {

                                        printf("\nEstos son tus objeto:\n");

                                        printf("%d.%s:\n",n,jug->mochila[j].identificadorobjeto);
                                        printf(" Tipo: %s\n",jug->mochila[j].tipo);
                                        printf(" Alcance: %f\n",jug->mochila[j].alcance);
                                        printf(" Dano: %i\n",jug->mochila[j].dano);
                                        printf(" Coste: %i\n",jug->mochila[j].coste);
                                        printf(" Cantidad: %i\n",jug->mochila[j].cantidad);
                                        printf(" Descripcion: %s\n",jug->mochila[j].descripcion);
                                        n++;

                                    }
                                    do {
                                        printf("\n\t¿Que objeto quieres sustituir?(indique la id):");
                                        fgets(u,10,stdin);
                                        fflush(stdin);

                                        //Busca el objeto usando la id proporcionada= n

                                        for(n=0; n<=jug->num_objetos; n++) {
                                            if(strcmp(u,jug->mochila[n].identificadorobjeto)==0) {

                                                jug->cartera=jug->cartera-objetos[k].coste;

                                                strcpy(jug->mochila[n].identificadorobjeto,objetos[k].identificadorobjeto);
                                                strcpy(jug->mochila[n].descripcion,objetos[k].descripcion);
                                                jug->mochila[n].alcance=objetos[k].alcance;
                                                jug->mochila[n].coste=objetos[k].coste;
                                                jug->mochila[n].dano=objetos[k].dano;
                                                strcpy(jug->mochila[n].tipo,objetos[k].tipo);
                                                jug->mochila[n].cantidad=objetos[k].cantidad;

                                                n=jug->num_objetos;//para que no realice mas iteraciones

                                                z=1;//objeto encontrado
                                            }
                                        }

                                        if(z==0)
                                            printf("\nObjeto no encontrado indique una id valida\n");
                                    } while(z==0);

                                    printf("\nSustitucion realizada\n");

                                    break;



                                //No  queremos
                                case 'n':
                                    printf("\nNo se comprara el objeto y no se le quitara dinero\n");
                                    break;

                                default:
                                    printf("\nNo se comprara el objeto y no se le quitara dinero\n");
                                    break;


                                }

                            }
                        }

                    } else {

                        printf("\nNo tienes suficiente dinero\n");


                    }

                }
            }

        }



        printf("Desea comprar algo mas?[si/no]");
        scanf("%s",c2);

        comp2=compara_palabra(c2,"si","Si");


    } while(comp2==1);


    printf("\n\tSaliendo de la tienda\n");

    system("pause");


}

/** \brief Menu para editar la configuracion de partida
 *
 * \return No devuelve nada
 *
 */

void editar_configuracion() {

    int c,x,comp;
    float x1;
    char c2[2];

    system("cls");

    printf("\n\tConfiguracion Partida\n");
    printf("\n---------------------------------------\n");
    printf(" 1.Tamaño mapa(Radio)\n");
    printf(" 2.Distancia maxima para recoger objeto\n");
    printf(" 3.Distancia para alcanzar a un oponente con el arma por defecto\n");
    printf(" 4.Monedas por defecto\n");
    printf(" 5.Minimo de jugadores\n");
    printf(" 6.Valor del desplazamiento\n");
    printf(" 7.Tamaño mochila\n");
    printf(" 8.Numero de partidas para subir de nivel\n");
    printf(" 9.Maximo acciones por turno\n");
    printf("10.Salir");

    printf("\n\t Su eleccion:");

    scanf("%i",&c);

    do {

        do {
            switch(c) {

            case 1:
                printf("\n\tQue valor desea poner en la opcion 1:");
                scanf("%f",&x1);
                objeto_juego->radio=x1;
                printf("\nCambio realizado\n");
                break;
            case 2:
                printf("\n\tQue valor desea poner en la opcion 2:");
                scanf("%f",&x1);
                objeto_juego->alcance_recoger=x1;
                printf("\nCambio realizado\n");
                break;
            case 3:
                printf("\n\tQue valor desea poner en la opcion 3:");
                scanf("%f",&x1);
                objeto_juego->rango_arma_base=x1;
                printf("\nCambio realizado\n");
                break;
            case 4:
                printf("\n\tQue valor desea poner en la opcion 4:");
                scanf("%i",&x);
                objeto_juego->cartera_defecto=x;
                printf("\nCambio realizado\n");
                break;
            case 5:
                printf("\n\tQue valor desea poner en la opcion 5:");
                scanf("%i",&x);
                objeto_juego->jugadores_min=x;
                printf("\nCambio realizado\n");
                break;
            case 6:
                printf("\n\tQue valor desea poner en la opcion 6:");
                scanf("%f",&x1);
                objeto_juego->tamano_paso=x1;
                printf("\nCambio realizado\n");
                break;
            case 7:
                printf("\n\tQue valor desea poner en la opcion 7:");
                scanf("%i",&x);
                objeto_juego->tamano_mochila=x;
                printf("\nCambio realizado\n");
                break;
            case 8:
                printf("\n\tQue valor desea poner en la opcion 8:");
                scanf("%i",&x);
                objeto_juego->numero_partidas_por_nivel=x;
                printf("\nCambio realizado\n");
                break;
            case 9:
                printf("\n\tQue valor desea poner en la opcion 9:");
                scanf("%i",&x);
                objeto_juego->numero_acciones_por_turno=x;
                printf("\nCambio realizado\n");
                break;
            case 10:

                printf("\nSaliendo....\n");
                break;

            default:
                printf("\nOpcion no valida\n");
                break;

            }

        } while(c<1 && c>10);
        printf("Desea cambiar otra cosa[si|no]");
        scanf("%s",c2);

        comp=compara_palabra(c2,"si","Si");

    } while(comp==1);
}

/** \brief Menu para editar la informacion de los objetos registrados
 *
 * \return No devuelve nada
 *
 */


void editar_objetos() {
    int i,k=0,comp,c,aproved=0,j,m;
    char c1[10],c2[2];

    system("cls");

    printf("\n\tObjetos\n");
    printf("\n---------------------------------------\n");

    for(i=0; i<total_objetos; i++) {
        printf("%d. %s  ",i,objetos[i].identificadorobjeto);

        k++;
        if(k==3) {
            printf("\n");
            k=0;
        }
    }


    do {

        printf("1.Nuevo Objeto\n");
        printf("2.Eliminar Objeto\n");
        printf("3.Salir\n");
        printf("\tSu eleccion:");
        scanf("%d",&c);
        printf("\n");

        switch(c) {
        case 1:
            total_objetos++;
            objetos=(objeto*)realloc(objetos,total_objetos*sizeof(objeto));
            printf("\n\nIntroduzca id:");
            scanf("%s",objetos[total_objetos-1].identificadorobjeto);
            printf("\nIntroduzca descripcion:");
            scanf("%s",objetos[total_objetos-1].descripcion);
            printf("\nIntroduzca tipo:");
            scanf("%s",objetos[total_objetos-1].tipo);
            printf("\nIntroduzca coste:");
            scanf("%i",&objetos[total_objetos-1].coste);
            printf("\nIntroduzca alcance:");
            scanf("%f",&objetos[total_objetos-1].alcance);
            printf("\nIntroduzca dano:");
            scanf("%i",&objetos[total_objetos-1].dano);
            printf("\n");
            objetos[total_objetos].cantidad=1;
            printf("\n\n  Objeto Creado \n");
            break;

        case 2:
            printf("\n\nIntroduzca id:");
            scanf("%s",c1);
            for(j=0; j<total_objetos; j++) {
                if(strcmp(c1,objetos[j].identificadorobjeto)==0) {
                    aproved=1;
                    m=j;
                    j=total_objetos;
                }

            }
            if(aproved==1) {

                strcpy(objetos[m].identificadorobjeto,objetos[j-1].identificadorobjeto);
                strcpy(objetos[m].descripcion,objetos[j-1].descripcion);
                strcpy(objetos[m].tipo,objetos[j-1].tipo);
                objetos[m].alcance=objetos[j-1].alcance;
                objetos[m].dano=objetos[j-1].dano;
                objetos[m].coste=objetos[j-1].coste;
                objetos[m].cantidad=objetos[j-1].cantidad;

                total_objetos--;
                objetos=(objeto*)realloc(objetos,total_objetos*sizeof(objeto));
                printf("\n\n  Objeto Eliminado \n");

            } else {

                printf("\n\n Fallo al borrar el objeto\n");

            }

            break;

        case 3:

            return;

            break;

        }

        printf("Desea cambiar otra cosa[si|no]");

        scanf("%s",c2);

        comp=compara_palabra(c2,"si","Si");

    } while(comp==1);

}

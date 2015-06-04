#ifndef __Lista_h

#define __Lista_h

/*-------------------------------------------------------------------*/

/* "DISENO Y MANEJO DE ESTRUCTURAS DE DATOS EN C" - V. 1.0           */

/* J. Villalobos - Universidad de los Andes (Sept.-1995)             */

/*-------------------------------------------------------------------*/

/* TAD Lista [TipoL]                                                 */

/* TAD Lista - Implementacion #2                                     */

/*-------------------------------------------------------------------*/



/*-------------------------------------------------------------------*/

/*                  ***  ESTRUCTURAS DE DATOS  ***                   */

/*-------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

//#include <malloc.h>



#define TAMLISTA 10



typedef int TipoL;



typedef struct

{ 

  TipoL *info;

  int longitud, ventana;

  int tam;

} TLista, *Lista;



typedef int Ventana;



/*-------------------------------------------------------------------*/

/*               ***  OPERACIONES & COMPLEJIDAD  ***                 */

/*-------------------------------------------------------------------*/



/* Constructora */

Lista inicLista( void );                            /* O ( 1 ) */



/* Modificadoras */

void anxLista( Lista lst, TipoL elem );             /* O ( N ) */

void insLista( Lista lst, TipoL elem );             /* O ( N ) */

void elimLista( Lista lst );                        /* O ( N ) */

void sigLista( Lista lst );                         /* O ( 1 ) */

void primLista( Lista lst );                        /* O ( 1 ) */

void ultLista( Lista lst );                         /* O ( 1 ) */

void posLista( Lista lst, int pos );                /* O ( 1 ) */

void situarLista( Lista lst, Ventana vent );        /* O ( 1 ) */



/* Analizadoras */

TipoL infoLista( Lista lst );                       /* O ( 1 ) */

int longLista( Lista lst );                         /* O ( 1 ) */

int finLista( Lista lst );                          /* O ( 1 ) */

Ventana ventanaLista( Lista lst );                  /* O ( 1 ) */



/* Destructora */

void destruirLista( Lista lst );                    /* O ( 1 ) */



/* Persistencia */

Lista cargarLista( FILE *fp );                      /* O ( N ) */

void salvarLista( Lista lst, FILE *fp );            /* O ( N ) */



/* Depuracion */

void impLista( Lista lst );                         /* O ( N ) */



Lista unionLista(Lista,Lista);

int miembroLista(Lista, TipoL);                   

void copiaLista(Lista,Lista);



/*-------------------------------------------------------------------*/

/*                       ***  ESPECIFICACION  ***                    */

/*--------------------------------------------------------------------



Lista inicLista( void )

{ post: inicLista es una lista vacia }



void anxLista( Lista lst, TipoL elem )

{ post: se ha anexado el elemento elem despues de la ventana en la lista

   lst. Si lst era vacia, ahora tiene un solo elemento: elem }



void insLista( Lista lst, TipoL elem )

{ post: se ha insertado el elemento elem antes de la ventana en la lista

   lst. Si lst era vacia, ahora tiene un solo elemento: elem }



void elimLista( Lista lst )

{ pre: lst no es vacia, la ventana sobre lst esta definida }

{ post: se ha eliminado el elemento que se encontraba en la ventana de la

   lista lst, la ventana ha quedado en la siguiente posicion de la lista }



void sigLista( Lista lst )

{ pre: lst no es vacia, la ventana sobre lst esta definida }

{ post: la ventana de lst se ha desplazado una posicion a la derecha. Si

   la ventana se encontraba en la ultima posicion, queda indefinida }



void primLista( Lista lst )

{ post: la ventana de lst esta en la primera posicion. Si la lista

   es vacia, deja la ventana indefinida }



void ultLista( Lista lst )

{ post: la ventana de lst esta en su ultima posicion. Si la lista

   es vacia, deja la ventana indefinida }



void posLista( Lista lst, int pos )

{ post: se ha colocado la ventana de lst en su pos-esima posicion }



void situarLista( Lista lst, Ventana vent )

{ post: se ha colocado la ventana de lst en vent }



TipoL infoLista( Lista lst )

{ pre: lst no es vacia, la ventana sobre lst esta definida }

{ post: infoLista = contenido de lst en la ventana }



int longLista( Lista lst )

{ post: logLista = longitud de la lista lst }



int finLista( Lista lst )

{ post: finLista = la ventana de lst esta indefinida }



Ventana ventanaLista( Lista lst )

{ post: ventanaLista = ventana actual de lst }



void destruirLista( Lista lst )

{ post: se ha eliminado lst, liberando la memoria que ocupaba }



Lista cargarLista( FILE *fp )

{ pre: el archivo con descriptor fp esta abierto y es estructuralmente

       correcto, de acuerdo con el esquema de persistencia }

{ post: se ha construido la lista que corresponde a la imagen de la

   informacion del archivo}



void salvarLista( Lista lst, FILE *fp )

{ pre: el archivo con descriptor fp esta abierto }

{ post: se ha hecho persistir la lista lst en el archivo con descriptor

   fp de acuerdo con el esquema de persistencia }



void impLista( Lista lst )

{ post: se ha desplegado la informacion de la lista lst por pantalla }



-----------------------------------------------------------------------*/

#endif




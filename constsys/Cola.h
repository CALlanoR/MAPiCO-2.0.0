#ifndef __Cola_h

#define __Cola_h

/*-------------------------------------------------------------------*/

/* "DISENO Y MANEJO DE ESTRUCTURAS DE DATOS EN C" - V. 1.0           */

/* J. Villalobos - Universidad de los Andes (Sept.-1995)             */

/*-------------------------------------------------------------------*/

/* TAD Cola [TipoC]                                                  */

/* TAD Cola -Implementacion #1                                       */

/*-------------------------------------------------------------------*/



/*-------------------------------------------------------------------*/

/*                 ***  ESTRUCTURAS DE DATOS  ***                    */

/*-------------------------------------------------------------------*/



#include "Lista.h"



typedef TipoL TipoC;

typedef Lista Cola;



/*-------------------------------------------------------------------*/

/*                ***  OPERACIONES & COMPLEJIDAD  ***                */

/*-------------------------------------------------------------------*/



/* Inicializadora */

Cola inicCola( void );                               /* O ( 1 ) */



/* Modificadoras */

void adicCola( Cola col, TipoC elem );               /* O ( 1 ) */

void elimCola( Cola col );                           /* O ( 1 ) */



/* Analizadoras */

TipoC infoCola( Cola col );                          /* O ( 1 ) */

int vaciaCola( Cola col );                           /* O ( 1 ) */

int existeElementoCola(Cola col, TipoC elem);        /* O ( N ) */



/* Destructora */

void destruirCola( Cola col );                       /* O ( N ) */



/* Depuracion */

void impCola( Cola col );                            /* O ( N ) */



/*-------------------------------------------------------------------*/

/*                        ***  ESPECIFICACION  ***                   */

/*--------------------------------------------------------------------



Cola inicCola( void )

{ post: inicCola es una cola vacia }



void adicCola( Cola col, TipoC elem )

{ post: adicCola es la cola resultante a adicionar el elemento elem

	a la cola col }



void elimCola( Cola col )

{ pre: la cola col no esta vacia }

{ post: elimCola es la cola resultado de eliminar el primer elemento

	de col }



TipoC infoCola( Cola col )

{ pre: la cola col no esta vacia }

{ post: infoCola es el primer elemento de la cola }



int vaciaCola( Cola col )

{ post: vaciaCola = la cola col esta vacia }



void destruirCola( Cola col )

{ post: la cola col ha sido destruida, liberando la memoria que ocupaba }



void impCola( Cola col )

{ post: se ha desplegado por pantalla la cola col }



-------------------------------------------------------------------*/

#endif


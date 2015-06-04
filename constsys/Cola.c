/*-------------------------------------------------------------------*/

/* "DISENO Y MANEJO DE ESTRUCTURAS DE DATOS EN C" - V. 1.0           */

/* J. Villalobos - Universidad de los Andes (Sept.-1995)             */

/*-------------------------------------------------------------------*/

/* TAD Cola [TipoC]                                                  */

/* TAD Cola - Implementacion #1 (sobre el TAD Lista)                 */

/*-------------------------------------------------------------------*/



#include "Cola.h"



/*-------------------------------------------------------------------*/

/* Inicializadora: Crea una cola vacia                               */

/* Complejidad : O( 1 )                                              */



Cola inicCola( void )

{	return inicLista( );

}



/*-------------------------------------------------------------------*/

/* Modificadora: Agrega un elemento al final de la cola              */

/* Complejidad : O( 1 )                                              */



void adicCola( Cola col, TipoC elem )

{	ultLista( col );

	anxLista( col, elem );

}



/*-------------------------------------------------------------------*/

/* Modificadora: Elimina el primer elemento de la cola               */

/* Complejidad : O( 1 )                                              */



void elimCola( Cola col )

{	primLista( col );

	elimLista( col );

}



/*-------------------------------------------------------------------*/

/* Analizadora: Retorna el primer elemento de la cola                */

/* Complejidad : O( 1 )                                              */



TipoC infoCola( Cola col )

{	primLista( col );

	return infoLista( col );

}



/*-------------------------------------------------------------------*/

/* Analizadora: Informa si la cola se encuentra vacia                */

/* Complejidad : O( 1 )                                              */



int vaciaCola( Cola col )

{	return longLista( col ) == 0;

}



/*-------------------------------------------------------------------*/

/* Analizadora: Informa si elem se encuentra en la cola              */

/* Complejidad : O( N )                                              */

int existeElementoCola( Cola col,TipoC elem )

{

  for(primLista(col);!finLista(col);sigLista(col))

    if(infoLista(col)==elem)

      return 1;

  return 0;

}



/*-------------------------------------------------------------------*/

/* Destructora: Destruye la cola, retornando toda la memoria         */



void destruirCola( Cola col )

{	destruirLista( col );

}



/*-------------------------------------------------------------------*/

/* Depuracion: Imprime el contenido de una cola                      */



void impCola( Cola col )

{	impLista( col );

}


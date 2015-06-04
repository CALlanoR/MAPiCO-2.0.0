/*-------------------------------------------------------------------*/

/* "DISENO Y MANEJO DE ESTRUCTURAS DE DATOS EN C" - V. 1.0           */

/* J. Villalobos - Universidad de los Andes (Sept.-1995)             */

/*-------------------------------------------------------------------*/

/* TAD Lista [TipoL]                                                 */

/* TAD Lista - Implementacion #2 (Vectores)                          */

/*-------------------------------------------------------------------*/

#include "Lista.h"



/*-------------------------------------------------------------------*/

/* Inicializadora: Crea una lista vacia. La ventana es indefinida    */

/* Complejidad:    O( 1 )                                            */



Lista inicLista( void )

{	Lista resp;

	resp = ( Lista )malloc( sizeof( TLista ) );

	if (!resp)

	  {

	    printf("Error en la asignacion de memoria en el archivo Lista.c\n");

	    exit(1);

	  }

	resp->info = ( TipoL *)malloc( TAMLISTA *sizeof( TipoL ) );

	if (!(resp->info))

	  {

	    printf("Error en la asignacion de memoria en el archivo Lista.c\n");

	    exit(1);

	  }

	

	resp->longitud = resp->ventana = 0;

	resp->tam = TAMLISTA;

        return resp;

}



/*-------------------------------------------------------------------*/

/* Modificadora: Coloca el nuevo elemento en la posicion siguiente a */

/*               la ventana. Si la lista es vacia lo coloca de       */

/*               primero en la lista                                 */

/* Complejidad:  O( N )                                              */



void anxLista( Lista lst, TipoL elem )

{	

  int i;

  if ( lst->longitud >= lst->tam )

    {

      lst->info = ( TipoL *)realloc( lst->info, (TAMLISTA+lst->tam) *sizeof( TipoL ) );

      if (!(lst->info))

	{

	  printf("Error en la asignacion de memoria en el archivo Lista.c\n");

	  exit(1);

	}

      (lst->tam)=(lst->tam)+TAMLISTA;

    }

  if ( lst->longitud != 0 )

    for ( i = lst->longitud - 1; i > lst->ventana - 1; i-- )

      lst->info[ i + 1 ] = lst->info[ i ];

  lst->info[ lst->ventana ] = elem;

  lst->ventana++;

  lst->longitud++;

}



/*-------------------------------------------------------------------*/

/* Modificadora: Coloca el nuevo elemento en la posicion anterior a  */

/*               la ventana. Si la lista es vacia lo coloca de       */

/*               primero en la lista                                 */

/* Complejidad:  O( N )                                              */



void insLista( Lista lst, TipoL elem )

{	

  int i;

  if ( lst->longitud >= lst->tam )

    {

      lst->info = ( TipoL *)realloc( lst->info, (TAMLISTA+lst->tam) *sizeof( TipoL ) );

      if (!(lst->info))

	{

	  printf("Error en la asignacion de memoria en el archivo Lista.c\n");

	  exit(1);

	}

      (lst->tam)=(lst->tam)+TAMLISTA;

    }

  if ( lst->longitud == 0 )

    lst->ventana = 1;

  else

    for ( i = lst->longitud - 1; i >= lst->ventana - 1; i-- )

      lst->info[ i + 1 ] = lst->info[ i ];

  lst->info[ lst->ventana - 1 ] = elem;

  lst->longitud++;

}



/*-------------------------------------------------------------------*/

/* Modificadora: Elimina el elemento que se encuentra en la ventana  */

/*               de la lista. La ventana queda sobre el siguiente    */

/*               elemento. Si era el ultimo, la ventana queda        */

/*               indefinida.                                         */

/* Complejidad:  O( N )                                              */



void elimLista( Lista lst )

{	int i;

	for ( i = lst->ventana - 1; i < lst->longitud; i++ )

		lst->info[ i ] = lst->info[ i + 1 ];

	lst->longitud--;

	if ( lst->ventana > lst->longitud )

		lst->ventana = 0;

}



/*-------------------------------------------------------------------*/

/* Modificadora: Mueve una posicion a la derecha la ventana. Si esta */

/*               sobre el ultimo elemento la ventana queda           */

/*               indefinida                                          */

/* Complejidad:  O( 1 )                                              */



void sigLista( Lista lst )

{	if ( lst->ventana == lst->longitud )

		lst->ventana = 0;

	else

		lst->ventana++;

}



/*-------------------------------------------------------------------*/

/* Modificadora: Coloca la ventana sobre el primer elemento          */

/* Complejidad:  O( 1 )                                              */



void primLista( Lista lst )

{	if ( lst->longitud == 0 )

		lst->ventana = 0;

	else

		lst->ventana = 1;

}



/*-------------------------------------------------------------------*/

/* Modificadora: Coloca la ventana sobre el ultimo elemento          */

/* Complejidad:  O( 1 )                                              */



void ultLista( Lista lst )

{	lst->ventana = lst->longitud;

}



/*-------------------------------------------------------------------*/

/* Modificadora: Coloca la ventana sobre una posicion dada           */

/* Complejidad:  O( 1 )                                              */



void posLista( Lista lst, int pos )

{	lst->ventana = pos;

}



/*-------------------------------------------------------------------*/

/* Modificadora: Coloca la ventana en vent                           */

/* Complejidad:	O( 1 )                                               */



void situarLista( Lista lst, Ventana vent )

{	lst->ventana = vent;

}



/*-------------------------------------------------------------------*/

/* Analizadora: Retorna el elemento que se encuentra en la ventana   */

/* Complejidad: O( 1 )                                               */



TipoL infoLista( Lista lst )

{	return lst->info[ lst->ventana - 1 ];

}



/*-------------------------------------------------------------------*/

/* Analizadora: Retorna la longitud de la lista                      */

/* Complejidad: O( 1 )                                               */



int longLista( Lista lst )

{	return lst->longitud;

}



/*-------------------------------------------------------------------*/

/* Analizadora: Indica si la ventana se encuentra indefinida         */

/* Complejidad: O( 1 )                                               */



int finLista( Lista lst )

{	return lst->ventana == 0;

}



/*-------------------------------------------------------------------*/

/* Analizadora: Retorna la ventana                                   */

/* Complejidad:	O( 1 )                                               */



Ventana ventanaLista( Lista lst )

{	return lst->ventana;

}



/*-------------------------------------------------------------------*/

/* Destructora: Retorna la memoria ocupada por una lista             */

/* Complejidad:	O( 1 )                                               */



void destruirLista( Lista lst )

{

  if(lst != NULL)

    {	

      if((lst->info) != NULL)

	{

	  free(lst->info);

	  lst->info=NULL;

	}

      free( lst );

      lst=NULL;

    }

}



/*-------------------------------------------------------------------*/

/* Persistencia: Carga una lista de un archivo                       */

/* Complejidad:	O( N )                                               */



Lista cargarLista( FILE *fp )

{	int longit, elem;

	Lista lst = inicLista( );

	fscanf( fp, "%d", &longit );

	for( ; longit > 0; longit-- )

	{	fscanf( fp, "%d", &elem );

		anxLista( lst, elem );

	}

	return lst;

}



/*-------------------------------------------------------------------*/

/* Persistencia: Salva una lista en un archivo                       */

/* Complejidad:	O( N )                                               */



void salvarLista( Lista lst, FILE *fp )

{	fprintf( fp, "%d\n", longLista( lst ) );

	for( primLista( lst ); !finLista( lst ); sigLista( lst ) )

		fprintf( fp, "%d\n", infoLista( lst ) );

}



/*-------------------------------------------------------------------*/

/* Depuracion: Imprime el contenido de una lista, mostrando su       */

/*             longitud y la posicion de la ventana                  */



void impLista( Lista lst )

{	int i;



	/* Imprime la longitud */

	printf( "\n[%d] < ", lst->longitud );

	/* Recorre la lista imprimiendo sus elementos */

	for ( i = 0; i < lst->longitud; i++ )

	{	/* Indica la posicion de la ventana */

		if ( i == lst->ventana - 1 )

			printf( "[ " );

		printf( "%d ", lst->info[ i ] );

		/* Indica la posicion de la ventana */

		if ( i == lst->ventana - 1 )

			printf( "] " );

	}

	printf( ">" );

	if ( lst->ventana == 0 )

		printf( " *" );

	printf( "\n" );

}





Lista unionLista(Lista lst1,Lista lst2)

{

    int tamlst1,tamlst2;

    Lista resp=inicLista();



    tamlst1=longLista(lst1);

    tamlst2=longLista(lst2);

    primLista(lst1);

    primLista(lst2);

    while(1)

	{

	  if(!finLista(lst1) && !finLista(lst2))

	    {

	      if(infoLista(lst1) <= infoLista(lst2))

		{

		  anxLista(resp,infoLista(lst1));

		  sigLista(lst1);

		}

	      else

		{

		  anxLista(resp,infoLista(lst2));

		  sigLista(lst2);

		}

	    }

	  else

	    {

	      for(;!finLista(lst1);sigLista(lst1))

		anxLista(resp,infoLista(lst1));

	      for(;!finLista(lst2);sigLista(lst2))

		anxLista(resp,infoLista(lst2));

	      break;

	    }

	}

    return resp;

}



int miembroLista(Lista lst, TipoL elem)

{

  int pos;

  pos=0;

  for(primLista(lst);!finLista(lst);sigLista(lst))

    {

      pos++;

      if(infoLista(lst)==elem)

	return pos;

    }

  posLista(lst, pos);

  pos=0;

  return pos;

}



void copiaLista(Lista resp, Lista lst)

{

  for( primLista( lst ); !finLista( lst ); sigLista( lst ) )

    anxLista(resp,infoLista( lst ) );

}

/*-------------------------------------------------------------------*/


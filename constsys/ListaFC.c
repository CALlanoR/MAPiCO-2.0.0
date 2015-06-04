/*-------------------------------------------------------------------*/
/* "DISENO Y MANEJO DE ESTRUCTURAS DE DATOS EN C" - V. 1.0           */
/* J. Villalobos - Universidad de los Andes (Sept.-1995)             */
/*-------------------------------------------------------------------*/
/* TAD ListaFC [TipoLFC]                                                 */
/* TAD ListaFC - Implementacion #2 (Vectores)                          */
/*-------------------------------------------------------------------*/
#include "ListaFC.h"

/*-------------------------------------------------------------------*/
/* Inicializadora: Crea una lista vacia. La ventana es indefinida    */
/* Complejidad:    O( 1 )                                            */

ListaFC inicListaFC( void )
{
  int i;	
  ListaFC resp;
  resp = ( ListaFC )malloc( sizeof( TListaFC ) );
  if (!resp)
    {
      printf("Error en la asignacion de memoria en el archivo ListaFC.c\n");
      exit(1);
    }
  resp->info = ( TipoLFC *)malloc( TAMLISTAFC *sizeof( TipoLFC ) );
  if (!(resp->info))
    {
      printf("Error en la asignacion de memoria en el archivo ListaFC.c\n");
      exit(1);
    }
  
  for(i=0;i<TAMLISTAFC;i++)
    (resp->info)[i]=NULL;

  resp->longitud = resp->ventana = 0;
  resp->tam = TAMLISTAFC;
  return resp;
}

/*-------------------------------------------------------------------*/
/* Modificadora: Coloca el nuevo elemento en la posicion siguiente a */
/*               la ventana. Si la lista es vacia lo coloca de       */
/*               primero en la lista                                 */
/* Complejidad:  O( N )                                              */

void anxListaFC( ListaFC lst, TipoLFC elem )
{	
  int i;
  if ( lst->longitud >= lst->tam )
    {

      lst->info = ( TipoLFC *)realloc( lst->info, (TAMLISTAFC+(lst->tam)) * sizeof( TipoLFC ) );
      if (!(lst->info))
	{
	  printf("Error en la asignacion de memoria en el archivo ListaFC.c\n");
	  exit(1);
	}

      for(i=(lst->tam);i<((lst->tam)+TAMLISTAFC);i++)
	(lst->info)[i]=NULL;
      
      (lst->tam)=(lst->tam)+TAMLISTAFC;
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

void insListaFC( ListaFC lst, TipoLFC elem )
{	
  int i;
  if ( lst->longitud >= lst->tam )
    {
      lst->info = ( TipoLFC *)realloc( lst->info, (TAMLISTAFC+lst->tam) *sizeof( TipoLFC ) );
      if (!(lst->info))
	{
	  printf("Error en la asignacion de memoria en el archivo ListaFC.c\n");
	  exit(1);
	}

      for(i=(lst->tam);i<((lst->tam)+TAMLISTAFC);i++)
	(lst->info)[i]=NULL;
      
      (lst->tam)=(lst->tam)+TAMLISTAFC;
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

void elimListaFC( ListaFC lst )
{	
  int i;

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

void sigListaFC( ListaFC lst )
{	if ( lst->ventana == lst->longitud )
		lst->ventana = 0;
	else
		lst->ventana++;
}

/*-------------------------------------------------------------------*/
/* Modificadora: Coloca la ventana sobre el primer elemento          */
/* Complejidad:  O( 1 )                                              */

void primListaFC( ListaFC lst )
{	if ( lst->longitud == 0 )
		lst->ventana = 0;
	else
		lst->ventana = 1;
}

/*-------------------------------------------------------------------*/
/* Modificadora: Coloca la ventana sobre el ultimo elemento          */
/* Complejidad:  O( 1 )                                              */

void ultListaFC( ListaFC lst )
{	lst->ventana = lst->longitud;
}

/*-------------------------------------------------------------------*/
/* Modificadora: Coloca la ventana sobre una posicion dada           */
/* Complejidad:  O( 1 )                                              */

void posListaFC( ListaFC lst, int pos )
{	lst->ventana = pos;
}

/*-------------------------------------------------------------------*/
/* Modificadora: Coloca la ventana en vent                           */
/* Complejidad:	O( 1 )                                               */

void situarListaFC( ListaFC lst, VentanaFC vent )
{	lst->ventana = vent;
}

/*-------------------------------------------------------------------*/
/* Analizadora: Retorna el elemento que se encuentra en la ventana   */
/* Complejidad: O( 1 )                                               */

TipoLFC infoListaFC( ListaFC lst )
{	return lst->info[ lst->ventana - 1 ];
}

/*-------------------------------------------------------------------*/
/* Analizadora: Retorna la longitud de la lista                      */
/* Complejidad: O( 1 )                                               */

int longListaFC( ListaFC lst )
{	return lst->longitud;
}

/*-------------------------------------------------------------------*/
/* Analizadora: Indica si la ventana se encuentra indefinida         */
/* Complejidad: O( 1 )                                               */

int finListaFC( ListaFC lst )
{	return lst->ventana == 0;
}

/*-------------------------------------------------------------------*/
/* Analizadora: Retorna la ventana                                   */
/* Complejidad:	O( 1 )                                               */

VentanaFC ventanaListaFC( ListaFC lst )
{	return lst->ventana;
}

/*-------------------------------------------------------------------*/
/* Destructora: Retorna la memoria ocupada por una lista             */
/* Complejidad:	O( 1 )                                               */

void destruirListaFC( ListaFC lst )
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
/* Depuracion: Imprime el contenido de una lista, mostrando su       */
/*             longitud y la posicion de la ventana                  */

void impListaFC( ListaFC lst )
{	int i;

	/* Imprime la longitud */
	printf( "\n[%d] < ", lst->longitud );
	/* Recorre la lista imprimiendo sus elementos */
	for ( i = 0; i < lst->longitud; i++ )
	{	/* Indica la posicion de la ventana */
		if ( i == lst->ventana - 1 )
			printf( "[ " );
		ImprimirFrameConst((lst->info)[ i ]);
		/* Indica la posicion de la ventana */
		if ( i == lst->ventana - 1 )
			printf( "] " );
	}
	printf( ">" );
	if ( lst->ventana == 0 )
		printf( " *" );
	printf( "\n" );
}

/*---------------------------------------------------------------------*/
/* Modificadora: Actualiza el info del elemento que esta en  la ventana*/
/* Complejidad:  O( 1 )                                                */
ListaFC actinfoListaFC(ListaFC lst,TipoLFC elem)
{  
  (lst->info)[(lst->ventana)-1]=elem;  
  return lst;
}

/*---------------------------------------------------------------------*/
/* Modificadora: Adiciona al final de la lista                         */
/* Complejidad:  O( N )                                                */
void adicListaFC(ListaFC lst, TipoLFC elem)
{
  posListaFC(lst,longListaFC(lst));
  anxListaFC(lst,elem);
}

/*-------------------------------------------------------------------*/

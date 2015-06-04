#ifndef __ListaFC_h
#define __ListaFC_h
/*-------------------------------------------------------------------*/
/* "DISENO Y MANEJO DE ESTRUCTURAS DE DATOS EN C" - V. 1.0           */
/* J. Villalobos - Universidad de los Andes (Sept.-1995)             */
/*-------------------------------------------------------------------*/
/* TAD Lista [TipoLFC]                                                 */
/* TAD Lista - Implementacion #2                                     */
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/*                  ***  ESTRUCTURAS DE DATOS  ***                   */
/*-------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
//#include <malloc.h>
#include "FrameConst.h"

#define TAMLISTAFC 20

typedef FrameConst TipoLFC;

typedef struct
{ 
  TipoLFC *info;
  int longitud, ventana;
  int tam;
} TListaFC, *ListaFC;

typedef int VentanaFC;

/*-------------------------------------------------------------------*/
/*               ***  OPERACIONES & COMPLEJIDAD  ***                 */
/*-------------------------------------------------------------------*/

/* Constructora */
ListaFC inicListaFC( void );                            /* O ( 1 ) */

/* Modificadoras */
void anxListaFC( ListaFC lst, TipoLFC elem );             /* O ( N ) */
void insListaFC( ListaFC lst, TipoLFC elem );             /* O ( N ) */
void elimListaFC( ListaFC lst );                        /* O ( N ) */
void sigListaFC( ListaFC lst );                         /* O ( 1 ) */
void primListaFC( ListaFC lst );                        /* O ( 1 ) */
void ultListaFC( ListaFC lst );                         /* O ( 1 ) */
void posListaFC( ListaFC lst, int pos );                /* O ( 1 ) */
void situarListaFC( ListaFC lst, VentanaFC vent );        /* O ( 1 ) */

/* Analizadoras */
TipoLFC infoListaFC( ListaFC lst );                       /* O ( 1 ) */
int longListaFC( ListaFC lst );                         /* O ( 1 ) */
int finListaFC( ListaFC lst );                          /* O ( 1 ) */
VentanaFC ventanaListaFC( ListaFC lst );                  /* O ( 1 ) */

/* Destructora */
void destruirListaFC( ListaFC lst );                    /* O ( 1 ) */

/* Depuracion */
void impListaFC( ListaFC lst );                         /* O ( N ) */

ListaFC actinfoListaFC(ListaFC,TipoLFC);
void adicListaFC(ListaFC, TipoLFC);

/*-------------------------------------------------------------------*/
/*                       ***  ESPECIFICACION  ***                    */
/*--------------------------------------------------------------------

ListaFC inicListaFC( void )
{ post: inicListaFC es una lista vacia }

void anxListaFC( ListaFC lst, TipoLFC elem )
{ post: se ha anexado el elemento elem despues de la ventana en la lista
	lst. Si lst era vacia, ahora tiene un solo elemento: elem }

void insListaFC( ListaFC lst, TipoLFC elem )
{ post: se ha insertado el elemento elem antes de la ventana en la lista
	lst. Si lst era vacia, ahora tiene un solo elemento: elem }

void elimListaFC( ListaFC lst )
{ pre: lst no es vacia, la ventana sobre lst esta definida }
{ post: se ha eliminado el elemento que se encontraba en la ventana de la
	lista lst, la ventana ha quedado en la siguiente posicion de la lista }

void sigListaFC( ListaFC lst )
{ pre: lst no es vacia, la ventana sobre lst esta definida }
{ post: la ventana de lst se ha desplazado una posicion a la derecha. Si
	la ventana se encontraba en la ultima posicion, queda indefinida }

void primListaFC( ListaFC lst )
{ post: la ventana de lst esta en la primera posicion. Si la lista
	es vacia, deja la ventana indefinida }

void ultListaFC( ListaFC lst )
{ post: la ventana de lst esta en su ultima posicion. Si la lista
	es vacia, deja la ventana indefinida }

void posListaFC( ListaFC lst, int pos )
{ post: se ha colocado la ventana de lst en su pos-esima posicion }

void situarListaFC( ListaFC lst, VentanaFC vent )
{ post: se ha colocado la ventana de lst en vent }

TipoLFC infoListaFC( ListaFC lst )
{ pre: lst no es vacia, la ventana sobre lst esta definida }
{ post: infoListaFC = contenido de lst en la ventana }

int longListaFC( ListaFC lst )
{ post: logListaFC = longitud de la lista lst }

int finListaFC( ListaFC lst )
{ post: finListaFC = la ventana de lst esta indefinida }

VentanaFC ventanaListaFC( ListaFC lst )
{ post: ventanaListaFC = ventana actual de lst }

void destruirListaFC( ListaFC lst )
{ post: se ha eliminado lst, liberando la memoria que ocupaba }

ListaFC cargarListaFC( FILE *fp )
{ pre: el archivo con descriptor fp esta abierto y es estructuralmente
       correcto, de acuerdo con el esquema de persistencia }
{ post: se ha construido la lista que corresponde a la imagen de la
	informacion del archivo}

void salvarListaFC( ListaFC lst, FILE *fp )
{ pre: el archivo con descriptor fp esta abierto }
{ post: se ha hecho persistir la lista lst en el archivo con descriptor
	fp de acuerdo con el esquema de persistencia }

void impListaFC( ListaFC lst )
{ post: se ha desplegado la informacion de la lista lst por pantalla }

-----------------------------------------------------------------------*/
#endif


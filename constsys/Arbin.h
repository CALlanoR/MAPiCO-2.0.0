#ifndef __Arbin_h_
#define __Arbin_h_
/*-------------------------------------------------------------------*/
/* "DISENO Y MANEJO DE ESTRUCTURAS DE DATOS EN C" - V. 1.0           */
/* J. Villalobos - Universidad de los Andes (Sept.-1995)             */
/*-------------------------------------------------------------------*/
/* TAD Arbin [TipoA]                                                 */
/* TAD Arbin - Implementacion #2 (Encadenamiento al padre)           */
/*-------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
//#include <malloc.h>
/*-------------------------------------------------------------------*/
/*                 ***  ESTRUCTURAS DE DATOS  ***                    */
/*-------------------------------------------------------------------*/

#define LEFT 0
#define RIGHT 1

typedef struct
{
  int tipo;
  int valor;
}TipoA;

typedef struct NodoArbin
{	TipoA info;
	struct NodoArbin *izq,*der;
} TArbin,*Arbin;

typedef TArbin TFrameConst;
typedef Arbin FrameConst;


/*-------------------------------------------------------------------*/
/*                  ***  OPERACIONES & COMPLEJIDAD  ***              */
/*-------------------------------------------------------------------*/
/* Inicializadora*/
Arbin inicArbin(int,int);
Arbin inicpArbin(Arbin);

/* Analizadoras */
#define izqArbin( _a )   (_a)->izq              /* O ( 1 ) */

#define derArbin( _a )   (_a)->der              /* O ( 1 ) */

#define raizArbin( _a )  (_a)->info             /* O ( 1 ) */

#define vacioArbin( _a ) ( (_a) == NULL )       /* O ( 1 ) */

/* Modificadoras*/
void insertArbin(Arbin, Arbin, int);           /* O ( 1 ) */

/* Destructora */
void destruirArbin( Arbin a );                /* O ( N ) */

void imprimirArbin(Arbin a);
#endif

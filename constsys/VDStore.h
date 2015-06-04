#ifndef _VDStore_h
#define _VDStore_h
/****************************************************************
* INTERFAZ MODULO: VDStore.
* FECHA CREACION:  22-Mar-01
* REQUERIMIENTOS:  FDVariable.h
*
* AUTORES:         CATHERINE GARIA
*                  ALEJANDRA MARIA VASQUEZ
* MODIFICACIONES:
* AUTOR FECHA:
*
*****************************************************************/

/*--------------------------------------------------------------*
         Archivos de Interfaz de librerias estandar
 *--------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include "FDVariable.h"
//#include <malloc.h>
/*--------------------------------------------------------------*
         Declaracion  de Constantes y Macros publicos
 *--------------------------------------------------------------*/
#define TAMINICSTORE 300 /* tamaño inicial de store. */
#define TAMINICTEMPSTORE  30/* tamaño inicial de store de las variables temporales modelo Carlsson. */
#define INCSTORE 100 /* Incremento para el realloc del store */
#define INCTEMPSTORE 5 /* Incremento para el realloc del store */
/*--------------------------------------------------------------*
  Declaracion de struct's, union's, enum's y typedef's publicos
 *--------------------------------------------------------------*/
typedef struct 
{  
  FDVariable *variables; /* vector dinamico que contiene las variables del store*/
  int position; /* posicion hasta donde existen variables en el vector variables */
  int size; /* Tamaño del vector de variables */
  FDVariable *tempvariables; /* vector dinamico que contiene las variables temporales del Modelo de Carlsson*/
  int tempsize; /* Indice del vector de variables temporales */
}TVDStore,*VDStore;

typedef VDStore Store;
/*--------------------------------------------------------------*
         Declaracion  de variables publicas
 *--------------------------------------------------------------*/

/*--------------------------------------------------------------*
         Prototipo de las funciones publicas
 *--------------------------------------------------------------*/
VDStore InicVDStore(void);
VDStore InicpVDStore(Store);
Store putVDStore(Store, int, FDVariable);
Store puttempVDStore(Store, int, FDVariable);
FDVariable  getVDStore(Store, int);
FDVariable  gettempVDStore(Store, int);
int getsizeVDStore(Store);
int gettempsizeVDStore(Store);
int getpositionVDStore(Store);
void ImprimirVDStore(Store);
void freeVDStore(Store);
#endif

/****EOF****/

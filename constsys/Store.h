#ifndef _Store_h
#define _Store_h
/****************************************************************
* INTERFAZ MODULO: Store.
* FECHA CREACION:  17-Mar-01
* REQUERIMIENTOS:  VDStore.h
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
#include "VDStore.h"
/*--------------------------------------------------------------*
         Declaracion  de Constantes y Macros publicos
 *--------------------------------------------------------------*/
/*--------------------------------------------------------------*
  Declaracion de struct's, union's, enum's y typedef's publicos
 *--------------------------------------------------------------*/
/*--------------------------------------------------------------*
         Declaracion  de variables publicas
 *--------------------------------------------------------------*/
/*--------------------------------------------------------------*
         Prototipo de las funciones publicas
 *--------------------------------------------------------------*/
Store inicStore(void);
Store inicpStore(Store);
Store insertVariableStore(Store,int,FDVariable);
int updateVarDomStore(Store, int, Domain);
Store updateVarStampStore(Store, int, int);
FDVariable getVariableStore(Store,int);
int isDeterminatedStore(Store,int);
Store desrefVariableDepStore(Store, int);
void ImprimirStore(Store);
void freeStore(Store);
#endif

/****EOF****/


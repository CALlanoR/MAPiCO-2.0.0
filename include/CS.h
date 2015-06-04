#ifndef _CS_h
#define _CS_h
/****************************************************************
* INTERFAZ MODULO: ConstraintSystem.
* FECHA CREACION:  12-Mar-01
* REQUERIMIENTOS:  
*                  stdlib.h
*                  stdio.h
*                  malloc.h
*                  FrameConst.h
*                  AskTell.h
*                  AritToIndex.h
*                  Indexicals.h
*                  Store.h
*                  Monotonicity.h
*                  Cola.h
*                  FDEmulator.h
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
//#include <malloc.h>
#include "FrameConst.h"
#include "AskTell.h"
#include "AritToIndex.h" 
#include "Indexicals.h"
#include "Store.h"
#include "Monotonicity.h"
#include "Cola.h"
#include "FDEmulator.h"
/*--------------------------------------------------------------*
         Declaracion  de Constantes y Macros publicos
 *--------------------------------------------------------------*/

/*--------------------------------------------------------------*
  Declaracion de struct's, union's, enum's y typedef's publicos
 *--------------------------------------------------------------*/
typedef int Stamp;

/*--------------------------------------------------------------*
         Declaracion  de variables publicas
 *--------------------------------------------------------------*/

/*--------------------------------------------------------------*
         Prototipo de las funciones publicas
 *--------------------------------------------------------------*/
int tell(Store,Indexicals,Stamp *,int *,FrameConst);
int basicTell(Store,Indexicals,Stamp *,int *,FrameConst);
int VariableCheck(Store,Indexicals,Stamp *,Cola);
Lista suspended(Store, int);
int ask(Store,Indexicals,Stamp *,FrameConst);
int basicAsk(Store, Indexicals, Stamp *, FrameConst);
int entailmentCheck(Store, Indexical);

#endif

/****EOF****/


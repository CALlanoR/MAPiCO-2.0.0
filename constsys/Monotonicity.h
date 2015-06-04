#ifndef _Monotonicity_h
#define _Monotonicity_h
/****************************************************************
* INTERFAZ MODULO: Monotonicity.
* FECHA CREACION:  22-Mar-01
* REQUERIMIENTOS:  Range.h
*                  FrameConst.h
*                  Lista.h
*                  Monotonicity.h
*                  Store.h   
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
#include "Range.h"
#include "FrameConst.h" 
#include "Lista.h"
#include "Store.h"
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
int Monotonicity(FrameConst,Store);
void frameToA(Lista, FrameConst);
void frameToM(Lista, FrameConst);
void frameToS(Lista, FrameConst);
void frameToG(Lista, FrameConst);
#endif

/****EOF****/

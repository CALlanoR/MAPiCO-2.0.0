#ifndef _FrameConst_h_
#define _FrameConst_h_
/****************************************************************
* INTERFAZ MODULO: FrameConst.
* FECHA CREACION:  29-Mar-01
* REQUERIMIENTOS: 
*                  stdio.h
*                  stdlib.h
*                  ValueFrameConst.h
*                  TypeFrameConst.h
*                  Arbin.h
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
#include <stdio.h>
#include <stdlib.h>
#include "ValueFrameConst.h"
#include "TypeFrameConst.h"
#include "Arbin.h"
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
FrameConst InicFrameConst(int, int);
FrameConst InicpFrameConst(FrameConst);
void insertSonFrameConst(FrameConst, FrameConst, int);
FrameConst getLefSonFrameConst(FrameConst);
FrameConst getRigSonFrameConst(FrameConst);
TipoA getInfoFrameConst(FrameConst);
int getTypeFrameConst(FrameConst);
int getValueFrameConst(FrameConst);
void setLefSonFrameConst(FrameConst, FrameConst);
void setRigSonFrameConst(FrameConst, FrameConst);
int EsNegativoFrameConst(FrameConst);
int EsLinealFrameConst(FrameConst);
FrameConst CeilFrameConst (FrameConst);
FrameConst FloorFrameConst (FrameConst);
FrameConst ComplementFrameConst (FrameConst);
FrameConst SupremoFrameConst(FrameConst);
FrameConst InfimoFrameConst(FrameConst);
int NumConstFrameConst(FrameConst);
void DestruirFrameConst(FrameConst);
void ImprimirFrameConst(FrameConst);
#endif


#ifndef _AritToIndex_h
#define _AritToIndex_h
/****************************************************************
* INTERFAZ MODULO: AritToIndex.
* FECHA CREACION:  27-Mar-01
* REQUERIMIENTOS: ListaFC.h
*                 FrameConst.h
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
#include "ListaFC.h"
#include "FrameConst.h"
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
ListaFC IndexNecAritToIndex(ListaFC,int *,FrameConst);
FrameConst IndexSufAritToIndex(FrameConst);
FrameConst ConstToIndexSufAritToIndex(FrameConst);
ListaFC ConstToIndexNecAritToIndex(ListaFC, FrameConst, int*); 
ListaFC NormalNecAritToIndex(ListaFC, FrameConst);
FrameConst NormalSufAritToIndex (FrameConst);
ListaFC EquivalentAritToIndex(ListaFC);
FrameConst OrdIzqAritToIndex(FrameConst);
#endif
/****EOF****/

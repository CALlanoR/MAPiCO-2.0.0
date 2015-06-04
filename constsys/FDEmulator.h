#ifndef _FDEmulator_h
#define _FDEmulator_h
/****************************************************************
* INTERFAZ MODULO: FDEmulator.
* FECHA CREACION: 04-Abr-01
* REQUERIMIENTOS: 
*                 stdio.h
*                 stdlib.h
*                 Store.h
*                 malloc.h
*
* AUTORES:         CATHERINE GARCIA
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
#include "Store.h"
//#include <malloc.h>
/*--------------------------------------------------------------*
         Declaracion  de Constantes y Macros publicos
 *--------------------------------------------------------------*/
/*--------------------------------------------------------------*
  Declaracion de struct's, union's, enum's y typedef's publicos
*--------------------------------------------------------------*/
enum Type {Val, Dom, Und};

union Info
{
  int value;
  Domain domain;
};

typedef union Info Info;

struct TFDEmulator
{
  enum Type flagtype;
  Info info;
};

typedef struct TFDEmulator TFDEmulator;

/*--------------------------------------------------------------*
         Declaracion  de variables publicas
 *--------------------------------------------------------------*/
/*--------------------------------------------------------------*
         Prototipo de las funciones publicas
 *--------------------------------------------------------------*/
Domain r_Sigma(Store, Indexical);
#endif
/****EOF****/

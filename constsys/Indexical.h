#ifndef _Indexical_h
#define _Indexical_h
/****************************************************************
* INTERFAZ MODULO: Indexical.
* FECHA CREACION:  20-Mar-01
* REQUERIMIENTOS: 
*                Lista.h
*                Monotonicity.h
*                Dependency.h
*                FrameConst.h
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
#include "Lista.h"
#include "Dependency.h"
#include "FrameConst.h"
#include "FDCompiler.h"
//#include <malloc.h>
/*--------------------------------------------------------------*
         Declaracion  de Constantes y Macros publicos
 *--------------------------------------------------------------*/
#define TAMCODER 25

/*--------------------------------------------------------------*
  Declaracion de struct's, union's, enum's y typedef's publicos
 *--------------------------------------------------------------*/
typedef struct
{
  char ** coder; /* Representacion del Rango Compilado */
  int tamcoder; /* Tamaño del vector dinamico coder*/
  FrameConst codef; /* Representacion del Rango como un FrameConst */
  int x; /* Identificador de la variable dentro del store */
  int stamp; /* Registra la ultima vez que se ejecuto un indexical  */
  int entailed; /* Determina si el indexical es deducido o no */
//  int monotonicity; /* Determina la monotonicidad del rango */
}TIndexical,*Indexical;

/*--------------------------------------------------------------*
         Declaracion  de variables publicas
 *--------------------------------------------------------------*/

/*--------------------------------------------------------------*
         Prototipo de las funciones publicas
 *--------------------------------------------------------------*/
Indexical InicIndexical(void);
Indexical InicpIndexical(FrameConst, int);
char ** getCoder(Indexical);
int getTamCoder(Indexical);
FrameConst getCodef(Indexical);
int getX(Indexical);
int getStamp(Indexical);
int getEntailed(Indexical);
Lista getVariablesIndexical(Indexical);
void setCoder(Indexical,char **,int);
void setTamCoder(Indexical, int);
void setCodef(Indexical, FrameConst);
void setX(Indexical, int);
void setStamp(Indexical, int);
void setEntailed(Indexical, int);
void setMonotonicity(Indexical, int);
int DependencyType(Indexical, int);
void freeIndexical(Indexical);
#endif

/****EOF****/

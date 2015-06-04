#ifndef _Indexicals_h
#define _Indexicals_h
/****************************************************************
* INTERFAZ MODULO: Indexicals.
* FECHA CREACION:  24-Mar-01
* REQUERIMIENTOS:  Indexical.h
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
#include <stdlib.h>
#include <stdio.h>
//#include <malloc.h>
#include "Indexical.h"
#include "FDCompiler.h"
/*--------------------------------------------------------------*
         Declaracion  de Constantes y Macros publicos
 *--------------------------------------------------------------*/
#define TAMININDEXICALS 600
/*--------------------------------------------------------------*
  Declaracion de struct's, union's, enum's y typedef's publicos
 *--------------------------------------------------------------*/
typedef struct 
{
  Indexical *VDIndexicals; /* vector dinamico que contiene todos los indexical a 
			   *  ser evaluados en el store 
			   */
  int size; /* Indice del vector dinamico, adicionalmente informa del tamaño
		 *  del mismo
		*/
 }TIndexicals,*Indexicals;

/*--------------------------------------------------------------*
         Declaracion  de variables publicas
 *--------------------------------------------------------------*/
/*--------------------------------------------------------------*
         Prototipo de las funciones publicas
 *--------------------------------------------------------------*/
Indexicals InicIndexicals(void);
Indexicals InicpIndexicals(Indexicals);
int sizeIndexicals(Indexicals);
Indexical elementAtIndexicals(Indexicals,int);
Indexicals addElementIndexicals(Indexicals,Indexical);
Indexicals removeElementAtIndexicals(Indexicals, int);
Indexicals setElementAtIndexicals(Indexicals, Indexical, int);
void freeIndexicals(Indexicals); 
#endif

/****EOF****/

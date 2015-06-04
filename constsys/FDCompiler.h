#ifndef _FDCompiler_h
#define _FDCompiler_h
/****************************************************************
* INTERFAZ MODULO: FDCompiler.
* FECHA CREACION:  27-Mar-01
* REQUERIMIENTOS: 
*                  stdio.h
*                  stdlib.h
*                  malloc.h
*                  string.h
*                  TypeFrameConst.h
*                  Indexical.h
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
//#include <malloc.h>
#include <string.h>
#include "TypeFrameConst.h"
#include "Indexical.h"

/*--------------------------------------------------------------*
         Declaracion  de Constantes y Macros publicos
 *--------------------------------------------------------------*/
#define TAMAUX 17
/*--------------------------------------------------------------*
  Declaracion de struct's, union's, enum's y typedef's publicos
 *--------------------------------------------------------------*/
/*--------------------------------------------------------------*
         Declaracion  de variables publicas
 *--------------------------------------------------------------*/
/*--------------------------------------------------------------*
         Prototipo de las funciones publicas
 *--------------------------------------------------------------*/
char ** translate(FrameConst, char **, int *);
char ** addElement(char **, char *, int *);
#endif


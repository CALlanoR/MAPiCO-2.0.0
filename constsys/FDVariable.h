#ifndef _FDVariable_h
#define _FDVariable_h
/****************************************************************
* INTERFAZ MODULO: FDVariable.
* FECHA CREACION:  21-Mar-01
* REQUERIMIENTOS:  
*                  Lista.h
*                  Domain.h
*                  Indexicals.h
*                  stdlib.h
*                  stdio.h
*                  malloc.h
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
#include "Lista.h"
#include "Domain.h"
#include "Indexicals.h"
#include <stdlib.h>
#include <stdio.h>
//#include <malloc.h>
/*--------------------------------------------------------------*
         Declaracion  de Constantes y Macros publicos
 *--------------------------------------------------------------*/
/*--------------------------------------------------------------*
  Declaracion de struct's, union's, enum's y typedef's publicos
 *--------------------------------------------------------------*/
typedef struct 
{
  Lista Chain_Val; /* Lista de dependencias de valor */
  Lista Chain_Dom; /* Lista de dependencias de dominio */
  Lista Chain_Min; /* Lista de dependencias de minimo */
  Lista Chain_Max; /* Lista de dependencias de maximo */
  Lista Chain_MinMax; /* Lista de dependencias de minimo y maximo */
  Domain domain; /* Dominio de la variable*/
  int Time_Stamp; /* Registro de tiempo de la ultima modificación de la variable*/ 
}TFDVariable,*FDVariable;

/*--------------------------------------------------------------*
         Declaracion  de variables publicas
 *--------------------------------------------------------------*/
/*--------------------------------------------------------------*
         Prototipo de las funciones publicas
 *--------------------------------------------------------------*/
FDVariable InicFDVariable(void);
FDVariable InicpFDVariable(int,int,Indexicals);
FDVariable Inicp1FDVariable(FDVariable);
Domain getDomainFDVariable(FDVariable);
Lista getChainValFDVariable(FDVariable);
Lista getChainDomFDVariable(FDVariable);
Lista getChainMinFDVariable(FDVariable);
Lista getChainMaxFDVariable(FDVariable);
Lista getChainMinMaxFDVariable(FDVariable);
int getPruneTypeFDVariable(FDVariable);
int getStampFDVariable(FDVariable);
void setPruneTypeFDVariable(FDVariable,int);
void setStampFDVariable(FDVariable,int);
void setChainValFDVariable(FDVariable,Lista);
void setChainDomFDVariable(FDVariable,Lista);
void setChainMinFDVariable(FDVariable,Lista);
void setChainMaxFDVariable(FDVariable,Lista);
void setChainMinMaxFDVariable(FDVariable,Lista);
void setDomainFDVariable(FDVariable,Domain);
void updateDepFDVariable(FDVariable,int, Indexical,int);
void desrefDepFDVariable(FDVariable, int);
int isConsistentFDVariable(FDVariable);
int isDeterminatedFDVariable(FDVariable);
void ImprimirFDVariable(FDVariable);
void freeFDVariable(FDVariable);
#endif

/****EOF****/

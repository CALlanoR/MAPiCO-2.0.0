#ifndef _ValueFrameConst_c_
#define _ValueFrameConst_c_

/****************************************************************
* IMPLEMENTACION MODULO: ValueFrameConst.c
* FECHA CREACION:  22-Mar-01
* DESCRIPCION: 
*   Implementa funciones que invierte relaciones o funciones, 
*   adicionalmente niega las relaciones que se encuentran
*   en las restricciones aritmeticas a evaluar representadas
*   como FrameConst
*
* AUTORES:         CATHERINE GARIA
*                  ALEJANDRA MARIA VASQUEZ
* MODIFICACIONES:
* AUTOR FECHA:
*
*****************************************************************/

/*===============================================================*
  Tabla de Contenido:
  
  0. Instrucciones para compilar el modulo
       gcc -c ValueFrameConst.c

  1. Librerias requeridas para su linkeo:
       -lm -lX11

  2. Listado de estructuras de datos definidas (publicas y privadas)

  3. Listado de funciones definidas (publicas y privadas)
     int InvRel(int)
     int NegRel(int)
     int InvFun(int)
  4. Instruccion para modificar el modulo
  4.1 Construcciones importantes para tener en cuenta (e.g. tipos, variables, funciones)
  4.2 Observaciones Adicionales
  
  ===============================================================*/

/*--------------------------------------------------------------*
  Archivos de Interfaz de librerias estandar y de otros modulos
 *--------------------------------------------------------------*/
#include "ValueFrameConst.h"
/*--------------------------------------------------------------*
         Declaracion  de Constantes y Macros privados
 *--------------------------------------------------------------*/
/*--------------------------------------------------------------*
  Declaracion de struct's, union's, enum's y typedef's privados
 *--------------------------------------------------------------*/
/*--------------------------------------------------------------*
         Declaracion  de variables publicas
 *--------------------------------------------------------------*/
/*--------------------------------------------------------------*
         Declaracion  de variables privadas
 *--------------------------------------------------------------*/
/*--------------------------------------------------------------*
         Prototipo de las funciones privadas
 *--------------------------------------------------------------*/
/*--------------------------------------------------------------*
         Definicion  de las funciones privadas
 *--------------------------------------------------------------*/
int InvRel(int Value)
/*---------------------------------------------------------------
  DESCRIPCION: Invierte la relacion del parametro Value 

  PARAMETROS: Value: Relacion que se va a invertir
  USA:
  RETORNA: Value pero invertido
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  switch (Value)
    {
    case (int)MAY:
      return MEN;
    case MEN:
      return MAY;
    case MAI:
      return MEI;
    case MEI:
      return MAI;
    }
  return Value;
  }

int NegRel(int Value)
/*---------------------------------------------------------------
  DESCRIPCION: Niega la relacion del parametro Value 

  PARAMETROS: Value: Relacion que se va a negar
  USA:
  RETORNA: Value pero negado
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  switch (Value)
    {
    case MAY:
      return MEI;
    case MEN:
      return MAI;
    case MAI:
      return MEN;
    case MEI:
      return MAY; 
    case IGUAL:
      return DIF;
    default: //DIF
      return IGUAL;
    }
}

int InvFun(int Value)
/*---------------------------------------------------------------
  DESCRIPCION: Invierte la funcion del parametro Value 

  PARAMETROS: Value: Funcion que se va a invertir
  USA:
  RETORNA: Value pero Invertido
  PRE: Value = Funcion
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  switch (Value)
    {
    case ADD:
      return SUBS;
    default: //case (int)SUBS:
      return ADD;
    }	 
}

#endif


#ifndef _Monotonicity_c
#define _Monotonicity_c
/****************************************************************
* IMPLEMENTACION MODULO: Monotonicity.c
* FECHA CREACION:  22-Mar-01
* DESCRIPCION: 
*   Implementa los algoritmos de monotinicidad
*
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
       gcc -c Monotonicity.c

  1. Librerias requeridas para su linkeo:
       -lm -lX11

  2. Listado de estructuras de datos definidas (publicas y privadas)

  3. Listado de funciones definidas (publicas y privadas)
     int monotonicity(FrameConst,Store)
     Lista frameToA(FrameConst)
     Lista frameToM(FrameConst)
     Lista frameToS(FrameConst)
     Lista frameToG(FrameConst)

  4. Instruccion para modificar el modulo
  4.1 Construcciones importantes para tener en cuenta (e.g. tipos, variables, funciones)
  4.2 Observaciones Adicionales
  
  ===============================================================*/

/*--------------------------------------------------------------*
  Archivos de Interfaz de librerias estandar y de otros modulos
 *--------------------------------------------------------------*/
#include "Monotonicity.h"
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
int Monotonicity(FrameConst r,Store sigma)
/*---------------------------------------------------------------
  DESCRIPCION: Decide la (anti)monotonicidad de r en sigma
  PARAMETROS: sigma:el store
              r:la representacion de un rango como frameconst
  USA:
  RETORNA: CONSTANT || MONOTONE || ANTIMONOTONE || UNDEFINED
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  int Msigma,Asigma;
  Lista Mr,Ar;
 
  Msigma=0;
  Asigma=0;
  Mr=inicLista();
  Ar=inicLista();

  frameToM(Mr, r);
  frameToA(Ar, r);

  for(primLista(Mr);!finLista(Mr);sigLista(Mr))
    {
      if(!isDeterminatedStore(sigma,infoLista(Mr)))
	{
	  Msigma++;
	  break;
	}
    }
  for(primLista(Ar);!finLista(Ar);sigLista(Ar))
    {
      if(!isDeterminatedStore(sigma,infoLista(Ar)))
	{
	  Asigma++;
	  break;
	}
    }

  destruirLista(Mr);
  destruirLista(Ar);

  if(Msigma==0 && Asigma==0)
    return CONSTANT;
  else 
    if(Msigma==0)
      return MONOTONE;
  else 
    if(Asigma==0)
      return ANTIMONOTONE;
  else 
    return UNDEFINED;
}

void frameToM(Lista res, FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Calcula el conjunto de variables que deben estar 
               determinadas para que f sea un rango monotono
  PARAMETROS:  f:la representacion de un rango como frameconst
               res: Lista donde va a quedar la respuesta.
  USA:
  RETORNA: Lista de variables determinadas con respecto a f para 
           que este sea monotono.
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  int value;

  value=getValueFrameConst(f);

  switch(value)
    {
    case RANGE:
      frameToG(res, getLefSonFrameConst(f));
      frameToS(res, getRigSonFrameConst(f));
      break;
    case DOM:
      break;
    case OR:
    case AND:
    case IMP:
    case SETADD:
    case SETSUB:
      frameToM(res, getLefSonFrameConst(f));
      frameToM(res, getRigSonFrameConst(f));
      break;
    case DIFF:
      frameToM(res, getLefSonFrameConst(f));
      frameToA(res, getRigSonFrameConst(f));
      break;
    case SETMULT:
    case SETDIV:
    case SETMOD:
      frameToM(res, getLefSonFrameConst(f));
      frameToG(res, getRigSonFrameConst(f));
      break;
    }
}

void frameToA(Lista res, FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Calcula el conjunto de variables que deben estar 
               determinadas para que f sea un rango antimonotono
  PARAMETROS:  f:la representacion de un rango como frameconst
               res: Lista donde va a quedar la respuesta.
  USA:
  RETORNA: Lista de variables determinadas con respecto a f para 
           que este sea antimonotono.
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  int value;

  value=getValueFrameConst(f);

  switch(value)
    {
    case RANGE:
      frameToS(res, getLefSonFrameConst(f));
      frameToG(res, getRigSonFrameConst(f));
      break;
    case DOM:
      frameToG(res, getLefSonFrameConst(f));
      break;
    case OR:
    case AND:
    case IMP:
    case SETADD:
    case SETSUB:
      frameToA(res, getLefSonFrameConst(f));
      frameToA(res, getRigSonFrameConst(f));
      break;
    case DIFF:
      frameToA(res, getLefSonFrameConst(f));
      frameToM(res, getRigSonFrameConst(f));
      break;
    case SETMULT:
    case SETDIV:
    case SETMOD:
      frameToA(res, getLefSonFrameConst(f));
      frameToG(res, getRigSonFrameConst(f));
      break;
    }
}

void frameToS(Lista res, FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Especifica el conjunto de variables del frameconst
               f que deben determinarse para que t_sigma <= t�_sigma
               donde sigma >= sigma'
  PARAMETROS:  f:la representacion de un rango como frameconst
               res: Lista donde va a quedar la respuesta.
  USA:
  RETORNA: Lista de variables determinadas con respecto a f para 
           que t_sigma <= t�_sigma donde sigma >= sigma'.
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  int value,type;

  value=getValueFrameConst(f);
  type=getTypeFrameConst(f);
  switch(type)
    {
    case CONSTANTE:
      break;
    case VARIABLE:
      anxLista(res,value);
      break;
    case FUNCION:
      switch(value)
	{
	case ADD:
	case MULT:
	case MOD:
	  frameToS(res, getLefSonFrameConst(f));
	  frameToS(res, getRigSonFrameConst(f));
	  break;
	
	case SUBS:
	case DIV:
	  frameToS(res, getLefSonFrameConst(f));
	  frameToG(res, getRigSonFrameConst(f));
	  break;
	case MIN:
	  frameToG(res, getLefSonFrameConst(f));
	  break;
	case MAX:
	  break;
	}
      break;
    }
}

void frameToG(Lista res, FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Especifica el conjunto de variables del frameconst
               f que deben determinarse para que t_sigma <= t�_sigma
               donde sigma <= sigma'
  PARAMETROS:  f:la representacion de un rango como frameconst
               res: Lista donde va a quedar la respuesta.
  USA:
  RETORNA: Lista de variables determinadas con respecto a f para 
           que t_sigma <= t�_sigma donde sigma <= sigma'.
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  int value,type;

  value=getValueFrameConst(f);
  type=getTypeFrameConst(f);
  switch(type)
    {
    case CONSTANTE:
      break;
    case VARIABLE:
      anxLista(res,value);
      break;
    case FUNCION:
      switch(value)
	{
	case ADD:
	case MULT:
	case MOD:
	  frameToG(res, getLefSonFrameConst(f));
	  frameToG(res, getRigSonFrameConst(f));
	  break;
	
	case SUBS:
	case DIV:
	  frameToG(res, getLefSonFrameConst(f));
	  frameToS(res, getRigSonFrameConst(f));
	  break;
	case MIN:
	  break;
	case MAX:
	  frameToG(res, getLefSonFrameConst(f));
	  break;
	}
      break;
    }
}

#endif

/**** EOF ****/



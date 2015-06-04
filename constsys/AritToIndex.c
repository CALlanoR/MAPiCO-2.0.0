#ifndef _AritToIndex_c
#define _AritToIndex_c
/****************************************************************
* IMPLEMENTACION MODULO: AritToIndex.c
* FECHA CREACION:  27-Mar-01
* DESCRIPCION: 
*   Implementa la traslacion de una restriccion aritmetica al
*   modelo de Indexicals de la forma x in r.
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
       gcc -c AritToIndex.c

  1. Librerias requeridas para su linkeo:
       -lm -lX11

  2. Listado de estructuras de datos definidas (publicas y privadas)
  
  3. Listado de funciones definidas (publicas y privadas)
  
     IndexNecAritToIndex(ListaFC,int *,FrameConst)
     IndexSufAritToIndex(FrameConst)
     ConstToIndexSufAritToIndex(FrameConst)
     ConstToIndexNecAritToIndex(ListaFC, FrameConst, int*)
     NormalNecAritToIndex(ListaFC, FrameConst)
     NormalSufAritToIndex (FrameConst)
     EquivalentAritToIndex(ListaFC)
     OrdIzqAritToIndex(FrameConst)

  4. Instruccion para modificar el modulo
  4.1 Construcciones importantes para tener en cuenta (e.g. tipos, variables, funciones)
  4.2 Observaciones Adicionales
  
  ===============================================================*/
/*--------------------------------------------------------------*
  Archivos de Interfaz de librerias estandar y de otros modulos
 *--------------------------------------------------------------*/
#include "AritToIndex.h"
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
ListaFC IndexNecAritToIndex(ListaFC ListOfIndex,int *newvalue,FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Funcion que genera los indexicals necesarios de f.

  PARAMETROS: f: FrameConst del cual se van a extraer los indexicals
                 necesarios.
	      newvale: identificador para las variables generadas por
	               restriciones no lineales.
	      ListOfIndex: Lista de indexicals necesarios.
  USA:
  RETORNA: Una lista de indexicals necesarios como FrameConst.
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  ListaFC ListOfConst;
  ListOfConst = inicListaFC();
  ListOfConst = NormalNecAritToIndex(ListOfConst, f);
  ListOfConst = EquivalentAritToIndex(ListOfConst);

  for (primListaFC(ListOfConst); !finListaFC(ListOfConst); sigListaFC(ListOfConst))
    {
      ListOfConst = actinfoListaFC(ListOfConst, OrdIzqAritToIndex(infoListaFC(ListOfConst)));
      ListOfIndex = ConstToIndexNecAritToIndex(ListOfIndex, infoListaFC(ListOfConst),newvalue);
    }
  destruirListaFC(ListOfConst);
  return ListOfIndex;
}

FrameConst IndexSufAritToIndex(FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Funcion que genera el indexical suficiente 
               correspondientes al f.

  PARAMETROS: f: FrameConst del cual se van a extraer los indexical
                 suficiente.
  USA:
  RETORNA:La traduccion del indexical suficiente de f.
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
    FrameConst resp = NormalSufAritToIndex(f);
    return (ConstToIndexSufAritToIndex(resp));
}

FrameConst ConstToIndexSufAritToIndex(FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Funcion que genera el indexical suficiente 
               correspondientes al f.

  PARAMETROS: f: FrameConst del cual se van a extraer los indexical
                 suficiente.
  USA:
  RETORNA:La traduccion del indexical suficiente de f como FrameConst.
  PRE: f esta normalizado
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int value;
  FrameConst frmconst, deltadd, deltasub, range, sonrig;

  frmconst = InicFrameConst(PREDICADO, IN);
  insertSonFrameConst(frmconst, getLefSonFrameConst(f), LEFT);
  sonrig = getRigSonFrameConst(f);
  range = InicFrameConst(FUNCION, RANGE);
  value=getValueFrameConst(f);

  switch(value)
    {
    case IGUAL:
      insertSonFrameConst(range, SupremoFrameConst(sonrig), LEFT);
      insertSonFrameConst(range, InfimoFrameConst(sonrig), RIGHT);
      insertSonFrameConst(frmconst, range, RIGHT);
      return frmconst;
    case MEI:
      insertSonFrameConst(range, InicFrameConst(CONSTANTE, MININ), LEFT);
      insertSonFrameConst(range, InfimoFrameConst(sonrig), RIGHT);
      insertSonFrameConst(frmconst, range, RIGHT);
      return frmconst;
    case MAI:
      insertSonFrameConst(range, SupremoFrameConst(sonrig), LEFT);
      insertSonFrameConst(range, InicFrameConst(CONSTANTE, MAXIN), RIGHT);
      insertSonFrameConst(frmconst, range, RIGHT);
      return frmconst;
    case MEN:

      deltasub = InicFrameConst(FUNCION, SUBS);
      insertSonFrameConst(deltasub, sonrig, LEFT);

      insertSonFrameConst(deltasub, InicFrameConst(CONSTANTE, 1), RIGHT);
      insertSonFrameConst(range, InicFrameConst(CONSTANTE, MININ), LEFT);
      insertSonFrameConst(range, InfimoFrameConst(deltasub), RIGHT);
      insertSonFrameConst(frmconst, range, RIGHT);
      return frmconst;
    case MAY:
      deltadd = InicFrameConst(FUNCION, ADD);
      insertSonFrameConst(deltadd, sonrig, LEFT);
      insertSonFrameConst(deltadd, InicFrameConst(CONSTANTE, 1), RIGHT);

      insertSonFrameConst(range, SupremoFrameConst(deltadd), LEFT);
      insertSonFrameConst(range, InicFrameConst(CONSTANTE, MAXIN), RIGHT);
      insertSonFrameConst(frmconst, range, RIGHT);
      return frmconst;
    default:
      insertSonFrameConst(range, InfimoFrameConst(sonrig), LEFT);
      insertSonFrameConst(range, SupremoFrameConst(sonrig), RIGHT);
      insertSonFrameConst(frmconst, ComplementFrameConst(range), RIGHT);
      return frmconst;
    }
}

ListaFC NormalNecAritToIndex(ListaFC ListOfConst, FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Funcion que normaliza la restriccion aritmetica f
               para el caso necesario. Convierte las divisiones 
	       en multiplicaciones. Lo adiciona en el vector
	       ListOfConst.

  PARAMETROS: f: FrameConst al cual se le van a suprimir las divisiones
	      ListOfConst: Lista de restricciones para actualizar.
  USA:
  RETORNA:
  PRE: f esta normalizado
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  FrameConst flef, frig, frmconst, sonrig;

  flef = getLefSonFrameConst(f);
  frig = getRigSonFrameConst(f);
  sonrig = InicFrameConst(FUNCION, MULT);
  
  if (getTypeFrameConst(frig) == VARIABLE)
      {
	  if (getTypeFrameConst(flef) == CONSTANTE || getTypeFrameConst(flef) == FUNCION)
	      {
		  frmconst = InicFrameConst(getTypeFrameConst(f), InvRel(getValueFrameConst(f)));
		  insertSonFrameConst(frmconst, frig, LEFT);
		  insertSonFrameConst(frmconst, flef, RIGHT);
		  anxListaFC(ListOfConst, frmconst);
 		  DestruirFrameConst(sonrig); 
		  return ListOfConst;
	      }
      }
  if (getTypeFrameConst(frig) == FUNCION)
      {
	  if (getValueFrameConst(frig) == DIV)
	      {
		  if (EsNegativoFrameConst(getRigSonFrameConst(frig)))
		      frmconst = InicFrameConst(PREDICADO, getValueFrameConst(f));
		  else
		      frmconst = InicFrameConst(PREDICADO, InvRel(getValueFrameConst(f)));
		 
		  insertSonFrameConst(sonrig, flef,LEFT);
		  insertSonFrameConst(sonrig, getRigSonFrameConst(frig),RIGHT);
		  insertSonFrameConst(frmconst, getLefSonFrameConst(frig),LEFT);
		  insertSonFrameConst(frmconst, sonrig, RIGHT);
		  anxListaFC(ListOfConst, frmconst);
		  return ListOfConst;
	      }
      }
  anxListaFC(ListOfConst, f);
  DestruirFrameConst(sonrig); 
  return ListOfConst;
}

FrameConst NormalSufAritToIndex(FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Funcion que normaliza la restriccion aritmetica f
               para el caso suficiente.

  PARAMETROS: f: FrameConst al cual se le van a suprimir las divisiones

  USA:
  RETORNA: f normalizado.
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int cons, value, type, valuerig, valuelef, valuerigrig,valueriglef;
  FrameConst sonlef, sonrig, sonriglef, sonrigrig, frmconst, delta;

  value = getValueFrameConst(f);
  type = getTypeFrameConst(f);

  sonlef = getLefSonFrameConst(f);
  sonrig = getRigSonFrameConst(f);

  valuerig = getValueFrameConst(sonrig);
  valuelef = getValueFrameConst(sonlef);
  
  if (getTypeFrameConst(sonrig) == CONSTANTE)
      return f;
  else if (getTypeFrameConst(sonrig) == VARIABLE)
      {
	if (getTypeFrameConst(sonlef) == VARIABLE)
	    return f;
	else if (getTypeFrameConst(sonlef) == CONSTANTE)
	  {
	    frmconst = InicFrameConst(getTypeFrameConst(f), InvRel(getValueFrameConst(f)));
	    insertSonFrameConst(frmconst, sonrig, LEFT);
	    insertSonFrameConst(frmconst, sonlef, RIGHT);
	    return frmconst;
	  }
      }

  sonriglef = getLefSonFrameConst(sonrig);
  sonrigrig = getRigSonFrameConst(sonrig);

  valueriglef = getValueFrameConst(sonriglef);
  valuerigrig = getValueFrameConst(sonrigrig);

  cons = NumConstFrameConst(f);
  
  switch(cons)
    {
    case 0:
      frmconst = InicFrameConst(type, value);
      delta = InicFrameConst(FUNCION, SUBS);
      insertSonFrameConst(delta, sonrig, LEFT);
      insertSonFrameConst(delta, sonlef, RIGHT);
      insertSonFrameConst(frmconst, InicFrameConst(CONSTANTE, 0), LEFT);
      insertSonFrameConst(frmconst, delta, RIGHT);
      return frmconst;
    case 1:
      if ( getTypeFrameConst(sonriglef) == CONSTANTE)
	{
	  if (valuerig == MULT)
	    {
	      frmconst = InicFrameConst(type, InvRel(value));
	      delta = InicFrameConst(FUNCION, SUBS);
	      insertSonFrameConst(delta, sonlef, LEFT);
	      insertSonFrameConst(delta, sonrig, RIGHT);
	      insertSonFrameConst(frmconst, InicFrameConst(CONSTANTE, 0), LEFT);
	      insertSonFrameConst(frmconst, delta, RIGHT);
	      return frmconst;
	    }
	  else 
	    {
	      frmconst = InicFrameConst(type, InvRel(value));
	      delta = InicFrameConst(FUNCION, InvFun(getValueFrameConst(sonrig)));
	      insertSonFrameConst(delta, sonlef, LEFT);
	      insertSonFrameConst(delta, sonrigrig, RIGHT);
	      insertSonFrameConst(frmconst, sonriglef, LEFT);
	      insertSonFrameConst(frmconst, delta, RIGHT);
	      return frmconst;
	    }
	}
      else if ( getTypeFrameConst(sonrigrig) == CONSTANTE )
	{
	  if ( valuerig == MULT )
	    {
	      frmconst = InicFrameConst(type, InvRel(value));
	      delta = InicFrameConst(FUNCION, SUBS);
	      insertSonFrameConst(delta, sonlef, LEFT);
	      insertSonFrameConst(delta, sonrig, RIGHT);
	      insertSonFrameConst(frmconst, InicFrameConst(CONSTANTE, 0), LEFT);
	      insertSonFrameConst(frmconst, delta, RIGHT);
	      return frmconst;
	    }
	  else if (valuerig == ADD)
	    {
	      frmconst = InicFrameConst(type, InvRel(value));
	      delta = InicFrameConst(FUNCION, SUBS);
	      insertSonFrameConst(delta, sonlef, LEFT);
	      insertSonFrameConst(delta, sonriglef, RIGHT);
	      insertSonFrameConst(frmconst, sonrigrig, LEFT);
	      insertSonFrameConst(frmconst, delta, RIGHT);
	      return frmconst;
	    }
	  else
	    {
	      frmconst = InicFrameConst(type, InvRel(value));
	      delta = InicFrameConst(FUNCION, SUBS);
	      insertSonFrameConst(delta, sonriglef, LEFT);
	      insertSonFrameConst(delta, sonlef, RIGHT);
	      insertSonFrameConst(frmconst, sonrigrig, LEFT);
	      insertSonFrameConst(frmconst, delta, RIGHT);
	      return frmconst;
	    }
	}
      else 
	return f;
    case 2:
      if (getTypeFrameConst(sonrigrig) == VARIABLE )
	{
	  if (valuerig == MULT)
	    return f;
	  else if (valuerig == ADD)
	    {
	      frmconst = InicFrameConst(type, value);
	      insertSonFrameConst(frmconst, InicFrameConst(CONSTANTE, valuelef-valueriglef), LEFT);
	      insertSonFrameConst(frmconst, sonrigrig, RIGHT);
	      return frmconst;
	    }
	  else 
	    {
	      frmconst = InicFrameConst(type, value);
	      insertSonFrameConst(frmconst, InicFrameConst(CONSTANTE, valueriglef-valuelef), LEFT);
	      insertSonFrameConst(frmconst, sonrigrig, RIGHT);
	      return frmconst;
	    }
	}
      else if (getTypeFrameConst(sonriglef) == VARIABLE)
	{
	  if (valuerig == MULT)
	    return f;
	  else if (valuerig == ADD)
	    {
	      frmconst = InicFrameConst(type, value);
	      insertSonFrameConst(frmconst, InicFrameConst(CONSTANTE, valuelef-valueriglef), LEFT);
	      insertSonFrameConst(frmconst, sonrigrig, RIGHT);
	      return frmconst;
	    }
	  else
	    {
	      frmconst = InicFrameConst(type, value);
	      insertSonFrameConst(frmconst, InicFrameConst(CONSTANTE, valuerigrig+valuelef), LEFT);
	      insertSonFrameConst(frmconst, sonriglef, RIGHT);
	      return frmconst;
	    }
	}
      else
	{
	  if (valuerig == MULT)
	    {
	      frmconst = InicFrameConst(type, value);
	      insertSonFrameConst(frmconst, InicFrameConst(CONSTANTE, valueriglef*valuerigrig), LEFT);
	      insertSonFrameConst(frmconst, sonlef, RIGHT);
	      return frmconst;
	    }
	  else if (valuerig == ADD)
	    {
	      frmconst = InicFrameConst(type, value);
	      insertSonFrameConst(frmconst, InicFrameConst(CONSTANTE, valueriglef+valuerigrig), LEFT);
	      insertSonFrameConst(frmconst, sonlef, RIGHT);
	      return frmconst;
	    }
	  else
	    {
	      frmconst = InicFrameConst(type, value);
	      insertSonFrameConst(frmconst, InicFrameConst(CONSTANTE, valueriglef-valuerigrig), LEFT);
	      insertSonFrameConst(frmconst, sonlef, RIGHT);
	      return frmconst;
	    }
	}
    default:
      return f;
    }
}

ListaFC EquivalentAritToIndex(ListaFC ListOfConst)
/*---------------------------------------------------------------
  DESCRIPCION: Genera los elementos equivalentes del primer y unico
               elemento de la ListOfConst y los adiciona a la 
	       misma.

  PARAMETROS: ListOfConst: Lista de restricciones para actualizar.
  USA:
  RETORNA: ListOfConst: Lista de restricciones.
  PRE: 
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  FrameConst element, aux1, aux2, sonrig1, sonrig2;
  primListaFC(ListOfConst);

  element = infoListaFC(ListOfConst);

  if (getTypeFrameConst(getLefSonFrameConst(element)) == CONSTANTE)
    elimListaFC(ListOfConst);

  if (getTypeFrameConst(getRigSonFrameConst(element)) == FUNCION)
    switch(getValueFrameConst(getRigSonFrameConst(element)))
      {
      case ADD:
	aux1 = InicFrameConst(PREDICADO, InvRel(getValueFrameConst(element)));
	aux2 = InicFrameConst(PREDICADO, InvRel(getValueFrameConst(element)));
	sonrig1 = InicFrameConst(FUNCION, SUBS);
	sonrig2 = InicFrameConst(FUNCION, SUBS);
	insertSonFrameConst(sonrig1, getLefSonFrameConst(element), LEFT);
	insertSonFrameConst(sonrig1, getRigSonFrameConst(getRigSonFrameConst(element)), RIGHT);
	insertSonFrameConst(sonrig2, getLefSonFrameConst(element), LEFT);
	insertSonFrameConst(sonrig2, getLefSonFrameConst(getRigSonFrameConst(element)), RIGHT);
	insertSonFrameConst(aux1, getLefSonFrameConst(getRigSonFrameConst(element)), LEFT);
	insertSonFrameConst(aux1, sonrig1, RIGHT);
	insertSonFrameConst(aux2, getRigSonFrameConst(getRigSonFrameConst(element)), LEFT);
	insertSonFrameConst(aux2, sonrig2, RIGHT);
	if(getTypeFrameConst(getLefSonFrameConst(aux1)) != CONSTANTE)
	  {
	    adicListaFC(ListOfConst, aux1);
	    return ListOfConst;
	  }
	if(getTypeFrameConst(getLefSonFrameConst(aux2)) != CONSTANTE)
	  {
	    adicListaFC(ListOfConst, aux2);
	    return ListOfConst;
	  }
	break;
      case SUBS:
	aux1 = InicFrameConst(PREDICADO, InvRel(getValueFrameConst(element)));
	aux2 = InicFrameConst(PREDICADO, getValueFrameConst(element));
	sonrig1 = InicFrameConst(FUNCION, ADD);
	sonrig2 = InicFrameConst(FUNCION, SUBS);
	insertSonFrameConst(sonrig1, getLefSonFrameConst(element), LEFT);
	insertSonFrameConst(sonrig1, getRigSonFrameConst(getRigSonFrameConst(element)), RIGHT);
	insertSonFrameConst(sonrig2, getLefSonFrameConst(getRigSonFrameConst(element)), LEFT);
	insertSonFrameConst(sonrig2, getLefSonFrameConst(element), RIGHT);
	insertSonFrameConst(aux1,getLefSonFrameConst(getRigSonFrameConst(element)), LEFT);
	insertSonFrameConst(aux1,sonrig1, RIGHT);
	insertSonFrameConst(aux2,getRigSonFrameConst(getRigSonFrameConst(element)), LEFT);
	insertSonFrameConst(aux2,sonrig2, RIGHT);
	if(getTypeFrameConst(getLefSonFrameConst(aux1)) != CONSTANTE)
	  {
	    adicListaFC(ListOfConst, aux1);
	    return ListOfConst;
	  }
	if(getTypeFrameConst(getLefSonFrameConst(aux2)) != CONSTANTE)
	  {
	    adicListaFC(ListOfConst, aux2);
	    return ListOfConst;
	  }
	break;
      default:
	aux1 = InicFrameConst(PREDICADO, InvRel(getValueFrameConst(element)));
	insertSonFrameConst(aux1, getRigSonFrameConst(element),LEFT);
	insertSonFrameConst(aux1, getLefSonFrameConst(element),RIGHT);
	if (getTypeFrameConst(getLefSonFrameConst(aux1)) != CONSTANTE)
	  {
	    adicListaFC(ListOfConst, aux1);
	    return ListOfConst;
	  }
	else
	  DestruirFrameConst(aux1);
      }
  else
    {
      aux1 = InicFrameConst(PREDICADO, InvRel(getValueFrameConst(element)));
      insertSonFrameConst(aux1, getRigSonFrameConst(element), LEFT);
      insertSonFrameConst(aux1, getLefSonFrameConst(element), RIGHT);
      if (getTypeFrameConst(getLefSonFrameConst(aux1)) != CONSTANTE)
	{
	  adicListaFC(ListOfConst, aux1);
	  return ListOfConst;
	}
    }
  return ListOfConst;
}

FrameConst OrdIzqAritToIndex(FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION:  Toma el hijo izquierdo de la restriccion aritmetica f. 
                Si es una multiplicacion coloca las constantes
		(si existen) como primer factor. Si los dos 
		factores son una constante deja una sola constante.

  PARAMETROS: f: FrameConst a organizar el hijo izquierdo.
  USA:
  RETORNA: f pero aplicado el concepto de orden izquierdo.
  PRE: 
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int type, value, product;
  FrameConst frmconst, sonlef, prod;
  
  sonlef = getLefSonFrameConst(f);
  
  type = getTypeFrameConst(sonlef);
  value = getValueFrameConst(sonlef);

  if ( type == FUNCION)
      {
	  if ( value == MULT)
	      {
		  if (getTypeFrameConst(getLefSonFrameConst(sonlef)) == CONSTANTE)
		      {
			  if (getTypeFrameConst(getRigSonFrameConst(sonlef)) == CONSTANTE)
			      {
				  frmconst = InicFrameConst(getTypeFrameConst(f), getValueFrameConst(f));
				  product = getValueFrameConst(getLefSonFrameConst(sonlef))*getValueFrameConst(getRigSonFrameConst(sonlef));
				  insertSonFrameConst(frmconst, InicFrameConst(CONSTANTE, product), LEFT);
				  insertSonFrameConst(frmconst, getRigSonFrameConst(f), RIGHT);

				  return frmconst;
			      }
			  return f;
		      }
		  else
		      {
			  frmconst = InicFrameConst(getTypeFrameConst(f), getValueFrameConst(f));
			  prod = InicFrameConst(FUNCION, MULT);
			  insertSonFrameConst(prod, getRigSonFrameConst(sonlef), LEFT);
			  insertSonFrameConst(prod, getLefSonFrameConst(sonlef), RIGHT);
			  insertSonFrameConst(frmconst, prod, LEFT);
			  insertSonFrameConst(frmconst, getRigSonFrameConst(f), RIGHT);
			  return frmconst;
		      }
	      }
      }
  return f;
}


ListaFC ConstToIndexNecAritToIndex(ListaFC ListOfIndex, FrameConst f,int *newvalue)
/*---------------------------------------------------------------
  DESCRIPCION: Funcion que genera los indexicals necesarios 
               correspondientes al frameconst f.

  PARAMETROS: f: FrameConst del cual se van a extraer los indexicals
                 necesarios.
	      ListOfIndex: Lista de indexicals.
	      newvalue: Identificador de las variables generadas por
	                las restricciones no lineales.
  USA:
  RETORNA:La traduccion de los indexicals necesarios de f como FrameConst.
  PRE: f esta normalizado
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int value,lineal,typelef;
  FrameConst sonlef,sonrig,rlef,rrig,r,indexical,delta,ni, by, bx,  domy, domx, conjdomy0, 
    conjdomx0, impdomy0, impdomx0,disjimpdomy01, disjimpdomx01, maxby, minby, maxbx, minbx, 
    maxbyminby, impmaxbyminby, rp, rpder, rpizq, rmax, rmin, rpmax, rpmin, maxbxminbx, impmaxbxminbx,
    indx, indy, indbx, indby, comp, comp1;

  sonlef = getLefSonFrameConst(f);
  sonrig = getRigSonFrameConst(f);

  value=getValueFrameConst(f);
  lineal=EsLinealFrameConst(sonlef);
  typelef=getTypeFrameConst(sonlef);

  switch(value)
    {
    case IGUAL:
      if(lineal)
	{
	  if(typelef==VARIABLE || typelef==CONSTANTE)
	    ni=InicFrameConst(CONSTANTE,1);
	  else
	    ni=getLefSonFrameConst(sonlef);
	  rlef=InicFrameConst(FUNCION,DIV);
	  insertSonFrameConst(rlef,InfimoFrameConst(sonrig),LEFT);
	  insertSonFrameConst(rlef,ni,RIGHT);
	  rrig=InicFrameConst(FUNCION,DIV);
	  insertSonFrameConst(rrig,SupremoFrameConst(sonrig),LEFT);
	  insertSonFrameConst(rrig,ni,RIGHT);
	  r=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(r,CeilFrameConst(rlef),LEFT);
	  insertSonFrameConst(r,FloorFrameConst(rrig),RIGHT);
	  
	  indexical=InicFrameConst(PREDICADO,IN);	  
	  if(typelef == VARIABLE || typelef == CONSTANTE)
	    insertSonFrameConst(indexical,sonlef,LEFT);
	  else
	    insertSonFrameConst(indexical,getRigSonFrameConst(sonlef),LEFT);
	  insertSonFrameConst(indexical,r,RIGHT);
	  adicListaFC(ListOfIndex,indexical);
	}
      else
	{
	  domy=InicFrameConst(FUNCION,DOM);
	  insertSonFrameConst(domy,getRigSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  conjdomy0=InicFrameConst(FUNCION,AND);
	  insertSonFrameConst(conjdomy0,domy,LEFT);
	  insertSonFrameConst(conjdomy0,InicFrameConst(CONSTANTE,0),RIGHT);
	  impdomy0=InicFrameConst(FUNCION,IMP);
	  insertSonFrameConst(impdomy0,conjdomy0,LEFT);
	  insertSonFrameConst(impdomy0,InicFrameConst(CONSTANTE,0),RIGHT);
	  disjimpdomy01=InicFrameConst(FUNCION,OR);
	  insertSonFrameConst(disjimpdomy01,impdomy0,LEFT);
	  insertSonFrameConst(disjimpdomy01,InicFrameConst(CONSTANTE,1),RIGHT);
	  by=InicFrameConst(VARIABLE,*newvalue);
	  (*newvalue)--;
	  indby=InicFrameConst(PREDICADO,IN);
	  insertSonFrameConst(indby,by,LEFT);
	  insertSonFrameConst(indby,disjimpdomy01,RIGHT);
	  adicListaFC(ListOfIndex,indby);
	  
	  rmax=InicFrameConst(FUNCION,MAX);
	  insertSonFrameConst(rmax,getRigSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  rmin=InicFrameConst(FUNCION,MIN);
	  insertSonFrameConst(rmin,getRigSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  rlef=InicFrameConst(FUNCION,DIV);
	  insertSonFrameConst(rlef,InfimoFrameConst(getRigSonFrameConst(f)),LEFT);
	  insertSonFrameConst(rlef,rmax,RIGHT);
	  rrig=InicFrameConst(FUNCION,DIV);
	  insertSonFrameConst(rrig,SupremoFrameConst(getRigSonFrameConst(f)),LEFT);
	  insertSonFrameConst(rrig,rmin,RIGHT);
	  r=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(r,CeilFrameConst(rlef),LEFT);
	  insertSonFrameConst(r,FloorFrameConst(rrig),RIGHT);

	  maxby=InicFrameConst(FUNCION,MAX);
	  insertSonFrameConst(maxby,by,LEFT);
	  minby=InicFrameConst(FUNCION,MIN);
	  insertSonFrameConst(minby,by,LEFT);
	  maxbyminby=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(maxbyminby,maxby,LEFT);
	  insertSonFrameConst(maxbyminby,minby,RIGHT);
	  impmaxbyminby=InicFrameConst(FUNCION,IMP);
	  insertSonFrameConst(impmaxbyminby,maxbyminby,LEFT);
	  insertSonFrameConst(impmaxbyminby,r,RIGHT);
	  indx=InicFrameConst(PREDICADO,IN);
	  insertSonFrameConst(indx,getLefSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  insertSonFrameConst(indx,impmaxbyminby,RIGHT);
	  adicListaFC(ListOfIndex,indx);
	  domx=InicFrameConst(FUNCION,DOM);
	  insertSonFrameConst(domx,getLefSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  conjdomx0=InicFrameConst(FUNCION,AND);
	  insertSonFrameConst(conjdomx0,domx,LEFT);
	  insertSonFrameConst(conjdomx0,InicFrameConst(CONSTANTE,0),RIGHT);
	  impdomx0=InicFrameConst(FUNCION,IMP);
	  insertSonFrameConst(impdomx0,conjdomx0,LEFT);
	  insertSonFrameConst(impdomx0,InicFrameConst(CONSTANTE,0),RIGHT);
	  disjimpdomx01=InicFrameConst(FUNCION,OR);
	  insertSonFrameConst(disjimpdomx01,impdomx0,LEFT);
	  insertSonFrameConst(disjimpdomx01,InicFrameConst(CONSTANTE,1),RIGHT);
	  bx=InicFrameConst(VARIABLE,*newvalue);
	  (*newvalue)--;
	  indbx=InicFrameConst(PREDICADO,IN);
	  insertSonFrameConst(indbx,bx,LEFT);
	  insertSonFrameConst(indbx,disjimpdomx01,RIGHT);
	  adicListaFC(ListOfIndex,indbx);

	  rpmax=InicFrameConst(FUNCION,MAX);
	  insertSonFrameConst(rpmax,getLefSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  rpmin=InicFrameConst(FUNCION,MIN);
	  insertSonFrameConst(rpmin,getLefSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  rpizq=InicFrameConst(FUNCION,DIV);
	  insertSonFrameConst(rpizq,InfimoFrameConst(getRigSonFrameConst(f)),LEFT);
	  insertSonFrameConst(rpizq,rpmax,RIGHT);
	  rpder=InicFrameConst(FUNCION,DIV);
	  insertSonFrameConst(rpder,SupremoFrameConst(getRigSonFrameConst(f)),LEFT);
	  insertSonFrameConst(rpder,rpmin,RIGHT);
	  rp=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(rp,CeilFrameConst(rpizq),LEFT);
	  insertSonFrameConst(rp,FloorFrameConst(rpder),RIGHT);

	  maxbx=InicFrameConst(FUNCION,MAX);
	  insertSonFrameConst(maxbx,bx,LEFT);
	  minbx=InicFrameConst(FUNCION,MIN);
	  insertSonFrameConst(minbx,bx,LEFT);
	  maxbxminbx=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(maxbxminbx,maxbx,LEFT);
	  insertSonFrameConst(maxbxminbx,minbx,RIGHT);
	  impmaxbxminbx=InicFrameConst(FUNCION,IMP);
	  insertSonFrameConst(impmaxbxminbx,maxbxminbx,LEFT);
	  insertSonFrameConst(impmaxbxminbx,rp,RIGHT);
	  indy=InicFrameConst(PREDICADO,IN);
	  insertSonFrameConst(indy,getRigSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  insertSonFrameConst(indy,impmaxbxminbx,RIGHT);
	  adicListaFC(ListOfIndex,indy);
	}
      break;

    case MEI:
      if(lineal)
	{
	  if(typelef==VARIABLE || typelef==CONSTANTE)
	    ni=InicFrameConst(CONSTANTE,1);
	  else
	    ni=getLefSonFrameConst(sonlef);
	  rlef=InicFrameConst(CONSTANTE,MININ);
	  rrig=InicFrameConst(FUNCION,DIV);
	  insertSonFrameConst(rrig,SupremoFrameConst(sonrig),LEFT);
	  insertSonFrameConst(rrig,ni,RIGHT);
	  r=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(r,rlef,LEFT);
	  insertSonFrameConst(r,FloorFrameConst(rrig),RIGHT);
	  indexical=InicFrameConst(PREDICADO,IN);
	  if(typelef == VARIABLE || typelef == CONSTANTE)
	    insertSonFrameConst(indexical,sonlef,LEFT);
	  else
	    insertSonFrameConst(indexical,getRigSonFrameConst(sonlef),LEFT);
	  insertSonFrameConst(indexical,r,RIGHT);
	  adicListaFC(ListOfIndex,indexical);
	}
      else
	{
	  domy=InicFrameConst(FUNCION,DOM);
	  insertSonFrameConst(domy,getRigSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  conjdomy0=InicFrameConst(FUNCION,AND);
	  insertSonFrameConst(conjdomy0,domy,LEFT);
	  insertSonFrameConst(conjdomy0,InicFrameConst(CONSTANTE,0),RIGHT);
	  impdomy0=InicFrameConst(FUNCION,IMP);
	  insertSonFrameConst(impdomy0,conjdomy0,LEFT);
	  insertSonFrameConst(impdomy0,InicFrameConst(CONSTANTE,0),RIGHT);
	  disjimpdomy01=InicFrameConst(FUNCION,OR);
	  insertSonFrameConst(disjimpdomy01,impdomy0,LEFT);
	  insertSonFrameConst(disjimpdomy01,InicFrameConst(CONSTANTE,1),RIGHT);
	  by=InicFrameConst(VARIABLE,*newvalue);
	  (*newvalue)--;
	  indby=InicFrameConst(PREDICADO,IN);
	  insertSonFrameConst(indby,by,LEFT);
	  insertSonFrameConst(indby,disjimpdomy01,RIGHT);
	  adicListaFC(ListOfIndex,indby);
	  
	  rmax=InicFrameConst(FUNCION,MAX);
	  insertSonFrameConst(rmax,getRigSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  rmin=InicFrameConst(FUNCION,MIN);
	  insertSonFrameConst(rmin,getRigSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  rlef=InicFrameConst(CONSTANTE,MININ);
	  rrig=InicFrameConst(FUNCION,DIV);
	  insertSonFrameConst(rrig,SupremoFrameConst(getRigSonFrameConst(f)),LEFT);
	  insertSonFrameConst(rrig,rmin,RIGHT);
	  r=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(r,rlef,LEFT);
	  insertSonFrameConst(r,FloorFrameConst(rrig),RIGHT);

	  maxby=InicFrameConst(FUNCION,MAX);
	  insertSonFrameConst(maxby,by,LEFT);
	  minby=InicFrameConst(FUNCION,MIN);
	  insertSonFrameConst(minby,by,LEFT);
	  maxbyminby=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(maxbyminby,maxby,LEFT);
	  insertSonFrameConst(maxbyminby,minby,RIGHT);
	  impmaxbyminby=InicFrameConst(FUNCION,IMP);
	  insertSonFrameConst(impmaxbyminby,maxbyminby,LEFT);
	  insertSonFrameConst(impmaxbyminby,r,RIGHT);
	  indx=InicFrameConst(PREDICADO,IN);
	  insertSonFrameConst(indx,getLefSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  insertSonFrameConst(indx,impmaxbyminby,RIGHT);
	  adicListaFC(ListOfIndex,indx);
	  domx=InicFrameConst(FUNCION,DOM);
	  insertSonFrameConst(domx,getLefSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  conjdomx0=InicFrameConst(FUNCION,AND);
	  insertSonFrameConst(conjdomx0,domx,LEFT);
	  insertSonFrameConst(conjdomx0,InicFrameConst(CONSTANTE,0),RIGHT);
	  impdomx0=InicFrameConst(FUNCION,IMP);
	  insertSonFrameConst(impdomx0,conjdomx0,LEFT);
	  insertSonFrameConst(impdomx0,InicFrameConst(CONSTANTE,0),RIGHT);
	  disjimpdomx01=InicFrameConst(FUNCION,OR);
	  insertSonFrameConst(disjimpdomx01,impdomx0,LEFT);
	  insertSonFrameConst(disjimpdomx01,InicFrameConst(CONSTANTE,1),RIGHT);
	  bx=InicFrameConst(VARIABLE,*newvalue);
	  (*newvalue)--;
	  indbx=InicFrameConst(PREDICADO,IN);
	  insertSonFrameConst(indbx,bx,LEFT);
	  insertSonFrameConst(indbx,disjimpdomx01,RIGHT);
	  adicListaFC(ListOfIndex,indbx);

	  rpmax=InicFrameConst(FUNCION,MAX);
	  insertSonFrameConst(rpmax,getLefSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  rpmin=InicFrameConst(FUNCION,MIN);
	  insertSonFrameConst(rpmin,getLefSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  rpizq=InicFrameConst(CONSTANTE,MININ);
	  rpder=InicFrameConst(FUNCION,DIV);
	  insertSonFrameConst(rpder,SupremoFrameConst(getRigSonFrameConst(f)),LEFT);
	  insertSonFrameConst(rpder,rpmin,RIGHT);
	  rp=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(rp,rpizq,LEFT);
	  insertSonFrameConst(rp,FloorFrameConst(rpder),RIGHT);

	  maxbx=InicFrameConst(FUNCION,MAX);
	  insertSonFrameConst(maxbx,bx,LEFT);
	  minbx=InicFrameConst(FUNCION,MIN);
	  insertSonFrameConst(minbx,bx,LEFT);
	  maxbxminbx=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(maxbxminbx,maxbx,LEFT);
	  insertSonFrameConst(maxbxminbx,minbx,RIGHT);
	  impmaxbxminbx=InicFrameConst(FUNCION,IMP);
	  insertSonFrameConst(impmaxbxminbx,maxbxminbx,LEFT);
	  insertSonFrameConst(impmaxbxminbx,rp,RIGHT);
	  indy=InicFrameConst(PREDICADO,IN);
	  insertSonFrameConst(indy,getRigSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  insertSonFrameConst(indy,impmaxbxminbx,RIGHT);
	  adicListaFC(ListOfIndex,indy);
	}
      break;

    case MAI:
      if(lineal)
	{
	  if(typelef==VARIABLE || typelef==CONSTANTE)
	    ni=InicFrameConst(CONSTANTE,1);
	  else
	    ni=getLefSonFrameConst(sonlef);
	  rlef=InicFrameConst(FUNCION,DIV);
	  insertSonFrameConst(rlef,InfimoFrameConst(sonrig),LEFT);
	  insertSonFrameConst(rlef,ni,RIGHT);
	  rrig=InicFrameConst(CONSTANTE,MAXIN);
	  r=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(r,CeilFrameConst(rlef),LEFT);
	  insertSonFrameConst(r,rrig,RIGHT);
	  indexical=InicFrameConst(PREDICADO,IN);
	  if(typelef == VARIABLE || typelef == CONSTANTE)
	    insertSonFrameConst(indexical,sonlef,LEFT);
	  else
	    insertSonFrameConst(indexical,getRigSonFrameConst(sonlef),LEFT);
	  insertSonFrameConst(indexical,r,RIGHT);
	  adicListaFC(ListOfIndex,indexical);
	}
      else
	{
	  domy=InicFrameConst(FUNCION,DOM);
	  insertSonFrameConst(domy,getRigSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  conjdomy0=InicFrameConst(FUNCION,AND);
	  insertSonFrameConst(conjdomy0,domy,LEFT);
	  insertSonFrameConst(conjdomy0,InicFrameConst(CONSTANTE,0),RIGHT);
	  impdomy0=InicFrameConst(FUNCION,IMP);
	  insertSonFrameConst(impdomy0,conjdomy0,LEFT);
	  insertSonFrameConst(impdomy0,InicFrameConst(CONSTANTE,0),RIGHT);
	  disjimpdomy01=InicFrameConst(FUNCION,OR);
	  insertSonFrameConst(disjimpdomy01,impdomy0,LEFT);
	  insertSonFrameConst(disjimpdomy01,InicFrameConst(CONSTANTE,1),RIGHT);
	  by=InicFrameConst(VARIABLE,*newvalue);
	  (*newvalue)--;
	  indby=InicFrameConst(PREDICADO,IN);
	  insertSonFrameConst(indby,by,LEFT);
	  insertSonFrameConst(indby,disjimpdomy01,RIGHT);
	  adicListaFC(ListOfIndex,indby);
	  
	  rmax=InicFrameConst(FUNCION,MAX);
	  insertSonFrameConst(rmax,getRigSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  rmin=InicFrameConst(FUNCION,MIN);
	  insertSonFrameConst(rmin,getRigSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  rlef=InicFrameConst(FUNCION,DIV);
	  insertSonFrameConst(rlef,InfimoFrameConst(getRigSonFrameConst(f)),LEFT);
	  insertSonFrameConst(rlef,rmax,RIGHT);
	  rrig=InicFrameConst(CONSTANTE,MAXIN);
	  r=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(r,CeilFrameConst(rlef),LEFT);
	  insertSonFrameConst(r,rrig,RIGHT);

	  maxby=InicFrameConst(FUNCION,MAX);
	  insertSonFrameConst(maxby,by,LEFT);
	  minby=InicFrameConst(FUNCION,MIN);
	  insertSonFrameConst(minby,by,LEFT);
	  maxbyminby=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(maxbyminby,maxby,LEFT);
	  insertSonFrameConst(maxbyminby,minby,RIGHT);
	  impmaxbyminby=InicFrameConst(FUNCION,IMP);
	  insertSonFrameConst(impmaxbyminby,maxbyminby,LEFT);
	  insertSonFrameConst(impmaxbyminby,r,RIGHT);
	  indx=InicFrameConst(PREDICADO,IN);
	  insertSonFrameConst(indx,getLefSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  insertSonFrameConst(indx,impmaxbyminby,RIGHT);
	  adicListaFC(ListOfIndex,indx);
	  domx=InicFrameConst(FUNCION,DOM);
	  insertSonFrameConst(domx,getLefSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  conjdomx0=InicFrameConst(FUNCION,AND);
	  insertSonFrameConst(conjdomx0,domx,LEFT);
	  insertSonFrameConst(conjdomx0,InicFrameConst(CONSTANTE,0),RIGHT);
	  impdomx0=InicFrameConst(FUNCION,IMP);
	  insertSonFrameConst(impdomx0,conjdomx0,LEFT);
	  insertSonFrameConst(impdomx0,InicFrameConst(CONSTANTE,0),RIGHT);
	  disjimpdomx01=InicFrameConst(FUNCION,OR);
	  insertSonFrameConst(disjimpdomx01,impdomx0,LEFT);
	  insertSonFrameConst(disjimpdomx01,InicFrameConst(CONSTANTE,1),RIGHT);
	  bx=InicFrameConst(VARIABLE,*newvalue);
	  (*newvalue)--;
	  indbx=InicFrameConst(PREDICADO,IN);
	  insertSonFrameConst(indbx,bx,LEFT);
	  insertSonFrameConst(indbx,disjimpdomx01,RIGHT);
	  adicListaFC(ListOfIndex,indbx);

	  rpmax=InicFrameConst(FUNCION,MAX);
	  insertSonFrameConst(rpmax,getLefSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  rpmin=InicFrameConst(FUNCION,MIN);
	  insertSonFrameConst(rpmin,getLefSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  rpizq=InicFrameConst(FUNCION,DIV);
	  insertSonFrameConst(rpizq,InfimoFrameConst(getRigSonFrameConst(f)),LEFT);
	  insertSonFrameConst(rpizq,rpmax,RIGHT);
	  rpder=InicFrameConst(CONSTANTE,MAXIN);
	  rp=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(rp,CeilFrameConst(rpizq),LEFT);
	  insertSonFrameConst(rp,rpder,RIGHT);

	  maxbx=InicFrameConst(FUNCION,MAX);
	  insertSonFrameConst(maxbx,bx,LEFT);
	  minbx=InicFrameConst(FUNCION,MIN);
	  insertSonFrameConst(minbx,bx,LEFT);
	  maxbxminbx=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(maxbxminbx,maxbx,LEFT);
	  insertSonFrameConst(maxbxminbx,minbx,RIGHT);
	  impmaxbxminbx=InicFrameConst(FUNCION,IMP);
	  insertSonFrameConst(impmaxbxminbx,maxbxminbx,LEFT);
	  insertSonFrameConst(impmaxbxminbx,rp,RIGHT);
	  indy=InicFrameConst(PREDICADO,IN);
	  insertSonFrameConst(indy,getRigSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  insertSonFrameConst(indy,impmaxbxminbx,RIGHT);
	  adicListaFC(ListOfIndex,indy);
	}
      break;

    case MEN:
       if(lineal)
	{
	  if(typelef==VARIABLE || typelef==CONSTANTE)
	    ni=InicFrameConst(CONSTANTE,1);
	  else
	    ni=getLefSonFrameConst(sonlef);
	  delta=InicFrameConst(FUNCION,SUBS);
	  insertSonFrameConst(delta,sonrig,LEFT);
	  insertSonFrameConst(delta,InicFrameConst(CONSTANTE,1),RIGHT);
	  rlef=InicFrameConst(CONSTANTE,MININ);
	  rrig=InicFrameConst(FUNCION,DIV);
	  insertSonFrameConst(rrig,SupremoFrameConst(delta),LEFT);
	  insertSonFrameConst(rrig,ni,RIGHT);
	  r=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(r,rlef,LEFT);
	  insertSonFrameConst(r,FloorFrameConst(rrig),RIGHT);
	  indexical=InicFrameConst(PREDICADO,IN);
	  if(typelef == VARIABLE || typelef == CONSTANTE)
	    insertSonFrameConst(indexical,sonlef,LEFT);
	  else
	    insertSonFrameConst(indexical,getRigSonFrameConst(sonlef),LEFT);
	  insertSonFrameConst(indexical,r,RIGHT);
	  adicListaFC(ListOfIndex,indexical);
	}
      else
	{
	  domy=InicFrameConst(FUNCION,DOM);
	  insertSonFrameConst(domy,getRigSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  conjdomy0=InicFrameConst(FUNCION,AND);
	  insertSonFrameConst(conjdomy0,domy,LEFT);
	  insertSonFrameConst(conjdomy0,InicFrameConst(CONSTANTE,0),RIGHT);
	  impdomy0=InicFrameConst(FUNCION,IMP);
	  insertSonFrameConst(impdomy0,conjdomy0,LEFT);
	  insertSonFrameConst(impdomy0,InicFrameConst(CONSTANTE,0),RIGHT);
	  disjimpdomy01=InicFrameConst(FUNCION,OR);
	  insertSonFrameConst(disjimpdomy01,impdomy0,LEFT);
	  insertSonFrameConst(disjimpdomy01,InicFrameConst(CONSTANTE,1),RIGHT);
	  by=InicFrameConst(VARIABLE,*newvalue);
	  (*newvalue)--;
	  indby=InicFrameConst(PREDICADO,IN);
	  insertSonFrameConst(indby,by,LEFT);
	  insertSonFrameConst(indby,disjimpdomy01,RIGHT);
	  adicListaFC(ListOfIndex,indby);
	  
	  rmax=InicFrameConst(FUNCION,MAX);
	  insertSonFrameConst(rmax,getRigSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  rmin=InicFrameConst(FUNCION,MIN);
	  insertSonFrameConst(rmin,getRigSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  rlef=InicFrameConst(CONSTANTE,MININ);
	  delta=InicFrameConst(FUNCION,SUBS);
	  insertSonFrameConst(delta,getRigSonFrameConst(f),LEFT);
	  insertSonFrameConst(delta,InicFrameConst(CONSTANTE,1),RIGHT);
	  rrig=InicFrameConst(FUNCION,DIV);
	  insertSonFrameConst(rrig,SupremoFrameConst(delta),LEFT);
	  insertSonFrameConst(rrig,rmin,RIGHT);
	  r=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(r,rlef,LEFT);
	  insertSonFrameConst(r,FloorFrameConst(rrig),RIGHT);

	  maxby=InicFrameConst(FUNCION,MAX);
	  insertSonFrameConst(maxby,by,LEFT);
	  minby=InicFrameConst(FUNCION,MIN);
	  insertSonFrameConst(minby,by,LEFT);
	  maxbyminby=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(maxbyminby,maxby,LEFT);
	  insertSonFrameConst(maxbyminby,minby,RIGHT);
	  impmaxbyminby=InicFrameConst(FUNCION,IMP);
	  insertSonFrameConst(impmaxbyminby,maxbyminby,LEFT);
	  insertSonFrameConst(impmaxbyminby,r,RIGHT);
	  indx=InicFrameConst(PREDICADO,IN);
	  insertSonFrameConst(indx,getLefSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  insertSonFrameConst(indx,impmaxbyminby,RIGHT);
	  adicListaFC(ListOfIndex,indx);
	  domx=InicFrameConst(FUNCION,DOM);
	  insertSonFrameConst(domx,getLefSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  conjdomx0=InicFrameConst(FUNCION,AND);
	  insertSonFrameConst(conjdomx0,domx,LEFT);
	  insertSonFrameConst(conjdomx0,InicFrameConst(CONSTANTE,0),RIGHT);
	  impdomx0=InicFrameConst(FUNCION,IMP);
	  insertSonFrameConst(impdomx0,conjdomx0,LEFT);
	  insertSonFrameConst(impdomx0,InicFrameConst(CONSTANTE,0),RIGHT);
	  disjimpdomx01=InicFrameConst(FUNCION,OR);
	  insertSonFrameConst(disjimpdomx01,impdomx0,LEFT);
	  insertSonFrameConst(disjimpdomx01,InicFrameConst(CONSTANTE,1),RIGHT);
	  bx=InicFrameConst(VARIABLE,*newvalue);
	  (*newvalue)--;
	  indbx=InicFrameConst(PREDICADO,IN);
	  insertSonFrameConst(indbx,bx,LEFT);
	  insertSonFrameConst(indbx,disjimpdomx01,RIGHT);
	  adicListaFC(ListOfIndex,indbx);

	  rpmax=InicFrameConst(FUNCION,MAX);
	  insertSonFrameConst(rpmax,getLefSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  rpmin=InicFrameConst(FUNCION,MIN);
	  insertSonFrameConst(rpmin,getLefSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  rpizq=InicFrameConst(CONSTANTE,MININ);
	  rpder=InicFrameConst(FUNCION,DIV);
	  insertSonFrameConst(rpder,SupremoFrameConst(getRigSonFrameConst(f)),LEFT);
	  insertSonFrameConst(rpder,rpmin,RIGHT);
	  rp=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(rp,rpizq,LEFT);
	  insertSonFrameConst(rp,FloorFrameConst(rpder),RIGHT);

	  maxbx=InicFrameConst(FUNCION,MAX);
	  insertSonFrameConst(maxbx,bx,LEFT);
	  minbx=InicFrameConst(FUNCION,MIN);
	  insertSonFrameConst(minbx,bx,LEFT);
	  maxbxminbx=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(maxbxminbx,maxbx,LEFT);
	  insertSonFrameConst(maxbxminbx,minbx,RIGHT);
	  impmaxbxminbx=InicFrameConst(FUNCION,IMP);
	  insertSonFrameConst(impmaxbxminbx,maxbxminbx,LEFT);
	  insertSonFrameConst(impmaxbxminbx,rp,RIGHT);
	  indy=InicFrameConst(PREDICADO,IN);
	  insertSonFrameConst(indy,getRigSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  insertSonFrameConst(indy,impmaxbxminbx,RIGHT);
	  adicListaFC(ListOfIndex,indy);
	}
      break;

    case MAY:
      if(lineal)
	{
	  if(typelef==VARIABLE || typelef==CONSTANTE)
	    ni=InicFrameConst(CONSTANTE,1);
	  else
	    ni=getLefSonFrameConst(sonlef);
	  delta=InicFrameConst(FUNCION,ADD);
	  insertSonFrameConst(delta,sonrig,LEFT);
	  insertSonFrameConst(delta,InicFrameConst(CONSTANTE,1),RIGHT);
	  rlef=InicFrameConst(FUNCION,DIV);
	  insertSonFrameConst(rlef,InfimoFrameConst(delta),LEFT);
	  insertSonFrameConst(rlef,ni,RIGHT);
	  rrig=InicFrameConst(CONSTANTE,MAXIN);
	  r=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(r,CeilFrameConst(rlef),LEFT);
	  insertSonFrameConst(r,rrig,RIGHT);
	  indexical=InicFrameConst(PREDICADO,IN);
	  if(typelef == VARIABLE || typelef == CONSTANTE)
	    insertSonFrameConst(indexical,sonlef,LEFT);
	  else
	    insertSonFrameConst(indexical,getRigSonFrameConst(sonlef),LEFT);
	  insertSonFrameConst(indexical,r,RIGHT);
	  adicListaFC(ListOfIndex,indexical);
	}
      else
	{
	  domy=InicFrameConst(FUNCION,DOM);
	  insertSonFrameConst(domy,getRigSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  conjdomy0=InicFrameConst(FUNCION,AND);
	  insertSonFrameConst(conjdomy0,domy,LEFT);
	  insertSonFrameConst(conjdomy0,InicFrameConst(CONSTANTE,0),RIGHT);
	  impdomy0=InicFrameConst(FUNCION,IMP);
	  insertSonFrameConst(impdomy0,conjdomy0,LEFT);
	  insertSonFrameConst(impdomy0,InicFrameConst(CONSTANTE,0),RIGHT);
	  disjimpdomy01=InicFrameConst(FUNCION,OR);
	  insertSonFrameConst(disjimpdomy01,impdomy0,LEFT);
	  insertSonFrameConst(disjimpdomy01,InicFrameConst(CONSTANTE,1),RIGHT);
	  by=InicFrameConst(VARIABLE,*newvalue);
	  (*newvalue)--;
	  indby=InicFrameConst(PREDICADO,IN);
	  insertSonFrameConst(indby,by,LEFT);
	  insertSonFrameConst(indby,disjimpdomy01,RIGHT);
	  adicListaFC(ListOfIndex,indby);
	  
	  rmax=InicFrameConst(FUNCION,MAX);
	  insertSonFrameConst(rmax,getRigSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  rmin=InicFrameConst(FUNCION,MIN);
	  insertSonFrameConst(rmin,getRigSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  delta=InicFrameConst(FUNCION,ADD);
	  insertSonFrameConst(delta,getRigSonFrameConst(f),LEFT);
	  insertSonFrameConst(delta,InicFrameConst(CONSTANTE,1),RIGHT);
	  rlef=InicFrameConst(FUNCION,DIV);
	  insertSonFrameConst(rlef,InfimoFrameConst(delta),LEFT);
	  insertSonFrameConst(rlef,rmax,RIGHT);
	  rrig=InicFrameConst(CONSTANTE,MAXIN);
	  r=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(r,CeilFrameConst(rlef),LEFT);
	  insertSonFrameConst(r,rrig,RIGHT);

	  maxby=InicFrameConst(FUNCION,MAX);
	  insertSonFrameConst(maxby,by,LEFT);
	  minby=InicFrameConst(FUNCION,MIN);
	  insertSonFrameConst(minby,by,LEFT);
	  maxbyminby=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(maxbyminby,maxby,LEFT);
	  insertSonFrameConst(maxbyminby,minby,RIGHT);
	  impmaxbyminby=InicFrameConst(FUNCION,IMP);
	  insertSonFrameConst(impmaxbyminby,maxbyminby,LEFT);
	  insertSonFrameConst(impmaxbyminby,r,RIGHT);
	  indx=InicFrameConst(PREDICADO,IN);
	  insertSonFrameConst(indx,getLefSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  insertSonFrameConst(indx,impmaxbyminby,RIGHT);
	  adicListaFC(ListOfIndex,indx);
	  domx=InicFrameConst(FUNCION,DOM);
	  insertSonFrameConst(domx,getLefSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  conjdomx0=InicFrameConst(FUNCION,AND);
	  insertSonFrameConst(conjdomx0,domx,LEFT);
	  insertSonFrameConst(conjdomx0,InicFrameConst(CONSTANTE,0),RIGHT);
	  impdomx0=InicFrameConst(FUNCION,IMP);
	  insertSonFrameConst(impdomx0,conjdomx0,LEFT);
	  insertSonFrameConst(impdomx0,InicFrameConst(CONSTANTE,0),RIGHT);
	  disjimpdomx01=InicFrameConst(FUNCION,OR);
	  insertSonFrameConst(disjimpdomx01,impdomx0,LEFT);
	  insertSonFrameConst(disjimpdomx01,InicFrameConst(CONSTANTE,1),RIGHT);
	  bx=InicFrameConst(VARIABLE,*newvalue);
	  (*newvalue)--;
	  indbx=InicFrameConst(PREDICADO,IN);
	  insertSonFrameConst(indbx,bx,LEFT);
	  insertSonFrameConst(indbx,disjimpdomx01,RIGHT);
	  adicListaFC(ListOfIndex,indbx);

	  rpmax=InicFrameConst(FUNCION,MAX);
	  insertSonFrameConst(rpmax,getLefSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  rpmin=InicFrameConst(FUNCION,MIN);
	  insertSonFrameConst(rpmin,getLefSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  rpizq=InicFrameConst(FUNCION,DIV);
	  insertSonFrameConst(rpizq,InfimoFrameConst(getRigSonFrameConst(f)),LEFT);
	  insertSonFrameConst(rpizq,rpmax,RIGHT);
	  rpder=InicFrameConst(CONSTANTE,MAXIN);
	  rp=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(rp,CeilFrameConst(rpizq),LEFT);
	  insertSonFrameConst(rp,rpder,RIGHT);

	  maxbx=InicFrameConst(FUNCION,MAX);
	  insertSonFrameConst(maxbx,bx,LEFT);
	  minbx=InicFrameConst(FUNCION,MIN);
	  insertSonFrameConst(minbx,bx,LEFT);
	  maxbxminbx=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(maxbxminbx,maxbx,LEFT);
	  insertSonFrameConst(maxbxminbx,minbx,RIGHT);
	  impmaxbxminbx=InicFrameConst(FUNCION,IMP);
	  insertSonFrameConst(impmaxbxminbx,maxbxminbx,LEFT);
	  insertSonFrameConst(impmaxbxminbx,rp,RIGHT);
	  indy=InicFrameConst(PREDICADO,IN);
	  insertSonFrameConst(indy,getRigSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  insertSonFrameConst(indy,impmaxbxminbx,RIGHT);
	  adicListaFC(ListOfIndex,indy);
	}
      break;

    case DIF:
      if(lineal)
	{
	  if(typelef==VARIABLE || typelef==CONSTANTE)
	    ni=InicFrameConst(CONSTANTE,1);
	  else
	    ni=getLefSonFrameConst(sonlef);

	  rlef=InicFrameConst(FUNCION,DIV);
	  insertSonFrameConst(rlef,SupremoFrameConst(sonrig),LEFT);
	  insertSonFrameConst(rlef,ni,RIGHT);
	  rrig=InicFrameConst(FUNCION,DIV);
	  insertSonFrameConst(rrig,InfimoFrameConst(sonrig),LEFT);
	  insertSonFrameConst(rrig,ni,RIGHT);
	  r=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(r,FloorFrameConst(rlef),LEFT);
	  insertSonFrameConst(r,CeilFrameConst(rrig),RIGHT);

	  indexical=InicFrameConst(PREDICADO,IN);
	  if(typelef == VARIABLE || typelef == CONSTANTE)
	    insertSonFrameConst(indexical,sonlef,LEFT);
	  else
	    insertSonFrameConst(indexical,getRigSonFrameConst(sonlef),LEFT);
	  insertSonFrameConst(indexical,ComplementFrameConst(r),RIGHT);
	  adicListaFC(ListOfIndex,indexical);
	}
      else
	{
	  domy=InicFrameConst(FUNCION,DOM);
	  insertSonFrameConst(domy,getRigSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  conjdomy0=InicFrameConst(FUNCION,AND);
	  insertSonFrameConst(conjdomy0,domy,LEFT);
	  insertSonFrameConst(conjdomy0,InicFrameConst(CONSTANTE,0),RIGHT);
	  impdomy0=InicFrameConst(FUNCION,IMP);
	  insertSonFrameConst(impdomy0,conjdomy0,LEFT);
	  insertSonFrameConst(impdomy0,InicFrameConst(CONSTANTE,0),RIGHT);
	  disjimpdomy01=InicFrameConst(FUNCION,OR);
	  insertSonFrameConst(disjimpdomy01,impdomy0,LEFT);
	  insertSonFrameConst(disjimpdomy01,InicFrameConst(CONSTANTE,1),RIGHT);
	  by=InicFrameConst(VARIABLE,*newvalue);
	  (*newvalue)--;
	  indby=InicFrameConst(PREDICADO,IN);
	  insertSonFrameConst(indby,by,LEFT);
	  insertSonFrameConst(indby,disjimpdomy01,RIGHT);
	  adicListaFC(ListOfIndex,indby);
	  
	  rmax=InicFrameConst(FUNCION,MAX);
	  insertSonFrameConst(rmax,getRigSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  rmin=InicFrameConst(FUNCION,MIN);
	  insertSonFrameConst(rmin,getRigSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  rlef=InicFrameConst(FUNCION,DIV);
	  insertSonFrameConst(rlef,InfimoFrameConst(getRigSonFrameConst(f)),LEFT);
	  insertSonFrameConst(rlef,rmax,RIGHT);
	  rrig=InicFrameConst(FUNCION,DIV);
	  insertSonFrameConst(rrig,SupremoFrameConst(getRigSonFrameConst(f)),LEFT);
	  insertSonFrameConst(rrig,rmin,RIGHT);
	  comp=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(comp,FloorFrameConst(rrig),LEFT);
	  insertSonFrameConst(comp,CeilFrameConst(rlef),RIGHT);
	  r=InicFrameConst(FUNCION,COMP);
	  insertSonFrameConst(r,comp,LEFT);

	  maxby=InicFrameConst(FUNCION,MAX);
	  insertSonFrameConst(maxby,by,LEFT);
	  minby=InicFrameConst(FUNCION,MIN);
	  insertSonFrameConst(minby,by,LEFT);
	  maxbyminby=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(maxbyminby,maxby,LEFT);
	  insertSonFrameConst(maxbyminby,minby,RIGHT);
	  impmaxbyminby=InicFrameConst(FUNCION,IMP);
	  insertSonFrameConst(impmaxbyminby,maxbyminby,LEFT);
	  insertSonFrameConst(impmaxbyminby,r,RIGHT);
	  indx=InicFrameConst(PREDICADO,IN);
	  insertSonFrameConst(indx,getLefSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  insertSonFrameConst(indx,impmaxbyminby,RIGHT);
	  adicListaFC(ListOfIndex,indx);
	  domx=InicFrameConst(FUNCION,DOM);
	  insertSonFrameConst(domx,getLefSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  conjdomx0=InicFrameConst(FUNCION,AND);
	  insertSonFrameConst(conjdomx0,domx,LEFT);
	  insertSonFrameConst(conjdomx0,InicFrameConst(CONSTANTE,0),RIGHT);
	  impdomx0=InicFrameConst(FUNCION,IMP);
	  insertSonFrameConst(impdomx0,conjdomx0,LEFT);
	  insertSonFrameConst(impdomx0,InicFrameConst(CONSTANTE,0),RIGHT);
	  disjimpdomx01=InicFrameConst(FUNCION,OR);
	  insertSonFrameConst(disjimpdomx01,impdomx0,LEFT);
	  insertSonFrameConst(disjimpdomx01,InicFrameConst(CONSTANTE,1),RIGHT);
	  bx=InicFrameConst(VARIABLE,*newvalue);
	  (*newvalue)--;
	  indbx=InicFrameConst(PREDICADO,IN);
	  insertSonFrameConst(indbx,bx,LEFT);
	  insertSonFrameConst(indbx,disjimpdomx01,RIGHT);
	  adicListaFC(ListOfIndex,indbx);

	  rpmax=InicFrameConst(FUNCION,MAX);
	  insertSonFrameConst(rpmax,getLefSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  rpmin=InicFrameConst(FUNCION,MIN);
	  insertSonFrameConst(rpmin,getLefSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  rpizq=InicFrameConst(FUNCION,DIV);
	  insertSonFrameConst(rpizq,InfimoFrameConst(getRigSonFrameConst(f)),LEFT);
	  insertSonFrameConst(rpizq,rpmax,RIGHT);
	  rpder=InicFrameConst(FUNCION,DIV);
	  insertSonFrameConst(rpder,SupremoFrameConst(getRigSonFrameConst(f)),LEFT);
	  insertSonFrameConst(rpder,rpmin,RIGHT);
	  comp1=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(comp1,FloorFrameConst(rpder),LEFT);
	  insertSonFrameConst(comp1,CeilFrameConst(rpizq),RIGHT);
	  rp=InicFrameConst(FUNCION,COMP);
	  insertSonFrameConst(rp,comp,LEFT);


	  maxbx=InicFrameConst(FUNCION,MAX);
	  insertSonFrameConst(maxbx,bx,LEFT);
	  minbx=InicFrameConst(FUNCION,MIN);
	  insertSonFrameConst(minbx,bx,LEFT);
	  maxbxminbx=InicFrameConst(FUNCION,RANGE);
	  insertSonFrameConst(maxbxminbx,maxbx,LEFT);
	  insertSonFrameConst(maxbxminbx,minbx,RIGHT);
	  impmaxbxminbx=InicFrameConst(FUNCION,IMP);
	  insertSonFrameConst(impmaxbxminbx,maxbxminbx,LEFT);
	  insertSonFrameConst(impmaxbxminbx,rp,RIGHT);
	  indy=InicFrameConst(PREDICADO,IN);
	  insertSonFrameConst(indy,getRigSonFrameConst(getLefSonFrameConst(f)),LEFT);
	  insertSonFrameConst(indy,impmaxbxminbx,RIGHT);
	  adicListaFC(ListOfIndex,indy);
	}
      break;
    }
  return ListOfIndex;
}

#endif

/**** EOF ****/



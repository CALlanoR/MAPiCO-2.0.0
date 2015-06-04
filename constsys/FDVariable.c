#ifndef _FDVariable_c
#define _FDVariable_c
/****************************************************************
* IMPLEMENTACION MODULO: FDVariable.c
* FECHA CREACION:  21-Mar-01
* DESCRIPCION: 
*   Implementa el modelo utilizado para representar las
*   variables de dominio finito.
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
       gcc -c FDVariable.c

  1. Librerias requeridas para su linkeo:
       -lm -lX11

  2. Listado de estructuras de datos definidas (publicas y privadas)
     typedef struct 
     {
     Lista Chain_Val; 
     Lista Chain_Dom;
     Lista Chain_Min; 
     Lista Chain_Max;
     Lista Chain_MinMax; 
     Domain domain; 
     int Time_Stamp; 
     }TFDVariable,*FDVariable;

  3. Listado de funciones definidas (publicas y privadas)
     FDVariable InicFDVariable(void)
     FDVariable InicpFDVariable(int,int,Indexicals)
     FDVariable Inicp1FDVariable(FDVariable)
     Domain getDomainFDVariable(FDVariable)
     Lista getChainValFDVariable(FDVariable)
     Lista getChainDomFDVariable(FDVariable)
     Lista getChainMinFDVariable(FDVariable)
     Lista getChainMaxFDVariable(FDVariable)
     Lista getChainMinMaxFDVariable(FDVariable)
     int getPruneTypeFDVariable(FDVariable)
     int getTime_StampFDVariable(FDVariable)
     void setruneTypeFDVariable(FDVariable,int)
     void setStampFDVariable(FDVariable,int)
     void setChainValFDVariable(FDVariable,Lista)
     void setChainDomFDVariable(FDVariable,Lista)
     void setChainMinFDVariable(FDVariable,Lista)
     void setChainMaxFDVariable(FDVariable,Lista)
     void setChainMinMaxFDVariable(FDVariable,Lista)
     void setDomainFDVariable(FDVariable,Domain)
     void updateDepFDVariable(FDVariable,int, Indexical,int)
     void desrefDepFDVariable(FDVariable, int)
     int isConsistentFDVariable(FDVariable)
     int isDeterminatedFDVariable(FDVariable)
     void ImprimirFDVariable(FDVariable)
     void freeFDVariable(FDVariable)

  4. Instruccion para modificar el modulo
  4.1 Construcciones importantes para tener en cuenta (e.g. tipos, variables, funciones)
  4.2 Observaciones Adicionales
  
  ===============================================================*/

/*--------------------------------------------------------------*
  Archivos de Interfaz de librerias estandar y de otros modulos
 *--------------------------------------------------------------*/

#include "FDVariable.h"
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
FDVariable InicFDVariable(void)
/*---------------------------------------------------------------
  DESCRIPCION: Crea una variablede dominio finito.

  PARAMETROS: 
  USA:
  RETORNA: Un puntero a la variable creada
  PRE:
  POS: fdvariable=dir || fdvariable=NULL 
  NOTAS:
  ---------------------------------------------------------------*/
{
  FDVariable fdvariable;

  fdvariable = ( FDVariable )malloc( sizeof( TFDVariable ) );
  if (!fdvariable)
    {
      printf("Error en la asignacion de memoria para FDVariable");
      exit(1);
    }
  fdvariable->Chain_Val=inicLista();
  fdvariable->Chain_Dom=inicLista();
  fdvariable->Chain_Min=inicLista(); 
  fdvariable->Chain_Max=inicLista();
  fdvariable->Chain_MinMax=inicLista();
  fdvariable->domain=InicDomain();
  fdvariable->Time_Stamp=-1;

  return fdvariable;
}

FDVariable InicpFDVariable(int id,int s,Indexicals indexicals)
/*---------------------------------------------------------------
  DESCRIPCION: Crea una variable de dominio finito.

  PARAMETROS: id:identificador de la variable
              s:estampa de tiempo de la variable  
              indexicals:indexicals del store   
  USA:
  RETORNA: Un puntero a la variable creada
  PRE:
  POS: fdvariable=dir || fdvariable=NULL 
  NOTAS:
  ---------------------------------------------------------------*/
{
  int tam,pos;
  FDVariable fdvariable;
  Indexical aux;
  
  fdvariable = ( FDVariable )malloc( sizeof( TFDVariable ) );
  if (!fdvariable)
    {
      printf("Error en la asignacion de memoria para FDVariable");
      exit(1);
    }
  fdvariable->Chain_Val=inicLista();
  fdvariable->Chain_Dom=inicLista();
  fdvariable->Chain_Min=inicLista(); 
  fdvariable->Chain_Max=inicLista();
  fdvariable->Chain_MinMax=inicLista();
  tam = sizeIndexicals(indexicals);
  for(pos=0;pos<=tam;pos++)
    {
      aux = elementAtIndexicals(indexicals,pos);
      if ( aux != NULL )
	{
	  updateDepFDVariable(fdvariable,pos,aux,id);
	  freeIndexical(aux);
	}
    }
  fdvariable->domain=InicDomain();
  fdvariable->Time_Stamp=s;

  return fdvariable;
}

FDVariable Inicp1FDVariable(FDVariable fv)
/*---------------------------------------------------------------
  DESCRIPCION: Crea una variable de dominio finito.

  PARAMETROS: fv : Una variable de dominio finito.
  USA:
  RETORNA: Un puntero a la variable creada
  PRE:
  POS: fdvariable=dir || fdvariable=NULL 
  NOTAS:
  ---------------------------------------------------------------*/
{
  FDVariable fdvariable;

  if(fv != NULL)
    {
      fdvariable=InicFDVariable();
      setChainValFDVariable(fdvariable, getChainValFDVariable(fv));
      setChainDomFDVariable(fdvariable, getChainDomFDVariable(fv));
      setChainMinFDVariable(fdvariable, getChainMinFDVariable(fv));
      setChainMaxFDVariable(fdvariable,getChainMaxFDVariable(fv));
      setChainMinMaxFDVariable(fdvariable, getChainMinMaxFDVariable(fv));
      setDomainFDVariable(fdvariable,getDomainFDVariable(fv));
      setStampFDVariable(fdvariable, getStampFDVariable(fv));
      return fdvariable;
    }
  else
      return NULL;
}

Domain getDomainFDVariable(FDVariable fv)
/*---------------------------------------------------------------
  DESCRIPCION: retorna el domino de la variable

  PARAMETROS: fv:la variable de dominio finito
  USA:
  RETORNA: un puntero al domino de la variable
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  return fv->domain;
}

Lista getChainValFDVariable(FDVariable fv)
/*---------------------------------------------------------------
  DESCRIPCION: retorna la lista de dependencias de valor

  PARAMETROS: fv:la variable de dominio finito
  USA:
  RETORNA: un puntero a la lista de dependencias de valor
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  return fv->Chain_Val;
}

Lista getChainDomFDVariable(FDVariable fv)
/*---------------------------------------------------------------
  DESCRIPCION: retorna la lista de dependencias de dominio

  PARAMETROS: fv:la variable de dominio finito
  USA:
  RETORNA: un puntero a la lista de dependencias de dominio
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  return fv->Chain_Dom;
}

Lista getChainMinFDVariable(FDVariable fv)
/*---------------------------------------------------------------
  DESCRIPCION: retorna la lista de dependencias de minimo

  PARAMETROS: fv:la variable de dominio finito
  USA:
  RETORNA: un puntero a la lista de dependencias de minimo
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  return fv->Chain_Min;
}

Lista getChainMaxFDVariable(FDVariable fv)
/*---------------------------------------------------------------
  DESCRIPCION: retorna la lista de dependencias de maximo

  PARAMETROS: fv:la variable de dominio finito
  USA:
  RETORNA: un puntero a la lista de dependencias de maximo
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  return fv->Chain_Max;
}

Lista getChainMinMaxFDVariable(FDVariable fv)
/*---------------------------------------------------------------
  DESCRIPCION: retorna la lista de dependencias de minimo y maximo

  PARAMETROS: fv:la variable de dominio finito
  USA:
  RETORNA: un puntero a la lista de dependencias de minimo y maximo
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  return fv->Chain_MinMax;
}

int getPruneTypeFDVariable(FDVariable fv)
/*---------------------------------------------------------------
  DESCRIPCION: retorna el tipo de poda del dominio de la variable

  PARAMETROS: fv:la variable de dominio finito
  USA:
  RETORNA: el tipo de poda del dominio de la variable fv.
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  int res;
  res=getPruneTypeDomain(fv->domain);
  return res;
}

int getStampFDVariable(FDVariable fv)
/*---------------------------------------------------------------
  DESCRIPCION: retorna la estampa de la variable

  PARAMETROS: fv:la variable de dominio finito
  USA:
  RETORNA:la estampa de la variable fv.
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  int s;
  s=fv->Time_Stamp;
  return s;
}

void setPruneTypeFDVariable(FDVariable fv,int t)
/*---------------------------------------------------------------
  DESCRIPCION: actualiza el tipo de poda del dominio de la variable

  PARAMETROS: fv:la variable de dominio finito
              t:el nuevo tipo de poda 
  USA:
  RETORNA: 
  PRE:
  POS: fv->domain->prune_type=t
  NOTAS:
  ---------------------------------------------------------------*/
{
  setPruneTypeDomain(fv->domain,t);
}


void setStampFDVariable(FDVariable fv,int s)
/*---------------------------------------------------------------
  DESCRIPCION:actualiza la estampa de la variable
  PARAMETROS: fv:la variable de dominio finito
              s:el nuevo valor de la estampa
  USA:
  RETORNA:
  PRE:
  POS: fv->Time_Stamp=s
  NOTAS:
  ---------------------------------------------------------------*/
{
  fv->Time_Stamp=s;
}

void setChainValFDVariable(FDVariable fv,Lista l)
/*---------------------------------------------------------------
  DESCRIPCION:actualiza la lista de dependencias de valor de la
              variable
  PARAMETROS: fv:la variable de dominio finito
              l:la nueva lista de dependencias de valor
  USA:
  RETORNA:
  PRE:
  POS: fv->Chain_Val=l
  NOTAS:
  ---------------------------------------------------------------*/
{
  copiaLista(fv->Chain_Val,l);
}

void setChainDomFDVariable(FDVariable fv,Lista l)
/*---------------------------------------------------------------
  DESCRIPCION:actualiza la lista de dependencias de dominio de la
              variable
  PARAMETROS: fv:la variable de dominio finito
              l:la nueva lista de dependencias de dominio
  USA:
  RETORNA:
  PRE:
  POS: fv->Chain_Dom=l
  NOTAS:
  ---------------------------------------------------------------*/
{
  copiaLista(fv->Chain_Dom,l);
}

void setChainMinFDVariable(FDVariable fv,Lista l)
/*---------------------------------------------------------------
  DESCRIPCION:actualiza la lista de dependencias de minimo de la
              variable
  PARAMETROS: fv:la variable de dominio finito
              l:la nueva lista de dependencias de minimo
  USA:
  RETORNA:
  PRE:
  POS: fv->Chain_Min=l
  NOTAS:
  ---------------------------------------------------------------*/
{
  copiaLista(fv->Chain_Min,l);
}

void setChainMaxFDVariable(FDVariable fv,Lista l)
/*---------------------------------------------------------------
  DESCRIPCION:actualiza la lista de dependencias de maximo de la
              variable
  PARAMETROS: fv:la variable de dominio finito
              l:la nueva lista de dependencias de maximo
  USA:
  RETORNA:
  PRE:
  POS: fv->Chain_Max=l
  NOTAS:
  ---------------------------------------------------------------*/
{
  copiaLista(fv->Chain_Max,l);
}

void setChainMinMaxFDVariable(FDVariable fv,Lista l)
/*---------------------------------------------------------------
  DESCRIPCION:actualiza la lista de dependencias de minmax
              de la variable
  PARAMETROS: fv:la variable de dominio finito
              l:la nueva lista de dependencias de minmax
  USA:
  RETORNA:
  PRE:
  POS: fv->Chain_MinMax=l
  NOTAS:
  ---------------------------------------------------------------*/
{
  copiaLista(fv->Chain_MinMax,l);
}

void setDomainFDVariable(FDVariable fv,Domain d)
/*---------------------------------------------------------------
  DESCRIPCION:actualiza el dominio de la variable fv
  
  PARAMETROS: fv:la variable de dominio finito
              d:el nuevo dominio de la variable
  USA:
  RETORNA:
  PRE:
  POS: fv->domain=d
  NOTAS:
  ---------------------------------------------------------------*/
{
  setMinimumDomain(fv->domain, getMinimumDomain(d));
  setMaximumDomain(fv->domain, getMaximumDomain(d));
  setPruneTypeDomain(fv->domain, getPruneTypeDomain(d));
  setExpandedDomain(fv->domain, getExpandedDomain(d));
  setInfoDomain(fv->domain, getInfoDomain(d));
}

void updateDepFDVariable(FDVariable fv,int pos, Indexical indexical,int key)
/*---------------------------------------------------------------
  DESCRIPCION:actualiza las dependencias de la variable con respecto 
              a indexical.
  
  PARAMETROS: fv:la variable de dominio finito
              pos:la posicion del indexical en los indexicals del
	          sistema de restricciones
              indexical:el indexical
              key: el identificador de la variable en el store
  USA:
  RETORNA:
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  int dep,b,element;

  dep = DependencyType(indexical, key);
  switch(dep){
  case DINT:
    b=FALSE;
    for(primLista(fv->Chain_Val);!finLista(fv->Chain_Val);sigLista(fv->Chain_Val))
      {
	element=infoLista(fv->Chain_Val);
	if(element==pos)
	  {
	    b=TRUE;
	    break;
	  }
	else
	  if(element>pos)
	    {
	      insLista(fv->Chain_Val,pos);
	      b = TRUE;
	    }
      }
    posLista(fv->Chain_Val,longLista(fv->Chain_Val));
    if (!b)
      anxLista(fv->Chain_Val,pos);
    break;

  case DDOM:
    b=FALSE;
    for(primLista(fv->Chain_Dom);!finLista(fv->Chain_Dom);sigLista(fv->Chain_Dom))
      {
	element=infoLista(fv->Chain_Dom);
	if(element==pos)
	  {
	    b=TRUE;
	    break;
	  }
	else
	  if(element>pos)
	    {
	      insLista(fv->Chain_Dom,pos);
	      b = TRUE;
	    }
      }
    posLista(fv->Chain_Dom,longLista(fv->Chain_Dom));
    if (!b)
      anxLista(fv->Chain_Dom,pos);
    break;
    
  case DMIN:
    b=FALSE;
    for(primLista(fv->Chain_Min);!finLista(fv->Chain_Min);sigLista(fv->Chain_Min))
      {
	element=infoLista(fv->Chain_Min);
	if(element==pos)
	  {
	    b=TRUE;
	    break;
	  }
	else
	  if(element>pos)
	    {
	      insLista(fv->Chain_Min,pos);
	      b = TRUE;
	    }
      }
    posLista(fv->Chain_Min,longLista(fv->Chain_Min));
    if (!b)
      anxLista(fv->Chain_Min,pos);
    break;
    
  case DMAX:
    b=FALSE;
    for(primLista(fv->Chain_Max);!finLista(fv->Chain_Max);sigLista(fv->Chain_Max))
      {
	element=infoLista(fv->Chain_Max);
	if(element==pos)
	  {
	    b=TRUE;
	    break;
	  }
	else
	  if(element>pos)
	    {
	      insLista(fv->Chain_Max,pos);
	      b = TRUE;
	    }
      }
    posLista(fv->Chain_Max,longLista(fv->Chain_Max));
    if (!b)
      anxLista(fv->Chain_Max,pos);
    break;
    
  case DMINMAX:
    b=FALSE;
    for(primLista(fv->Chain_MinMax);!finLista(fv->Chain_MinMax);sigLista(fv->Chain_MinMax))
      {
	element=infoLista(fv->Chain_MinMax);
	if(element==pos)
	  {
	    b=TRUE;
	    break;
	  }
	else
	  if(element>pos)
	    {
	      insLista(fv->Chain_MinMax,pos);
	      b = TRUE;
	    }
      }
    posLista(fv->Chain_MinMax,longLista(fv->Chain_MinMax));
    if (!b)
      anxLista(fv->Chain_MinMax,pos);
    break;

  default:;
  }
}

void desrefDepFDVariable(FDVariable fv, int pos)
/*---------------------------------------------------------------
  DESCRIPCION: Desreferencia las dependencias de la variable fv
               con respecto al indexical ubicado en la posicion
	       pos dentro de indexicals.
              
  PARAMETROS: fv:la variable de dominio finito
              pos:la posicion del indexical dentro de indexicals del
	          sistema de restricciones
  USA:
  RETORNA:
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  int position;

  position = miembroLista(fv->Chain_Val, pos);
  if(position)
    {
      posLista(fv->Chain_Val, position);
      elimLista(fv->Chain_Val);
    }
  
  position = miembroLista(fv->Chain_Dom, pos);
  if(position)
    {
      posLista(fv->Chain_Dom, position);
      elimLista(fv->Chain_Dom);
    }
  
  position = miembroLista(fv->Chain_Min, pos);
  if(position)
    {
      posLista(fv->Chain_Min, position);
      elimLista(fv->Chain_Min);
    }

  position = miembroLista(fv->Chain_Max, pos);
  if(position)
    {
      posLista(fv->Chain_Max, position);
      elimLista(fv->Chain_Max);
    }

  position = miembroLista(fv->Chain_MinMax, pos);
  if(position)
    {
      posLista(fv->Chain_MinMax, position);
      elimLista(fv->Chain_MinMax);
    }
}

int isConsistentFDVariable(FDVariable fv)
/*---------------------------------------------------------------
  DESCRIPCION: determina si el dominio de la variable fv es
               consistente.
  PARAMETROS: fv:la variable de dominio finito
  USA:
  RETORNA: TRUE || FALSE
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
    return(isConsistentDomain(fv->domain));
}

int isDeterminatedFDVariable(FDVariable fv)
/*---------------------------------------------------------------
  DESCRIPCION: determina si el dominio de la variable fv esta
               determinado.
  PARAMETROS: fv:la variable de dominio finito
  USA:
  RETORNA: TRUE || FALSE
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
    return(isDeterminatedDomain(fv->domain));
}

void ImprimirFDVariable(FDVariable fv)
/*---------------------------------------------------------------
  DESCRIPCION: Imprime toda la variable de dominio finito fv

  PARAMETROS: fv:la variable de dominio finito
  USA:
  RETORNA:
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  ImprimirDomain(fv->domain);
  printf("Val:\n");
  impLista(fv->Chain_Val);
  printf("Dom:\n");
  impLista(fv->Chain_Dom);
  printf("Min:\n");
  impLista(fv->Chain_Min);
  printf("Max:\n");
  impLista(fv->Chain_Max);
  printf("MinMax:\n");
  impLista(fv->Chain_MinMax);
}

void freeFDVariable(FDVariable fdvariable)
/*---------------------------------------------------------------
  DESCRIPCION: Libera la memoria separada para la variable
               fdvariable.
  PARAMETROS: fv:la variable de dominio finito
  USA:
  RETORNA: 
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  if(fdvariable != NULL)
    {
      destruirLista(fdvariable->Chain_Val);
      destruirLista(fdvariable->Chain_Dom);
      destruirLista(fdvariable->Chain_Min);
      destruirLista(fdvariable->Chain_Max);
      destruirLista(fdvariable->Chain_MinMax);
      freeDomain(fdvariable->domain);
      free(fdvariable);
      fdvariable=NULL;
    }
}
#endif

/**** EOF ****/

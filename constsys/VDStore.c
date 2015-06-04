#ifndef _VDStore_c
#define _VDStore_c
/****************************************************************
* IMPLEMENTACION MODULO: VDStore.c
* FECHA CREACION:  22-Mar-01
* DESCRIPCION: 
*   Implementa el store como un vector dinamico
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
       gcc -c VDStore.c

  1. Librerias requeridas para su linkeo:
       -lm -lX11

  2. Listado de estructuras de datos definidas (publicas y privadas)

  typedef struct 
  {  
  FDVariable *variables; vector dinamico que contiene las variables del store
  int position;  posicion hasta donde existen variables en el vector variables
  int size;  Tamaño del vector de variables
  FDVariable *tempvariables;  vector dinamico que contiene las variables temporales del Modelo de Carlsson
  int tempsize; Indice del vector de variables temporales 
  }TVDStore,*VDStore;

  3. Listado de funciones definidas (publicas y privadas)

  VDStore InicVDStore(void)
  VDStore InicpVDStore(Store)
  Store putVDStore(Store, int, FDVariable)
  Store puttempVDStore(Store, int, FDVariable)
  FDVariable  getVDStore(Store, int)
  FDVariable  gettempVDStore(Store, int)
  int getsizeVDStore(Store)
  int gettempsizeVDStore(Store)
  int getpositionVDStore(Store)
  void ImprimirVDStore(Store)
  void freeVDStore(Store)

  4. Instruccion para modificar el modulo
  4.1 Construcciones importantes para tener en cuenta (e.g. tipos, variables, funciones)
  4.2 Observaciones Adicionales
  
  ===============================================================*/

/*--------------------------------------------------------------*
  Archivos de Interfaz de librerias estandar y de otros modulos
 *--------------------------------------------------------------*/
#include "VDStore.h"
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
VDStore InicVDStore(void)
/*---------------------------------------------------------------
  DESCRIPCION: Crea un store como vector dinamico

  PARAMETROS: 
  USA:
  RETORNA: Un puntero al vector dinamico
  PRE:
  POS: vdstore=dir || vdstore=NULL 
  NOTAS:
  ---------------------------------------------------------------*/
{
    int i;
    VDStore store;

    store = ( VDStore )malloc(sizeof( TVDStore ) );
    if (!store)
	{
	    printf("Error en la asignacion de memoria para crear del VDStore");
	    exit(1);
	}
    
    store->variables = (FDVariable *)malloc(TAMINICSTORE*sizeof(FDVariable));
    
    if (!(store->variables))
	{
	    printf("Error en la asignacion de memoria para crear del VDStore");
	    exit(1);
	}
    
    for(i = 0; i < TAMINICSTORE; i++)
	(store->variables)[i] = NULL;
    store->position=-1;
    store->size = TAMINICSTORE;

    /* RESERVA PARA LAS VARIABLES TEMPORALES */
    store->tempvariables = (FDVariable *)malloc(TAMINICTEMPSTORE*sizeof(FDVariable));
    
    if (!(store->tempvariables))
	{
	    printf("Error en la asignacion de memoria para crear del VDStore");
	    exit(1);
	}
    
    for(i = 0; i < TAMINICTEMPSTORE; i++)
	(store->tempvariables)[i] = NULL;
    
    store->tempsize=1;
    
    return store;
}

VDStore InicpVDStore(Store s)
/*---------------------------------------------------------------
  DESCRIPCION: Crea un store como vector dinamico

  PARAMETROS: 
  USA:
  RETORNA: Un puntero al vector dinamico
  PRE:
  POS: vdstore=dir || vdstore=NULL 
  NOTAS:
  ---------------------------------------------------------------*/
{
  int aux, i;
  VDStore store;

  store= ( VDStore )malloc(sizeof( TVDStore ) );
  if (!store)
    {
      printf("Error en la asignacion de memoria para crear del VDStore");
      exit(1);
    }
  store->variables=(FDVariable*)malloc((s->size)*sizeof(FDVariable));
  if (!(store->variables))
    {
      printf("Error en la asignacion de memoria para crear del VDStore");
      exit(1);
    }
  
  aux = getsizeVDStore(s);
  for(i = 0; i < aux; i++)
    (store->variables)[i]=NULL;

  aux = getpositionVDStore(s);
  for(i = 0; i <= aux; i++)
    {
      if (getVDStore(s,i) != NULL)
	(store->variables)[i]= Inicp1FDVariable(getVDStore(s,i));
    }
  
  store->position=getpositionVDStore(s);
  store->size = getsizeVDStore(s);
  
  /* PARA LAS VARIABLES TEMPORALES DEL MODLEO DE CARLSSON */

  store->tempvariables=(FDVariable*)malloc(((s->tempsize)+1)*sizeof(FDVariable));
  if (!(store->tempvariables))
    {
      printf("Error en la asignacion de memoria para crear del VDStore");
      exit(1);
    }
  
  aux = gettempsizeVDStore(s);
  for(i = 0; i <= aux; i++)
    {
      if (gettempVDStore(s,i) != NULL)
      (store->tempvariables)[i]= Inicp1FDVariable(gettempVDStore(s,i));
    }
  
  store->tempsize=gettempsizeVDStore(s);

  return store;
}

Store putVDStore(Store s, int id, FDVariable var)
/*---------------------------------------------------------------
  DESCRIPCION: Adiciona la variable var al vector dinamico VDStore

  PARAMETROS: s: La representacion del store.
              id: Identificador de la variable var.
	      var: La variable que se va adicionar al store.
  USA:
  RETORNA:
  PRE:VDStore[id] = NULL;
  POS:VDStore[id] = var;
  NOTAS:
  ---------------------------------------------------------------*/
{
  int i;

  if (id < (s->size))
    {
      freeFDVariable((s->variables)[id]);
      (s->variables)[id]=Inicp1FDVariable(var);
      s->position=id>(s->position)?id:(s->position);
    }
  else 
    {/* El vector dinamico no tiene la capacidad para almacenar la nueva variable,
      * se debe hacer realloc
      */
      s->variables = (FDVariable *)realloc(s->variables,(id+1)*sizeof(FDVariable));  
      if (!(s->variables))
	{
	  printf("Error en la nueva asignacion de memoria...");
	  exit(1);
	}

      for(i = s->size ; i < id;i++)
	  (s->variables)[i] = NULL;

      (s->variables)[id]=InicFDVariable();
      setChainValFDVariable((s->variables)[id], getChainValFDVariable(var)); 
      setChainDomFDVariable((s->variables)[id], getChainDomFDVariable(var)); 
      setChainMinFDVariable((s->variables)[id], getChainMinFDVariable(var));
      setChainMaxFDVariable((s->variables)[id], getChainMaxFDVariable(var));
      setChainMinMaxFDVariable((s->variables)[id], getChainMinMaxFDVariable(var));
      setDomainFDVariable((s->variables)[id],getDomainFDVariable(var));
      setStampFDVariable((s->variables)[id],getStampFDVariable(var)); 
      s->position=id;
      s->size = id +1;
    }
  return s;
}

Store puttempVDStore(Store s, int id, FDVariable var)
/*---------------------------------------------------------------
  DESCRIPCION: Adiciona la variable var al vector dinamico VDStore

  PARAMETROS: s: La representacion del store.
              id: Identificador de la variable var.
	      var: La variable que se va adicionar al store.
  USA:
  RETORNA:
  PRE:VDStore[id] = NULL;
  POS:VDStore[id] = var;
  NOTAS:
  ---------------------------------------------------------------*/
{
  if (id <=  (s->tempsize))
    {
      freeFDVariable((s->tempvariables)[id]);
      (s->tempvariables)[id]=Inicp1FDVariable(var);
    }
  else 
    {/* El vector dinamico no tiene la capacidad para almacenar la nueva variable,
      * se debe hacer realloc
      */
      s->tempvariables = (FDVariable *)realloc(s->tempvariables,(id+1)*sizeof(FDVariable));  
      if (!(s->tempvariables))
	{
	  printf("Error en la nueva asignacion de memoria...");
	  exit(1);
	}
      
      (s->tempvariables)[id]=InicFDVariable();
      setChainValFDVariable((s->tempvariables)[id],getChainValFDVariable(var));
      setChainDomFDVariable((s->tempvariables)[id],getChainDomFDVariable(var));
      setChainMinFDVariable((s->tempvariables)[id],getChainMinFDVariable(var));
      setChainMaxFDVariable((s->tempvariables)[id],getChainMaxFDVariable(var));
      setChainMinMaxFDVariable((s->tempvariables)[id],getChainMinMaxFDVariable(var));
      setDomainFDVariable((s->tempvariables)[id],getDomainFDVariable(var));
      setStampFDVariable((s->tempvariables)[id],getStampFDVariable(var)); 
      s->tempsize = id;
    }
  
  return s;
}

FDVariable  getVDStore(Store s, int id)
/*---------------------------------------------------------------
  DESCRIPCION: Obtiene la variable identificada por
               id que existe en el store.

  PARAMETROS: s: La representacion del store.
              id: Identificador de la variable var.
  USA:
  RETORNA:
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  if ( id < (s->size) ) 
    return ((s->variables)[id]);
  else
    return NULL;
}


FDVariable  gettempVDStore(Store s, int id)
/*---------------------------------------------------------------
  DESCRIPCION: Obtiene la variable identificada por
               id que existe en el store.

  PARAMETROS: s: La representacion del store.
              id: Identificador de la variable var.
  USA:
  RETORNA:
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  if ( id <= (s->tempsize) )
    return ((s->tempvariables)[id]);
  else
    return NULL;
}

int getsizeVDStore(Store s)
/*---------------------------------------------------------------
  DESCRIPCION: Obtiene el tamaño del store.

  PARAMETROS: s: La representacion del store.
  USA:
  RETORNA: El tamaño del vector dinamico que representa el store
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int resp;
  resp = s->size;
  return resp;
}

int gettempsizeVDStore(Store s)
/*---------------------------------------------------------------
  DESCRIPCION: Obtiene el tamaño del store.

  PARAMETROS: s: La representacion del store.
  USA:
  RETORNA: El tamaño del vector dinamico donde estan almacenadas
           las variables que se generan cuando se compila una
	   restriccion no lineal.
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int resp;
  resp = s->tempsize;
  return resp;
}

int getpositionVDStore(Store s)
/*---------------------------------------------------------------
  DESCRIPCION: Obtiene la ultima posicion hasta la cual se encuentran
               variables dentro del vector dinamico que representa el 
	       store s.

  PARAMETROS: s: La representacion del store.
  USA:
  RETORNA: La ultima posicion en la cual puedo encontrar variables.
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int resp;
  resp = s->position;
  return resp;
}

void ImprimirVDStore(Store s)
/*---------------------------------------------------------------
  DESCRIPCION: Muestra el contenido del store.
  PARAMETROS: s: La representacion del store.
  USA:
  RETORNA: 
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int i;
  for (i = 0; i <= s->position; i++)
    if ((s->variables)[i] != NULL)
      {
	printf("Var:%d\n",i);
	ImprimirFDVariable((s->variables)[i]);
      }
}


void freeVDStore(Store s)
/*---------------------------------------------------------------
  DESCRIPCION: Libera la memoria reservada para la variable
               store s.
  PARAMETROS: s: La representacion del store.
  USA:
  RETORNA:
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int i;
    if(s != NULL)
      {
	if((s->variables) != NULL)
	  {
	    for(i=0;i<(s->size);i++)
	      freeFDVariable((s->variables)[i]);
	    free(s->variables);
	    s->variables=NULL;
	  }
	
	if((s->tempvariables) != NULL)
	  {
	    for(i=0;i<=(s->tempsize);i++)
	      freeFDVariable((s->tempvariables)[i]);
	    free(s->tempvariables);
	    s->tempvariables=NULL;
	  }
		
	free(s);
	s=NULL; 
      }
}
#endif 

/**** EOF ****/

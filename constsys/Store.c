#ifndef _Store_c
#define _Store_c
/****************************************************************
* IMPLEMENTACION MODULO: Store.c
* FECHA CREACION:  15-Mar-01
* DESCRIPCION: 
*   Simula un store de restricciones
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
       gcc -c Store.c

  1. Librerias requeridas para su linkeo:
       -lm -lX11

  2. Listado de estructuras de datos definidas (publicas y privadas)

  3. Listado de funciones definidas (publicas y privadas)

     Store inicStore(void)
     Store inicpStore(Store)
     void insertVariableStore(Store,int,FDVariable)
     int updateVarDomStore(Store, int, Domain)
     void updateVarStampStore(Store, int, int)
     FDVariable getVariableStore(Store,int)
     int isDeterminatedStore(Store,int)
     void desrefVariableDepStore(Store, int)
     void ImprimirStore(Store)
     void freeStore(Store)

  4. Instruccion para modificar el modulo
  4.1 Construcciones importantes para tener en cuenta (e.g. tipos, variables, funciones)
  4.2 Observaciones Adicionales
  
  ===============================================================*/

/*--------------------------------------------------------------*
  Archivos de Interfaz de librerias estandar y de otros modulos
 *--------------------------------------------------------------*/
#include "Store.h"
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
Store inicStore()
/*---------------------------------------------------------------
  DESCRIPCION: crea un store

  PARAMETROS: 
  USA:
  RETORNA: Un puntero al store creado
  PRE:
  POS: store=dir || store=NULL 
  NOTAS:
  ---------------------------------------------------------------*/
{
  Store store;
  store =InicVDStore();
  return store;
}


Store inicpStore(Store s)
/*---------------------------------------------------------------
  DESCRIPCION: crea un store donde copia el store que recibe

  PARAMETROS: s es un store
  USA:
  RETORNA: Un puntero al store creado
  PRE:
  POS: store=dir || store=NULL 
  NOTAS:
  ---------------------------------------------------------------*/
{
  Store store = InicpVDStore(s);
  return store;
}

Store insertVariableStore(Store s,int key,FDVariable x)
/*---------------------------------------------------------------
  DESCRIPCION: adiciona al store una variable

  PARAMETROS: s: es un store,
              x: es una FDVariable
              key: es la posicion en el vector que representa al
                   store s,donde se insertara la variable x.
  USA:
  RETORNA: 
  PRE:
  POS: s=s U x
  NOTAS:
  ---------------------------------------------------------------*/
{
  if ( key < 0 )
    s = puttempVDStore(s, (-1)*key, x);
  else
    s = putVDStore(s,key,x);
  
  return s;
}

int updateVarDomStore(Store s, int key, Domain d)
/*---------------------------------------------------------------
  DESCRIPCION: Actualiza el dominio de una variable dentro
               del store.

  PARAMETROS: s: es un store
              key: es la posicion dentro del store donde
              se encuentra la varible a la cual se
         le va actualizar el dominio.
         d: Dominio con el cual se va actulizar.
  USA:
  RETORNA: TRUE si la funcion fue existos o FALSE si
           no se realizo la funcion.
  PRE:La variable debe existir en el store.
  POS: store[key]=d
  NOTAS:
  ---------------------------------------------------------------*/
{
  if(key >= 0)
    {
      if (isConsistentDomain(d))
   {
     setDomainFDVariable(getVDStore(s, key),d);    
     return TRUE;
   }
      else
   return FALSE;
    }
  else
    {
      if (isConsistentDomain(d))
   {
     setDomainFDVariable(gettempVDStore(s, (-1)*key),d);
     return TRUE;
   }
      else
   return FALSE;
    }
}

Store updateVarStampStore(Store s, int key, int stamp)
/*---------------------------------------------------------------
  DESCRIPCION: Actualiza la stamp de una variable dentro
               del store.

  PARAMETROS: s: es un store
              key: es la posicion dentro del store donde
              se encuentra la varible a la cual se
         le va actualizar el dominio.
         stamp: estampa con la cual se va a actualizar..
  USA:
  RETORNA: 
  PRE:La variable debe existir en el store.
  POS: store[key].stamp=stamp
  NOTAS:
  ---------------------------------------------------------------*/
{
  if(key >= 0)
    setStampFDVariable(getVDStore(s,key),stamp);
  else
    {
      setStampFDVariable(gettempVDStore(s,(-1)*key),stamp);
    }
  return s;
}


FDVariable getVariableStore(Store s,int key)
/*---------------------------------------------------------------
  DESCRIPCION: obtiene una variable del store

  PARAMETROS: s: es un store
              key: es la posicion dentro del store donde
              se encuentra la variable a obtener.
  USA:
  RETORNA: la variable que se encuentra en el store en la 
           posicion. 
  PRE:La variable debe existir en el store
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  if (key < 0) 
      return(gettempVDStore(s, (-1)*key));
  else
      return(getVDStore(s,key));
}

int isDeterminatedStore(Store s,int key)
/*---------------------------------------------------------------
  DESCRIPCION: analiza si la variable que se encuentra en la 
               posicion key esta determinada  

  PARAMETROS: s: es un store
              key:la posicion d ela variable en el store
  USA:
  RETORNA: TRUE || FALSE
  PRE:la variable debe existir en el store
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  FDVariable fdvariable;
  
  if(key >= 0)
    fdvariable=getVDStore(s,key);
  else
    fdvariable=gettempVDStore(s,(-1)*key);
  
  if (isDeterminatedFDVariable(fdvariable))
    return TRUE;
  else
    return FALSE;
}

Store desrefVariableDepStore(Store s, int pos_indexical)
/*---------------------------------------------------------------
  DESCRIPCION: desreferencia todas las variables del store que 
               dependen del indexical que se encuentra en la
               posicion pos de indexicals

  PARAMETROS: s: es un store
              pos_indexical: es la posicion dentro de indexicals del 
                   indexical a desreferenciar de las vars.del store
  USA:
  RETORNA: Store: La bodega de restricciones.
  PRE:pos_indexical debe ser una posicion valida en el vector
      de indexicals
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/ 
{
  int pos,ult_pos,ult_pos_temp;
  FDVariable fdvariable;
  ult_pos=getpositionVDStore(s);

  for(pos=0; pos <= ult_pos; pos++)
    {
      fdvariable=getVDStore(s,pos);
      if(fdvariable!=NULL)
   {
     desrefDepFDVariable(fdvariable,pos_indexical);
   }
    }
  ult_pos_temp=gettempsizeVDStore(s);

  for(pos=1; pos <= ult_pos_temp; pos++)
    {
      fdvariable=gettempVDStore(s,pos);
      if(fdvariable!=NULL)
   {
     desrefDepFDVariable(fdvariable,pos_indexical);
   }
    }
  return s;
}

void ImprimirStore(Store s)
/*---------------------------------------------------------------
  DESCRIPCION: Muestra el contenido de la bodega de restricciones.
  PARAMETROS: s: es un store
  USA:
  RETORNA: 
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/ 
{
  ImprimirVDStore(s);
}

void freeStore(Store s)
/*---------------------------------------------------------------
  DESCRIPCION: Libera la memoria reservada para la variable s
  PARAMETROS: s: es un store
  USA:
  RETORNA: 
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/ 
{
  freeVDStore(s);
}
#endif

/****EOF****/

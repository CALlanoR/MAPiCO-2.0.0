#ifndef _FrameConst_c_
#define _FrameConst_c_
/****************************************************************
* IMPLEMENTACION MODULO: FrameConst.c
* FECHA CREACION:  29-Mar-01
* DESCRIPCION: 
*   Implementa el TAD que representa una restriccion aritmetica 
*   como un arbol.
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
       gcc -c FrameConst.c

  1. Librerias requeridas para su linkeo:
       -lm -lX11

  2. Listado de estructuras de datos definidas (publicas y privadas)
  
  3. Listado de funciones definidas (publicas y privadas)

  FrameConst InicFrameConst(int, int)
  FrameConst InicpFrameConst(FrameConst)
  void insertSonFrameConst(FrameConst, FrameConst, int)
  FrameConst getLefSonFrameConst(FrameConst)
  FrameConst getRigSonFrameConst(FrameConst)
  TipoA getInfoFrameConst(FrameConst)
  int getTypeFrameConst(FrameConst)
  int getValueFrameConst(FrameConst)
  void setLefSonFrameConst(FrameConst, FrameConst)
  void setRigSonFrameConst(FrameConst, FrameConst)
  int EsNegativoFrameConst(FrameConst)
  int EsLinealFrameConst(FrameConst)
  FrameConst CeilFrameConst (FrameConst)
  FrameConst FloorFrameConst (FrameConst)
  FrameConst ComplementFrameConst (FrameConst)
  FrameConst SupremoFrameConst(FrameConst)
  FrameConst InfimoFrameConst(FrameConst)
  int NumConstFrameConst(FrameConst)
  void DestruirFrameConst(FrameConst)
  void ImprimirFrameConst(FrameConst)

  4. Instruccion para modificar el modulo
  4.1 Construcciones importantes para tener en cuenta (e.g. tipos, variables, funciones)
  4.2 Observaciones Adicionales
  
  ===============================================================*/
/*--------------------------------------------------------------*
  Archivos de Interfaz de librerias estandar y de otros modulos
 *--------------------------------------------------------------*/
#include "FrameConst.h"
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

FrameConst InicFrameConst(int type, int value)
/*---------------------------------------------------------------
  DESCRIPCION: Crea un FrameConst con los parametros type y value.

  PARAMETROS: type: Tipo del FrameConst
              value: Valor del FrameConst
  USA:
  RETORNA: FrameConst
  PRE:
  POS:FrameConst = dir || FrameConst = NULL
  NOTAS:
  ---------------------------------------------------------------*/
{
  FrameConst resp;
  resp = inicArbin(type,value);  
  return resp;
}

FrameConst InicpFrameConst(FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Crea un FrameConst con parametro f.

  PARAMETROS: f: FrameConst del cual se va a extraer la informacion
                 para crear el FrameConst.
  USA:
  RETORNA: FrameConst
  PRE:
  POS:FrameConst = dir || FrameConst = NULL
  NOTAS:
  ---------------------------------------------------------------*/
{

  FrameConst resp;
  resp = inicpArbin(f);
  return resp;
}

void insertSonFrameConst(FrameConst f, FrameConst son, int flagson)
/*---------------------------------------------------------------
  DESCRIPCION: Inserta un hijo al FrameConst f.

  PARAMETROS: f: FrameConst al cual se le va adicionar el hijo
                 izquierdo.
         son: Hijo a ser insertado en el FrameConst f.
         flagson: Bandera la cual indica si se va adicionar
                  un hijo izq o der.
  USA:
  RETORNA:
  PRE:
  POS: f->izq = son ||  f->der = son
  NOTAS:
  ---------------------------------------------------------------*/
{
  insertArbin(f, son, flagson);
}

FrameConst getLefSonFrameConst(FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Obtiene el Hijo Izq del FrameConst f.

  PARAMETROS: f: FrameConst del cual se va a consultar el Hijo izq.
  USA:
  RETORNA: f->izq
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  return izqArbin(f);
}

FrameConst getRigSonFrameConst(FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Obtiene el Hijo Der del FrameConst f.

  PARAMETROS: f: FrameConst del cual se va a consultar el Hijo der.
  USA:
  RETORNA: f->der
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  return derArbin(f);
}

TipoA getInfoFrameConst(FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Obtiene el info del FrameConst f.

  PARAMETROS: f: FrameConst del cual se va a consultar el info.
  USA:
  RETORNA: f->info
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  TipoA resp;
  resp = raizArbin(f);
  return resp;
}

int getTypeFrameConst(FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Obtiene el tipo del info del parametro f.

  PARAMETROS: f: FrameConst del se va extraer informacion 
  USA:
  RETORNA: El tipo del Info
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int resp;
  resp = (raizArbin(f)).tipo;
  return resp;
}

int getValueFrameConst(FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Obtiene el valor del info del parametro f.

  PARAMETROS: f: FrameConst del se va extraer informacion 
  USA:
  RETORNA: El valor del info
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int resp;
  resp = (raizArbin(f)).valor;
  return resp;
}



void setLefSonFrameConst(FrameConst f, FrameConst lefson)
/*---------------------------------------------------------------
  DESCRIPCION: Actualiza el atributo iza  de f con el parametro
               lefson.

  PARAMETROS: f: FrameConst al cual se va actualizar el izq.
              lefson: Parametro para actualizar a f.
  USA:
  RETORNA: 
  PRE:
  POS:f->izq = lefson
  NOTAS:
  ---------------------------------------------------------------*/
{
  f->izq = lefson;
}

void setRigSonFrameConst(FrameConst f, FrameConst rigson)
/*---------------------------------------------------------------
  DESCRIPCION: Actualiza el atributo der  de f con el parametro
               rigson.

  PARAMETROS: f: FrameConst al cual se va actualizar el izq.
              rigson: Parametro para actualizar a f.
  USA:
  RETORNA: 
  PRE:
  POS:f->der = rigson
  NOTAS:
  ---------------------------------------------------------------*/
{
  f->der = rigson;
}

int EsNegativoFrameConst(FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Decide si f es un termino negativo.
  PARAMETROS: f: FrameConst a analizar.

  USA:
  RETORNA:TRUE || FALSE
  PRE: El valor de f no es un division
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int type, value;
  
  type = getTypeFrameConst(f);
  value = getValueFrameConst(f);
  if (type == VARIABLE)
    return FALSE;
  else
    if (type == CONSTANTE)
      if (value < 0)
   return TRUE;
      else
   return FALSE;
    else // Es tipo Funcion y valor multiplicacion
   if ((EsNegativoFrameConst(getLefSonFrameConst(f)) &&
        !(EsNegativoFrameConst(getRigSonFrameConst(f)))) || 
       (!EsNegativoFrameConst(getLefSonFrameConst(f)) && 
        EsNegativoFrameConst(getRigSonFrameConst(f))))
   return TRUE;
  return FALSE;
}

int EsLinealFrameConst(FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Decide si f tiene terminos lineales o no.
  PARAMETROS: f: FrameConst a analizar.

  USA:
  RETORNA:TRUE || FALSE
  PRE: f es un termino
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int type;
  type = getTypeFrameConst(f);
  if (type == VARIABLE || type == CONSTANTE)
    return TRUE;
  else
    if (type == FUNCION)
      {// Es una multiplicacion siempre
   if ((getTypeFrameConst(getLefSonFrameConst(f)) == CONSTANTE) || (getTypeFrameConst(getRigSonFrameConst(f)) == CONSTANTE))
     return TRUE;
      }

  return FALSE;
}

FrameConst CeilFrameConst(FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Esta funcion obtiene la representacion del techo de f.
  PARAMETROS: f: FrameConst al cual se le va a obtener el techo.

  USA:
  RETORNA: techo(x/y) = (x+y-1)/y
  PRE: El tipo de f es division
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{

  FrameConst resp, temporal, numerador, constante;
  
  resp = InicFrameConst(FUNCION, DIV);
  temporal= InicFrameConst(FUNCION, ADD);
  numerador = InicFrameConst(FUNCION,SUBS);
  constante = InicFrameConst(CONSTANTE,1);
  
  insertSonFrameConst(temporal, getLefSonFrameConst(f),LEFT);
  insertSonFrameConst(temporal, getRigSonFrameConst(f),RIGHT);
  insertSonFrameConst(numerador, temporal,LEFT);
  insertSonFrameConst(numerador, constante,RIGHT);
  insertSonFrameConst(resp, numerador,LEFT);
  insertSonFrameConst(resp, getRigSonFrameConst(f),RIGHT);
  
  return resp;
}

FrameConst FloorFrameConst(FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Esta funcion obtiene la representacion del piso de f.
  PARAMETROS: f: FrameConst al cual se le va a obtener el piso.

  USA:
  RETORNA: techo(x/y) = x / y
  PRE: El tipo de f es division
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  return f;
}

FrameConst ComplementFrameConst(FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Esta funcion obtiene el complemento de f.
  PARAMETROS: f: FrameConst al cual se le va a obtener el complemento.

  USA:
  RETORNA: El complemento de f.
  PRE: 
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  FrameConst resp, aux, aux0, aux1;

  resp = InicFrameConst(FUNCION, DIFF);
  aux = InicFrameConst(FUNCION, RANGE);
  aux0 = InicFrameConst(CONSTANTE,MININ);
  aux1 = InicFrameConst(CONSTANTE,MAXIN);

  insertSonFrameConst(aux, aux0, LEFT);
  insertSonFrameConst(aux, aux1, RIGHT);
  insertSonFrameConst(resp, aux, LEFT);
  insertSonFrameConst(resp, f, RIGHT);

  return resp;
}

FrameConst SupremoFrameConst(FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Esta funcion obtiene el supremo de f.
  PARAMETROS: f: FrameConst al cual se le va a obtener el supremo.

  USA
  RETORNA: El supremo de f.
  PRE: 
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int type, value;
  FrameConst resp;

  type = getTypeFrameConst(f);

  if (type == CONSTANTE)
    return f;
  else
    if (type == VARIABLE)
      {
   resp = InicFrameConst(FUNCION, MAX);
   insertSonFrameConst(resp,f,LEFT);
   return resp;
      }
  else
    { /* El tipo de f es funcion */ 
      value = getValueFrameConst(f);
      switch(value)
   {
   case ADD:
     resp = InicFrameConst(FUNCION, ADD);
     insertSonFrameConst(resp, SupremoFrameConst(getLefSonFrameConst(f)),LEFT);
     insertSonFrameConst(resp, SupremoFrameConst(getRigSonFrameConst(f)),RIGHT);
     return resp;

   case SUBS:
     resp = InicFrameConst(FUNCION, SUBS);
     insertSonFrameConst(resp, SupremoFrameConst(getLefSonFrameConst(f)),LEFT);
     insertSonFrameConst(resp, InfimoFrameConst(getRigSonFrameConst(f)),RIGHT);
     return resp;

   default: /* MULT */
     resp = InicFrameConst(FUNCION, MULT);
     insertSonFrameConst(resp, SupremoFrameConst(getLefSonFrameConst(f)),LEFT);
     insertSonFrameConst(resp, SupremoFrameConst(getRigSonFrameConst(f)),RIGHT);
     return resp;
   }
    }
}

FrameConst InfimoFrameConst(FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Esta funcion obtiene el infimo de f.
  PARAMETROS: f: FrameConst al cual se le va a obtener el infimo.

  USA
  RETORNA: El infimo de f.
  PRE: 
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int type, value;
  FrameConst resp;

  type = getTypeFrameConst(f);
 
  if (type == CONSTANTE)
    return f;
  else
    if (type == VARIABLE)
      {
   resp = InicFrameConst(FUNCION, MIN);
   insertSonFrameConst(resp,f,LEFT);
   return resp;
      }
  else
    { /* El tipo de f es funcion */ 
      value = getValueFrameConst(f);
      switch(value)
   {
   case ADD:
     resp = InicFrameConst(FUNCION, ADD);
     insertSonFrameConst(resp, InfimoFrameConst(getLefSonFrameConst(f)),LEFT);
     insertSonFrameConst(resp, InfimoFrameConst(getRigSonFrameConst(f)),RIGHT);
     return resp;

   case SUBS:
     resp = InicFrameConst(FUNCION, SUBS);
     insertSonFrameConst(resp, InfimoFrameConst(getLefSonFrameConst(f)),LEFT);
     insertSonFrameConst(resp, SupremoFrameConst(getRigSonFrameConst(f)),RIGHT);
     return resp;

   default: /* MULT */
     resp = InicFrameConst(FUNCION, MULT);
     insertSonFrameConst(resp,InfimoFrameConst(getLefSonFrameConst(f)),LEFT);
     insertSonFrameConst(resp, InfimoFrameConst(getRigSonFrameConst(f)),RIGHT);
     return resp;
   }
    }
}

int NumConstFrameConst(FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Esta funcion el numero de constante que estan en
               f.
  PARAMETROS: f: FrameConst al cual se le va a obtener el numero
                 de constantes.

  USA
  RETORNA: El numero de constantes en f.
  PRE: 
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
    int type, constlef, constrig;
    
    type = getTypeFrameConst(f);
    
    if (type == CONSTANTE)
   return 1;
    else
   if (type == VARIABLE)
       return 0;
   else
       { 
      constlef = NumConstFrameConst(getLefSonFrameConst(f));
      constrig = NumConstFrameConst(getRigSonFrameConst(f));
      return (constlef+constrig);
       }
}


void DestruirFrameConst(FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Libera la memoria reservada para la variable
               f.
  PARAMETROS: f: FrameConst al cual se va a liberar.
  USA:
  RETORNA:
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
    destruirArbin(f);
}

void ImprimirFrameConst(FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Imprimie el frameconst f

  PARAMETROS: f: FrameConst a imprimir.
  USA:
  RETORNA: 
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
    if ((izqArbin(f) == NULL) && (derArbin(f) == NULL))
    {
      printf("\n<T: %d, V: %d>", (raizArbin(f)).tipo,(raizArbin(f)).valor);
    }
    else
    {
         if(derArbin(f) == NULL)
         {     
            printf("\n<T:%d,V:%d>\nhijo[0]==>",(raizArbin(f)).tipo,(raizArbin(f)).valor);
            ImprimirFrameConst(izqArbin(f));
         }
         else 
         {
            printf("\n<T:%d,V:%d>\n[0]==>",(raizArbin(f)).tipo,(raizArbin(f)).valor);
            ImprimirFrameConst(izqArbin(f));
            printf("\n[1]==>");
            ImprimirFrameConst(derArbin(f));
         }
     }
}


#endif




#ifndef _Indexicals_c
#define _Indexicals_c
/****************************************************************
* IMPLEMENTACION MODULO: Indexicals.c
* FECHA CREACION:  22-Mar-01
* DESCRIPCION: 
*   Implementa los indexicals como un vector dinamico
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
       gcc -c Indexicals.c

  1. Librerias requeridas para su linkeo:
       -lm -lX11

  2. Listado de estructuras de datos definidas (publicas y privadas)
     typedef struct 
     {
      Indexical *VDIndexicals;
      int size; 
     }TIndexicals,*Indexicals;

  3. Listado de funciones definidas (publicas y privadas)

     Indexicals InicIndexicals(void)
     int sizeIndexicals(Indexicals)
     Indexical elementAtIndexicals(Indexicals,int)
     void  addElementIndexicals(Indexicals,Indexical)
     void removeElementAtIndexicals(Indexicals, int)
     void setElementAtIndexicals(Indexicals, Indexical, int)
     void freeIndexicals(Indexicals)

  4. Instruccion para modificar el modulo
  4.1 Construcciones importantes para tener en cuenta (e.g. tipos, variables, funciones)
  4.2 Observaciones Adicionales
  
  ===============================================================*/

/*--------------------------------------------------------------*
  Archivos de Interfaz de librerias estandar y de otros modulos
 *--------------------------------------------------------------*/
#include "Indexicals.h"
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
Indexicals InicIndexicals(void)
/*---------------------------------------------------------------
  DESCRIPCION: Crea el vector dinamico que representa todos los 
               indexicals, que a su vez es el modelo empleado
	       para representar las restricciones aritmeticas.

  PARAMETROS: 
  USA:
  RETORNA: Un puntero al vector dinamico
  PRE:
  POS: indexicals=dir || indexicals=NULL 
  NOTAS:
  ---------------------------------------------------------------*/
{
  int i;
  Indexicals indexicals;

  indexicals = ( Indexicals )malloc(sizeof( TIndexicals ) );
  if (!indexicals)
    {
      printf("Error en la asignacion de memoria para crear indexicals");
      exit(1);
    }
  indexicals->VDIndexicals=(Indexical*)malloc(TAMININDEXICALS*sizeof(Indexical));
  if (!(indexicals->VDIndexicals))
    {
      printf("Error en la asignacion de memoria para crear indexicals");
      exit(1);
    }
  for(i = 0; i < TAMININDEXICALS; i++)
    (indexicals->VDIndexicals)[i]=NULL;
  indexicals->size=-1;

  return indexicals;
}

Indexicals InicpIndexicals(Indexicals I)
/*---------------------------------------------------------------
  DESCRIPCION: Clona los indexicals del sistema de restricciones
               aritmetico.
  PARAMETROS: 
  USA:
  RETORNA: Un puntero al vector dinamico
  PRE:
  POS: indexicals=dir || indexicals=NULL 
  NOTAS:
  ---------------------------------------------------------------*/
{
  int i;
  Indexicals indexicals;

  indexicals = ( Indexicals )malloc(sizeof( TIndexicals ) );
  if (!indexicals)
    {
      printf("Error en la asignacion de memoria para crear indexicals");
      exit(1);
    }
  indexicals->VDIndexicals=(Indexical*)malloc((sizeIndexicals(I)+1)*sizeof(Indexical));
  if (!(indexicals->VDIndexicals))
    {
      printf("Error en la asignacion de memoria para crear indexicals");
      exit(1);
    }
  for(i = 0; i <= (sizeIndexicals(I)); i++)
    {
      ((indexicals->VDIndexicals)[i])=InicIndexical();
      setCoder(((indexicals->VDIndexicals)[i]),getCoder((I->VDIndexicals)[i]),getTamCoder((I->VDIndexicals)[i]));
      setTamCoder(((indexicals->VDIndexicals)[i]),getTamCoder((I->VDIndexicals)[i]));
      setCodef(((indexicals->VDIndexicals)[i]),getCodef((I->VDIndexicals)[i]));
      setX(((indexicals->VDIndexicals)[i]),getX((I->VDIndexicals)[i]));
      setStamp(((indexicals->VDIndexicals)[i]),getStamp((I->VDIndexicals)[i]));
      setEntailed(((indexicals->VDIndexicals)[i]),getEntailed((I->VDIndexicals)[i]));
    }

  indexicals->size=sizeIndexicals(I);

  return indexicals;
}

int sizeIndexicals(Indexicals index)
/*---------------------------------------------------------------
  DESCRIPCION: Obtiene la informacion de cuantos indexicals estan
               almacenados en indexicals (Vector Dinamico)

  PARAMETROS: index: Vector dinamico que representa los indexicals
  USA:
  RETORNA: La cantidad de indexicals almacenados.
  PRE:
  POS: index->size
  NOTAS:
  ---------------------------------------------------------------*/
{
  int res;

  res = index->size;
  return res;
}

Indexical elementAtIndexicals(Indexicals indexicals,int pos)
/*---------------------------------------------------------------
  DESCRIPCION: Da la informacion del indexical que se encuentra
               en la posicion pos dentro del vector dinamico
	       indexicals.

  PARAMETROS: indexicals: La representacion de los indexicals
              pos: Posicion dentro del vector de indexicals
  USA:
  RETORNA:
  PRE: 0 < pos < TAMININDEXICALS
  POS:indexicals[pos] = index;
  NOTAS:
  ---------------------------------------------------------------*/
{
  Indexical resp;
  
  if ((indexicals->VDIndexicals)[pos] == NULL)
    return NULL;
  else
    {
      resp = InicIndexical();
      setCoder(resp, getCoder((indexicals->VDIndexicals)[pos]), getTamCoder((indexicals->VDIndexicals)[pos]));
      setTamCoder(resp,getTamCoder((indexicals->VDIndexicals)[pos]));
      setCodef(resp,(getCodef((indexicals->VDIndexicals)[pos])));
      setX(resp,(getX((indexicals->VDIndexicals)[pos])));
      setEntailed(resp,(getEntailed((indexicals->VDIndexicals)[pos])));
      setStamp(resp,(getStamp((indexicals->VDIndexicals)[pos])));
    }
  return resp;
}

Indexicals addElementIndexicals(Indexicals indexicals,Indexical indexical)
/*---------------------------------------------------------------
  DESCRIPCION: Adiciona el indexical al vector dinamico de
               indexicals.  

  PARAMETROS: indexicals: La representacion de los indexicals
              indexical: Indexical a adicionar
  USA:
  RETORNA:
  PRE:
  POS:indexicals[indexicals->size] = indexical;
  NOTAS:
  ---------------------------------------------------------------*/
{
  (indexicals->size)++;
  if ((indexicals->size) < TAMININDEXICALS)
    {/* Aun hay memoria reservada para almacenar */
      (indexicals->VDIndexicals)[indexicals->size]=InicIndexical();
      setCoder(((indexicals->VDIndexicals)[indexicals->size]),getCoder(indexical),getTamCoder(indexical));
      setTamCoder(((indexicals->VDIndexicals)[indexicals->size]),getTamCoder(indexical));
      setCodef(((indexicals->VDIndexicals)[indexicals->size]),getCodef(indexical));
      setX(((indexicals->VDIndexicals)[indexicals->size]),getX(indexical));
      setStamp(((indexicals->VDIndexicals)[indexicals->size]),getStamp(indexical));
      setEntailed(((indexicals->VDIndexicals)[indexicals->size]),getEntailed(indexical));
    }
  else 
    {/* El vector dinamico no tiene la capacidad para almacenar la nueva variable,
      * se debe hacer realloc
      */
      indexicals->VDIndexicals=(Indexical*)realloc( indexicals->VDIndexicals,((indexicals->size)+1)*sizeof(Indexical));

      if (!(indexicals->VDIndexicals))
	{
	  printf("Error en la reasignacion de memoria para crear indexicals");
	  exit(0);
	}
      
      (indexicals->VDIndexicals)[indexicals->size]= InicIndexical();
      setCoder(((indexicals->VDIndexicals)[indexicals->size]),getCoder(indexical),getTamCoder(indexical));
      setTamCoder(((indexicals->VDIndexicals)[indexicals->size]),getTamCoder(indexical));
      setCodef(((indexicals->VDIndexicals)[indexicals->size]),getCodef(indexical));
      setX(((indexicals->VDIndexicals)[indexicals->size]),getX(indexical));
      setStamp(((indexicals->VDIndexicals)[indexicals->size]),getStamp(indexical));
      setEntailed(((indexicals->VDIndexicals)[indexicals->size]),getEntailed(indexical));
    }

  return indexicals;
}

Indexicals removeElementAtIndexicals(Indexicals indexicals, int pos)
/*---------------------------------------------------------------
  DESCRIPCION: Borra el indexical que se encuentra en la posicion
               pos del vector de indexicals.

  PARAMETROS: indexicals: Vector de indexicals del Sistema de Restricciones
              pos: Posicion dentro del vector de indexicals a ser removido.
  USA:
  RETORNA:
  PRE: 0 < pos < TAMININDEXICALS
  POS:indexicals[pos] = NULL
  NOTAS:
  ---------------------------------------------------------------*/
{
  freeIndexical((indexicals->VDIndexicals)[pos]);
  (indexicals->VDIndexicals)[pos] = NULL;
  return indexicals;
}

Indexicals setElementAtIndexicals(Indexicals indexicals, Indexical indexical, int pos)
/*---------------------------------------------------------------
  DESCRIPCION: Reemplaza lo que exista en la posicion pos del vector
               de indexicals, por indexical.
  PARAMETROS: indexicals: Vector Dinamico de indexicals.
              indexical: Nuevo elemento del vector de indexicals.
	      pos: Posicion dentro del vector de indexicals.
  USA:
  RETORNA:
  PRE:  0 < pos < TAMININDEXICALS
  POS:indexicals[pos]=indexical
  NOTAS:
  ---------------------------------------------------------------*/
{
  freeIndexical(((indexicals->VDIndexicals)[pos]));

  ((indexicals->VDIndexicals)[pos])=InicIndexical();
  setCoder(((indexicals->VDIndexicals)[pos]),getCoder(indexical),getTamCoder(indexical));
  setTamCoder(((indexicals->VDIndexicals)[pos]),getTamCoder(indexical));
  setCodef(((indexicals->VDIndexicals)[pos]),getCodef(indexical));
  setX(((indexicals->VDIndexicals)[pos]),getX(indexical));
  setStamp(((indexicals->VDIndexicals)[pos]),getStamp(indexical));
  setEntailed(((indexicals->VDIndexicals)[pos]),getEntailed(indexical));
  
  return indexicals;
}


void freeIndexicals(Indexicals indexicals)
/*---------------------------------------------------------------
  DESCRIPCION: Libera la memoria reservada para la variable indexicals
  PARAMETROS: indexicals: Variable a la cual se le va liberar la 
                          memoria.
  USA:
  RETORNA:
  PRE: 
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int i;
  if(indexicals != NULL)
    {
      for(i=0;i<=(indexicals->size);i++)
	freeIndexical((indexicals->VDIndexicals)[i]);
      free(indexicals->VDIndexicals);
      indexicals->VDIndexicals=NULL;
      free(indexicals);
      indexicals=NULL;
    }
}
#endif 

/**** EOF ****/

#ifndef _Indexical_c
#define _Indexical_c
/****************************************************************
* IMPLEMENTACION MODULO: Indexical.c
* FECHA CREACION:  20-Mar-01
* DESCRIPCION: 
*   Implementa el modelo utilizado para representar las
*   Restricciones Aritmeticas de la forma x in r.
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
       gcc -c Indexical.c

  1. Librerias requeridas para su linkeo:
       -lm -lX11

  2. Listado de estructuras de datos definidas (publicas y privadas)
      typedef struct
      {
        char ** coder;
	int tamcoder;
	FrameConst codef; 
	int x; 
	int stamp; 
	int entailed;
	int monotonicity; 
	}TIndexical,*Indexical;
  
  3. Listado de funciones definidas (publicas y privadas)
      Indexical InicIndexical(void)
      Indexical InicpIndexical(FrameConst f, int s)
      char ** getCoder(Indexical)
      int getTamCoder(Indexical)
      FrameConst getCodef(Indexical)
      int getX(Indexical)
      int getStamp(Indexical)
      int getEntailed(Indexical)
      Lista getVariablesIndexical(Indexical)
      void setCoder(Indexical,char **)
      void setTamCoder(Indexical, int)
      void setCodef(Indexical, FrameConst)
      void setX(Indexical, int)
      void setStamp(Indexical, int)
      void setEntailed(Indexical, int)
      int DependencyType(Indexical, int)
      void freeIndexical(Indexical)

  4. Instruccion para modificar el modulo
  4.1 Construcciones importantes para tener en cuenta (e.g. tipos, variables, funciones)
  4.2 Observaciones Adicionales
  
  ===============================================================*/

/*--------------------------------------------------------------*
  Archivos de Interfaz de librerias estandar y de otros modulos
 *--------------------------------------------------------------*/
#include "Indexical.h"
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
Indexical InicIndexical(void)
/*---------------------------------------------------------------
  DESCRIPCION: Crea un indexical

  PARAMETROS: 
  USA:
  RETORNA: Un puntero al indexical creado
  PRE:
  POS: indexical=dir || indexical=NULL 
  NOTAS:
  ---------------------------------------------------------------*/
{
  int i;  
  Indexical res;

  res = ( Indexical )malloc( sizeof( TIndexical ) );
  if (!res)
    {
      printf("Error en la asignacion de memoria para un Indexical. Archivo Indexical.c");
      exit(1);
    }
  res->coder = (char **)malloc(TAMCODER*sizeof(char *));
  if (!(res->coder))
    {
      printf("Error en la asignacion de memoria para la representacion del rango compilado");
      exit(1);
    }
  for(i=0;i<TAMCODER;i++)
    (res->coder)[i]=NULL;

    res->tamcoder = -1;
    res->codef = NULL;
    res->x = -1;
    res->stamp = -1;
    res->entailed = FALSE;
    return res;
}

Indexical InicpIndexical(FrameConst f, int s)
/*---------------------------------------------------------------
  DESCRIPCION: Crea un indexical con los parametros f y s

  PARAMETROS: f: Es una restriccion aritmetica como FrameConst
              s: Estampa de tiempo para el indexical a crear.
  USA:
  RETORNA: Un puntero al indexical creado
  PRE:
  POS: indexical=dir || indexical=NULL 
  NOTAS:
  ---------------------------------------------------------------*/
{
  int i;  
  Indexical res;
  
  res = ( Indexical )malloc( sizeof( TIndexical ) );
  if (!res)
    {
      printf("Error en la asignacion de memoria para un indexical");
      exit(1);
    }
   
    res->coder = (char **)malloc(TAMCODER*sizeof(char *));
    
    if (!(res->coder))
	{
	    printf("Error en la asignacion de memoria para la representacion del rango compilado");
	    exit(1);
	}

    for(i=0;i<TAMCODER;i++)
      (res->coder)[i]=NULL;
    
    res->tamcoder = -1;
    res->codef = InicpFrameConst(getRigSonFrameConst(f));
    res->x = getValueFrameConst(getLefSonFrameConst(f));
    res->stamp = s;
    res->entailed = FALSE;
    res->coder = translate( res->codef,res->coder,&(res->tamcoder));  
    return res;   
}

char **getCoder(Indexical index)
/*---------------------------------------------------------------
  DESCRIPCION: Retorna el rango compilado del indexical index

  PARAMETROS: index: Indexical del cual se va a consultar rango compilado
  USA:
  RETORNA: El rango compilado del indexical
  PRE:
  POS:  
  NOTAS:
  ---------------------------------------------------------------*/
{
  return index->coder;
}

int getTamCoder(Indexical index)
/*---------------------------------------------------------------
  DESCRIPCION: Retorna el tamaño del vector compilado que representa
               el rango.
  PARAMETROS:index: Indexical del cual se va a consultar el tamaño
             del rango compilado
  USA:
  RETORNA: El tamaño del rango compilado del indexical
  PRE:
  POS:  
  NOTAS:
  ---------------------------------------------------------------*/
{
  int resp;
  
  resp = index->tamcoder;
  return resp;
}

FrameConst getCodef(Indexical index)
/*---------------------------------------------------------------
  DESCRIPCION: Retorna el rango como FrameConst del indexical index

  PARAMETROS:index: Indexical del cual se va a consultar el rango
  USA:
  RETORNA: El rango como FrameConst del indexical
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  return index->codef;
}

int getX(Indexical index)
/*---------------------------------------------------------------
  DESCRIPCION: Retorna el identificador de la variable a la izq
               del indexical

  PARAMETROS:index :Indexical del cual se va a consultar su variable
  USA:
  RETORNA: El identificador de la variable de la izq del indexical
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  int res;
  res = index->x;
  return res;
}

int getStamp(Indexical index)
/*---------------------------------------------------------------
  DESCRIPCION: Retorna la estampa del indexical index

  PARAMETROS:index :Indexical del cual se va a consultar su estampa
  USA:
  RETORNA: La estampa del indexical
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  int res;
  res = index->stamp;
  return res;
}

int getEntailed(Indexical index)
/*---------------------------------------------------------------
  DESCRIPCION: Retorna si el indexical index ha sido deducido o no

  PARAMETROS:index: Indexical del cual se va a consultar si esta
             o no deducido.
  USA:
  RETORNA: El estado del indexical
  PRE:
  POS:  
  NOTAS:
  ---------------------------------------------------------------*/
{
  int resp;
  resp = index->entailed;
  return resp;
}

Lista getVariablesIndexical(Indexical index)
/*---------------------------------------------------------------
  DESCRIPCION: Obtiene todas las variables involucradas en el
               indexical index.

  PARAMETROS:index: Indexical del cual se van a extraer las variables
  USA:
  RETORNA: Una lista con todas las variables que aparecen en el 
           indexical
  PRE:
  POS:  
  NOTAS:
  ---------------------------------------------------------------*/
{
  int i,valor;
  Lista resp;

  resp = inicLista(); 
  anxLista(resp,index->x); 
  
  for (i = 0; i <= (index->tamcoder); i++)
    {
      if (strcmp("val",(index->coder)[i])== 0 ||
	  strcmp("dom",(index->coder)[i])== 0 ||
	  strcmp("dom_min",(index->coder)[i])== 0 ||
	  strcmp("dom_max",(index->coder)[i])== 0)
	{
	  valor = atoi(index->coder[i+1]);
	  if (miembroLista(resp, valor)==0)
	    anxLista(resp, valor);
	}
    }    
  return resp;
}

void setCoder(Indexical index, char **coder,int sizecoder)
/*---------------------------------------------------------------
  DESCRIPCION: Cambia el rango compilado de indexical index, con el valor
               coder.
  PARAMETROS:index: Indexical al cual se va a cambiar el rango compilado
             coder: Un rango compilado.
	     sizecoder: Tamaño del codigo compilado.
  USA:
  RETORNA: 
  PRE:
  POS:index->coder=coder  
  NOTAS:
  ---------------------------------------------------------------*/
{
  int i,l;
    
  for ( i = 0; i <= (index->tamcoder); i++)
    {
      if((index->coder)[i] != NULL)
	{
	  free((index->coder)[i]);
	  (index->coder)[i]=NULL;
	}
    }
  
  if((index->tamcoder)<sizecoder)
    {
      index->coder = (char **)realloc((index->coder),(sizecoder+1)*sizeof(char*));
      if (!(index->coder))
	{
	  printf("Error en la reasignacion de memoria para la adicion de un elemento del rango compilado");
	  exit(1);
	}
      
      for ( i = (index->tamcoder)+1; i <= sizecoder; i++)
	(index->coder)[i]=NULL;
    }
  
  for ( i = 0; i <= sizecoder; i++)
    {
      l=strlen(coder[i]);
      (index->coder)[i]=(char *)malloc((l+1)*sizeof(char));
      if (!((index->coder)[i]))
	{
	  printf("Error en la asignacion de memoria para la representacion del rango compilado");
	  exit(1);
	}
      strcpy((index->coder)[i],coder[i]);
    }
}

void setTamCoder(Indexical index, int tam)
/*---------------------------------------------------------------
  DESCRIPCION: Cambia el tamaño de coder de indexical index, con el valor
               tam.

  PARAMETROS:index: Indexical al cual se va a cambiar la estampa
             tam: Valor para actualizar tamcoder del index
  USA:
  RETORNA: 
  PRE:
  POS:index->tamcoder=tam;
  NOTAS:
  ---------------------------------------------------------------*/
{
  index->tamcoder= tam;
}

void setCodef(Indexical index, FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Cambia el codef de indexical index, con el valor
               f.
  PARAMETROS:index: Indexical al cual se va a cambiar el codef
             codef: Valor para actualizar codef del index
  USA:
  RETORNA: 
  PRE:
  POS:index->codef=f;
  NOTAS:
  ---------------------------------------------------------------*/
{
  index->codef = InicpFrameConst(f);
}

void setX(Indexical index, int id)
/*---------------------------------------------------------------
  DESCRIPCION: Cambia el id de la variable de indexical index, con el valor
               id.

  PARAMETROS:index: Indexical al cual se va a cambiar el id
             id: Valor para actualizar x del indexical
  USA:
  RETORNA: 
  PRE:
  POS:index->x=id; 
  NOTAS:
  ---------------------------------------------------------------*/
{
  index->x=id;
}

void setStamp(Indexical index, int s)
/*---------------------------------------------------------------
  DESCRIPCION: Cambia la estampa de indexical index, con el valor
               s.

  PARAMETROS:index: Indexical al cual se va a cambiar la estampa
             s: Valor para actualizar la estampa del indexical
  USA:
  RETORNA: 
  PRE:
  POS:  
  NOTAS:
  ---------------------------------------------------------------*/
{
  index->stamp=s;
}

void setEntailed(Indexical index, int e)
/*---------------------------------------------------------------
  DESCRIPCION: Cambia la bandera de la caracteristica de deducido
               del indexical index

  PARAMETROS:index: Indexical al cual se va a cambiar la estampa
             e: Valor para actualizar la bandera de la caracteristica
	     de deducido.
  USA:
  RETORNA: 
  PRE:
  POS: 
  NOTAS:
  ---------------------------------------------------------------*/
{
  index->entailed=e;
}


int DependencyType(Indexical index, int id)
/*---------------------------------------------------------------
  DESCRIPCION: Determina el tipo de dependencia de la variable id
               con respecto al indexical.

  PARAMETROS:index: Indexical al cual se va verificar la dependencia
                 con respecto a la variable id.
             id: Identificador de la variable
  USA:
  RETORNA: La dependencia de la variable con respecto al indexical
  PRE:
  POS:  
  NOTAS:
  ---------------------------------------------------------------*/
{
  int longi, i, bmax, bmin, bdom, bint;
  int m, n;
  char * aux, * aux1;

  bmax = FALSE;
  bmin = FALSE;
  bdom = FALSE;
  bint = FALSE;
  
  aux1 = (char *)malloc(17*sizeof(char));
  if (aux1 == NULL)
    {
      printf("Error en la asignacion de memoria....\n");
      exit(1);
    }
 
  for (i = 0; i <= index->tamcoder; i++)
    {
      if (id < 0)
	{
	  strcpy(aux1,"-");
	  strcat(aux1,fcvt(id,0,&m,&n));
	}
      else
	strcpy(aux1,fcvt(id,0,&m,&n));
      if (strcmp((index->coder)[i],aux1)==0)
	{
	  longi = strlen((index->coder)[i-1]);
	  aux = (char *)malloc((longi+1)*sizeof(char));
	  if (aux == NULL)
	    {
	      printf("Error en la asignacion de memoria..... Archivo Indexical.c\n");
	      exit(1);
	    }
	  strcpy(aux,(index->coder)[i-1]);
	  if ( strcmp(aux, "val") == 0 ) 
	    bint = TRUE;
	  else 
	    {
	      if ( strcmp(aux, "dom") == 0  ) 
		bdom = TRUE;
	      else 
		{
		  if ( strcmp(aux, "dom_min") == 0 ) 
		    bmin = TRUE;
		  else 
		    {
		      if ( strcmp(aux, "dom_max") == 0 ) 
			bmax = TRUE;
		    }
		}
	    }
	  if(aux != NULL)
	    {
	      free(aux);
	      aux=NULL;
	    }
	}
    }

  if(aux1 != NULL)
    {
      free(aux1);
      aux1=NULL;
    }

  if(bmin && bmax) 
    return DMINMAX;
  if(bmin) 
    return DMIN;
  if(bmax) 
    return DMAX;
  if(bdom) 
    return  DDOM;       
  if(bint) 
    return DINT;
  return NODEPENDENCY;
}

void freeIndexical(Indexical indexical)
/*---------------------------------------------------------------
  DESCRIPCION: Libera la memoria separada para la variable indexical.

  PARAMETROS: indexical: Indexical al cual se va a liberar la memoria.
  USA:
  RETORNA: 
  PRE:
  POS:  
  NOTAS:
  ---------------------------------------------------------------*/
{
  int i;
  if(indexical != NULL)
    {
      if(indexical->coder != NULL)
	{
	  for(i=0;i<=(indexical->tamcoder);i++)
	    {
	      if((indexical->coder)[i] != NULL)
		{
		  free((indexical->coder)[i]);
		  (indexical->coder)[i]=NULL;
		}
	    }
	  free(indexical->coder);
	  indexical->coder=NULL;
	}
      DestruirFrameConst(indexical->codef);
      free(indexical);
      indexical=NULL;
    }
}
#endif

/**** EOF ****/



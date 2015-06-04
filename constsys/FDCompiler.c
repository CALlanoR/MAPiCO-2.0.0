#ifndef _FDCompiler_c
#define _FDCompiler_c
/****************************************************************
* IMPLEMENTACION MODULO: FDCompiler.c
* FECHA CREACION:  27-Mar-01
* DESCRIPCION: 
*   Implementa la funcion la cual compila el rango de un indexical
*   dado, para ser luego evaluado por el FDEmulador.
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
       gcc -c FDCompiler.c

  1. Librerias requeridas para su linkeo:
       -lm -lX11

  2. Listado de estructuras de datos definidas (publicas y privadas)
  
  3. Listado de funciones definidas (publicas y privadas)
 
  char ** translate(FrameConst, char **, int *)
  char ** addElement(char **, char *, int *)

  4. Instruccion para modificar el modulo
  4.1 Construcciones importantes para tener en cuenta (e.g. tipos, variables, funciones)
  4.2 Observaciones Adicionales
  
  ===============================================================*/
/*--------------------------------------------------------------*
  Archivos de Interfaz de librerias estandar y de otros modulos
 *--------------------------------------------------------------*/
#include "FDCompiler.h"
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
char ** translate(FrameConst rango, char **coder, int *tamcoder)
/*---------------------------------------------------------------
  DESCRIPCION: Funcion que traduce el rango "rango" a codigo de 
               bytes en el store asociado "store".

  PARAMETROS: rango: Rango a ser compilado
              coder: Variable en la cual va a quedar almacenado 
	             el rango una vez haya sido compilado.
	      tamcoder: Tamaño e indice el vector dinamico coder.
  USA:
  RETORNA: El rango compilado
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int i, value, type, sizeLef, sizeRig, pos, m, n;
  char ** transLef, **transRig;
  char * aux;

  value = getValueFrameConst(rango);
  type = getTypeFrameConst(rango);

  /* Inicializacion de la variable auxiliar aux */

  aux = (char *)malloc(TAMAUX * sizeof(char));
  if (!aux)
    {
      printf("Error en la asignacion de memoria para el hijo izquierdo del rango a compilar");
      exit(1);
    }

  /* Inicializacion para la variable auxiliar que va a compilar el hijo izquierdo del rango */
  transLef = (char **)malloc(TAMCODER*sizeof(char *));
   if (!transLef)
    {
      printf("Error en la asignacion de memoria para el hijo izquierdo del rango a compilar");
      exit(1);
    }
  for(i = 0; i < TAMCODER; i++)
    transLef[i]=NULL;

  sizeLef = -1;

  /* Inicializacion para la variable auxiliar que va a compilar el hijo derecho del rango */
  transRig = (char **)malloc(TAMCODER*sizeof(char *));
  if (!transRig)
    {
      printf("Error en la asignacion de memoria para el hijo izquierdo del rango a compilar");
      exit(1);
    }
  for(i = 0; i < TAMCODER; i++)
    transRig[i]=NULL;

  sizeRig = -1;

  /* Inicio del algoritmo */
  
  if (type == VARIABLE)
    {
      strcpy(aux,"val");
      coder=addElement(coder, aux, tamcoder);
      if (value < 0)
	{
	  strcpy(aux,"-");
	  strcat(aux,fcvt(value,0,&m,&n));
	}
      else
	{
	  strcpy(aux,fcvt(value,0,&m,&n)); /* Convierte a char la posicion en la cual se encuentra la variable
			 * dentro del store 
			 */
	}
      coder=addElement(coder, aux, tamcoder); 
      if(aux != NULL)
	{
	  free(aux);
	  aux=NULL;
	}
      if(transLef != NULL)
	{
	  free(transLef);
	  transLef=NULL;
	}
      if(transRig != NULL)
	{
	  free(transRig);
	  transRig=NULL;
	} 
      return coder;
    }
  else
      {
       if (type == CONSTANTE)
	   {
	       strcpy(aux,"const");
	       coder=addElement(coder, aux, tamcoder);
	       strcpy(aux,fcvt(value,0,&m,&n)); /* Convierte a char la posicion en la cual se encuentra la variable
				  * dentro del store 
				  */
	       coder=addElement(coder, aux, tamcoder);

	       if(aux != NULL)
		   {
		       free(aux);
		       aux=NULL;
		   }
	       if(transLef != NULL)
		   {
		       free(transLef);
		       transLef=NULL;
		   }
	       if(transRig != NULL)
		   {
		       free(transRig);
		       transRig=NULL;
		   }
	       return coder;
	   }
      else
	{
	  switch(value)
	    {
	    case RANGE:
	      transLef = translate(getLefSonFrameConst(rango),transLef,&sizeLef);
	      transRig = translate(getRigSonFrameConst(rango),transRig,&sizeRig);
	      for (i = 0; i <= sizeRig; i++)
		coder=addElement(coder, transRig[i], tamcoder);
	      for (i = 0; i <= sizeLef; i++)
		coder=addElement(coder, transLef[i], tamcoder);
	      strcpy(aux,"range");
	      coder=addElement(coder, aux, tamcoder);
	      if(aux != NULL)
		{
		  free(aux);
		  aux=NULL;
		}
	      if(transLef != NULL)
		{
		  for(i=0; i<=sizeLef; i++)
		    {
		      if(transLef[i] != NULL)
			{
			  free(transLef[i]);
			  transLef[i]=NULL;
			}
		    }
		  free(transLef);
		  transLef=NULL;
		}
	      if(transRig != NULL)
		{
		  for(i=0; i<=sizeRig; i++)
		    {
		      if(transRig[i] != NULL)
			{
			  free(transRig[i]);
			  transRig[i]=NULL;
			}
		    }
		  free(transRig);
		  transRig=NULL;
		}
	      break;
	    case SETADD:
	      transLef = translate(getLefSonFrameConst(rango),transLef,&sizeLef);
	      transRig = translate(getRigSonFrameConst(rango),transRig,&sizeRig);
	      for (i = 0; i <= sizeRig; i++)
		coder=addElement(coder, transRig[i], tamcoder);
	      for (i = 0; i <= sizeLef; i++)
		coder=addElement(coder, transLef[i], tamcoder);
	      strcpy(aux,"set_add");
	      coder=addElement(coder, aux, tamcoder);
	      if(aux != NULL)
		{
		  free(aux);
		  aux=NULL;
		}
	      if(transLef != NULL)
		{
		  for(i=0; i<=sizeLef; i++)
		    {
		      if(transLef[i] != NULL)
			{
			  free(transLef[i]);
			  transLef[i]=NULL;
			}
		    }
		  free(transLef);
		  transLef=NULL;
		}
	      if(transRig != NULL)
		{
		  for(i=0; i<=sizeRig; i++)
		    {
		      if(transRig[i] != NULL)
			{
			  free(transRig[i]);
			  transRig[i]=NULL;
			}
		    }
		  free(transRig);
		  transRig=NULL;
		}
	      break;
	    case SETSUB:
	      transLef = translate(getLefSonFrameConst(rango),transLef,&sizeLef);
	      transRig = translate(getRigSonFrameConst(rango),transRig,&sizeRig);
	      for (i = 0; i <= sizeRig; i++)
		coder=addElement(coder, transRig[i], tamcoder);
	      for (i = 0; i <= sizeLef; i++)
		coder=addElement(coder, transLef[i], tamcoder);
	      strcpy(aux,"set_sub");
	      coder=addElement(coder, aux, tamcoder);
	      if(aux != NULL)
		  {
		  free(aux);
		  aux=NULL;
		}
	      if(transLef != NULL)
		{
		  for(i=0; i<=sizeLef; i++)
		    {
		      if(transLef[i] != NULL)
			{
			  free(transLef[i]);
			  transLef[i]=NULL;
			}
		    }
		  free(transLef);
		  transLef=NULL;
		}
	      if(transRig != NULL)
		{
		  for(i=0; i<=sizeRig; i++)
		    {
		      if(transRig[i] != NULL)
			{
			  free(transRig[i]);
			  transRig[i]=NULL;
			}
		    }
		  free(transRig);
		  transRig=NULL;
		}
	      break;
	    case OR:
	      transLef = translate(getLefSonFrameConst(rango),transLef,&sizeLef);
	      transRig = translate(getRigSonFrameConst(rango),transRig,&sizeRig);
	      for (i = 0; i <= sizeRig; i++)
		coder=addElement(coder, transRig[i], tamcoder);
	      for (i = 0; i <= sizeLef; i++)
		coder=addElement(coder, transLef[i], tamcoder);
	      strcpy(aux,"union");
	      coder=addElement(coder, aux, tamcoder);
	      if(aux != NULL)
		{
		  free(aux);
		  aux=NULL;
		}
	      if(transLef != NULL)
		{
		  for(i=0; i<=sizeLef; i++)
		    {
		      if(transLef[i] != NULL)
			{
			  free(transLef[i]);
			  transLef[i]=NULL;
			}
		    }
		  free(transLef);
		  transLef=NULL;
		}
	      if(transRig != NULL)
		{
		  for(i=0; i<=sizeRig; i++)
		    {
		      if(transRig[i] != NULL)
			{
			  free(transRig[i]);
			  transRig[i]=NULL;
			}
		    }
		  free(transRig);
		  transRig=NULL;
		}
	      break;
	    case AND:
	      transLef = translate(getLefSonFrameConst(rango),transLef,&sizeLef);
	      transRig = translate(getRigSonFrameConst(rango),transRig,&sizeRig);
	      for (i = 0; i <= sizeRig; i++)
		coder=addElement(coder, transRig[i], tamcoder);
	      for (i = 0; i <= sizeLef; i++)
		coder=addElement(coder, transLef[i], tamcoder);
	      strcpy(aux,"inter");
	      coder=addElement(coder, aux, tamcoder);
	      if(aux != NULL)
		{
		  free(aux);
		  aux=NULL;
		}
	      if(transLef != NULL)
		{
		  for(i=0; i<=sizeLef; i++)
		    {
		      if(transLef[i] != NULL)
			{
			  free(transLef[i]);
			  transLef[i]=NULL;
			}
		    }
		  free(transLef);
		  transLef=NULL;
		}
	      if(transRig != NULL)
		{
		  for(i=0; i<=sizeRig; i++)
		    {
		      if(transRig[i] != NULL)
			{
			  free(transRig[i]);
			  transRig[i]=NULL;
			}
		    }
		  free(transRig);
		  transRig=NULL;
		}
	      break;
	    case DIFF:
	      transLef = translate(getLefSonFrameConst(rango),transLef,&sizeLef);
	      transRig = translate(getRigSonFrameConst(rango),transRig,&sizeRig);
	      for (i = 0; i <= sizeRig; i++)
		coder=addElement(coder, transRig[i], tamcoder);
	      for (i = 0; i <= sizeLef; i++)
		coder=addElement(coder, transLef[i], tamcoder);
	      strcpy(aux,"diff");
	      coder=addElement(coder, aux, tamcoder);
	      if(aux != NULL)
		{
		  free(aux);
		  aux=NULL;
		}
	      if(transLef != NULL)
		{
		  for(i=0; i<=sizeLef; i++)
		    {
		      if(transLef[i] != NULL)
			{
			  free(transLef[i]);
			  transLef[i]=NULL;
			}
		    }
		  free(transLef);
		  transLef=NULL;
		}
	      if(transRig != NULL)
		{
		  for(i=0; i<=sizeRig; i++)
		    {
		      if(transRig[i] != NULL)
			{
			  free(transRig[i]);
			  transRig[i]=NULL;
			}
		    }
		  free(transRig);
		  transRig=NULL;
		}
	      break;
	    case SETMULT:
	      transLef = translate(getLefSonFrameConst(rango),transLef,&sizeLef);
	      transRig = translate(getRigSonFrameConst(rango),transRig,&sizeRig);
	      for (i = 0; i <= sizeRig; i++)
		coder=addElement(coder, transRig[i], tamcoder);
	      for (i = 0; i <= sizeLef; i++)
		coder=addElement(coder, transLef[i], tamcoder);
	      strcpy(aux,"set_mult");
	      coder=addElement(coder, aux, tamcoder);
	      if(aux != NULL)
		{
		  free(aux);
		  aux=NULL;
		}
	      if(transLef != NULL)
		{
		  for(i=0; i<=sizeLef; i++)
		    {
		      if(transLef[i] != NULL)
			{
			  free(transLef[i]);
			  transLef[i]=NULL;
			}
		    }
		  free(transLef);
		  transLef=NULL;
		}
	      if(transRig != NULL)
		{
		  for(i=0; i<=sizeRig; i++)
		    {
		      if(transRig[i] != NULL)
			{
			  free(transRig[i]);
			  transRig[i]=NULL;
			}
		    }
		  free(transRig);
		  transRig=NULL;
		}
	      break;
	    case SETDIV:
	      transLef = translate(getLefSonFrameConst(rango),transLef,&sizeLef);
	      transRig = translate(getRigSonFrameConst(rango),transRig,&sizeRig);
	      for (i = 0; i <= sizeRig; i++)
		coder=addElement(coder, transRig[i], tamcoder);
	      for (i = 0; i <= sizeLef; i++)
		coder=addElement(coder, transLef[i], tamcoder);
	      strcpy(aux,"set_div");
	      coder=addElement(coder, aux, tamcoder);
	      if(aux != NULL)
		{
		  free(aux);
		  aux=NULL;
		}
	      if(transLef != NULL)
		{
		  for(i=0; i<=sizeLef; i++)
		    {
		      if(transLef[i] != NULL)
			{
			  free(transLef[i]);
			  transLef[i]=NULL;
			}
		    }
		  free(transLef);
		  transLef=NULL;
		}
	      if(transRig != NULL)
		{
		  for(i=0; i<=sizeRig; i++)
		    {
		      if(transRig[i] != NULL)
			{
			  free(transRig[i]);
			  transRig[i]=NULL;
			}
		    }
		  free(transRig);
		  transRig=NULL;
		}
	      break;
	    case SETMOD:
	      transLef = translate(getLefSonFrameConst(rango),transLef,&sizeLef);
	      transRig = translate(getRigSonFrameConst(rango),transRig,&sizeRig);
	      for (i = 0; i <= sizeRig; i++)
		coder=addElement(coder, transRig[i], tamcoder);
	      for (i = 0; i <= sizeLef; i++)
		coder=addElement(coder, transLef[i], tamcoder);
	      strcpy(aux,"set_mod");
	      coder=addElement(coder, aux, tamcoder);
	      if(aux != NULL)
		{
		  free(aux);
		  aux=NULL;
		}
	      if(transLef != NULL)
		{
		  for(i=0; i<=sizeLef; i++)
		    {
		      if(transLef[i] != NULL)
			{
			  free(transLef[i]);
			  transLef[i]=NULL;
			}
		    }
		  free(transLef);
		  transLef=NULL;
		}
	      if(transRig != NULL)
		{
		  for(i=0; i<=sizeRig; i++)
		    {
		      if(transRig[i] != NULL)
			{
			  free(transRig[i]);
			  transRig[i]=NULL;
			}
		    }
		  free(transRig);
		  transRig=NULL;
		}	
	      break;
	    case IMP:
	      transLef = translate(getLefSonFrameConst(rango),transLef,&sizeLef);
	      transRig = translate(getRigSonFrameConst(rango),transRig,&sizeRig);
	      for (i = 0; i <= sizeLef; i++)
		coder=addElement(coder, transLef[i], tamcoder);
	      coder=addElement(coder, "check", tamcoder);
	      strcpy(aux,fcvt(sizeRig+2,0,&m,&n));
	      coder=addElement(coder, aux, tamcoder);
	      for (i = 0; i <= sizeRig; i++)
		coder=addElement(coder, transRig[i], tamcoder);
	      strcpy(aux,fcvt(sizeRig+2,0,&m,&n));
	      coder=addElement(coder, aux, tamcoder);
	      if(aux != NULL)
		  {
		      free(aux);
		      aux=NULL;
		  }
	      if(transLef != NULL)
		  {
		      for(i=0; i<=sizeLef; i++)
			  {
			      if(transLef[i] != NULL)
				  {
				      free(transLef[i]);
				      transLef[i]=NULL;
				  }
			  }
		      free(transLef);
		      transLef=NULL;
		  }
	      if(transRig != NULL)
		{
		  for(i=0; i<=sizeRig; i++)
		    {
		      if(transRig[i] != NULL)
			{
			  free(transRig[i]);
			  transRig[i]=NULL;
			}
		    }
		  free(transRig);
		  transRig=NULL;
		}
	      break;
	    case DOM:
	      strcpy(aux,"dom");
	      coder=addElement(coder, aux, tamcoder);
	      pos = getValueFrameConst(getLefSonFrameConst(rango)); /* Posicion en el store */
	      if (pos < 0)
		{
		  strcpy(aux,"-");
		  strcat(aux,fcvt(pos,0,&m,&n));
		}
	      else
		{
		  strcpy(aux,fcvt(pos,0,&m,&n));
		}
	      coder=addElement(coder, aux, tamcoder);
	      if(aux != NULL)
		  {
		      free(aux);
		      aux=NULL;
		  }
	      if(transLef != NULL)
		  {
		      free(transLef);
		      transLef=NULL;
		  }
	      if(transRig != NULL)
		  {
		      free(transRig);
		      transRig=NULL;
		  }
	      break;
	    case ADD:
	      transLef = translate(getLefSonFrameConst(rango),transLef,&sizeLef);
	      transRig = translate(getRigSonFrameConst(rango),transRig,&sizeRig);
	      for (i = 0; i <= sizeRig; i++)
		  coder=addElement(coder, transRig[i], tamcoder);
	      for (i = 0; i <= sizeLef; i++)
		  coder=addElement(coder, transLef[i], tamcoder);
	      strcpy(aux,"add");
	      coder=addElement(coder, aux, tamcoder);
	      if(aux != NULL)
		{
		  free(aux);
		  aux=NULL;
		}
	      if(transLef != NULL)
		{
		  for(i=0; i<=sizeLef; i++)
		    {
		      if(transLef[i] != NULL)
			{
			  free(transLef[i]);
			  transLef[i]=NULL;
			}
		    }
		  free(transLef);
		  transLef=NULL;
		}
	      if(transRig != NULL)
		{
		  for(i=0; i<=sizeRig; i++)
		    {
		      if(transRig[i] != NULL)
			{
			  free(transRig[i]);
			  transRig[i]=NULL;
			}
		    }
		  free(transRig);
		  transRig=NULL;
		}
	      break;
	    case SUBS:
	      transLef = translate(getLefSonFrameConst(rango),transLef,&sizeLef);
	      transRig = translate(getRigSonFrameConst(rango),transRig,&sizeRig);
	      for (i = 0; i <= sizeRig; i++)
		coder=addElement(coder, transRig[i], tamcoder);
	      for (i = 0; i <= sizeLef; i++)
		coder=addElement(coder, transLef[i], tamcoder);
	      strcpy(aux,"sub");
	      coder=addElement(coder, aux, tamcoder);
	      if(aux != NULL)
		{
		  free(aux);
		  aux=NULL;
		}
	      if(transLef != NULL)
		{
		  for(i=0; i<=sizeLef; i++)
		    {
		      if(transLef[i] != NULL)
			{
			  free(transLef[i]);
			  transLef[i]=NULL;
			}
		    }
		  free(transLef);
		  transLef=NULL;
		}
	      if(transRig != NULL)
		{
		  for(i=0; i<=sizeRig; i++)
		    {
		      if(transRig[i] != NULL)
			{
			  free(transRig[i]);
			  transRig[i]=NULL;
			}
		    }
		  free(transRig);
		  transRig=NULL;
		}
	      break;
	    case MULT:
	      transLef = translate(getLefSonFrameConst(rango),transLef,&sizeLef);
	      transRig = translate(getRigSonFrameConst(rango),transRig,&sizeRig);
	      for (i = 0; i <= sizeRig; i++)
		coder=addElement(coder, transRig[i], tamcoder);
	      for (i = 0; i <= sizeLef; i++)
		coder=addElement(coder, transLef[i], tamcoder);
	      strcpy(aux,"mult");
	      coder=addElement(coder, aux, tamcoder);
	      if(aux != NULL)
		{
		  free(aux);
		  aux=NULL;
		}
	      if(transLef != NULL)
		{
		  for(i=0; i<=sizeLef; i++)
		    {
		      if(transLef[i] != NULL)
			{
			  free(transLef[i]);
			  transLef[i]=NULL;
			}
		    }
		  free(transLef);
		  transLef=NULL;
		}
	      if(transRig != NULL)
		{
		  for(i=0; i<=sizeRig; i++)
		    {
		      if(transRig[i] != NULL)
			{
			  free(transRig[i]);
			  transRig[i]=NULL;
			}
		    }
		  free(transRig);
		  transRig=NULL;
		}
	      break;
	    case DIV:
	      transLef = translate(getLefSonFrameConst(rango),transLef,&sizeLef);
	      transRig = translate(getRigSonFrameConst(rango),transRig,&sizeRig);
	      for (i = 0; i <= sizeRig; i++)
		coder=addElement(coder, transRig[i], tamcoder);
	      for (i = 0; i <= sizeLef; i++)
		coder=addElement(coder, transLef[i], tamcoder);
	      strcpy(aux,"div");
	      coder=addElement(coder, aux, tamcoder);
	      if(aux != NULL)
		{
		  free(aux);
		  aux=NULL;
		}
	      if(transLef != NULL)
		{
		  for(i=0; i<=sizeLef; i++)
		    {
		      if(transLef[i] != NULL)
			{
			  free(transLef[i]);
			  transLef[i]=NULL;
			}
		    }
		  free(transLef);
		  transLef=NULL;
		}
	      if(transRig != NULL)
		{
		  for(i=0; i<=sizeRig; i++)
		    {
		      if(transRig[i] != NULL)
			{
			  free(transRig[i]);
			  transRig[i]=NULL;
			}
		    }
		  free(transRig);
		  transRig=NULL;
		}
	      break;
	    case MOD:
	      transLef = translate(getLefSonFrameConst(rango),transLef,&sizeLef);
	      transRig = translate(getRigSonFrameConst(rango),transRig,&sizeRig);
	      for (i = 0; i <= sizeRig; i++)
		coder=addElement(coder, transRig[i], tamcoder);
	      for (i = 0; i <= sizeLef; i++)
		coder=addElement(coder, transLef[i], tamcoder);
	      strcpy(aux,"mod");
	      coder=addElement(coder, aux, tamcoder);
	      if(aux != NULL)
		{
		  free(aux);
		  aux=NULL;
		}
	      if(transLef != NULL)
		{
		  for(i=0; i<=sizeLef; i++)
		    {
		      if(transLef[i] != NULL)
			{
			  free(transLef[i]);
			  transLef[i]=NULL;
			}
		    }
		  free(transLef);
		  transLef=NULL;
		}
	      if(transRig != NULL)
		{
		  for(i=0; i<=sizeRig; i++)
		    {
		      if(transRig[i] != NULL)
			{
			  free(transRig[i]);
			  transRig[i]=NULL;
			}
		    }
		  free(transRig);
		  transRig=NULL;
		}
	      break;
	    case MIN:
	      if (getTypeFrameConst(getLefSonFrameConst(rango)) == VARIABLE)
		{
		  strcpy(aux,"dom_min");
		  coder=addElement(coder, aux, tamcoder);
		  pos = getValueFrameConst(getLefSonFrameConst(rango)); /* Posicion en el store */
		  if ( pos < 0)
		    {
		      strcpy(aux, "-");
		      strcat(aux, fcvt(pos,0,&m,&n));
		    }
		  else
		    {
		      strcpy(aux, fcvt(pos,0,&m,&n));
		    }
		  coder=addElement(coder, aux, tamcoder);
		  if(aux != NULL)
		     {
		       free(aux);
		       aux=NULL;
		     }
		  if(transLef != NULL)
		      {
		       free(transLef);
		       transLef=NULL;
		      }
		  if(transRig != NULL)
		      {
			  free(transRig);
			  transRig=NULL;
		      }
		}
	      else
		{
		  transLef = translate(getLefSonFrameConst(rango),transLef,&sizeLef);
		  for (i = 0; i <= sizeLef; i++)
		    coder=addElement(coder, transLef[i], tamcoder);
		  strcpy(aux,"min");
		  coder=addElement(coder, aux, tamcoder);
		  if(aux != NULL)
		     {
		       free(aux);
		       aux=NULL;
		     }
		   if(transLef != NULL)
		     {
		       for(i=0; i<=sizeLef; i++)
			 {
			   if(transLef[i] != NULL)
			     {
			       free(transLef[i]);
			       transLef[i]=NULL;
			     }
			 }
		       free(transLef);
		       transLef=NULL;
		     }
		   if(transRig != NULL)
		     {
		       free(transRig);
		       transRig=NULL;
		     }
		}
	      break;
	    default:/* Case MAX */
	      if (getTypeFrameConst(getLefSonFrameConst(rango)) == VARIABLE)
		{
		  strcpy(aux,"dom_max");
		  coder=addElement(coder, aux, tamcoder);
		  pos = getValueFrameConst(getLefSonFrameConst(rango)); /* Posicion en el store */
		  if (pos < 0)
		    {
		      strcpy(aux, "-");
		      strcat(aux, fcvt(pos,0,&m,&n));
		    }
		  else
		    {
		      strcpy(aux,fcvt(pos,0,&m,&n));
		    }
		  coder=addElement(coder, aux, tamcoder);
		  if(aux != NULL)
		      {
			  free(aux);
			  aux=NULL;
		      }
		  if(transLef != NULL)
		      {
			  free(transLef);
			  transLef=NULL;
		      }
		  if(transRig != NULL)
		      {
			  free(transRig);
			  transRig=NULL;
		      }
		}
	      else
		{
		  transLef = translate(getLefSonFrameConst(rango),transLef,&sizeLef);
		  for (i = 0; i <= sizeLef; i++)
		    coder=addElement(coder, transLef[i], tamcoder);
		  strcpy(aux,"max");
		  coder=addElement(coder, aux, tamcoder);
		  if(aux != NULL)
		    {
		      free(aux);
		      aux=NULL;
		    }
		  if(transLef != NULL)
		    {
		      for(i=0; i<=sizeLef; i++)
			{
			  if(transLef[i] != NULL)
			    {
			      free(transLef[i]);
			      transLef[i]=NULL;
			    }
			}
		      free(transLef);
		      transLef=NULL;
		    }
		  if(transRig != NULL)
		    {
		      free(transRig);
		      transRig=NULL;
		    }
		}
	      break;
	    }
	  return coder;
	}
      }
}

char** addElement(char ** coder, char * aux, int *tamcoder)
/*---------------------------------------------------------------
  DESCRIPCION: Funcion auxiliar que adiciona al vector dinamico
               coder la variable aux.

  PARAMETROS: coder: Vector dinamico al cual se le va adicionar
                     aux en la ultima posicion.
              aux: Variable a adicionar al coder.
	      tamcoder: Tamaño e indice del vector dinamico coder.
  USA:
  RETORNA: El codigo compilado.
  PRE:
  POS:coder[tamcoder+1]  = aux
  NOTAS:
  ---------------------------------------------------------------*/
{
  (*tamcoder)++;

  /* Verificacion si se debe o no hacer un realloc */
  if ((*tamcoder) >= TAMCODER)
    {
      coder = (char **)realloc(coder,((*tamcoder)+1)*sizeof(char*));
      if (!(coder))
	{
	  printf("Error en la reasignacion de memoria para la adicion de un elemento del rango compilado");
	  exit(1);
	}
      (coder)[*tamcoder] = (char *)malloc((strlen(aux)+1)*sizeof(char));
      if (!((coder)[*tamcoder]))
	{
	  printf("Error en la asignacion de memoria para adicionar al coder");
	  exit(1);
	}
      strcpy((coder)[*tamcoder],aux);
    }
  else
    {
      (coder)[*tamcoder] = (char *)malloc((strlen(aux)+1)*sizeof(char));
      if (!((coder)[*tamcoder]))
	{
	  printf("Error en la asignacion de memoria para adicionar al coder");
	  exit(1);
	}
      strcpy((coder)[*tamcoder],aux);
    }
  return coder;
}

#endif

/**** EOF ****/



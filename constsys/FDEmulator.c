#ifndef _FDEmulator_c
#define _FDEmulator_c
/****************************************************************
* IMPLEMENTACION MODULO: FDEmulator.c
* FECHA CREACION:  29-Mar-01
* DESCRIPCION: 
*   Metodo que evalua un rango compilado en el store.
*
* AUTORES:         CATHERINE GARCIA
*                  ALEJANDRA MARIA VASQUEZ
* MODIFICACIONES:
* AUTOR FECHA:
*
*****************************************************************/
/*===============================================================*
  Tabla de Contenido:
  
  0. Instrucciones para compilar el modulo
       gcc -c FDEmulator.c

  1. Librerias requeridas para su linkeo:
       -lm -lX11

  2. Listado de estructuras de datos definidas (publicas y privadas)

  struct TFDEmulator
  {
  enum Type flagtype;
  Info info;
  };

  3. Listado de funciones definidas (publicas y privadas)

  Domain r_Sigma(Store, Indexical)

  4. Instruccion para modificar el modulo
  4.1 Construcciones importantes para tener en cuenta (e.g. tipos, variables, funciones)
  4.2 Observaciones Adicionales
  
  ===============================================================*/
/*--------------------------------------------------------------*
  Archivos de Interfaz de librerias estandar y de otros modulos
 *--------------------------------------------------------------*/
#include "FDEmulator.h"
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
Domain r_Sigma(Store store, Indexical indexical)
/*---------------------------------------------------------------
  DESCRIPCION: Funcion que evalua el rango "rango" en el store.

  PARAMETROS: store: Store del sistema de Restricciones
              indexical: Indexical a evaluar.
  USA:
  RETORNA:
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int temp;
  char **c, **coder;
  int a, i, j, k , m, n;
  Domain d, d_p,r_sigma;
  TFDEmulator v[(indexical->tamcoder)+2];
  FDVariable var;

  coder = getCoder(indexical);
 
  c=(char**)malloc((getTamCoder(indexical)+2)*sizeof(char *));
  
  for(a = 0; a <= getTamCoder(indexical); a++)
    {
      c[a]= (char *)malloc((strlen(coder[a])+1)*sizeof(char));
      if( !c[a] )
	{
	  printf("Error en la asignacion de memoria para la copia del coder del emulator...\n");
	  exit(1);
	}
      strcpy(c[a],coder[a]);
    }

  c[getTamCoder(indexical)+1]= (char *)malloc(6*sizeof(char));
  if( !c[a] )
    {
      printf("Error en la asignacion de memoria para la copia del coder del emulator...\n");
      exit(1);
    }
  strcpy(c[getTamCoder(indexical)+1], "halt");

  for(a = 0; a <= (getTamCoder(indexical)+1); a++)
    {
      v[a].flagtype = Und;
    }
 
  /* Inicio del algoritmo */  
  i = 0;
  j = 0;
  for (;;)
    {
      if (strcmp(c[i], "const") == 0)
	{
	  if ((v[j]).flagtype == Dom)
	    freeDomain((v[j]).info.domain);
	  (v[j]).flagtype = Val;
	  (v[j++]).info.value = atoi(c[i+1]);
	  i = i + 2;
	}
      else if (strcmp(c[i], "val") == 0)
	{
	  if ((v[j]).flagtype == Dom)
	    freeDomain((v[j]).info.domain);
	  k = atoi(c[i+1]);
	  (v[j]).flagtype = Val;
	  var=getVariableStore(store, k);
	  (v[j++]).info.value = a_kDomain(getDomainFDVariable(var));
	  i = i + 2;
	}
      else if (strcmp(c[i], "dom") == 0)
	{
	  if ((v[j]).flagtype == Dom)
	    freeDomain((v[j]).info.domain);
	  (v[j]).flagtype = Dom;
	  k = atoi(c[i+1]);
	  var=getVariableStore(store, k);
	  (v[j++]).info.domain = Inicp1Domain(getDomainFDVariable(var));
	  i = i + 2;
	}
      else if (strcmp(c[i], "dom_min") == 0)
	{
	  if ((v[j]).flagtype == Dom)
	    freeDomain((v[j]).info.domain);
	  k = atoi(c[i+1]);
	  (v[j]).flagtype = Val;
	  var=getVariableStore(store, k);
	  (v[j++]).info.value = getMinimumDomain(getDomainFDVariable(var));
	  i = i + 2;
	}
      else if (strcmp(c[i], "dom_max") == 0)
	{
	  if ((v[j]).flagtype == Dom)
	    freeDomain((v[j]).info.domain);
	  k = atoi(c[i+1]);
	  (v[j]).flagtype = Val;
	  var=getVariableStore(store, k);
	  (v[j++]).info.value = getMaximumDomain(getDomainFDVariable(var));
	  i = i + 2;
	}
      else if (strcmp(c[i], "range") == 0)
	{
	  n = (v[--j]).info.value;
	  m = (v[--j]).info.value;
	  if ((v[j]).flagtype == Dom)
	    freeDomain((v[j]).info.domain);
	  (v[j]).flagtype = Dom;
	  (v[j++]).info.domain = InicpDomain(n, m);
	  i++;
	}
      else if (strcmp(c[i], "set_add") == 0)
	{
	  temp = (v[--j]).flagtype;
	  if (temp == Dom)
	    d = Inicp1Domain((v[j]).info.domain);
	  else
	    d = InicpDomain((v[j]).info.value, (v[j]).info.value);

	  temp = (v[--j]).flagtype;
	  n = (v[j]).info.value;
	  if ((v[j]).flagtype == Dom)
	    freeDomain((v[j]).info.domain);
	  (v[j]).flagtype = Dom;
	  addIntDomain(d, n);
	  (v[j++]).info.domain = Inicp1Domain(d);
	  i++;
	  freeDomain(d);
	}
      else if (strcmp(c[i], "set_sub") == 0)
	{
	  temp = (v[--j]).flagtype;
	  if (temp == Dom)
	    d = Inicp1Domain((v[j]).info.domain);
	  else
	    d = InicpDomain((v[j]).info.value, (v[j]).info.value);
	  
	  temp = (v[--j]).flagtype;
	  if ((v[j]).flagtype == Dom)
	    freeDomain((v[j]).info.domain);
	  n = (v[j]).info.value;
	  (v[j]).flagtype = Dom;
	  subIntDomain(d, n);
	  (v[j++]).info.domain = Inicp1Domain(d);
	  i++;
	  freeDomain(d);
	}
      else if (strcmp(c[i], "union") == 0)
	{
	  temp = (v[--j]).flagtype;
	  if (temp == Dom)
	    d = Inicp1Domain((v[j]).info.domain);
	  else
	    d = InicpDomain((v[j]).info.value, (v[j]).info.value);
	  
	  temp = (v[--j]).flagtype;
	  if (temp == Dom)
	    d_p = Inicp1Domain((v[j]).info.domain);
	  else
	    d_p = InicpDomain((v[j]).info.value,(v[j]).info.value);
	  if ((v[j]).flagtype == Dom)
	    freeDomain((v[j]).info.domain);
	  (v[j]).flagtype = Dom;
	  unionDomain(d, d_p);
	  (v[j++]).info.domain = Inicp1Domain(d);
	  i++;
	  freeDomain(d_p);
	  freeDomain(d);
	}
      else if (strcmp(c[i], "inter") == 0)
	{
	  temp = (v[--j]).flagtype;
	  if (temp == Dom)
	    d = Inicp1Domain((v[j]).info.domain);
	  else
	    d = InicpDomain((v[j]).info.value, (v[j]).info.value);
	  
	  temp = (v[--j]).flagtype;
	  if (temp == Dom)
	    d_p = Inicp1Domain((v[j]).info.domain);
	  else
	    d_p = InicpDomain((v[j]).info.value,(v[j]).info.value);
	  if ((v[j]).flagtype == Dom)
	    freeDomain((v[j]).info.domain);
	  (v[j]).flagtype = Dom;
	  intersectionDomain(d, d_p);
	  (v[j++]).info.domain = Inicp1Domain(d);
	  i++;
	  freeDomain(d_p);
	  freeDomain(d);
	}
      else if (strcmp(c[i], "diff") == 0)
	{
	  temp = (v[--j]).flagtype;
	  if (temp == Dom)
	    d = Inicp1Domain((v[j]).info.domain);
	  else
	    d = InicpDomain((v[j]).info.value, (v[j]).info.value);
	  
	  temp = (v[--j]).flagtype;
	  if (temp == Dom)
	    d_p = Inicp1Domain((v[j]).info.domain);
	  else
	    d_p = InicpDomain((v[j]).info.value,(v[j]).info.value);
	  if ((v[j]).flagtype == Dom)
	    freeDomain((v[j]).info.domain);
	  (v[j]).flagtype = Dom;
	  diffDomain(d, d_p);
	  (v[j++]).info.domain = Inicp1Domain(d);
	  i++;
	  freeDomain(d_p);
	  freeDomain(d);
	}
       else if (strcmp(c[i], "check") == 0)
	{
	  temp = (v[--j]).flagtype;
	  if (temp == Dom)
	    d = Inicp1Domain((v[j]).info.domain);
	  else
	    d = InicpDomain((v[j]).info.value, (v[j]).info.value);
	  
	  if (!isConsistentDomain(d))
	    {
	      if ((v[j]).flagtype == Dom)
		freeDomain((v[j]).info.domain);
	      (v[j]).flagtype = Dom;
	      (v[j++]).info.domain = Inicp1Domain(d);
	      n = atoi(c[i+1]);
	      i = i + n;
	    }
	  else
	      i = i + 2;
	  freeDomain(d);
	}
      else if (strcmp(c[i], "add") == 0)
	{
	  n = (v[--j]).info.value;
	  m = (v[--j]).info.value;
	  if ((v[j]).flagtype == Dom)
	    freeDomain((v[j]).info.domain);
	  (v[j]).flagtype = Val;
	  (v[j++]).info.value = (n+m);
	  i++;
	  }
      else if (strcmp(c[i], "sub") == 0)
	{
	      n = (v[--j]).info.value;
	      m = (v[--j]).info.value;
	      if ((v[j]).flagtype == Dom)
		freeDomain((v[j]).info.domain);
	      (v[j]).flagtype = Val;
	      (v[j++]).info.value = (n-m);
	      i++;
	  }
      else if (strcmp(c[i], "mult") == 0)
	  {
	      n = (v[--j]).info.value;
	      m = (v[--j]).info.value;
	      if ((v[j]).flagtype == Dom)
		freeDomain((v[j]).info.domain);
	      (v[j]).flagtype = Val;
	      (v[j++]).info.value = (n*m);
	      i++;
	  }
      else if (strcmp(c[i], "div") == 0)
	  {
	  n = (v[--j]).info.value;
	  m = (v[--j]).info.value;
	  if ((v[j]).flagtype == Dom)
	    freeDomain((v[j]).info.domain);
	  (v[j]).flagtype = Val;
	  (v[j++]).info.value = (n/m);
	  i++;
	}
      else if (strcmp(c[i], "mod") == 0)
	{
	  n = (v[--j]).info.value;
	  m = (v[--j]).info.value;
	  if ((v[j]).flagtype == Dom)
	    freeDomain((v[j]).info.domain);
	  (v[j]).flagtype = Val;
	  (v[j++]).info.value = (n%m);
	  i++;
	}
       else if (strcmp(c[i], "min") == 0)
	{
	  temp = (v[--j]).flagtype;
	  if (temp == Dom)
	    d = Inicp1Domain((v[j]).info.domain);
	  else
	    d = InicpDomain((v[j]).info.value, (v[j]).info.value);

	  if ((v[j]).flagtype == Dom)
	    freeDomain((v[j]).info.domain);
	  (v[j]).flagtype = Val;
	  (v[j++]).info.value = getMinimumDomain(d);
	  i++;
	  freeDomain(d);
	}
      else if (strcmp(c[i], "max") == 0)
	{
	  temp = (v[--j]).flagtype;
	  if (temp == Dom)
	    d = Inicp1Domain((v[j]).info.domain);
	  else
	    d = InicpDomain((v[j]).info.value, (v[j]).info.value);

	  if ((v[j]).flagtype == Dom)
	    freeDomain((v[j]).info.domain);
	  (v[j]).flagtype = Val;
	  (v[j++]).info.value = getMaximumDomain(d);
	  i++;
	  freeDomain(d);
	}
      else if (strcmp(c[i], "halt") == 0)
	{
	  temp = (v[j-1]).flagtype;
	  if (temp == Val)
	    {
	      d = InicpDomain((v[j-1]).info.value, (v[j-1]).info.value);
	      if ((v[j-1]).flagtype == Dom)
		freeDomain((v[j-1]).info.domain);
	      (v[j-1]).flagtype = Dom;
	      (v[j-1]).info.domain = Inicp1Domain(d);
	      freeDomain(d);
	    }
	  break;
	}
      else
	i++;
    }
  
  r_sigma = Inicp1Domain((v[j-1]).info.domain);

  if(c!=NULL)
    {
      for(i=0;i<=(getTamCoder(indexical)+1);i++)
	{
	  if(c[i] != NULL)
	    {
	      free(c[i]);
	      c[i]=NULL;
	    }
	}
      free(c);
      c=NULL;
    }
  
  for(a = 0; a <= (getTamCoder(indexical)+1); a++)
    {
      if ( v[a].flagtype == Dom )
      freeDomain((v[a].info).domain);
    }
  
  return r_sigma;
}


#endif

/**** EOF ****/



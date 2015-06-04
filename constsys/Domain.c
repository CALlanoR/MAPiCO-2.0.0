#ifndef _Domain_c_
#define _Domain_c_
/****************************************************************
* IMPLEMENTACION MODULO: Domain.c
* FECHA CREACION:  27-Mar-01
* DESCRIPCION: 
*   Implementa la representacion del dominio de una variable
*   de dominio finito.
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
       gcc -c Domain.c

  1. Librerias requeridas para su linkeo:
       -lm -lX11

  2. Listado de estructuras de datos definidas (publicas y privadas)
  
  typedef struct
  {
  char info[MAXINFO];  Informacion del Dominio 
  int min;  Minimo del dominio
  int max;  Maximo del dominio 
  int prune_type;  Tipo de poda con respecto a la ultima actualizacion del dominio
  int expanded; Informacion si el dominio esta expandido o no
  }TDomain, *Domain;
  
  3. Listado de funciones definidas (publicas y privadas)

  Domain InicDomain(void)
  Domain InicpDomain(int, int)
  Domain Inicp1Domain(Domain)
  char * getInfoDomain(Domain)
  void ImprimirDomain(Domain)
  int getMinimumDomain(Domain)
  int getMaximumDomain(Domain)
  int getExpandedDomain(Domain)
  int getPruneTypeDomain(Domain)
  int getBitDomain(Domain, int)
  void setMinimumDomain(Domain, int)
  void setMaximumDomain(Domain, int)
  void setPruneTypeDomain(Domain, int)
  void setInfoDomain(Domain, char [])
  void setExpandedDomain(Domain, int)
  void expandDomain(Domain)
  int a_kDomain(Domain)
  void diffDomain(Domain,Domain)
  int isDeterminatedDomain(Domain)
  void unionDomain(Domain,Domain)
  void intersectionDomain(Domain,Domain)
  void updateDomain(Domain , Domain)
  int isConsistentDomain(Domain)
  int equalsDomain(Domain, Domain)
  void addIntDomain(Domain,int)
  void addDomain(Domain,Domain)
  void subIntDomain(Domain,int)
  void substractDomain(Domain,Domain)
  void multiplicationDomain(Domain,int)
  void divisionDomain(Domain,int)
  void modDomain(Domain,int)
  void freeDomain(Domain)

  4. Instruccion para modificar el modulo
  4.1 Construcciones importantes para tener en cuenta (e.g. tipos, variables, funciones)
  4.2 Observaciones Adicionales
  
  ===============================================================*/
/*--------------------------------------------------------------*
  Archivos de Interfaz de librerias estandar y de otros modulos
 *--------------------------------------------------------------*/
#include "Domain.h"
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
Domain InicDomain(void)
/*---------------------------------------------------------------
  DESCRIPCION: Funcion que crea un Dominio para una variable de
               dominio finito.
  PARAMETROS: 
  USA:
  RETORNA: Dominio
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
    Domain resp;

    resp = (Domain)malloc(sizeof(TDomain));
    if (!resp)
	{
	    printf("Error en la asignacion de memoria para crear un dominio");
	    exit(1);
	}
   
    resp->min = MININ;
    resp->max = MAXIN;
    /* El Dominio inicialmente no ha sido podado */
    resp->prune_type = NOPRUNE;
    /* El Dominio inicialmente no esta expando */
    resp->expanded = FALSE;
    memset(resp->info, 0, MAXINFO);

    return resp;
}

Domain InicpDomain(int min, int max)
/*---------------------------------------------------------------
  DESCRIPCION: Funcion que crea un Dominio para una variable de
               dominio finito.

  PARAMETROS: min: El Minimo del dominio a ser creado
              max: El Maximo del dominio a ser creado  
  USA:
  RETORNA: Dominio
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
    Domain resp;

    resp = (Domain)malloc(sizeof(TDomain));
    if (!resp)
	{
	    printf("Error en la asignacion de memoria para crear un dominio");
	    exit(1);
	}
   
    if (min < MININ)
	resp->min = MININ;
    else 
      resp->min = min;

    if (max > MAXIN)
	resp->max = MAXIN;
    else
      resp->max = max;
    
    /* El Dominio inicialmente no ha sido podado */
    resp->prune_type = NOPRUNE;
    /* El Dominio inicialmente no esta expandido */
    resp->expanded = FALSE;
    memset(resp->info, 0, MAXINFO);

    return resp;
}

Domain Inicp1Domain(Domain d)
/*---------------------------------------------------------------
  DESCRIPCION: Funcion que crea un Dominio para una variable de
               dominio finito, a partir de la informacion de d.

  PARAMETROS: d: Es un Dominio del cual se va a extraer la informacion 
                 para crear el dominio.
  USA:
  RETORNA: Dominio
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
    Domain resp;

    resp = (Domain)malloc(sizeof(TDomain));
    if (!resp)
	{
	    printf("Error en la asignacion de memoria para crear un dominio");
	    exit(1);
	}
   
    setMinimumDomain(resp, getMinimumDomain(d));
    setMaximumDomain(resp, getMaximumDomain(d));
    /* El Dominio inicialmente no ha sido podado */
    setPruneTypeDomain(resp, getPruneTypeDomain(d));
    /* El Dominio inicialmente no esta expandido */
    setExpandedDomain(resp, getExpandedDomain(d));
    if (getExpandedDomain(resp))
      setInfoDomain(resp, d->info);
    else
      memset(resp->info, 0, MAXINFO);

    return resp;
}

char * getInfoDomain(Domain d)
/*---------------------------------------------------------------
  DESCRIPCION:Obtiene el atributo info de un dominio.

  PARAMETROS: d: Es un Dominio del cual se va a extraer la informacion 
                 del atributo info.
  USA:
  RETORNA: El atributo info
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  return d->info;
}

void ImprimirDomain(Domain d)
/*---------------------------------------------------------------
  DESCRIPCION: Imprime el dominio de variable.

  PARAMETROS: d: dominio a imprimir.
  USA:
  RETORNA: 
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int i;
  printf("info:\n ");
  for ( i = 0; i < MAXINFO; i++)
    {
      if((((d->info)[i]) & 128) == 128)
	printf("%d,",BYTE*i);
      if((((d->info)[i]) & 64) == 64)
	printf("%d,",(BYTE*i)+1);
      if((((d->info)[i]) & 32) == 32)
	printf("%d,",(BYTE*i)+2);
      if((((d->info)[i]) & 16) == 16)
	printf("%d,",(BYTE*i)+3);
      if((((d->info)[i]) & 8) == 8)
	printf("%d,",(BYTE*i)+4);
      if((((d->info)[i]) & 4) == 4)
	printf("%d,",(BYTE*i)+5);
      if((((d->info)[i]) & 2) == 2)
	printf("%d,",(BYTE*i)+6);
      if((((d->info)[i]) & 1) == 1)
	printf("%d,",(BYTE*i)+7);   
    }
  printf("expanded: %d\n min:%d \n max:%d\n",d->expanded,d->min,d->max);
}

int getMinimumDomain(Domain d)
/*---------------------------------------------------------------
  DESCRIPCION:Obtiene el atributo min de un dominio.

  PARAMETROS: d: Es un Dominio del cual se va a extraer la informacion 
                 del atributo min.
  USA:
  RETORNA: el valor minimo de la variable
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int resp;
  resp = d->min;
  return resp;
}

int getMaximumDomain(Domain d)
/*---------------------------------------------------------------
  DESCRIPCION:Obtiene el atributo max de un dominio.

  PARAMETROS: d: Es un Dominio del cual se va a extraer la informacion 
                 del atributo max.
  USA:
  RETORNA: el valor maximo de la variable
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int resp;
  resp = d->max;
  return resp;
}

int getExpandedDomain(Domain d)
/*---------------------------------------------------------------
  DESCRIPCION:Obtiene el atributo expanded de un dominio.

  PARAMETROS: d: Es un Dominio del cual se va a extraer la informacion 
                 del atributo expanded.
  USA:
  RETORNA: el atributo expanded.
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int resp;
  resp = d->expanded;
  return resp;
}

int getPruneTypeDomain(Domain d)
/*---------------------------------------------------------------
  DESCRIPCION:Obtiene el atributo tipo de poda de un dominio.

  PARAMETROS: d: Es un Dominio del cual se va a extraer la informacion 
                 del atributo tipo de poda.
  USA:
  RETORNA: el atributo tipo de poda.
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int resp;
  resp = d->prune_type;
  return resp;
}

int getBitDomain(Domain d, int i)
/*---------------------------------------------------------------
  DESCRIPCION:Obtiene del atributo info el i-esimo elemento.

  PARAMETROS: d: Es un Dominio del cual se va a extraer la informacion 
	      i: bit que se desea obtener.
  USA:
  RETORNA: bit
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int num, aux, aux1;

  if (!isConsistentDomain(d))
    return FALSE;
  else
    {
      if (!getExpandedDomain(d))
	{
	  if (i >= getMinimumDomain(d) && i <= getMaximumDomain(d))
	    return TRUE;
	  else
	    return FALSE;
	}

      aux = i % BYTE;
      aux1 = (int)pow((double)2, (double)((BYTE-1)-aux));
      num = i / BYTE;
      if(((d->info)[num] & aux1) == aux1)
	return TRUE;
      else
	return FALSE;
    }
}

void setMinimumDomain(Domain d, int min)
/*---------------------------------------------------------------
  DESCRIPCION: Cambia el atributo min del parametro d.

  PARAMETROS: d: Es un Dominio al cual se le va a cambiar el atributo
                 min.
	      min: Valor para actualizar el atributo min.
  USA:
  RETORNA:
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
    d->min = min;
}

void setMaximumDomain(Domain d, int max)
/*---------------------------------------------------------------
  DESCRIPCION: Cambia el atributo max del parametro d.

  PARAMETROS: d: Es un Dominio al cual se le va a cambiar el atributo
                 min.
	      max: Valor para actualizar el atributo max.
  USA:
  RETORNA:
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
    d->max = max;
}


void setPruneTypeDomain(Domain d, int prunetype)
/*---------------------------------------------------------------
  DESCRIPCION: Cambia el atributo prune_type del parametro d.

  PARAMETROS: d: Es un Dominio al cual se le va a cambiar el atributo
                 prune_type.
	      prunetype: Valor para actualizar el atributo prune_type.
  USA:
  RETORNA:
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
    d->prune_type = prunetype;
}

void setInfoDomain(Domain d, char info [])
/*---------------------------------------------------------------
  DESCRIPCION: Cambia el atributo info del parametro d.

  PARAMETROS: d: Es un Dominio al cual se le va a cambiar el atributo
                 info.
	      info: Valor para actualizar el atributo info.
  USA:
  RETORNA:
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{ 
  memcpy(d->info,info,MAXINFO);
}

void setExpandedDomain(Domain d, int expanded)
/*---------------------------------------------------------------
  DESCRIPCION: Cambia el atributo expanded del parametro d.

  PARAMETROS: d: Es un Dominio al cual se le va a cambiar el atributo
                 expanded.
	      expanded: Valor para actualizar el atributo expanded.
  USA:
  RETORNA:
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
    d->expanded=expanded;
}

void expandDomain(Domain d)
/*---------------------------------------------------------------
  DESCRIPCION: Esta funcion expande el atributo info del parametro 
               d.

  PARAMETROS: d: Es un Dominio al cual se va expandir el atributo
                 info.
  USA:
  RETORNA:
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
    int i, j, n, m, mask, aux;

    mask=0;

    i=(d->min) / BYTE;
    j=(d->max) / BYTE;
    n=(d->min) % BYTE;
    m=(d->max) % BYTE;
    
    if(i==j && ((d->max)-(d->min))<BYTE) /* El min. y el max se encuentran
					    en un mismo byte */
      {
	mask=(int)(pow(2,(double)((BYTE-1)-n+1))) - (int)(pow(2,(double)((BYTE-1)-m)));
	(d->info)[i]=mask;
      }
    
    if((((d->max)-(d->min)) % BYTE) == 0 && i == j && (d->max != d->min))
      /* Min y max cubren totalmente 1 o mas bytes contiguos*/
      memset(&((d->info)[i]),255,j-i+1);
    
    if((j-i) == 1 && ((d->min) % BYTE) == 0) /* Min y max cubren totalmente 1 
						o mas bytes, y otro byte 
					        contiguo en su parte alta */
      {
	memset(&((d->info)[i]),255,j-i);
	aux = ((d->max) - m) % BYTE;
	mask=(int)(pow(2,(double)((BYTE-1)-aux+1))) - (int)(pow(2,(double)((BYTE-1)-m)));
	(d->info)[j] = mask;
      }
    if((d->max) % BYTE == (BYTE-1) && (j-i) == 1) /* Min y max cubren un byte 
						     en su parte alta, y 1 
						     o mas bytes contiguos en
						     su totalidad. */
      {
	mask=(int)(pow(2,(double)((BYTE-1)-n+1))) - 1;
	(d->info)[i] = mask;
	memset(&((d->info)[i+1]),255,j-i);
      }
    if((d->max)%BYTE != (BYTE-1) && (j-i) == 1 && ((d->min) % BYTE) != 0)
      /* Min y max cubren un byte en su parte alta y otro contiguo 
	 en su parte baja*/
      {
	mask=(int)(pow(2,(double)((BYTE-1)-n+1))) - 1;
	(d->info)[i] = mask;
	aux = ((d->max) - m) % BYTE;
	mask=(int)(pow(2,(double)((BYTE-1)-aux+1))) - (int)(pow(2,(double)((BYTE-1)-m)));
	d->info[j]=mask;
      }
    if(j-i > 1) /* Min y max cubren un byte en su parte alta, uno o mas
		   bytes contiguos y otro byte en su parte baja*/
      {
	mask=(int)(pow(2,(double)((BYTE-1)-n+1))) - 1;
	(d->info)[i] = mask;
	memset(&((d->info)[i+1]),255,j-i-1);
	aux = ((d->max) - m) % BYTE;
	mask=(int)(pow(2,(double)((BYTE-1)-aux+1))) - (int)(pow(2,(double)((BYTE-1)-m)));
	(d->info)[j] = mask;
      }
    d->expanded = TRUE;

}

int a_kDomain(Domain d)
/*---------------------------------------------------------------
  DESCRIPCION: Esta funcion obtiene el dominio unitario

  PARAMETROS: d: Es un Dominio
  USA:
  RETORNA: el valor del dominio como conjunto unitario
  PRE: d debe ser un dominio unitario
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int singleton;
  singleton= d->min;
  return singleton;
}

void diffDomain(Domain d1, Domain d2)
/*---------------------------------------------------------------
  DESCRIPCION: Esta funcion calcula la diferencia entre d1 y d2
  PARAMETROS: d1 y d2: son  representaciones de dominios
  USA:
  RETORNA:
  PRE:
  POS: d1\d2
  NOTAS:
  ---------------------------------------------------------------*/
{
  int i,j,min,max,bmin,bmax,newmin,n,newmax,start,end;
  Domain temp;
  
  if (isConsistentDomain(d1) && isConsistentDomain(d2))
    {
      if (equalsDomain(d1,d2))
	{/* La diferencia dio vacia, es decir una inconsistencia */
	  d1->min=MAXIN;
	  d1->max=MININ;
	  d1->expanded = FALSE;
	}
      else
	{
	  min=d1->min;
	  max=d1->max;
	  bmin=FALSE;
	  bmax=FALSE;
	  temp=Inicp1Domain(d2);
	  if(!(d1->expanded))
	    expandDomain(d1);
	  if(!getExpandedDomain(temp))
	    expandDomain(temp);
	  start=min/BYTE;
	  end=max/BYTE;


	  for(i=start;i<=end;i++)
	    {
	      (d1->info)[i]= ((d1->info)[i]) & (~((temp->info)[i]));
	      if((((d1->info)[i] | 0) != 0) && bmin==FALSE)
		{
		  for(j=0;j<BYTE;j++)
		    {
		      n=(i*8)+j;
		      if(getBitDomain(d1,n))
			{
			  newmin=n;
			  bmin=TRUE;
			  break;
			}
		    }
		}
	    }
	  for(i=end;i>=start && bmax==FALSE;i--)
	    {
	      if(((d1->info)[i] | 0) != 0)
		for(j=(BYTE-1);j>=0;j--)
		  {
		    n=(i*8)+j;
		    if(getBitDomain(d1,n))
		      {
			newmax=n;
			bmax=TRUE;
			break;
		      }
		  }
	    }
	  
	  if(newmin == min)
	    bmin=FALSE;
	  if(newmax == max)
	    bmax=FALSE;
	  d1->min=newmin;
	  d1->max=newmax;
	  
	  if(bmin && bmax) /* actualizar el tipo de poda */
	    d1->prune_type = PMINMAX;
	  else 
	    if(bmin)
	      d1->prune_type = PMIN;
	    else if(bmax)
	      d1->prune_type = PMAX;
	    else
	      d1->prune_type = PDOM;

	  freeDomain(temp);
	}
    }
  if(!isConsistentDomain(d1) && isConsistentDomain(d2))
    {/* La diferencia dio vacia, es decir una inconsistencia */
      d1->min=MAXIN;
      d1->max=MININ;
      d1->expanded = FALSE;
    }

}

int isDeterminatedDomain(Domain d)
/*---------------------------------------------------------------
  DESCRIPCION: Esta funcion decide si el dominio esta determinado
  PARAMETROS: d: es un dominio
  USA:
  RETORNA: TRUE | FALSE
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  return (d->min==d->max);
}

void unionDomain(Domain d1, Domain d2)
/*---------------------------------------------------------------
  DESCRIPCION: Esta funcion calcula la union de los dominios d1 y d2
  PARAMETROS: d1 y d2: son representaciones de dominios
  USA:
  RETORNA: 
  PRE:
  POS:d1= d1 U d2
  NOTAS:
  ---------------------------------------------------------------*/
{
  int min,max,k, bmin, bmax,i;
  Domain temp;

  min=d1->min;
  max=d1->max;
  temp=Inicp1Domain(d2);

  if(!isConsistentDomain(d1))
    {
      setInfoDomain(d1,d2->info);
      setMinimumDomain(d1,getMinimumDomain(d2));
      setMaximumDomain(d1,getMaximumDomain(d2));
      setPruneTypeDomain(d1,getPruneTypeDomain(d2));
      setExpandedDomain(d1,getExpandedDomain(d2));
    }
  if(isConsistentDomain(d1) && isConsistentDomain(d2))
    {
      if(!(d1->expanded))
	expandDomain(d1);
      if(!(temp->expanded))
	expandDomain(temp);
      d1->min=(d1->min)<=getMinimumDomain(d2)?(d1->min):getMinimumDomain(d2);
      d1->max=(d1->max)>=getMaximumDomain(d2)?(d1->max):getMaximumDomain(d2);
      if(d1->min == min)
	bmin=FALSE;
      if(d1->max == max)
	bmax=FALSE;
      
      if(bmin && bmax)//actualizar el tipo de poda
	d1->prune_type = PMINMAX;
      else if(bmin)
	d1->prune_type = PMIN;
      else if(bmax)
	d1->prune_type = PMAX;
      else
	d1->prune_type = PDOM;
      min=d1->min;
      max=d1->max;
      for(i=min;i<=max;i++)
	{
	  k= i / BYTE;
	  d1->info[k]=(d1->info[k]) | (temp->info[k]);
	}
    }
  freeDomain(temp);
}


void intersectionDomain(Domain d1, Domain d2)
/*---------------------------------------------------------------
  DESCRIPCION: Esta funcion calcula la intersección de los dominios
               d1 y d2
  PARAMETROS: d1 y d2: son representaciones de dominios
  USA:
  RETORNA: 
  PRE:
  POS:d1= d1 && d2
  NOTAS:
  ---------------------------------------------------------------*/
{
  int min,max,i,j, bmin, bmax,start,end,n;
  Domain temp, tempd1;

  min=d1->min;
  max=d1->max;
  temp=Inicp1Domain(d2);


  if(!isConsistentDomain(d2))
    {
      setInfoDomain(d1,d2->info);
      setMinimumDomain(d1,getMinimumDomain(d2));
      setMaximumDomain(d1,getMaximumDomain(d2));
      setPruneTypeDomain(d1,getPruneTypeDomain(d2));
      setExpandedDomain(d1,getExpandedDomain(d2));
    }
  if(isConsistentDomain(d1) && isConsistentDomain(d2))
    {
      if(!getExpandedDomain(d1) && !getExpandedDomain(d2))
	{
	  d1->min=(d1->min)>=getMinimumDomain(d2)?(d1->min):getMinimumDomain(d2);
	  d1->max=(d1->max)<=getMaximumDomain(d2)?(d1->max):getMaximumDomain(d2);
	  if(d1->min == min)
	    bmin=FALSE;
	  if(d1->max == max)
	    bmax=FALSE;

	  if(bmin && bmax)//actualizar el tipo de poda
	    d1->prune_type = PMINMAX;
	  else if(bmin)
	    d1->prune_type = PMIN;
	  else if(bmax)
	    d1->prune_type = PMAX;
	  else
	    d1->prune_type = PDOM;
	}
      else
	{
	 
	  if(!(d1->expanded))
	    expandDomain(d1);
	  if(!(temp->expanded))
	    expandDomain(temp);

	  tempd1=InicDomain();

	  bmin=FALSE;
	  bmax=FALSE;
	  start=min/BYTE;
	  end=max/BYTE;

	  tempd1->expanded = TRUE;

	  for(i=start;i<=end;i++)
	    {
	      tempd1->info[i]=(d1->info[i]) & (temp->info[i]);
	      if((((tempd1->info)[i] | 0) != 0) && bmin==FALSE)
		{
		  for(j=0;j<BYTE;j++)
		    {
		      n=(i*8)+j;
		      if(getBitDomain(tempd1,n))
			{
			  d1->min=n;
			  tempd1->min=n;
			  bmin=TRUE;
			  break;
			}
		    }
		}
	    }
	  if ( bmin == FALSE)
	    {
	      d1->min = MAXIN;
	      d1->max = MININ;
	      d1->expanded = FALSE;
	    }
	  else
	    {
	      for(i=end;i>=start && bmax==FALSE;i--)
		{
		  if(((tempd1->info)[i] | 0) != 0)
		    for(j=(BYTE-1);j>=0;j--)
		      {
			n=(i*8)+j;
			if(getBitDomain(tempd1,n))
			  {
			    d1->max=n;
			    tempd1->max=n;
			    bmax=TRUE;
			    break;
			  }
		      }
		}
	      setInfoDomain(d1,getInfoDomain(tempd1));
	      freeDomain(tempd1);
	    }
	 
	}
      if(d1->min == min)
	  bmin=FALSE;
      if(d1->max == max)
	  bmax=FALSE;
      
      if(bmin && bmax)//actualizar el tipo de poda
	  d1->prune_type = PMINMAX;
      else if(bmin)
	  d1->prune_type = PMIN;
      else if(bmax)
	  d1->prune_type = PMAX;
      else
	  d1->prune_type = PDOM;
    }
  freeDomain(temp);
}


void updateDomain(Domain d1, Domain d2)
/*---------------------------------------------------------------
  DESCRIPCION: Esta funcion calcula la intersección de los dominios
               d1 y d2
  PARAMETROS: d1 y d2: son representaciones de dominios
  USA:
  RETORNA: 
  PRE:
  POS:d1= d1 && d2
  NOTAS:
  ---------------------------------------------------------------*/
{
  intersectionDomain(d1,d2);
}

int isConsistentDomain(Domain d)
/*---------------------------------------------------------------
  DESCRIPCION: Decide si el dominio d es consistente
  PARAMETROS: d: es una representacion de dominio
  USA:
  RETORNA: TRUE | FALSE 
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  return ((d->max)>=(d->min));
}

int equalsDomain(Domain d1, Domain d2)
/*---------------------------------------------------------------
  DESCRIPCION: Esta funcion decide si los dominios d1 y d2 son
               iguales
  PARAMETROS: d1 y d2: son representaciones de dominios
  USA:
  RETORNA: TRUE | FALSE 
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/

{
  Domain copiad1,copiad2;

  if((d1->min)==(d2->min) && (d1->max)==(d2->max))
    {
      if(!(d1->expanded) && !(d2->expanded))
	  return TRUE;
      else
	{
	  copiad1=Inicp1Domain(d1);
	  copiad2=Inicp1Domain(d2);
	  if(!(copiad1->expanded))
	    expandDomain(copiad1);
	  if(!(copiad2->expanded))
	    expandDomain(copiad2);
	  if(strcmp(copiad1->info,copiad2->info)==0)
	    {
	      freeDomain(copiad1);
	      freeDomain(copiad2);
	      return TRUE;
	    }
	  else
	    {
	      freeDomain(copiad1);
	      freeDomain(copiad2);
	      return FALSE;
	    }
	}
    }
  else
    return FALSE;
}

void addIntDomain(Domain d,int m)
/*---------------------------------------------------------------
  DESCRIPCION: Esta funcion calcula el dominio resultante de sumar
                m a cada elemento del dominio d
  PARAMETROS: d:es una representacion de dominio
              m:el entero a sumar  
  USA:
  RETORNA: 
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int min,max,i,j,k,bmin,bmax,newnum;
  Domain temp;

  bmin=FALSE;
  bmax=FALSE;
  min=d->min;
  max=d->max;
  if(isConsistentDomain(d))
    {
      if(!(d->expanded))
	{
	  if((min+m)<=MAXIN)
	    {
	      d->min=MAXIN<(min+m)?MAXIN:(m+min);
	      d->max=MAXIN<(max+m)?MAXIN:(m+max);
	    }
	  else
	    {
	      d->min=MAXIN;
	      d->max=MININ;
	    }
	}
      else
	{     
	  if((min+m)<=MAXIN)
	    {
	      temp=InicDomain();
	      for(i=min;i<=max;i++)
		{
		  if(getBitDomain(d,i))
		    {
		      newnum=i+m;
		      if(newnum <= MAXIN)
			{
			  j=newnum / BYTE;
			  k=newnum % BYTE;
			  (temp->info)[j] = (temp->info)[j] | (int)(pow(2,(double)((BYTE-1)-k)));
			  if(bmin==FALSE)
			    {
			      d->min=newnum;
			      bmin=TRUE;
			    }
			  d->max=newnum;
			}
		    }
		}
	      setInfoDomain(d, temp->info);
	      freeDomain(temp);
	    }
	  else
	    {
	      d->min=MAXIN;
	      d->max=MININ;
	      d->expanded = FALSE;
	    }
	}
      if(d->min == min)
	bmin=FALSE;
      if(d->max == max)
	bmax=FALSE;
      
      if(bmin && bmax)//actualizar el tipo de poda
	d->prune_type = PMINMAX;
      else if(bmin)
	d->prune_type = PMIN;
      else if(bmax)
	d->prune_type = PMAX;
      else
	d->prune_type = PDOM;
    } 
}


void addDomain(Domain d1,Domain d2)
/*---------------------------------------------------------------
  DESCRIPCION: Esta funcion calcula el dominio resultante de sumar
               el dominio d2 al dominio d1
  PARAMETROS: d1:es una representacion de dominio
              d2:es una representacion de dominio
  USA:
  RETORNA: 
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int d1min,d1max,i,j,k,l,bmin,bmax,newnum,d2min,d2max;
  char temp[MAXINFO];
  Domain copyd1,copyd2;


  bmin=FALSE;
  bmax=FALSE;
  d1min=d1->min;
  d1max=d1->max;
  d2min=d2->min;
  d2max=d2->max;

  if(isConsistentDomain(d1))
    {
      if(isConsistentDomain(d2))
	{
	  
	  if(!(d1->expanded) && !(d2->expanded))
	    {
	      if((d1min+d2min)<=MAXIN)
		{
		  d1->min=(d1min)+(d2min);
		  d1->max=MAXIN<(d1max+d2max)?MAXIN:(d1max+d2max);
		}
	      else
		{
		  d1->min=MAXIN;
		  d1->max=MININ;
		}
	    }
	  else
	    {     
	      if((d1min+d2min)<=MAXIN)
		{
		  if(!(d1->expanded))
		    {
		      copyd1=Inicp1Domain(d1);
		      expandDomain(copyd1);
		      d1=InicDomain();
		    }
		  if(!(d2->expanded))
		    {	
		      copyd2=Inicp1Domain(d2);
		      expandDomain(copyd2);
		    }
		  
		  d1->min=(d1min+d2min);
		  d1->max=(d1max+d2max);
		  
		  for(i=d2min;i<=d2max;i++)
		    {
		      if(getBitDomain(copyd2,i))
			{
			  memset(temp, 0, MAXINFO);
			  for(l=d1min;l<=d1max;l++)
			    {
			      if(getBitDomain(copyd1,l))
				{
				  newnum=i+l;
				  if(newnum<=MAXIN)
				    {
				      j=newnum / BYTE;
				      k=newnum % BYTE;
				      temp[j] = temp[j] | (int)(pow(2,(double)((BYTE-1)-k)));
				      d1->min=(d1->min)<newnum?(d1->min):newnum;
				      d1->max=(d1->max)>newnum?(d1->max):newnum;
				    }
				}
			    }
			  for(k=0;k<MAXINFO;k++)
			    (d1->info)[k]=((d1->info)[k])| temp[k];
			}
		    }
		}
	      else
		{
		  d1->min = MAXIN;
		  d1->max = MININ;
		  d1->expanded = FALSE;
		}
	    }
	 
      if(d1->min == d1min)
	bmin=FALSE;
      if(d1->max == d1max)
	bmax=FALSE;
      
      if(bmin && bmax)//actualizar el tipo de poda
	d1->prune_type = PMINMAX;
      else if(bmin)
	d1->prune_type = PMIN;
      else if(bmax)
	d1->prune_type = PMAX;
      else
	d1->prune_type = PDOM;
	}
    }
}

void subIntDomain(Domain d,int m)
/*---------------------------------------------------------------
  DESCRIPCION: Esta funcion calcula el dominio resultante de 
               sustraer m a cada elemento del dominio d
  PARAMETROS: d:es una representacion de dominio
              m:el entero a sustraer  
  USA:
  RETORNA: 
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int min,max,i,j,k,bmin,bmax,newnum;
  Domain temp;


  bmin=FALSE;
  bmax=FALSE;
  min=d->min;
  max=d->max;
  if(isConsistentDomain(d))
    {
      if(!(d->expanded))
	{
	  if((max-m) >= MININ)
	    {
	      d->min=MININ>(min-m)?MININ:(min-m);
	      d->max=max-m;
	    }
	  else
	    {
	      d->min = MAXIN;
	      d->max = MININ;
	    }
	}
      else
	{  
	  if((max-m) >= MININ)
	    {
	      temp=InicDomain();
	      for(i=min;i<=max;i++)
		{
		  if(getBitDomain(d,i))
		    {
		      newnum=i-m;
		      if(newnum >= MININ)
			{
			  j=newnum / BYTE;
			  k=newnum % BYTE;
			  temp->info[j]=temp->info[j] | (int)(pow(2,(double)((BYTE-1)-k)));
			  if(bmin==FALSE)
			    {
			      d->min=newnum;
			      bmin=TRUE;
			    }
			  d->max=newnum;
			}
		    }
		}
	      setInfoDomain(d, temp->info);
	      freeDomain(temp);
	    }
	  else
	    {
	      d->min = MAXIN;
	      d->max = MININ;
	      d->expanded = FALSE;
	    }
	}
      if(d->min == min)
	bmin=FALSE;
      if(d->max == max)
	bmax=FALSE;
      
      if(bmin && bmax)//actualizar el tipo de poda
	d->prune_type = PMINMAX;
      else if(bmin)
	d->prune_type = PMIN;
      else if(bmax)
	d->prune_type = PMAX;
      else
	d->prune_type = PDOM;
    }
}

void substractDomain(Domain d1,Domain d2)
/*---------------------------------------------------------------
  DESCRIPCION: Esta funcion calcula el dominio resultante de restar
               el dominio d2 del dominio d1
  PARAMETROS: d1:es una representacion de dominio
              d2:es una representacion de dominio
  USA:
  RETORNA: 
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int d1min,d1max,i,j,k,l,bmin,bmax,newnum,d2min,d2max;
  Domain copyd1,copyd2;
  char temp[MAXINFO];

  bmin=FALSE;
  bmax=FALSE;
  d1min=d1->min;
  d1max=d1->max;
  d2min=d2->min;
  d2max=d2->max;
  if(isConsistentDomain(d1))
    {
      if(isConsistentDomain(d2))
	{
	  if(!(d1->expanded) && !(d2->expanded))
	    {
	      if((d1max-d2min) >= MININ)
		{
		  d1->min=(d1min-d2max)<MININ?MININ:(d1min-d2max);
		  d1->max=d1max-d2min;
		}
	      else
		{
		  d1->min = MAXIN;
		  d1->max = MININ;
		}
	    }
	  else
	    {   
	      if((d1max-d2min) >= MININ)
		{  
		  if(!(d1->expanded))
		    {
		      copyd1=Inicp1Domain(d1);
		      expandDomain(copyd1);
		      d1=InicDomain();
		    }
		  if(!(d2->expanded))
		    {	
		      copyd2=Inicp1Domain(d2);
		      expandDomain(copyd2);
		    }
		  
		  d1->min=d1min-d2max;
		  d1->max=d1max-d2min;
		  
		  for(i=d2min;i<=d2max;i++)
		    {
		      if(getBitDomain(copyd2,i))
			{
			  memset(temp, 0, MAXINFO);
			  for(l=d1min;l<=d1max;l++)
			    {
			      if(getBitDomain(copyd1,l))
				{
				  newnum=l-i;
				  if(newnum >= MININ)
				    {
				      j=newnum / BYTE;
				      k=newnum % BYTE;
				      temp[j] = temp[j] | (int)(pow(2,(double)((BYTE-1)-k)));
				      d1->min=(d1->min)<newnum?(d1->min):newnum;
				      d1->max=(d1->max)>newnum?(d1->max):newnum;
				    }
				}
			    }
			  for(k=0;k<MAXINFO;k++)
			    d1->info[k]=(d1->info[k])| temp[k];
			}
		    }
		}
	      else
		{
		  d1->min=MAXIN;
		  d1->max=MININ;
		  d1->expanded = FALSE;
		}
	    }
  
	  if(d1->min == d1min)
	    bmin=FALSE;
	  if(d1->max == d1max)
	    bmax=FALSE;
	  
	  if(bmin && bmax)//actualizar el tipo de poda
	    d1->prune_type = PMINMAX;
	  else if(bmin)
	    d1->prune_type = PMIN;
	  else if(bmax)
	    d1->prune_type = PMAX;
	  else
	    d1->prune_type = PDOM;
	}	
    }
}


void multiplicationDomain(Domain d,int m)
/*---------------------------------------------------------------
  DESCRIPCION: Esta funcion calcula el dominio resultante de
               multiplicar m a cada elemento del dominio d
  PARAMETROS: d:es una representacion de dominio
              m:el entero a multiplicar
  USA:
  RETORNA: 
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int min,max,i,j,k,bmin,bmax,newnum;
  Domain temp;


  bmin=FALSE;
  bmax=FALSE;
  min=d->min;
  max=d->max;

  if(isConsistentDomain(d))
    {
	if((max*m)<=MAXIN)
	    {
		if(!(d->expanded))
		    {
			
			d->min=min*m;
			d->max=max*m;
		    }
	    	else
		    {     
			temp=InicDomain();
			for(i=min;i<=max;i++)
			    {
				if(getBitDomain(d,i))
				    {
					newnum=i*m;
					j=newnum / BYTE;
					k=newnum % BYTE;
					(temp->info)[j] = (temp->info)[j] | (int)(pow(2,(double)((BYTE-1)-k)));
					if(bmin==FALSE)
					  {
					      d->min=newnum;
					      bmin=TRUE;
					  }
					d->max=newnum;
				    }
			    }
			setInfoDomain(d, temp->info);
			freeDomain(temp);
		    }
	    }
	else
	    {
		d->min=MAXIN;
		d->max=MININ;
		d->expanded=FALSE;
	    }
   
	if(d->min == min)
	    bmin=FALSE;
	if(d->max == max)
	    bmax=FALSE;
	
	if(bmin && bmax)//actualizar el tipo de poda
	    d->prune_type = PMINMAX;
	else if(bmin)
	    d->prune_type = PMIN;
	else if(bmax)
	    d->prune_type = PMAX;
	else
	    d->prune_type = PDOM;
    }
}


void divisionDomain(Domain d,int m)
/*---------------------------------------------------------------
  DESCRIPCION: Esta funcion calcula el dominio resultante de
               dividir entre m a cada elemento del dominio d
  PARAMETROS: d:es una representacion de dominio
              m:el dividendo
  USA:
  RETORNA: 
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int min,max,i,j,k,bmin,bmax,newnum;
  Domain temp;

  bmin=FALSE;
  bmax=FALSE;
  min=d->min;
  max=d->max;
  if(isConsistentDomain(d))
    {
	if((d->min/m)>=MININ)
	    {
		if(!(d->expanded))
		    {
			d->min=(d->min)/m;
			d->max=((d->max)/m)<MININ?MININ:((d->max)/m);
		    }
		else
		    {     
			temp=InicDomain();
			for(i=min;i<=max;i++)
			    {
				if(getBitDomain(d,i))
				    {
					newnum=i/m;
					if(newnum >= MININ)
					    {
						j=newnum / BYTE;
						k=newnum % BYTE;
						(temp->info)[j] = (temp->info)[j] | (int)(pow(2,(double)((BYTE-1)-k)));
						if(bmin==FALSE)
						    {
							d->min=newnum;
							bmin=TRUE;
						    }
						d->max=newnum;
					    }
				    }
			    }
			setInfoDomain(d, temp->info);
			freeDomain(temp);
		    }
	    }
	else
	    {
		d->min=MAXIN;
		d->max=MININ;
                d->expanded=FALSE;
	    }

	if(d->min == min)
	    bmin=FALSE;
	if(d->max == max)
	    bmax=FALSE;
	
	if(bmin && bmax)//actualizar el tipo de poda
	    d->prune_type = PMINMAX;
	else if(bmin)
	    d->prune_type = PMIN;
	else if(bmax)
	    d->prune_type = PMAX;
	else
	    d->prune_type = PDOM; 
    }
}


void modDomain(Domain d,int m)
/*---------------------------------------------------------------
  DESCRIPCION: Esta funcion calcula el dominio resultante de
               hacer mod de m a cada elemento del dominio d
  PARAMETROS: d:es una representacion de dominio
              m:el dividendo
  USA:
  RETORNA: 
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  int min,max,i,j,k,bmin,bmax,newnum;
  Domain temp;

  bmin=FALSE;
  bmax=FALSE;
  min=d->min;
  max=d->max;
  if(isConsistentDomain(d))
    {
	if((d->min%m)<=MAXIN)
	    {
		if(!(d->expanded))
		    {
			d->min=(d->min)%m;
			d->max=(d->max)%m;
		    }
		else
		    {     
			temp=InicDomain();
			for(i=min;i<=max;i++)
			    {
				if(getBitDomain(d,i))
				    {
					newnum=i%m;
					if(newnum >= MININ)
					    {
						j=newnum / BYTE;
						k=newnum % BYTE;
						(temp->info)[j] = (temp->info)[j] | (int)(pow(2,(double)((BYTE-1)-k)));
						if(bmin==FALSE)
						    {
							d->min=newnum;
							bmin=TRUE;
						    }
						d->max=newnum;
					    }
				    }
			    }
			setInfoDomain(d, temp->info);
			freeDomain(temp);
		    }
	    }
	else
	    {
		d->min=MAXIN;
		d->max=MININ;
	    }

	if(d->min == min)
	    bmin=FALSE;
	if(d->max == max)
	    bmax=FALSE;
	
	if(bmin && bmax)//actualizar el tipo de poda
	    d->prune_type = PMINMAX;
	else if(bmin)
	    d->prune_type = PMIN;
	else if(bmax)
	    d->prune_type = PMAX;
	else
	    d->prune_type = PDOM; 
    }
}

void freeDomain(Domain d)
/*---------------------------------------------------------------
  DESCRIPCION: Esta funcion libera la memoria utilizada por 
               una variable de tipo Domain.
  PARAMETROS: d:es una representacion de dominio
  USA:
  RETORNA: 
  PRE:
  POS:
  NOTAS:
  ---------------------------------------------------------------*/
{
  if(d != NULL)
    {
      free(d);
      d=NULL;
    }
}

#endif

/**** EOF ****/



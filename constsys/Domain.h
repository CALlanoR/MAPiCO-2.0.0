#ifndef _Domain_h_
#define _Domain_h_
/****************************************************************
* INTERFAZ MODULO: Domain.
* FECHA CREACION:  27-Mar-01
* REQUERIMIENTOS: stdio.h
*                 stdlib.h
*                 string.h
*                 math.h
*                 malloc.h
*                 PruneType.h
*
* AUTORES:         CATHERINE GARIA
*                  ALEJANDRA MARIA VASQUEZ
* MODIFICACIONES:
* AUTOR FECHA:
*
*****************************************************************/
/*--------------------------------------------------------------*
         Archivos de Interfaz de librerias estandar
 *--------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include <malloc.h>
#include "PruneType.h"
/*--------------------------------------------------------------*
         Declaracion  de Constantes y Macros publicos
 *--------------------------------------------------------------*/
#define MAXINFO 1332 //1251
#define BYTE 8
#define MININ 0
#define MAXIN 10655
#define TRUE 1
#define FALSE 0


/*--------------------------------------------------------------*
  Declaracion de struct's, union's, enum's y typedef's publicos
 *--------------------------------------------------------------*/
typedef struct
{
    char info[MAXINFO]; /* Informacion del Dominio */
    int min; /* Minimo del dominio */
    int max; /* Maximo del dominio */
    int prune_type; /* Tipo de poda con respecto a la ultima actualizacion del dominio */
    int expanded; /* Informacion si el dominio esta expandido o no */
}TDomain, *Domain;
/*--------------------------------------------------------------*
         Declaracion  de variables publicas
 *--------------------------------------------------------------*/
/*--------------------------------------------------------------*
         Prototipo de las funciones publicas
 *--------------------------------------------------------------*/
Domain InicDomain(void);
Domain InicpDomain(int, int);
Domain Inicp1Domain(Domain);
char * getInfoDomain(Domain);
void ImprimirDomain(Domain);
int getMinimumDomain(Domain);
int getMaximumDomain(Domain);
int getExpandedDomain(Domain);
int getPruneTypeDomain(Domain);
int getBitDomain(Domain, int);
void setMinimumDomain(Domain, int);
void setMaximumDomain(Domain, int);
void setPruneTypeDomain(Domain, int);
void setInfoDomain(Domain, char []);
void setExpandedDomain(Domain, int);
void expandDomain(Domain);
int a_kDomain(Domain);
void diffDomain(Domain,Domain);
int isDeterminatedDomain(Domain);
void unionDomain(Domain,Domain);
void intersectionDomain(Domain,Domain);
void updateDomain(Domain , Domain);
int isConsistentDomain(Domain);
int equalsDomain(Domain, Domain);
void addIntDomain(Domain,int);
void addDomain(Domain,Domain);
void subIntDomain(Domain,int);
void substractDomain(Domain,Domain);
void multiplicationDomain(Domain,int);
void divisionDomain(Domain,int);
void modDomain(Domain,int);
void freeDomain(Domain);
#endif


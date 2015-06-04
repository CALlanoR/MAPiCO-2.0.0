// StoreMA.h
// Copyright (c) 2002,  Alba Sarasti. <asarasti@puj.edu.co>, 
//                      Carlos A. Llano R. <callanor@puj.edu.co>
// Pontificia Universidad Javeriana, Colombia(Santiago de Cali)

// This is free software.  You are permitted to use,
// redistribute, and modify it as specified in the file "COPYING".

#include <stdio.h>
#include <stdlib.h>
#include "FrameConst.h"
#include "CS.h"

//Declaracion  de Constantes y Macros publicos
#define SUCCESS_MA SUCCESS
#define FAIL_MA FAIL
#define ASK_MA ASK
#define TELL_MA TELL
#define ENTAILED_MA ENTAILED
#define UNENTAILED_MA UNENTAILED
#define SUSPENDED_MA SUSPENDED
#define UNKNOWN_MA UNKNOWN
#define PREDICADOMA PREDICADO
#define FUNCIONMA FUNCION
#define VARIABLEMA VARIABLE
#define CONSTANTEMA CONSTANTE
#define StoreOK      0
#define StoreERR    1

/*! \typedef FrameConst Tipo para la interfaz con el FrameConst del Store Aritmetico
*/
typedef FrameConst FrameConstMA;

/*! \struct str_StoreMA
    \brief Estructura para almacenar el Store Aritmetico
*/
struct str_StoreMA
{
   Store s;                              //Store de Restricciones
   Indexicals i;                       //Indexicals 
   Stamp *t;                           //Stamp
   int *indextemp;                  //IndexTemp
   int Response;                   //Codigo de respuesta de la accion
   char *Error;                      //String con el mensaje de error
   int inicializado;                  //Indica si el store ha sido inicializado   
};

/*! \typedef FrameConst Tipo para la interfaz con el FrameConst del Store Aritmetico
*/
typedef struct str_StoreMA *StoreMA;

/*! \fn StoreMA inicStoreMA(void)
    \brief Inicializa el store aritmetico
    \return La estructura que contiene el store 
*/
StoreMA inicStoreMA(void);

/*! \fn StoreMA tellMA(StoreMA sm, FrameConstMA fc)
    \brief Funci'on que realiza un tell sobre el store
    \param sm El Store aritmetico
    \param fc Restricci'on que se ejecutara en el store
    \return La estructura que contiene el store 
*/
StoreMA tellMA(StoreMA sm, FrameConstMA fc);

/*! \fn StoreMA askMA(StoreMA sm, FrameConstMA fc)
    \brief Funci'on que realiza un ask sobre el store
    \param sm El Store aritmetico
    \param fc Restricci'on que se ejecutara en el store
    \return La estructura que contiene el store 
*/
StoreMA askMA(StoreMA sm, FrameConstMA fc);

/*! \fn FrameConstMA InicFrameConstMA(int, int)
    \brief Funci'on que inicializa una restricci'on
    \param tipo Tipo de restricci'on
    \param valor Valor de la restricci'on
    \return La restricci'on inicializada
*/
FrameConstMA InicFrameConstMA(int tipo, int valor);

/*! \fn FrameConstMA InicpFrameConstMA(FrameConstMA fc)
    \brief Funci'on que inicializa una restricci'on a partir de otra
    \param fc Restricci'on de entrada
    \return La restricci'on inicializada
*/
FrameConstMA InicpFrameConstMA(FrameConstMA fc);

/*! \fn FrameConstMA getLefSonFrameConstMA(FrameConstMA)
    \brief Funci'on que retorna el hijo izquierdo de una restricci'on
    \param fc Restricci'on padre
    \return Restricci'on izquierda
*/
FrameConstMA getLefSonFrameConstMA(FrameConstMA fc);

/*! \fn FrameConstMA getRigSonFrameConstMA(FrameConstMA)
    \brief Funci'on que retorna el hijo derecho de una restricci'on
    \param fc Restricci'on padre
    \return Restricci'on derecha
*/
FrameConstMA getRigSonFrameConstMA(FrameConstMA fc);

/*! \fn void setLefSonFrameConstMA(FrameConstMA, FrameConstMA)
    \brief Funci'on que asigna una restricci'on al hijo izquierdo de otra restricci'on
    \param fcFather Restricci'on padre
    \param fcSon Nueva restricci'on 
*/
void setLefSonFrameConstMA(FrameConstMA fcFather , FrameConstMA fcSon);

/*! \fn void setRigSonFrameConstMA(FrameConstMA, FrameConstMA)
    \brief Funci'on que asigna una restricci'on al hijo derecho de otra restricci'on
    \param fcFather Restricci'on padre
    \param fcSon Nueva restricci'on 
*/
void setRigSonFrameConstMA(FrameConstMA fcFather, FrameConstMA fcSon);

/*! \fn void DestruirFrameConstMA(FrameConstMA)
    \brief Funci'on que libera la memoria reservada por una restricci'on
    \param fc Restricci'on que sera liberada
*/
void DestruirFrameConstMA(FrameConstMA fc);

/*! \fn void ImprimirFrameConstMA(FrameConstMA)
    \brief Funci'on que imprime el contenido de una restricci'on
    \param fc Restricci'on a imprimir
*/
void ImprimirFrameConstMA(FrameConstMA fc);

/*! \fn int getResponseMA(StoreMA sm)
    \brief Funci'on que retorna el status de una operaci'on sobre el store
    \param sm Estructura que contiene el Store
    \return Codigo que indica el estado
*/
int getResponseMA(StoreMA sm);

/*! \fn int getInicializadoMA(StoreMA sm)
    \brief Funci'on que indica si el store se encuentra inicializado
    \param sm Estructura que contiene el Store
    \return Codigo indicando el estado del store
*/
int getInicializadoMA(StoreMA sm);

/*! \fn void freeStoreMA(StoreMA sm)
    \brief Funci'on que libera la memoria reservada por el Store
    \param sm Estructura que contiene el Store
*/
void freeStoreMA(StoreMA sm);

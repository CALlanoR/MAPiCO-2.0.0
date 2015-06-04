// Generic Structs.h
// Copyright (c) 2002,  Alba Sarasti. <asarasti@puj.edu.co>, 
//                      Carlos A. Llano R. <callanor@puj.edu.co>
// Pontificia Universidad Javeriana, Colombia(Santiago de Cali)

// This is free software.  You are permitted to use,
// redistribute, and modify it as specified in the file "COPYING".

#include "NodeList.h"
#include "NodeArg.h"
#include "List.h"
#include "StoreMA.h"
#include "Auxiliar.h"
#include "ObjectEval.h"

/*! \file Structs.h
    \brief Libreria de estructuras de MAPiCO
*/

/*! \struct NodeList
    \brief Estructura que define una lista doblemente encadenada
*/
struct NodeList
{
   void *Data;
   DEFINE_LINK(NodeList,NodeList);
};

/*! \typedef NodeList Tipo para definir la lista doblemente encadenada
*/
typedef struct NodeList *NodeList;

/*! \def DEFINE_LIST(List,NodeList)
    \brief Define una lista doblemente encadenada con apuntador al inicio y final de la misma
*/
DEFINE_LIST(List,NodeList);

/*! \typedef List Tipo para definir la lista doblemente encadenada con apuntador al inicio y final de la misma
*/
typedef struct List *List;

/*! \struct NodeArg
    \brief Estructura que define una lista de argumentos doblemente encadenada
*/
struct NodeArg
{
   void *Data;
   int Type;    //Type = { VARIABLE, METODO }
   DEFINE_LINK_ARG(NodeArg,NodeArg);
};

/*! \typedef NodeArg Tipo para definir la lista de argumentos doblemente encadenada
*/
typedef struct NodeArg *NodeArg;

/*! \struct Aux
    \brief Estructura del Apuntador de Argumentos y Restricciones
*/
struct Aux
{
   NodeArg nArg;
   FrameConstMA Fconst;
   short Tipo; // Tipo = { -1[Sin Tipo], 0[NodeArg], 1[FrameConst] }
};

/*! \typedef Aux Tipo para definir el tipo para los argumentos y restricciones
*/
typedef struct Aux *Auxiliar;

/*! \struct Aux
    \brief Estructura del Registro POA
*/
struct ObjEval
{
   int *PCS;
   int NumObjects;
   int Longitud;
};

/*! \typedef ObjEval Tipo para definir el tipo del registro POA
*/
typedef struct ObjEval *ObjectEval;

/*! \struct Var
    \brief Estructura de las variables de MAPiCO
*/
struct Var
{
   int IdVariable;
   int IdProceso;
};

/*! \typedef Var Tipo para definir una variable de MAPiCO
*/
typedef struct Var *Variable;



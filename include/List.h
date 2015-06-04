// Generic list macros
// Copyright (c) 2002,  Alba Sarasti. <asarasti@puj.edu.co>, 
//                      Carlos A. Llano R. <callanor@puj.edu.co>
// Pontificia Universidad Javeriana, Colombia(Santiago de Cali)

// This is free software.  You are permitted to use,
// redistribute, and modify it as specified in the file "COPYING".

#include "NodeList.h"

/*! \file List.h
    \brief Libreria de listas genericas con apuntador a la cabecera y la cola
*/

#ifndef LIST_H
#define LIST_H

/*! \def DEFINE_LIST( listTypeName, nodeTypeName )
    \brief Define una lista con cabecera y cola
*/
#define DEFINE_LIST( listTypeName, nodeTypeName )   \
struct listTypeName {                               \
    int Elements;                                   \
    struct nodeTypeName *head, *tail;               \
}

/*! \def LIST(NewList)
    \brief Crea un nueva lista
*/
#define LIST(NewList)                                     \
do {                                                      \
    NewList = (struct List *)malloc(sizeof(struct List)); \
    NewList->Elements=0;                                  \
    NewList->head = NewList->tail = 0;                    \
} while ( 0 )

/*! \def LENGTH_LIST(List)
    \brief Retorna la longitud de la lista. Complejidad: O(1)
*/
#define LENGTH_LIST(List) ( (List)->Elements )

/*! \def INSERT_AT_HEAD( List, Object )
    \brief Inserta un dato al inicio de la lista. Complejidad: O(1)
*/
#define INSERT_AT_HEAD( List, Object )       \
do {                                         \
    NodeList NewNode;                        \
    NODELIST(NewNode,Object);                \
    if ( List->head == 0 ) {                 \
       List->head = List->tail = NewNode;    \
    }                                        \
    else {                                   \
       List->head->prev##NodeList = NewNode; \
       NewNode->next##NodeList = List->head; \
       List->head = NewNode;                 \
    }                                        \
    List->Elements++;                        \
} while ( 0 )

/*! \def INSERT_AT_END( List, Object )
    \brief Inserta un nuevo dato al final de la lista. Complejidad: O(1)
*/
#define INSERT_AT_END( List, Object )             \
do {                                              \
    NodeList NewNode;                             \
    NODELIST(NewNode,Object);                     \
    if( List->tail == 0 && List->head == 0) {     \
       List->head = List->tail = NewNode;         \
       List->Elements = 1;                        \
    }                                             \
    else {                                        \
      List->tail->next##NodeList = NewNode;       \
      NewNode->prev##NodeList = List->tail;       \
      List->tail = List->tail->next##NodeList;    \
      List->Elements++;                           \
    }                                             \
} while ( 0 )

/*! \def FIRST_NODE(List)
    \brief Devuelve la referencia del inicio de la lista. Complejidad: O(1)
*/
#define FIRST_NODE(List) ( List->head )

/*! \def END_NODE(List) 
    \brief Devuelve la referencia del final de la lista. Complejidad: O(1)
*/
#define END_NODE(List) ( List->tail )

/*! \def ADD_AT_END(List,ListAppend) 
    \brief Agrega una lista al final de otra lista. Complejidad: O(1)
*/
#define ADD_AT_END(List,ListAppend)                             \
do {                                                            \
   NodeList NodeFirst = INIT_NODELIST(NodeFirst);               \
   NodeList NodeEnd = INIT_NODELIST(NodeEnd);                   \
   if(List->Elements==0) {                                      \
     List->head = FIRST_NODE(ListAppend);                       \
  }                                                             \
   else{                                                        \
     NodeEnd = END_NODE(List);                                  \
     NodeFirst = FIRST_NODE(ListAppend);                        \
     SETNEXT(NodeEnd,NodeFirst);                                \
   }                                                            \
   List->tail = END_NODE(ListAppend);                           \
   List->Elements = List->Elements +  LENGTH_LIST(ListAppend);  \
} while( 0 )

/*! \def INSERT_AT(List,index,Object)
    \brief Inserta un nuevo dato en la lista en un indice especifico. Complejidad: O(N)
*/
#define INSERT_AT(List,index,Object)                        \
do {                                                        \
   if( List->Elements < index ){                            \
     INSERT_AT_END(List,Object);                            \
   }                                                        \
   else{                                                    \
     if(index == 0){                                        \
        INSERT_AT_HEAD(List,Object);                        \
     }                                                      \
     else{                                                  \
        if(List->Elements == index)                         \
           INSERT_AT_END(List,Object);                      \
        else{                                               \
           NodeList NodeTemp1 = INIT_NODELIST(NodeTemp1);   \
           NodeList NodeTemp2 = INIT_NODELIST(NodeTemp2);   \
           NodeList NewNode;                                \
           NodeTemp1 = FIRST_NODE(List);                    \
           NodeTemp2 = GETNEXT(NodeTemp1);                  \
           for(int i=1; i<index;i++){                       \
              NodeTemp1 = NodeTemp2;                        \
              NodeTemp2 = GETNEXT(NodeTemp1);               \
           }                                                \
           NODELIST_CONTINUATION(NewNode,Object,NodeTemp2); \
           SETNEXT(NodeTemp1,NewNode);                      \
           List->Elements++;                                \
        }                                                   \
      }                                                     \
   }                                                        \
} while( 0 )

/*! \def DEL_FIRST_NODE(List)
    \brief Elimina el primer dato de la lista. Complejidad: O(1)
*/
#define DEL_FIRST_NODE(List)                               \
do {                                                       \
      if( List->Elements > 0 ) {                           \
         NodeList NodeDel = INIT_NODELIST(NodeDel);        \
         NodeDel = FIRST_NODE(List);                       \
         if(List->head==List->tail) {                      \
            NodeDel->next##NodeList = 0;                   \
            NodeDel->prev##NodeList = 0;                   \
            List->head = List->tail = 0;                   \
            List->Elements = 0;                            \
         }                                                 \
         else {                                            \
            List->head = NodeDel->next##NodeList;          \
            NodeDel->next##NodeList->prev##NodeList = 0;   \
            NodeDel->next##NodeList = 0;                   \
            NodeDel->prev##NodeList = 0;                   \
            List->Elements--;                              \
         }                                                 \
      }                                                    \
} while( 0 )

/*! \def FREE_LIST(List)
    \brief Libera una lista: O(1)
*/
#define FREE_LIST(List)        \
do {                           \
   List->head = 0;             \
   List->tail = 0;             \
   List->Elements = 0;         \
} while( 0 )

/*! \def DEL_AT(List,index)
    \brief Elimina un dato de la lista de un indice especifico. Complejidad: O(N)
*/
#define DEL_AT(List,index)                                         \
do {                                                               \
      NodeList NodeDel = INIT_NODELIST(NodeDel);                   \
      if( List->Elements > index ) {                               \
         if(List->head!=List->tail) {                              \
            NodeDel = FIRST_NODE(List);                            \
            for(int i=1; i<index;i++) {                            \
               NodeDel = NodeDel->next##NodeList;                  \
            }                                                      \
            if(NodeDel->prev##NodeList == 0) {                     \
              List->head = NodeDel->next##NodeList;                \
              if(List->Elements!=1) {                              \
                 NodeDel->next##NodeList->prev##NodeList = 0;      \
              }                                                    \
              NodeDel->next##NodeList = 0;                         \
            }                                                      \
            else {                                                 \
               NodeList NodeAnt = INIT_NODELIST(NodeAnt);          \
               NodeList NodeNext = INIT_NODELIST(NodeNext);        \
               NodeAnt = NodeDel->prev##NodeList;                  \
               NodeNext = NodeDel->next##NodeList;                 \
               NodeAnt->next##NodeList = NodeDel->next##NodeList;  \
               NodeNext->prev##NodeList = NodeDel->prev##NodeList; \
               NodeDel->next##NodeList = 0;                        \
               NodeDel->prev##NodeList = 0;                        \
            }                                                      \
            List->Elements--;                                      \
         }                                                         \
         else                                                      \
         {                                                         \
           NodeDel = FIRST_NODE(List);                             \
           List->head = List->tail = 0;                            \
           List->Elements = 0;                                     \
         }                                                         \
      }                                                            \
} while( 0 )

/*! \def GET_AT(List,index,Object,Tipo)
    \brief Devuelve un dato de la lista de un indice especifico. Complejidad: O(N)
*/
#define GET_AT(List,index,Object)                  \
do {                                               \
   if(List->Elements <= index)                     \
      Object = NULL;                               \
   else{                                           \
      NodeList NodeTemp = INIT_NODELIST(NodeTemp); \
      NodeTemp = FIRST_NODE(List);                 \
      for(int indice=0;indice<index;indice++)      \
          NodeTemp = GETNEXT(NodeTemp);            \
      Object = GETDATA(NodeTemp);                  \
   }                                               \
} while( 0 )

/*! \def SET_AT(List,index,Object)
    \brief Asigna un dato a la lista en un indice especifico. Complejidad: O(N)
*/
#define SET_AT(List,index,Object)                     \
do {                                                  \
   if(index == 0){                                    \
      SETDATA(FIRST_NODE(List),Object);               \
   }                                                  \
   else{                                              \
      if(List->Elements == index)                     \
         SETDATA(END_NODE(List),Object);              \
      else{                                           \
         NodeList NodeTemp = INIT_NODELIST(NodeTemp); \
         NodeTemp = FIRST_NODE(List);                 \
         for(int i=0; i<index;i++)                    \
            NodeTemp = GETNEXT(NodeTemp);             \
            SETDATA(NodeTemp,Object);                 \
      }                                               \
   }                                                  \
} while( 0 )

/*! \def FREE_MEMORY_LIST(List) 
    \brief Libera una Lista. Complejidad: O(N)
*/
#define FREE_MEMORY_LIST(List)                  \
do {                                            \
   if( List->Elements == 0 )                    \
     free(List);                                \
   else                                         \
     FREE_MEMORY_NODELIST(FIRST_NODE(List));    \
   free(List);                                  \
} while( 0 )

/*! \def PRINT_LIST(List) 
    \brief Imprime una Lista. Complejidad: O(N)
*/
#define PRINT_LIST(List)                        \
do {                                            \
   NodeList NodeTemp = INIT_NODELIST(NodeTemp); \
   NodeTemp = FIRST_NODE(List);                 \
   int *datoPrint;                              \
   printf("List->Elements [%d]\n", List->Elements); \
   for(int i=0;i<List->Elements;i++){           \
       datoPrint = GETDATA(NodeTemp);           \
       printf("Dato: [%d]\n",*datoPrint);       \
       NodeTemp = NodeTemp->next##NodeList;        \
   }                                            \
   datoPrint = NULL;                            \
   NodeTemp = NULL;                             \
} while( 0 )

#endif // LIST_H

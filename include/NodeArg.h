// Generic list arg macros
// Copyright (c) 2002,  Alba Sarasti. <asarasti@puj.edu.co>, 
//                      Carlos A. Llano R. <callanor@puj.edu.co>
// Pontificia Universidad Javeriana, Colombia(Santiago de Cali)

// This is free software.  You are permitted to use,
// redistribute, and modify it as specified in the file "COPYING".


#ifndef NODEARG_H
#define NODEARG_H

/*! \def DEFINE_LINK_ARG( listTypeName, nodeTypeName )
    \brief Define los apuntadores siguiente y atras de una lista. Complejidad: O(1)
*/
#define DEFINE_LINK_ARG( listTypeName, nodeTypeName ) \
    struct nodeTypeName * prev##listTypeName, * next##listTypeName

/*! \def NODEARG(Node, Objeto, TypeObject)
    \brief Constructor de un Nodo. Complejidad: O(1)
*/
#define NODEARG(Node, Objeto, TypeObject)             \
do{                                                 \
   Node = (struct NodeArg *)malloc(sizeof(struct NodeArg));         \
   Node->next##NodeArg = Node->prev##NodeArg = 0;   \
   Node->Data = Objeto;                             \
   Node->Type = TypeObject;                         \
}while( 0 )         

//Construye un nodo con continuacion
/*! \def NODE_CONTINUATION_ARG(Node,Objeto,TypeObject,Continuation)
    \brief Construye un nodo agregando otro nodo. Complejidad: O(1)
*/
#define NODE_CONTINUATION_ARG(Node,Objeto,TypeObject,Continuation) \
do{                                                                \
   Node = (struct NodeArg *)malloc(sizeof(struct NodeArg));                        \
   Node->Data = Objeto;                                            \
   Node->Type = TypeObject;                                        \
   Node->next##NodeArg = Continuation;                             \
   Continuation->prev##NodeArg = Node;                             \
}while( 0 )                                                     

/*! \def SETNEXT_ARG(Node, Continuation)
    \brief Define la continuacion de un nodo. Complejidad: O(1)
*/
#define SETNEXT_ARG(Node, Continuation)        \
do{                                           \
 if(Continuation==NULL)                       \
    Continuation = Node;                      \
 else{                                        \
    Continuation->prev##NodeArg = Node;       \
    Node->next##NodeArg = Continuation;       \
 }                                            \
}while( 0 )

/*! \def SETDATA_ARG(Node,Objeto,TypeObject)
    \brief Define la informacion de un nodo. Complejidad: O(1)
*/
#define SETDATA_ARG(Node,Objeto,TypeObject)   \
do{                                           \
   Node->Data = Objeto;                       \
   Node->Type = TypeObject;                   \
}while( 0 )

/*! \def GETNEXT_ARG(Node, Next)
    \brief Retorna el siguiente nodo. Complejidad: O(1)
*/
#define GETNEXT_ARG(Node, Next)               \
do{                                                                     \
   Next = Node->next##NodeArg;                      \
   Node->next##NodeArg = 0;                           \
   Node->prev##NodeArg = 0;                          \
   free(Node);                                                     \
}while(0)         

/*! \def ISVALIDNEXT_ARG(Node)
    \brief Valida si hay nodo siguiente. Complejidad: O(1)
*/
#define ISVALIDNEXT_ARG(Node) Node->next##NodeArg
                       
/*! \def GETDATA_ARG(Node)
    \brief Devuelve la informacion de un nodo. Complejidad: O(1)
*/
#define GETDATA_ARG(Node)  Node->Data

/*! \def GETTYPE_ARG(Node)
    \brief Devuelve el tipo de un nodo. Complejidad: O(1)
*/
#define GETTYPE_ARG(Node)  Node->Type

/*! \def GETDATAAT_ARG(Node,index,Respuesta)
    \brief Devuelve la informacion de un nodo dado. Complejidad: O(N)
*/
#define GETDATAAT_ARG(Node,index,Respuesta) \
do{                                           \
  NodeArg temp;                              \
  temp = Node;                              \
  for(int i=1;i<index;i++){                  \
       temp = temp->next##NodeArg;       \
  }                                           \
  Respuesta = temp->Data;                     \
}while( 0 )

/*! \def LENGTH_ARG(Node, Respuesta)
    \brief Devuelve la longitud de una lista. Complejidad: O(N)
*/
#define LENGTH_ARG(Node, Respuesta)     \
do{                                    \
  NodeArg temp;                       \
  temp = Node;                         \
  Respuesta=0;                         \
  while(temp!=0){                   \
    temp = GETNEXT_ARG(temp);        \
    Respuesta++;                       \
  }                                    \
}while( 0 )

/*! \def FREE_MEMORY_NODE_ARG(Node)
    \brief Libera la memoria de la lista. Complejidad: O(N)
*/
#define FREE_MEMORY_NODE_ARG(Node)  \
do{                                                                     \
  NodeArg temp;                                                \
  while(Node!=NULL){                                        \
    temp = Node;                                                 \
    Node = Node->next##NodeArg;                    \
    temp->next##NodeArg = 0;                           \
    temp->prev##NodeArg = 0;                           \
    free(temp->Data);                                           \
    free(temp);                                                      \
    temp = NULL;                                                 \
  }                                                                        \
}while( 0 )       

/*! \def PRINT_NODE_ARG(Node)
    \brief Imprime la lista. Complejidad: O(N)
*/
#define PRINT_NODE_ARG(Node)                    \
do {                                            \
   NodeArg NodeTemp;            \
   NodeTemp = Node;                             \
   int *dato;                                   \
   while(NodeTemp!=0){                      \
       dato = GETDATA_ARG(NodeTemp);          \
       printf("Dato: [%d]\n",*dato);            \
       NodeTemp = NodeTemp->next##NodeArg;  \
   }                                            \
} while( 0 )   


#endif // NODEARG_H

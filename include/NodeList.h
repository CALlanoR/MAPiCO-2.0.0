// Generic list macros
// Copyright (c) 2002,  Alba Sarasti. <asarasti@puj.edu.co>, 
//                      Carlos A. Llano R. <callanor@puj.edu.co>
// Pontificia Universidad Javeriana, Colombia(Santiago de Cali)

// This is free software.  You are permitted to use,
// redistribute, and modify it as specified in the file "COPYING".

/*! \file NodeList.h
    \brief Libreria de listas genericas
    
    La libreria ofrece funciones para leer el archivo en bytes
*/

#ifndef NODELIST_H
#define NODELIST_H

/*! \def DEFINE_LINK( listTypeName, nodeTypeName )
    \brief Define los apuntadores siguiente y atras de una lista. Complejidad: O(1)
*/
#define DEFINE_LINK( listTypeName, nodeTypeName ) \
    struct nodeTypeName * prev##listTypeName, * next##listTypeName

/*! \def NODELIST(Node,Object)
    \brief Constructor de un Nodo. Complejidad: O(1)
*/
#define NODELIST(Node,Object)                                  \
do{                                                            \
   Node = (struct NodeList *)malloc(sizeof(struct NodeList));  \
   Node->next##NodeList = Node->prev##NodeList = 0;            \
   Node->Data = Object;                                        \
}while( 0 )    

/*! \def INIT_NODELIST(Node,Object)
    \brief Asigna memoria a un Nodo. Complejidad: O(1)
*/
#define INIT_NODELIST(Node) ( (struct NodeList *)malloc(sizeof(struct NodeList)) ); 

/*! \def NODELIST_CONTINUATION(Node,Object,Continuation)
    \brief Construye un nodo agregando otro nodo. Complejidad: O(1)
*/
#define NODELIST_CONTINUATION(Node, Object, Continuation)       \
do{                                                             \
   Node = (struct NodeList *)malloc(sizeof(struct NodeList));   \
   Node->Data = Object;                                         \
   Node->next##NodeList = Continuation;                         \
   Continuation->prev##NodeList = Node;                         \
}while( 0 )                                                     

/*! \def SETNEXT(Node,Continuation)
    \brief Define la continuacion de un nodo. Complejidad: O(1)
*/
#define SETNEXT(Node,Continuation)             \
do{                                            \
 if(Continuation==NULL)                        \
    Continuation = Node;                       \
 else{                                         \
    Continuation->prev##NodeList = Node;       \
    Node->next##NodeList = Continuation;       \
 }                                             \
}while( 0 )

/*! \def SETDATA(Node,Object)
    \brief Define la informacion de un nodo. Complejidad: O(1)
*/
#define SETDATA(Node,Object)            \
do{                                     \
   Node->Data = Object;                 \
}while( 0 )

/*! \def GETNEXT(Node)
    \brief Retorna el siguiente nodo. Complejidad: O(1)
*/
#define GETNEXT(Node) ( Node->next##NodeList ) 

/*! \def GETPREV(Node)
    \brief Retorna el anterior nodo. Complejidad: O(1)
*/
#define GETPREV(Node) ( Node->prev##NodeList ) 

/*! \def GETDATA(Node)
    \brief Retorna la informacion de un nodo. Complejidad: O(1)
*/
#define GETDATA(Node)  Node->Data

/*! \def GETDATAAT(Node,index,Respuesta)
    \brief Retorna la informacion de un nodo dado. Complejidad: O(N)
*/
#define GETDATAAT(Node,index,Respuesta)   \
do{                                       \
  NodeList temp = INIT_NODELIST(temp);    \
  temp = Node;                            \
  for(int i=0;i<index;i++){               \
       temp = temp->next##NodeList;       \
  }                                       \
  Respuesta = temp->Data;                 \
}while( 0 )

/*! \def LENGTH(Node,Respuesta)
    \brief Devuelve la longitud de una lista. Complejidad: O(N)
*/
#define LENGTH(Node,Respuesta)         \
do{                                    \
  NodeList temp = INIT_NODELIST(temp); \
  temp = Node;                         \
  Respuesta=0;                         \
  while(temp!=NULL){                   \
    temp = temp->next##NodeList;       \
    Respuesta++;                       \
  }                                    \
}while( 0 )
  
/*! \def FREE_MEMORY_NODELIST(Node)
    \brief Libera la memoria de la lista. Complejidad: O(N)
*/
#define FREE_MEMORY_NODELIST(Node)     \
do{                                    \
  NodeList temp = INIT_NODELIST(temp); \
  while(Node!=NULL){                   \
    temp = Node;                       \
    Node = Node->next##NodeList;       \
    free(temp->Data);                  \
    free(temp);                        \
  }                                    \
}while( 0 )

/*! \def FREE_NODE(Node)
    \brief Libera la memoria de un nodo. Complejidad: O(1)
*/
#define FREE_NODE(Node)           \
do{                               \
  free(Node->Data);               \
  Node->Data = NULL;              \
  free(Node);                     \
  Node = NULL;                    \
}while( 0 )      

/*! \def PRINT_NODELIST(Node)
    \brief Imprime la lista. Complejidad: O(N)
*/
#define PRINT_NODELIST(Node)                   \
do {                                           \
  NodeList NodeTemp = INIT_NODELIST(NodeTemp); \
   NodeTemp = Node;                            \
   int *dato;                                  \
   while(NodeTemp!=0){                         \
       dato = GETDATA(NodeTemp);               \
       printf("[%d]<-",*dato);                 \
       NodeTemp = GETNEXT(NodeTemp);           \
	   dato = NULL;                            \
   }                                           \
   printf("\n");                               \
   NodeTemp = NULL;                            \
} while( 0 )   

#endif // NODELIST_H


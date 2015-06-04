// Generic BinaryTree.h
// Copyright (c) 2002,  Alba Sarasti. <asarasti@puj.edu.co>, 
//                      Carlos A. Llano R. <callanor@puj.edu.co>
// Pontificia Universidad Javeriana, Colombia(Santiago de Cali)

// This is free software.  You are permitted to use,
// redistribute, and modify it as specified in the file "COPYING".

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>

/*! \file BinaryTree.h
    \brief Libreria que permite administrar arboles binarios ordenados    
*/  

/*! \struct strProgram
    \brief Estructura del nodo del arbol
*/
struct NodeTree{
   int key;
   void *Value;
   struct NodeTree *Left;
   struct NodeTree *Right;  
};

/*! \typedef NodeTree Tipo para definir un arbol
*/
typedef struct NodeTree *NodeTree;

/*! \fn NodeTree newNode(int key, void *Value)
    \brief Crea un nuevo nodo. Complejidad: O(1)
    \param key Llave del nuevo nodo
    \param Value Valor que se guardara
    \return Un nodo en memoria
*/
NodeTree newNode(int key, void *Value);

/*! \fn  NodeTree insertNode(NodeTree Tree, int key, void *Value)
    \brief Inserta un nuevo nodo en el arbol. Complejidad: O(1)
    \param Tree Arbol al que se le agregara el nodo
    \param key Llave del nuevo nodo
    \param Value Valor del nuevo nodo
    \return Arbol con el nodo agregado
*/
NodeTree insertNode(NodeTree Tree, int key, void *Value);

/*! \fn NodeTree LeftNode(NodeTree Tree)
    \brief Retorna el hijo izquierdo del arbol. Complejidad: O(log2n)
    \param Tree Arbol raiz
    \return Hijo izquierdo del arbol
*/
NodeTree LeftNode(NodeTree Tree);

/*! \fn NodeTree RightNode(NodeTree Tree)
    \brief Retorna el hijo derecho del arbol. Complejidad: O(1)
    \param Tree Arbol raiz
    \return Hijo derecho del arbol
*/
NodeTree RightNode(NodeTree Tree);

/*! \fn void *searchNode(NodeTree, int key)
    \brief Se encarga de buscar un nodo por su llave
    \param Tree El Arbol raiz
    \param key La llave a buscar
    \return El valor del nodo
*/
void *searchNode(NodeTree, int key);

/*! \fn void inorden(NodeTree Tree)
    \brief Recorre un arbol en inorden. Primero el subárbol izquierdo, después el nodo actual y por último el subárbol derecho. Complejidad: O(log2n)
    \param Tree Arbol raiz
*/
void inorden(NodeTree Tree);

/*! \fn void freeTree(NodeTree Tree)
    \brief Libera la memoria reservada del arbol. Complejidad: O(log2n)
    \param Tree El arbol raiz
*/
void freeTree(NodeTree Tree);

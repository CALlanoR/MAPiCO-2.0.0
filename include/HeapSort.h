// Generic HeapSort.h
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

/*! \file HeapSort.h
    \brief Libreria de ordenaci'on y busqueda en un arreglo de enteros    
*/ 

/*! \fn int searchBinary(int A[], int Length, int Element)
    \brief Función que permite realizar busquedas binarias en un arreglo ordenado. Complejidad: O(log N)
    \param A[] Arreglo ordenado
    \param Length Longitud del arreglo
    \param Element Elemento buscado
    \return La posici'on del elemento en el array
*/
int searchBinary(int A[], int Length, int Element);

/*! \fn void Exchange(int A[],int i,int j)
    \brief Funci'on que intercambia de posici'on el elemento i con el elemento j. Complejidad: O(1)
    \param A[] Arreglo de elementos
    \param i Elemento i 
    \param j Elemento j
*/
void Exchange(int A[],int i,int j);

/*! \fn int Left(int i)
    \brief Funci'on que obtiene el hijo izquierdo del elemento i. Complejidad: O(1)
    \param i Elemento al cual se le obtendra su hijo izquierdo
    \return El hijo izquierdo del elemento i
*/
int Left(int i);

/*! \fn int Right(int i)
    \brief Funci'on que obtiene el hijo derecho del elemento i. Complejidad: O(1)
    \param i Elemento al cual se le obtendra su hijo derecho
    \return El hijo derecho del elemento i
*/
int Right(int i);

/*! \fn void Heapify(int A[],int i,int Tam)
    \brief Funci'on que ordena comparando al Padre con sus 2 hijos para luego ver si los cambia o no. Complejidad: O(log N)
    \param A[] Arreglo de elementos
    \param i Elemento i 
    \param Tam Tama~no del arreglo
*/
void Heapify(int A[],int i,int Tam);

/*! \fn void Build_Heap(int A[],int Tam)
    \brief Funci'on que permite generar una estructura de arbol heap. Complejidad: O(log N)
    \param A[] Arreglo de elementos
    \param Tam Tama~no del arreglo
*/
void Build_Heap(int A[],int Tam);

/*! \fn void HeapSort(int A[],int Tam)
    \brief Función que permite almacenar todos los elementos de un arreglo a ordenar en un montículo (heap), y luego extraerlos de la cima del montículo de uno en uno para obtener el arreglo ordenado. Complejidad: O(log N)
    \param A[] Arreglo de elementos
    \param Tam Tama~no del arreglo
*/
void HeapSort(int A[],int Tam);

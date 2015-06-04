// Generic ObjectEval macros
// Copyright (c) 2002,  Alba Sarasti. <asarasti@puj.edu.co>, 
//                      Carlos A. Llano R. <callanor@puj.edu.co>
// Pontificia Universidad Javeriana, Colombia(Santiago de Cali)

// This is free software.  You are permitted to use,
// redistribute, and modify it as specified in the file "COPYING".

/*! \file ObjectEval.h
    \brief Libreria para manejo de objetos evaluados por un proceso en MAPiCO
*/

#ifndef OBJECTEVAL_H
#define OBJECTEVAL_H

/*! \def INICOBJECTEVAL(POA)
    \brief Inicializa un arreglo de objetos. Complejidad: O(1)
*/
#define INICOBJECTEVAL(POA)                         \
do{                                                 \
  POA = (struct ObjEval *)malloc(sizeof(struct ObjEval)); \
  POA->PCS = (int *)malloc(10 * sizeof(int));         \
  memset(POA->PCS, 0, 10); \
  POA->NumObjects = 0;                              \
  POA->Longitud = 10;                               \
}while(0)   
          
/*! \def GETNUMOBJECTS(POA)
    \brief Devuelve el numero de Objetos Evaluados. Complejidad: O(1)
*/
#define GETNUMOBJECTS(POA)  POA->NumObjects

/*! \def SETNUMOBJECTS(POA, valor)
    \brief Asigna el numero de Objetos Evaluados. Complejidad: O(1)
*/
#define SETNUMOBJECTS(POA, valor) POA->NumObjects = valor

/*! \def DELPCS(POA)
    \brief Eliminar los Objetos Evaluados. Complejidad: O(1)
*/
#define DELPCS(POA) memset(POA->PCS, 0, (POA->Longitud))

/*! \def GETPCS(POA)
    \brief Devuelve el vector de Objetos Evaluados. Complejidad: O(1)
*/
#define GETPCS(POA)  POA->PCS

/*! \def GET_PC_AT(POA, indice)
    \brief Devuelve el numero de Objetos Evaluados. Complejidad: O(1)
*/
#define GET_PC_AT(POA, indice)  POA->PCS[indice]

/*! \def SAVE_PC(POA, PC)
    \brief Inserta el PC del Objeto en el vector de Objetos Evaluados. Complejidad: O(1)
*/
#define SAVE_PC(POA, PC)               \
do{                                            \
   if(POA->NumObjects+1 < POA->Longitud){                 \
     POA->PCS[POA->NumObjects+1] = PC;                    \
     POA->NumObjects++;                        \
   }else{                                      \
     POA->PCS = (int *)realloc(POA->PCS,10*sizeof(int)); \
     POA->PCS[POA->NumObjects+1] = PC;                    \
     POA->NumObjects++;                        \
     POA->Longitud = POA->Longitud + 10; \
   }                                           \
}while( 0 )

/*! \def PRINT_PCS(POA)
    \brief Inserta el PC del Objeto en el vector de Objetos Evaluados. Complejidad: O(N)
*/
#define PRINT_PCS(POA)               \
do{                                            \
   for(int i=1;i<=POA->NumObjects;i++){           \
      printf("PC[%d]=[%d]\t",i, POA->PCS[i]);            \
   }                                           \
}while( 0 )

#endif // OBJECTEVAL_H

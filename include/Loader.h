// Generic Loader.h
// Copyright (c) 2002,  Alba Sarasti. <asarasti@puj.edu.co>, 
//                      Carlos A. Llano R. <callanor@puj.edu.co>
// Pontificia Universidad Javeriana, Colombia(Santiago de Cali)

// This is free software.  You are permitted to use,
// redistribute, and modify it as specified in the file "COPYING".

#include "Define.h"

/*! \file Loader.h
    \brief Libreria que permite cargar en memoria un programa en Bytes
    
    La libreria ofrece funciones para leer el archivo en bytes
*/    
    
/*! \struct strProgram
    \brief Estructura que almacena el archivo en bytes y su tamaño
*/
struct strProgram{
  int Size;
  char *File;
};

/*! \typedef Program Tipo para definir el program bytes
*/
typedef struct strProgram *Program;


/*! \fn Program Loader(char *FileName)
    \brief Funci'on que permite cargar un programa en bytes en un arreglo en memoria. . Complejidad: O(1)
    \param FileName El nombre del archivo en bytes
*/
Program Loader(char *FileName);

/*! \fn get8(Program Data, int Pointer)
    \brief Funcion que retorna un byte. Complejidad: O(1)
    \param Data El ByteCode en memoria
    \param Pointer El apuntador desde el cual se leera el byte
*/
char get8(Program Data, int Pointer);    //Ocupa una(1) posicion en el arreglo

/*! \fn get16(Program Data, int Pointer)
    \brief Funcion que retorna un word. Complejidad: O(1)
    \param Data El ByteCode en memoria
    \param Pointer El apuntador desde el cual se leera el word
*/
short get16(Program Data, int Pointer); //Ocupa dos(2) posiciones en el arreglo

/*! \fn get32(Program Data, int Pointer)
    \brief Funcion que retorna un double word. Complejidad: O(1)
    \param Data El ByteCode en memoria
    \param Pointer El apuntador desde el cual se leera el double word
*/
int get32(Program Data, int Pointer);     //Ocupa cuatro(4) posiciones en el arreglo

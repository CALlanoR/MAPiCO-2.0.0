// Copyright (c) 2002,  Alba Sarasti. <asarasti@puj.edu.co>, 
//                      Carlos A. Llano R. <callanor@puj.edu.co>
// Pontificia Universidad Javeriana, Colombia(Santiago de Cali)

// This is free software.  You are permitted to use,
// redistribute, and modify it as specified in the file "COPYING"

#include "MAPiCO.h"

/*! \file MAPiCO.c
    \fn int main(int argc, char *argv[])
    \brief Funcion que realiza la ejecucion del program bytes
    \param argc Numero de argumentos
    \param argv[] Arreglo con los parametros
    \return int Estado de la ejecuci'on
*/
int main(int argc, char *argv[])
{
  //////////////////////////////////////
  // CAPTURA Y CARGA DEL PROGRAM BYTE //
  //////////////////////////////////////
  if(argc!=2)
  {
    printf("Carga del Program Byte [ERROR]: %s.\n", NOT_PROGRAM_BYTE);
    exit(1);
  }
  
  //Ejecutar MAPiCO
  return Execute(argv[1]); 
    
}//main
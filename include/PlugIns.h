// PlugIns.h
// Copyright (c) 2002,  Alba Sarasti. <asarasti@puj.edu.co>, 
//                      Carlos A. Llano R. <callanor@puj.edu.co>
// Pontificia Universidad Javeriana, Colombia(Santiago de Cali)

// This is free software.  You are permitted to use,
// redistribute, and modify it as specified in the file "COPYING".

#include "Parameters.h"

/*! \file PlugIns.h
    \brief Libreria para administrar los plugins y sus instrucciones
*/

/*! \fn Parameters loadInstructions(Parameters argv, char **Functions, char *PathLibrary, void *Handle, int NumPlugIn)
    \brief Funci'on que carga las instrucciones de un plugin. Complejidad: O(N), donde N es el numero de instrucciones
    \param argv La estructura de parametros que contiene los plugins 
    \param **Functions Apuntador a una funci'on generica
    \param *PathLibrary Apuntador al path de la libreria dinamica (PlugIn)
    \param *Handle Apuntador al plugIn
    \param NumPlugIn Identificador del plugin
    \return Estructura de parametros que contiene los plugins 
*/
Parameters loadInstructions(Parameters argv, char **Functions, char *PathLibrary, void *Handle, int NumPlugIn);

/*! \fn Parameters loadPlugIns(Parameters argv, char *PathPlugInList)
    \brief Funci'on que carga un plugIn en memoria. Complejidad: O(N), donde N es el numero de PlugIns
    \param argv La estructura de parametros que contiene los plugins 
    \param *PathPlugInList Path del plugIn a cargar
    \return Estructura de parametros que contiene los plugins
*/
Parameters loadPlugIns(Parameters argv, char *PathPlugInList);

/*! \fn void* getInstruction(Parameters argv, int NumInstruction)
    \brief  Funci'on que busca una instrucci'on y retorna un apuntador a ella. Complejidad: O(1)
    \param argv La estructura de parametros que contiene los plugins 
    \param NumInstruction Numero de la instrucci'on que se buscara
    \return Apuntador a la instrucci'on
*/
void* getInstruction(Parameters argv, int NumInstruction);

/*! \fn void closePlugIns(Parameters argv)
    \brief  Cierra los plugins cargados en memoria. Complejidad: O(N)
    \param argv La estructura de parametros que contiene los plugins
*/
void closePlugIns(Parameters argv);


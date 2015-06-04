// MAPiCO.h
// Copyright (c) 2002,  Alba Sarasti. <asarasti@puj.edu.co>, 
//                      Carlos A. Llano R. <callanor@puj.edu.co>
// Pontificia Universidad Javeriana, Colombia(Santiago de Cali)

// This is free software.  You are permitted to use,
// redistribute, and modify it as specified in the file "COPYING".

#include "Loader.h"
#include "PlugIns.h"
#include "Proceso.h"
#include <time.h>
#include <sys/timeb.h>

/*! \file MAPiCO.h
    \brief Libreria de listas genericas con apuntador a la cabecera y la cola
*/

/*! \struct str_MAPiCO_CONF
    \brief Estructura que almacena la configuraci'on de MAPiCO
*/
struct str_MAPiCO_CONF
{
  int OpCodeSchedule;                        //OpCode de la instruccion que realiza el cambio de proceso
  int MaxOpenPlugIns;                        //Numero maximo de plugins que seran leidos
  char PathPlugIns[MAX_PATH];       //Ruta donde se encuentra el archivo que contiene los paths de los plugIns que seran cargados
};

/*! \typedef Configuration Tipo para definir la configuraci'on
*/
typedef struct str_MAPiCO_CONF Configuration;


/*! \fn void printQ(List Q, char *nameCola)
    \brief Funci'on que permite imprimir el contenido de una cola. Complejidad: O(N)
    \param Q List La Cola
    \param nameCola El nombre de la cola
*/
void printQ(List Q, char *nameCola);   

/*! \fn Configuration loadConfiguration(void)
    \brief Funcion que lee el archivo de configuracion y carga sus valores en la estructura. Complejidad: O(1)
    \return Configuration La configuraci'on de MAPiCO en la estructura
*/
Configuration loadConfiguration(char *fileNameConfig);                                

/*! \fn void printParameters(Parameters argvPlugIn)
    \brief Funcion que imprime el contenido de los parametros. Complejidad: O(1)
    \param argvPlugIn Parametros de los plugins
    \param fileNameConfig Ruta del archivo de configuracion pasado por parametro
*/
void printParameters(Parameters argvPlugIn);

/*! \fn printHelp(void)
    \brief Funcion que imprime la descripciòn de la ayuda. Complejidad: O(1)
*/
void printHelp(void);

/*! \fn int Execute(char *fileName)
    \brief Funcion que contiene el bloque principal de MAPiCO
    \param fileName Ruta del archivo a ejecutar
    \param fileNameConfig Ruta del archivo de configuracion pasado por parametro
    \return int Estado de la ejecuci'on
*/
int Execute(char *fileName, char *fileNameConfig);

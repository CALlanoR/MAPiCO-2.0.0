// Define.h
// Copyright (c) 2002,  Alba Sarasti. <asarasti@puj.edu.co>, 
//                      Carlos A. Llano R. <callanor@puj.edu.co>
// Pontificia Universidad Javeriana, Colombia(Santiago de Cali)

// This is free software.  You are permitted to use,
// redistribute, and modify it as specified in the file "COPYING".

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <dlfcn.h>
#include <ctype.h>

/*! \file Define.h
    \brief Libreria que definir las constantes de MAPiCO    
*/  

//Variables para indicar si hubo error o no en alguna operacion
#define ERROR                  1
#define NOERROR                0

//Mensajes de error de MAPiCO
#define INSTRUCTION_DUPLICATE "Se encontro una instruccion duplicada"
#define NOT_FILE_CONFIG       "No se pudo abrir el archivo de configuracion"
#define NOT_FILE_PLUGINS_LIST "No se pudo abrir el archivo de que contiene la lista de PlugIns"
#define NOT_OPEN_LIBRARY      "No se puede abrir la libreria"
#define NOT_CATALOGUE         "No se encontro la funcion Catalogue en el PlugIn"
#define CLOSE_ERROR           "No de pudo cerrar la libreria"
#define NOT_FUNCTION          "No se encontro el nombre de la funcion"
#define NOT_PROGRAM_BYTE      "No se paso por parametro el nombre del programa en bytes a ejecutar"

//Configuracion de los PlugIns
#define MAX_OPEN_PLUGINS      5    //Numero maximo de PlugIns que soporta MAPiCO
#define MAX_INSTRUCTIONS     20    //Numero maximo de Instrucciones  que soporta MAPiCO  
#define PATH_FILE_CONFIG     "./PlugIns.list"  //Path donde se encuentra el archivo de rutas de PlugIns
#define NOEXIST             -99   //Constante que indica si una instruccion no existe en el arbol
#define EXIST              -100   //Constante que indica si un opCode se encuentra en el arbol 
#define MAX_PATH            300   //Define el tamaNo maximo del path del PlugIn

//Configuracion del Loader
#define MAXIMO             1024  //Maximo de bytes que leera el Loader

//Valores varios
#define OK                 0  //True
#define NOT                1  //False
#define NODEARGM           0  //Indica que el nodo es un Argumento
#define FRAMECONST         1  //Indica que el nodo es un FrameConst  
#define NOT_TYPE          -1  //Indica que el nodo no tiene Tipo definido
#define VAR                4  //Indica que el valor corresponde a una Variable
#define METH               5  //Indica que el valor corresponde al nombre de un metodo
#define NOT_FOUND         -1  //Indica que no se encontro el valor
#define _COBJCC           11  //Indica el opCode el OBJCC
#define SCHEDULE         "RET" //Almacena el nombre de la fucion encargada de realizar el Schedule 

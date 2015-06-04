// Parameters.h
// Copyright (c) 2002,  Alba Sarasti. <asarasti@puj.edu.co>, 
//                      Carlos A. Llano R. <callanor@puj.edu.co>
// Pontificia Universidad Javeriana, Colombia(Santiago de Cali)

// This is free software.  You are permitted to use,
// redistribute, and modify it as specified in the file "COPYING".

#include "Define.h"
#include "Struct.h"
#include "BinaryTree.h"

/*! \file Parameters.h
    \brief Libreria para almacenar los parametros de los PlugIns
*/

/*! \struct str_PlugIn
    \brief Estructura para almacenar la referencia a un PlugIn
*/
struct str_PlugIn
{
  void *Handle;       //Apuntador al Handle del PlugIn
  char *PathLibrary;  //Path donde se encuentra la libreria dinamica
};
/*! \typedef PlugIn Tipo para definir un PlugIn
*/
typedef struct str_PlugIn PlugIn;

/*! \struct str_Instruction
    \brief Estructura para almacenar la referencia a las instrucciones
*/
struct str_Instruction
{
  int IndexPlugIn;    //Indice donde se encuentra la funcion
  char *NameFunction; //Nombre de la funcion
};
/*! \typedef Instruction Tipo para definir una Instruccion 
*/
typedef struct str_Instruction *Instruction;

/*! \struct str_Parameters
    \brief Estructura para almacenar los parametros de los PlugIns
*/
struct str_Parameters
{
  List VblesMAPiCO;      //Lista de variables de MAPiCO con las cuales cuentan las instrucciones
  NodeTree Instructions; //Arbol de Instrucciones
  PlugIn *PlugIns;       //Array con los apuntadores a los PlugIns cargados
  int NumPlugInsLoad;    //Numero de PlugIns que se cargaron en la ejecucion
  int Response;          //Codigo de respuesta de la accion
  char *Error;           //String con el mensaje de error
  int OpCodeSchedule;    //Codigo OpCode de la funcion que realiza el Schedule
  StoreMA sMA;           //StoreMA
};
/*! \typedef Parameters Tipo para definir los parametros de MAPiCO 
*/
typedef struct str_Parameters Parameters;

/*! \fn Parameters newParameters(int MaxOpenPlugIns)
    \brief Funci'on que inicializa los parametros
    \param MaxOpenPlugIns Numero de plugIns que se abriran
    \return Parameters Estructura con los parametros de MAPiCO
*/
Parameters newParameters(int MaxOpenPlugIns);

/*! \fn Parameters addVblePlugIn(Parameters argv, void *Vble)
    \brief Funci'on que agrega una variable a la lista de Parametros. Complejidad: O(1)
    \param argv Estructura que contiene los parametros de MAPiCO
    \param Vble Variable que se agregara a los parametros
    \return Parameters Estructura con los parametros de MAPiCO
*/
Parameters addVblePlugIn(Parameters argv, void *Vble);

/*! \fn Parameters setAtVblePlugIn(Parameters argv, void *Vble, int Position)
    \brief Funci'on que permite asingar una variable en una posici'on especifica de la lista de parametros. Complejidad: O(1)
    \param argv Estructura que contiene los parametros de MAPiCO
    \param Vble Variable que se agregara a los parametros
    \param Position Posici'on en que se asignara una variable
    \return Parameters Estructura con los parametros de MAPiCO
*/
Parameters setAtVblePlugIn(Parameters argv, void *Vble, int Position); 

/*! \fn void *getAtVblePlugIn(Parameters argv, int Position)
    \brief Funci'on que permite obtener una variable de una posici'on especifica de la lista de parametros. Complejidad: O(1)
    \param argv Estructura que contiene los parametros de MAPiCO
    \param Position Posici'on en que se asignara una variable
    \return Variable 
*/
void *getAtVblePlugIn(Parameters argv, int Position);

/*! \fn Parameters setHandle(Parameters argv, void *Handle, int NumPlugin)
    \brief Funci'on que permite almacenar la referencia a un plugin. Complejidad: O(1)
    \param argv Estructura que contiene los parametros de MAPiCO
    \param Handle Referencia a un plugin
    \param NumPlugin Identificador unico del plugin
    \return Parameters Estructura con los parametros de MAPiCO
*/
Parameters setHandle(Parameters argv, void *Handle, int NumPlugin);

/*! \fn void* getHandle(Parameters argv, int NumPlugin)
    \brief Funci'on que permite obtener la referencia a un plugin. Complejidad: O(1)
    \param argv Estructura que contiene los parametros de MAPiCO
    \param NumPlugin Identificador unico del plugin
    \return La referencia de un plugin
*/
void* getHandle(Parameters argv, int NumPlugin);

/*! \fn Parameters setPathLibrary(Parameters argv, char *PathLibrary, int NumPlugin)
    \brief Funci'on que permite almacenar la ruta fisica de un plugin. Complejidad: O(1)
    \param argv Estructura que contiene los parametros de MAPiCO
    \param PathLibrary Ruta donde se encuentra el plugin
    \param NumPlugin Identificador unico del plugin
    \return Parameters Estructura con los parametros de MAPiCO
*/
Parameters setPathLibrary(Parameters argv, char *PathLibrary, int NumPlugin);

/*! \fn char* getPathLibrary(Parameters argv, int NumPlugin)
    \brief Funci'on que obtiene la ruta fisica de un plugin. Complejidad: O(1)
    \param argv Estructura que contiene los parametros de MAPiCO
    \param NumPlugin Identificado unico del plugin
    \return Ruta donde se encuentra el plugin
*/
char* getPathLibrary(Parameters argv, int NumPlugin);

/*! \fn Parameters setNameFunction(Parameters argv, char *NameFunction, int NumPlugIn, int NumInstruction)
    \brief Funci'on que relaciona el identificador de una instrucci'on con una funci'on. Complejidad: O(1)
    \param argv Estructura que contiene los parametros de MAPiCO
    \param NameFunction Nombre de la funci'on
    \param NumPlugin Identificador unico del plugin
    \param NumInstruction Identificador unico de la instrucci'on
    \return Parameters Estructura con los parametros de MAPiCO
*/
Parameters setNameFunction(Parameters argv, char *NameFunction, int NumPlugIn, int NumInstruction);

/*! \fn char* getNameFunction(Parameters argv, int NumInstruction)
    \brief Funci'on que obtiene el nombre de una instrucci'on. Complejidad: O(1)
    \param argv Estructura que contiene los parametros de MAPiCO
    \param NumInstruction Identificador unico de la instrucci'on
    \return Una cadena con el nombre de la funci'on
*/
char* getNameFunction(Parameters argv, int NumInstruction);


/*! \fn char* getNameFunctionByInstruction(Parameters argv, Instruction instruction)
    \brief Funci'on que obtiene el nombre de una instrucci'on directamente del nodo. Complejidad: O(1)
    \param argv Estructura que contiene los parametros de MAPiCO
    \param instruction Nodo que contiene la Instrucci'on
    \return Una cadena con el nombre de la funci'on
*/
char* getNameFunctionByInstruction(Parameters argv, Instruction instruction);

/*! \fn Parameters setResponse(Parameters argv, int Response)
    \brief Funci'on que guarda el codigo de respuesta de una operaci'on con los parametros. Complejidad: O(1)
    \param argv Estructura que contiene los parametros de MAPiCO
    \param Response Status que corresponde al estatus de una operaci'on sobre los parametros
    \return Parameters Estructura con los parametros de MAPiCO
*/
Parameters setResponse(Parameters argv, int Response);

/*! \fn int getResponse(Parameters argv)
    \brief Funci'on que obtiene el codigo de respuesta de una operaci'on sobre los parametros. Complejidad: O(1)
    \param argv Estructura que contiene los parametros de MAPiCO
    \return Un entero con el codigo de status
*/
int getResponse(Parameters argv);

/*! \fn Parameters setOpCodeSchedule(Parameters argv, int OpCode)
    \brief Funci'on que asigna el OpCode de la instrucci'on que realizara el Schedule de los procesos. Complejidad: O(1)
    \param argv Estructura que contiene los parametros de MAPiCO
    \param OpCode Numero de la instrucci'on
    \return Parameters Estructura con los parametros de MAPiCO
*/
Parameters setOpCodeSchedule(Parameters argv, int OpCode);

/*! \fn int getOpCodeSchedule(Parameters argv)
    \brief Funci'on que obtiene el OpCode de la funci'on que realizara el Schedule de los procesos. Complejidad: O(1)
    \param argv Estructura que contiene los parametros de MAPiCO
    \return Identificador unico de la instrucci'on
*/
int getOpCodeSchedule(Parameters argv);

/*! \fn Parameters setStoreMA(Parameters argv, StoreMA sMA)
    \brief Funci'on que asigna el Store que la maquina utilizar'a. Complejidad: O(1)
    \param argv Estructura que contiene los parametros de MAPiCO
    \params sMA Store aritmetico que utilizar'a MAPiCO
    \return Parameters Estructura con los parametros de MAPiCO
*/
Parameters setStoreMA(Parameters argv, StoreMA sMA);

/*! \fn StoreMA getStoreMA(Parameters argv)
    \brief Funci'on que obtiene el store que la maquina esta utilizando. Complejidad: O(1)
    \param argv Estructura que contiene los parametros de MAPiCO
    \return El Store utilizado
*/
StoreMA getStoreMA(Parameters argv);

/*! \fn Parameters setError(Parameters argv, char *Error)
    \brief Funci'on que asigna una descripci'on del error que se presento. Complejidad: O(1)
    \param argv Estructura que contiene los parametros de MAPiCO
    \param Error Cadena con la descripci'on del error
    \return Parameters Estructura con los parametros de MAPiCO
*/
Parameters setError(Parameters argv, char *Error);

/*! \fn char* getError(Parameters argv)
    \brief Funci'on que obtiene la descripci'on del error presentado. Complejidad: O(1)
    \param argv Estructura que contiene los parametros de MAPiCO
    \return Descripci'on del error
*/
char* getError(Parameters argv);

/*! \fn Parameters setNumPlugInsLoad(Parameters argv, int NumPlugInsLoad)
    \brief Funci'on que almacena el numero de plugIns cargados. Complejidad: O(1)
    \param argv Estructura que contiene los parametros de MAPiCO
    \param NumPlugInsLoad Numero de plugins cargados
    \return Parameters Estructura con los parametros de MAPiCO
*/
Parameters setNumPlugInsLoad(Parameters argv, int NumPlugInsLoad);

/*! \fn int getNumPlugInsLoad(Parameters argv)
    \brief Funci'on que obtiene el numero de plugIns cargados. Complejidad: O(1)
    \param argv Estructura que contiene los parametros de MAPiCO
    \return Numero de plugins cargados
*/
int getNumPlugInsLoad(Parameters argv);

/*! \fn int isInstruction(Parameters argv, int NumInstruction)
    \brief Funci'on que valida si un identificador es una instrucci'on. Complejidad: O(1)
    \param argv Estructura que contiene los parametros de MAPiCO
    \param NumInstruction Identificador de una instrucci'on
    \return 1 si Existe 0 sino existe
*/
int isInstruction(Parameters argv, int NumInstruction);

/*! \fn int getIndexPlugIn(Parameters argv, int NumInstruction)
    \brief Funci'on que obtiene la posici'on donde se encuentra el plugin que contiene la instrucci'on. Complejidad: O(1)
    \param argv Estructura que contiene los parametros de MAPiCO 
    \param NumInstruction Identificador de una instrucci'on
    \return Indice donde se encuentra el plugin
*/
int getIndexPlugIn(Parameters argv, int NumInstruction);

/*! \fn int getIndexPlugInByInstruction(Parameters argv, Instruction instruction)
    \brief Funci'on que obtiene la posici'on donde se encuentra el plugin que contiene la instrucci'on a partir del nodo Instruccion. Complejidad: O(1)
    \param argv Estructura que contiene los parametros de MAPiCO 
    \param instruction Nodo que contiene la Instrucci'on
    \return Indice donde se encuentra el plugin
*/
int getIndexPlugInByInstruction(Parameters argv, Instruction instruction);

/*! \fn void freeParameters(Parameters argv)
    \brief Funci'on que libera la memoria reservada por los plugins. Complejidad: O(N)
    \param argv Estructura que contiene los parametros de MAPiCO
*/
void freeParameters(Parameters argv);

/*! \fn Instruction searchInstruction(Parameters argv, int NumInstruction)
    \brief Funci'on que obtiene una instrucci'on a partir de su numero
    \param argv Estructura que contiene los parametros de MAPiCO
    \param NumInstruction Identificador de una instrucci'on
    \return Instrucci'on
*/
Instruction searchInstruction(Parameters argv, int NumInstruction);

/* --------------------------------------------------------- */
/* ***** EOF ***** */


#include "Parameters.h"

/**
* newParameters
*/
Parameters newParameters(int MaxOpenPlugIns)
{
   Parameters newArgv;
   int i;

   //Inicializacion del arbol de instrucciones
   newArgv.Instructions = NULL;

   //Asignacion de memoria para la lista de PlugIns a cargar
   newArgv.PlugIns = (PlugIn *)calloc(MaxOpenPlugIns,sizeof(struct str_PlugIn));

   /*
   for(i=0;i<MaxOpenPlugIns;i++)
       newArgv.PlugIns[i].PathLibrary=NULL;
   */   

   newArgv.NumPlugInsLoad=0;
   LIST(newArgv.VblesMAPiCO);

  return newArgv;
}//newParameters 

/**
* addVblePlugIn
*/
Parameters addVblePlugIn(Parameters argv, void *Vble)
{
  INSERT_AT_END(argv.VblesMAPiCO, Vble);
  return argv;
}//addVblePlugIn

/**
* setAtVblePlugIn
*/
Parameters setAtVblePlugIn(Parameters argv, void *Vble, int Position)
{
  SET_AT(argv.VblesMAPiCO,Position,Vble);
  return argv;
}//setAtVblePlugIn

/**
* getAtVblePlugIn
*/
void* getAtVblePlugIn(Parameters argv, int Position)
{
  void *Temp;
  GET_AT(argv.VblesMAPiCO, Position, Temp);
  return Temp;
}//getAtVblePlugIn

/**
* setHandle
*/
Parameters setHandle(Parameters argv, void *Handle, int NumPlugIn)
{
  argv.PlugIns[NumPlugIn].Handle = Handle;
  return argv;
}//setHandle

/**
* setPathLibrary
*/
Parameters setPathLibrary(Parameters argv, char *PathLibrary, int NumPlugIn)
{
  int Length;
  Length = strlen(PathLibrary);
  argv.PlugIns[NumPlugIn].PathLibrary = (char *)malloc(sizeof(char)*Length-1);
  strcpy(argv.PlugIns[NumPlugIn].PathLibrary,PathLibrary);

  return argv;
}//setPathLibrary

/**
* setNameFunction
*/
Parameters setNameFunction(Parameters argv, char *NameFunction, int NumPlugIn, int NumInstruction)
{
   int Length;
   Instruction instruction;   
   Length = strlen(NameFunction);
   
   instruction = (Instruction)malloc(sizeof(struct str_Instruction));

   //Se guardan la informacion de la instruction   
   instruction->IndexPlugIn = NumPlugIn;
   instruction->NameFunction = (char *)malloc(sizeof(char)*Length-1); 
   strcpy(instruction->NameFunction ,NameFunction);   
   
   //Agrega la instruccion al arbol binario de instrucciones
   argv.Instructions = insertNode(argv.Instructions, NumInstruction, instruction);
   
   return argv;
}//setNameFunction

/**
* setResponse
*/
Parameters setResponse(Parameters argv, int Response)
{
  argv.Response = Response;
  return argv;
}//setResponse

/**
* setError
*/
Parameters setError(Parameters argv, char *Error)
{
  int Length;
  Length = strlen(Error);
  
  if(argv.Error!=NULL)
  {
     free(argv.Error);
  }
        
  argv.Error = (char *)malloc(sizeof(char)*Length-1); 
  strcpy(argv.Error,Error);

  return argv;
}//setError

/**
* setNumPlugInsLoad
*/
Parameters setNumPlugInsLoad(Parameters argv, int NumPlugInsLoad)
{
  argv.NumPlugInsLoad = NumPlugInsLoad;
  return argv;
}//setNumPlugInsLoad

/**
* setOpCodeSchedule
*/
Parameters setOpCodeSchedule(Parameters argv, int OpCode)
{
   argv.OpCodeSchedule = OpCode;
   return argv;
}//setOpCodeSchedule

/**
* getOpCodeSchedule
*/
int getOpCodeSchedule(Parameters argv)
{
   return argv.OpCodeSchedule;
}//getOpCodeSchedule

/**
* setOpCodeSchedule
*/
Parameters setStoreMA(Parameters argv, StoreMA sMA)
{
   argv.sMA = sMA;   
   return argv;
}//setStoreMA

/**
* getOpCodeSchedule
*/
StoreMA getStoreMA(Parameters argv)
{
   return argv.sMA;
}//getStoreMA

/**
* getHandle
*/
void* getHandle(Parameters argv, int NumPlugin)
{
  return argv.PlugIns[NumPlugin].Handle;
}//getHandle

/**
* getPathLibrary
*/
char* getPathLibrary(Parameters argv, int NumPlugin)
{
  return argv.PlugIns[NumPlugin].PathLibrary;
}//getPathLibrary

/**
* getNameFunction
*/
char* getNameFunction(Parameters argv, int NumInstruction)
{
   Instruction instruction;
   
   instruction = searchNode(argv.Instructions, NumInstruction);
   
   return instruction->NameFunction;
}//getNameFunction

/**
* getNameFunctionByInstruction
*/
char* getNameFunctionByInstruction(Parameters argv, Instruction instruction)
{
   return instruction->NameFunction;
}//getNameFunctionByInstruction

/**
* searchInstruction
*/
Instruction searchInstruction(Parameters argv, int NumInstruction)
{
   return searchNode(argv.Instructions, NumInstruction);   
}//searchInstruction

/**
* getIndexPlugIn
*/
int getIndexPlugIn(Parameters argv, int NumInstruction)
{
   Instruction instruction;
   
   instruction = searchNode(argv.Instructions, NumInstruction);
   
   return instruction->IndexPlugIn;   
}//getIndexPlugIn

/**
* getIndexPlugInByInstruction
*/
int getIndexPlugInByInstruction(Parameters argv, Instruction instruction)
{
   return instruction->IndexPlugIn;   
}//getIndexPlugInByInstruction

/**
* getResponse
*/
int getResponse(Parameters argv)
{
  return argv.Response;
}//getResponse

/**
* getError
*/
char* getError(Parameters argv)
{
  return argv.Error;
}//getError

/**
* getNumPlugInsLoad
*/
int getNumPlugInsLoad(Parameters argv)
{
  return argv.NumPlugInsLoad;
}//getNumPlugInsLoad

/**
* isInstruction
*/
int isInstruction(Parameters argv, int NumInstruction)
{
   Instruction instruction;
   
   instruction = searchNode(argv.Instructions, NumInstruction);
   
   if(instruction==NULL)
    return NOEXIST;
  else
    return EXIST;      
}//isInstruction

/**
* freeParameters
*/
void freeParameters(Parameters argv)
{
  int NumPlugInsLoad, i;
  
  //Libera la memoria ocupada por la informacion de las instrucciones
   argv.Instructions = NULL;

  //Libera la memoria ocupada por la informacion del Path de los PlugIn's
  NumPlugInsLoad = getNumPlugInsLoad(argv);

  for(i=1;i<NumPlugInsLoad;i++)
    {
      free(argv.PlugIns[i].PathLibrary);
    }//for(i=1;i<NumPlugInsLoad;i++)
  
}//freeParameters


/** EOF **/

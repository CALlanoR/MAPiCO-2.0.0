// Generic MAPiCO.c
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
   struct timeb ini, fim;
   char *fileNameConfig=NULL;      //Nombre del archivo de configuración enviado por parametro
   char *fileNameProgramByte=NULL; //Nombre del archivo a ejecutar 
   
  /////////////////////////////////////////////
  // VALIDACION DE LOS PARAMETROS DE ENTRADA //
  /////////////////////////////////////////////
  if(argc<2)
  {
     //Imprime la ayuda ya que no trae el minimo de parametros a ejecutar
     printHelp();
  } 
  else if(argc>=2)
  {
     if(strcmp(argv[1],"-c")==0)
     {
        //Numero de parametros correcto para la opcion "-c"
        if(argc==4)
        {
           //Asigna el nombre del archivo de configuración pasado por parametro
           fileNameConfig = (char *)malloc(strlen(argv[2])*sizeof(char));
           strcpy(fileNameConfig, argv[2]);
           
           //Asigna el nombre del archivo a ejecutar
           fileNameProgramByte = (char *)malloc(strlen(argv[3])*sizeof(char));
           strcpy(fileNameProgramByte, argv[3]);           
        }
        else
        {
           //Imprime la ayuda ya que no trae el nombre del archivo a ejecutar
           printHelp();
        }
     }
     else if(strcmp(argv[1],"-h")==0)
     {
        //Imprime la ayuda por peticion
        printHelp();
     }
     else if(strcmp(argv[1],"-v")==0)
     {
        //Imprime la version de la maquina
        printf("MAPiCO C version 2.0.0.1\n");
        exit(0);
     }
     else
     {
        //Asigna el nombre del archivo a ejecutar
        fileNameProgramByte = (char *)malloc(strlen(argv[1])*sizeof(char));
        strcpy(fileNameProgramByte, argv[1]);   
        
        //Asigna el nombre del archivo de configuración por defecto
        fileNameConfig = (char *)malloc(20*sizeof(char));
        strcpy(fileNameConfig, "../doc/MAPiCO.conf");
                
     }
  }
    
  //Tiempo inicial
  ftime(&ini);
  
  //Ejecutar MAPiCO
  Execute(fileNameProgramByte, fileNameConfig); 
  
  //Tiempo Final
  ftime(&fim);
  
  printf("Duraciòn ejecuciòn total en milisegundos [%10.20f]\n", ((double)fim.time + ((double)fim.millitm * 0.001)) - ((double)ini.time + ((double)ini.millitm * 0.001)));
    
  free(fileNameConfig);
  free(fileNameProgramByte);
  
  return 0;
    
}//main

/*! \fn int Execute(char *fileName)
    \brief Funcion que contiene el bloque principal de MAPiCO
    \param fileName Ruta del archivo a ejecutar
    \param fileNameConfig Ruta del archivo de configuracion pasado por parametro
    \return Estado de la ejecuci'on
*/
int Execute(char *filename, char *fileNameConfig)
{
  //////////////////////////////
  // DECLARACION DE VARIABLES //
  //////////////////////////////
  //Vbles para manejo de PlugIn's
  short OpCode=0;                        //OpCode de la instruccion
  Configuration VarConfig;               //Variable de configuracion inicial
  Parameters (*Instruction)(Parameters); //Funcion de la instruccion
  Parameters argvPlugIn;                 //Parametros para los PlugIn's
  
  //Declaracion de colas
  List RunQ;                             //Cola de Ejecucion
  List ObjQ;                             //Cola de Objetos
  List MsgQ;                             //Cola de Mensajes
  List AskQ;                             //Cola de Ask 
  
  //Registros de MAPiCO
  int PCA;                               //Puntero a Codigo Actual
  void *PVA;                             //Puntero a Variables Actual
  void *PMA;                             //Puntero a Metodos Actual
  void *PAA;                             //Puntero a Argumentos Actual
  void *POA;                             //Puntero a Objetos Actual
  void *PAUX;                            //Puntero Auxiliar
  void *PTEMP;                           //Puntero Temporal
  
  //Vble para definir procesos
  Proceso Proc;

  //Vble que contiene el ProgramByte
  Program Data;

  //Otras Vbles
  int *VarCounter;                       //Contador de variables creadas  
  int ResultExecution = OK;              //Resultado de la ejecucion
  int *Finish;                           //Flag para finalizar la ejecucion
  //struct timeb loadIni, loadFin;       //Vbles para tomar tiempos de carga del program byte
  //struct timeb execIni, execFin;       //Vbles para tomar tiempos de ejecucion del program byte
  //struct timeb plugIni, plugFin;       //Vbles para tomar tiempos de cargue de los plugins
  
  //////////////////////////////////
  // CARGAR CONFIGURACION INICIAL //
  //////////////////////////////////
  VarConfig = loadConfiguration(fileNameConfig);

  ///////////////////////////
  // INICIALIZAR VARIABLES //
  ///////////////////////////
 
  //Inicializador de Parametros
  argvPlugIn = newParameters(VarConfig.MaxOpenPlugIns); 
  
  //Inicializar Contador de variables
  VarCounter = (int *)malloc(sizeof(int));
  *VarCounter = 0;

  //Inicializar Flag de ejecucion
  Finish = (int *)malloc(sizeof(int));
  *Finish = NOT;
  
  //Inicializacion de las colas de MAPiCO
  LIST(RunQ);
  LIST(ObjQ);
  LIST(MsgQ);
  LIST(AskQ);

  //Inicializar proceso inicial de la maquina
  Proc =  newProceso(0, PVA, PMA, PAA, POA, PAUX, PTEMP);
 
  //Tiempo inicial de carga del archivo de entrada
  //ftime(&loadIni);
  
  //Lectura de todo el archivo de entrada
  Data = Loader(filename);
  
  //Tiempo final de carga del archivo de entrada
  //ftime(&loadFin);

  /////////////////////////////////
  // CARGA DE TODOS LOS PLUGIN's //
  /////////////////////////////////
  
  //Tiempo inicial de carga del archivo de entrada
  //ftime(&plugIni);  
  
  argvPlugIn = loadPlugIns(argvPlugIn, VarConfig.PathPlugIns);
  if(getResponse(argvPlugIn)==ERROR)
  {
     printf("Carga de PlugIns. [ERROR]: %s\n", getError(argvPlugIn));
     exit(1);
  }
  
  //Tiempo final de ejecucion de la carga de plugins
  //ftime(&plugFin);

  /////////////////////////////////////////////////////////
  // CREACION DE LA LISTA DE VARIABLES PARA LOS PLUGIN'S //
  /////////////////////////////////////////////////////////
  //Se agrega el flag Finish que indica si MAPiCO debe seguir ejecutandose
  argvPlugIn = addVblePlugIn(argvPlugIn, Finish);
  
  //Se agrega el proceso a la lista de variables de los PlugIn's
  argvPlugIn = addVblePlugIn(argvPlugIn, Proc);
  
  //Se agrega el contador de variables a la lista de variables de los PlugIn's
  argvPlugIn = addVblePlugIn(argvPlugIn, VarCounter);
  
  //Se agrega el program byte a la lista de variables de los PlugIn's
  argvPlugIn = addVblePlugIn(argvPlugIn, Data);
  
  //Se agregan las colas de ejecucion RunQ, ObjQ, MsgQ, AskQ
  argvPlugIn = addVblePlugIn(argvPlugIn, RunQ);
  argvPlugIn = addVblePlugIn(argvPlugIn, ObjQ);
  argvPlugIn = addVblePlugIn(argvPlugIn, MsgQ);
  argvPlugIn = addVblePlugIn(argvPlugIn, AskQ);
   
  //Se agrega el codigo de la funcion que realiza el Schedule
  argvPlugIn = setOpCodeSchedule(argvPlugIn, VarConfig.OpCodeSchedule);
  
  //for(int i=0;i<64;i++)
    //printf("[%c]",Data->File[i]);

  //printf("Ejecución del Program Byte....\n");
  
  /////////////////////////////////////
  // EJECUCION DEL PROGRAMA EN BYTES //
  /////////////////////////////////////
  
  //Tiempo inicial de ejecuciòn del program byte
  //ftime(&execIni);  
  
  while(*Finish != OK)
  {
     //Se recupera el PC
     PCA = getPC(Proc);
     
     //Prueba de los parametros
    //printf("PCA->[%d]\n",PCA);
    
     ////////////////////////////////////////////
     // BUSQUEDA Y EJECUCION DE LA INSTRUCCION //
     ////////////////////////////////////////////
     //Lectura del program byte
     OpCode = get8(Data, PCA);

     //printf("OpCode->[%d]\n",OpCode);

     //Se busca la instruccion 
     Instruction = getInstruction(argvPlugIn, OpCode);

     //Se ejecuta la instruccion mandandole los parametros
     argvPlugIn = Instruction(argvPlugIn);

     /////////////////////////////////////////////////////////////////////
     //RECUPERACION DE LAS VARIABLES DE MAPiCO                          //
     //  Nota: No es necesario traer el program byte ya que no sufre    //
     //        modificaciones durante la ejecucion                      //   
     /////////////////////////////////////////////////////////////////////
     //Recuperacion del flag de ejecucion
     Finish = getAtVblePlugIn(argvPlugIn,0);

     //Recuperacion del proceso actual
     Proc = getAtVblePlugIn(argvPlugIn,1);

     //Recuperacion de las colas de ejecucion RunQ, ObjQ, MsgQ, AskQ
     RunQ = getAtVblePlugIn(argvPlugIn,4);
     //ObjQ = getAtVblePlugIn(argvPlugIn,5);

     //Prueba de funcionamiento de las colas
     //printQ(RunQ, "RunQ");
     //printQ(ObjQ, "ObjQ");
     //printQ(MsgQ, "MsgQ");
    
     //Se recupera el PC
     //PCA = getPC(Proc);        

  }//while
  
  //Tiempo final de ejecucion del program byte
  //ftime(&execFin);
  
  //Se cierran todos los PlugIns
  closePlugIns(argvPlugIn);

  //Liberar recursos
  free(VarCounter);
  //delProceso(Proc);
  
  /*
  printf("Tiempo cargue del program byte en milisegundos [%10.20f]\n", ((double)loadFin.time + ((double)loadFin.millitm * 0.001)) - ((double)loadIni.time + ((double)loadIni.millitm * 0.001)));
  
  printf("Tiempo ejecucion del program byte en milisegundos [%10.20f]\n", ((double)execFin.time + ((double)execFin.millitm * 0.001)) - ((double)execIni.time + ((double)execIni.millitm * 0.001)));  

  printf("Tiempo cargue de plugins en milisegundos [%10.20f]\n", ((double)plugFin.time + ((double)plugFin.millitm * 0.001)) - ((double)plugIni.time + ((double)plugIni.millitm * 0.001)));  
  */
  
   //Retorna el estado final de la ejecucion
  return ResultExecution;   
  
}//Execute


/**
 * Imprimir procesos de xQ
 */
void printQ(List Q, char *nameCola)
{
  //Variables
  Proceso ProcTemp;
  NodeList NodeTemp;
  int i;
  
  if(Q->Elements!=0)
  {
      printf("\n");
      printf("%s Test...\n", nameCola);
      
      NodeTemp = FIRST_NODE(Q);
      
      printf("<PC,PV,PM,PA,PO,PAUX,PTEMP>\n");
      
      for(i=0;i<Q->Elements;i++)
         {
               ProcTemp = GETDATA(NodeTemp);
               
               //Imprime el proceso
               printf("<%d,PV,PM,PA,PO,PAUX,PTEMP>\n",getPC(ProcTemp));
               
               if(ProcTemp->PV!=NULL)
               {
                  printf("PV->");
                  PRINT_NODELIST(ProcTemp->PV);     
                  printf("\n");
               }
               
               NodeTemp = GETNEXT(NodeTemp);      
         }  
   }    
}//printQ


/**
* Leer la configuracion de MAPiCO.conf y guardarla en memoria
*/

/*! \fn Configuration loadConfiguration(void)
    \brief Funci'on que lee la configuracion de MAPiCO.conf y la guardar en memoria
    \param fileNameConfig El nombre del de configuracion
    \return Configuration Estructura con los datos de configuracion de MAPiCO
*/
Configuration loadConfiguration(char *fileNameConfig)
{
   Configuration varConfig;
   FILE *FileConfig;
   char Line[MAXIMO];   
   char *Value, *Key;
   int TamLine=0;
   int Pos=0;
   
   //Se asigna por defecto que el OpCode no fue encontrado en el archivo de configuracion
   varConfig.OpCodeSchedule = NOT_FOUND;
   
   //Abrir archivo de configuracion MAPiCO.conf
   if((FileConfig=fopen(fileNameConfig,"r"))==NULL)
   {
      printf("[ERROR]: %s %s\n",NOT_FILE_CONFIG, fileNameConfig);
      exit(1);
   }
   else
   {         
         while(!feof(FileConfig))
         {   
            fgets(Line, MAXIMO, FileConfig);

            if(Line[0]!='#' && !iscntrl(Line[0]))
            {                                                                              
               //Se Elimina el salto de linea
               TamLine = strlen(Line);        
               if(iscntrl(Line[TamLine-1]))
                  Line[TamLine-1]='\0';
               else
                  Line[TamLine]='\0';   
               
               //Posicion donde se encuentra el separador "="
               Pos = strcspn(Line,"=");
   
               Key = (char *)malloc(sizeof(char)*Pos);
               Value  = (char *)malloc(sizeof(char)*(TamLine - Pos));
                     
               strncpy(Key, Line, Pos);
               strncpy(Value, (Line + Pos + 1), (TamLine - Pos));
               
               //printf("Key [%s], Value [%s]\n",Key, Value);
                                    
               if(strcmp(Key,"schedule")==0)
                  varConfig.OpCodeSchedule = atoi(Value);
               else
               {
                  if(strcmp(Key,"pathPlugInList")==0)
                     strncpy(varConfig.PathPlugIns, (Line + Pos + 1), (TamLine - Pos));
                  else
                  {
                     if(strcmp(Key,"maxOpenPlugIns")==0)
                        varConfig.MaxOpenPlugIns = atoi(Value);
                  }
               }//else::if(strcmp(schedule...
            }//if(Line[0]...   
         }//while               
   }//else
       
   //printf("schedule [%d], pathPlugInList [%s], maxOpenPlugIns [%d], maxInstructions [%d]\n", varConfig.OpCodeSchedule, varConfig.PathPlugIns, varConfig.MaxOpenPlugIns, varConfig.maxInstructions);   
   
   //printf("Carga de configuracion. [OK]\n");
      
   return varConfig;
}//loadConfiguration

/**
 * Print Parameters
 */
void printParameters(Parameters argvPlugIn)
{
   printf("Len(VbleMAPiCO) = [%d]\n", LENGTH_LIST(argvPlugIn.VblesMAPiCO));
   printf("NumPlugInsLoad = [%d]\n", argvPlugIn.NumPlugInsLoad);
   printf("OpCodeSchedule = [%d]\n", argvPlugIn.OpCodeSchedule);   
}//printParameters

/***
 * Print Help
 */
 
/*! \fn void printHelp(void)
    \brief Funci'on que imprime la ayuda del mapico
*/ 
void printHelp(void)
{
   printf("\n");
   printf("Usage: ./mapico [options] file... \n");
   printf("where options include:\n");
   printf("\t-c [configuration file]\n");
   printf("\t-v Run MAPiCO version number\n");
   printf("\t-h Display this information\n\n");
   printf("For bug reporting instructions, please see:\n");
   printf("<URL:http://gforge.puj.edu.co/projects/mapico2/>\n");   
   printf("\n");
   exit(0);   
}//printHelp

/* **EOF ** */


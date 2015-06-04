#include "Proceso.h"
#include "Loader.h"
#include "PlugIns.h"

#define NUM_FUNC_PLUGIN 6 //Numero de operaciones que tiene el PlugIn

Parameters ValidType_PAA(Parameters argv, Auxiliar PAA);

/**
 * Catalogue
 */
Parameters Catalogue(Parameters argv, char *PathLibrary, void *Handle, int NumPlugIn)
{
   char *Functions[] = {"1:INIT","7:POP","8:PUSHV","9:PUSHM","10:OBJCC","11:COBJCC","12:RET",NULL};
   
   //Cargar las instrucciones del PlugIn
   argv = loadInstructions(argv, Functions, PathLibrary, Handle, NumPlugIn);
   
   return argv;
}//Catalogue

/**
 * INIT
 */
Parameters INIT(Parameters argv)
{
  //Registro que se necesita de MAPiCO
  int    PCA;                    //Puntero a Codigo Actual
  NodeList PVA;                  //Puntero a Variables Actual
  NodeList PMA;                  //Puntero a Metodos Actual
  Auxiliar PAA;                  //Puntero Auxiliar Actual
  ObjectEval POA;                //Puntero a Objetos Actual
  Auxiliar PAUX;                 //Puntero Auxiliar
  void *PTEMP;                   //Puntero Temporal    
  
  //Vble para definir procesos
  Proceso Proc;
  
  //Vble para almacenar el Store
  StoreMA sMA;                   //Store MA
  
  //printf ("Begin INIT.\n");

  //Recuperacion del primer parametro (Proceso)
  Proc = getAtVblePlugIn(argv,1);

  //Se recupera el PC
  PCA = getPC(Proc);

  //Incrementar el PCA para la siguiente instruccion
  PCA = PCA + 1;
  
  //Inicializar el Apuntador a Objetos Evaluados    
  INICOBJECTEVAL(POA);
  
  //Inicializar PAA y PAUX
  INICAUXILIAR(PAA, NOT_TYPE); 
  INICAUXILIAR(PAUX, NOT_TYPE); 
  
  //Inicializacion resto de punteros 
  PVA = NULL;
  PMA = NULL;
  PTEMP = NULL;
  
  //Colocar el storeMA como no inicializado
  sMA = inicStoreMA();  

  //Se agrega el Store de MAPiCO
  argv = setStoreMA(argv, sMA);  
    
  //Asignacion de los nuevos valores
  setPC(Proc, PCA);
  setPV(Proc, PVA);
  setPM(Proc, PMA);
  setPA(Proc, PAA);
  setPO(Proc, POA);
  setPAUX(Proc,PAUX);
  setPTEMP(Proc, PTEMP);

  //Validar si por configuración se asigno OpCode de Schedule
  if(getOpCodeSchedule(argv) == NOT_FOUND)
  {
     //Se agrega el codigo "12" de la funcion que realiza el Schedule
     argv = setOpCodeSchedule(argv, 12);
  }
  
  //Se guardan las variables en la lista de vbles de los PlugIn's
  argv = setAtVblePlugIn(argv,Proc,1);

  //printf("End INIT\n");

  //Retorno de los argumentos
  return argv;

}//INIT

/**
 * POP
 */
Parameters POP(Parameters argv)
{
   //Registro que se necesitan de MAPiCO
   int PCA;                              //Program Counter
   NodeList PVA;                   //Puntero a Variables Actual
   NodeList PMA;                  //Puntero a Metodo 
   Auxiliar PAA;                     //Puntero Auxiliar Actual
   
   //Vbles para definir procesos
   Proceso Proc;
   
   //Vble para guardar el parametro
   NodeList NodeTempList;
   NodeArg  NodeArgPAA;
   NodeArg NodeTempArg;
   
   //Otras Variables
   int *Variable;
   int *Var;
   int Type;
   //int Longitud = 0;
   
   //printf("Begin POP.\n");
   
   //Recuperacion del primer parametro (Proceso)
   Proc = getAtVblePlugIn(argv,1);
   
   //Se recuperan los valores de los registros
   PCA = getPC(Proc);
   PVA = getPV(Proc);
   PMA = getPM(Proc);
   PAA = getPA(Proc);
   
   if(GETTYPE(PAA)!=NOT_TYPE)
   {         
         if(GETTYPE(PAA)==FRAMECONST)
         {
            //Como PAA contiene una restriccion esta sera eliminada sin guardarla en memoria
            FREEFRAMECONST(PAA);    
            
            //Se asigna el tipo de PAA de acuerdo a la lista de argumentos
            if(GETNODEARG(PAA)!=NULL)
            {
               SETTYPE(PAA,  NODEARGM);
            }//if(GETNODEARG(PAA)!=NULL)
            else
            {               
               SETTYPE(PAA,  NOT_TYPE);
            }//End::else::if(GETNODEARG(PAA)!=NULL)
         }//if(GETTYPE(PAA)==FRAMECONST)
         else
         {
            Variable = (int *)malloc(sizeof(int));
            Var = (int *)malloc(sizeof(int));
            
            //PAA contiene una variable que debe ser guardada en memoria      
            NodeArgPAA = GETNODEARG(PAA);
            
            Var = GETDATA_ARG(NodeArgPAA);
            Type = (int)GETTYPE_ARG(NodeArgPAA);
            
            *Variable = *Var;
            memcpy(Variable, Var, sizeof(int));
            //printf("Var [%d], Type [%d]\n",*Variable, Type);
            
            NODELIST(NodeTempList, Variable);
            
            if(Type == VAR)
            {
               //printf("POP para PVA\n");
               SETNEXT(NodeTempList, PVA);
               PVA = NodeTempList;
               
               //PRINT_NODELIST(PVA);
               //printf("\n");
            }//if(Type == VAR)
            else
            {
               //printf("POP para PMA\n");
               SETNEXT(NodeTempList, PMA);
               PMA = NodeTempList;
               
               //PRINT_NODELIST(PMA);
               //printf("\n");
            }//End::Else::if(Type == VAR)

            if(ISVALIDNEXT_ARG(NodeArgPAA)!=NULL)
            {            
               //printf("if(ISVALIDNEXT_ARG(NodeTempArg)!=NULL)\n");
               
               GETNEXT_ARG(NodeArgPAA, NodeTempArg);
               SETNODEARG(PAA, NodeTempArg);               
               SETTYPE(PAA,  NODEARGM);
            }//if(ISVALIDNEXT_ARG(NodeTempArg)!=NULL)
            else
            {
               //printf("else::if(GETNEXT_ARG(NodeTempArg)!=NULL)\n");
               FREE_MEMORY_NODE_ARG(GETNODEARG(PAA));
               if(GETFRAMECONST(PAA)==NULL)
               {
                  //Longitud = 0;
                  //LENGTH_ARG(GETNODEARG(PAA), Longitud);            
                  //printf("Longitud [%d]\n", Longitud);            

                  //printf("PAA quedo NOT_TYPE\n");
                  SETTYPE(PAA,  NOT_TYPE);  
                }
            }//End::else::if(GETNEXT_ARG(NodeTempArg)!=NULL)
            
            Var = NULL;
            free(Var);
            
         }//End::else::if(GETTYPE(PAA)==FRAMECONST)
   
         //Incrementar el PCA para la siguiente instruccion
         PCA = PCA + 1;         
         
         //Asignacion de los nuevos valores
         setPC(Proc, PCA);
         setPA(Proc, PAA);
         setPM(Proc, PMA);
         setPV(Proc, PVA);    
         
   }
   else
   {
      //printf("POP Error");
      int *Finish;
      Finish = (int *)malloc(sizeof(int));
      *Finish = OK;
   
      argv = setAtVblePlugIn(argv,Finish,0);
   }
   
   //Se guardan las variables en la lista de vbles de los PlugIn's
   argv = setAtVblePlugIn(argv,Proc,1);
   //printf("End POP\n");
   
   //Retorno de los argumentos
   return argv;

}//POP


/**
 * PUSHV
 */
Parameters PUSHV(Parameters argv)
{
  //Registro que se necesita de MAPiCO
  int    PCA;                      //Puntero a Codigo Actual
  NodeList PVA;                    //Puntero a Variables Actual
  Auxiliar PAA;                    //Puntero a Argumentos
  Auxiliar PAUX;                    //Puntero auxiliar

  //Vbles para definir procesos
  Proceso Proc;

  //Vble para el Program Byte
  Program Data;

  //Vble para guardar el parametro
  NodeArg NodeTempArg;

  //Otras Variables
  int Longitud=0;
  int *VariableTemp;
  int *Variable;
  int ArgumentoPushv;
  NodeArg FPAUX;

  //printf("Begin PUSHV.\n");

  //Recuperacion del primer parametro (Proceso)
  Proc = getAtVblePlugIn(argv,1);

  //Recuperacion del tercer parametro (Data)
  Data = getAtVblePlugIn(argv,3); 

  //Se recuperan los valores de los registros
  PCA = getPC(Proc);
  PVA = getPV(Proc);
  PAA = getPA(Proc);
    
  Variable = (int *)malloc(sizeof(int));  
  VariableTemp = (int *)malloc(sizeof(int));  
  LENGTH(PVA, Longitud);
  ArgumentoPushv = get16(Data, PCA+1);
  
  //printf("Longitud PVA [%d]\n", Longitud);
  //printf("PUSHV %d\n", ArgumentoPushv);

  if(Longitud >= ArgumentoPushv)
  {
     //Valor de Variable de la lista del PV    
     GETDATAAT(PVA, ArgumentoPushv, VariableTemp);      
     memcpy(Variable, VariableTemp, sizeof(int));
     //printf("PUSHV %d =  [%d]\n", *VariableTemp, *Variable);
  
     NODEARG(NodeTempArg, Variable, VAR);
          
     if(GETTYPE(PAA)==NOT_TYPE)
     {
        //printf("if(GETTYPE(PAA)==NOT_TYPE)\n");
         //Salvar los argumentos en PAA
         SETNODEARG(PAA, NodeTempArg); 
         SETTYPE(PAA, NODEARGM);
      }//if(GETTYPE(PAA)==NOT_TYPE)
      else
      {
         //printf("elseif(GETTYPE(PAA)==NOT_TYPE)\n");
         //Concatener el nuevo argumentos con los ya existentes
         FPAUX = GETNODEARG(PAA);
                 
         SETNEXT_ARG(NodeTempArg, FPAUX);  
                  
         SETNODEARG(PAA, NodeTempArg);                  
         SETTYPE(PAA, NODEARGM);
      }//End::else::if(PAA==NULL)
      
      //PRINT_NODE_ARG(GETNODEARG(PAA));

    //Incrementar el PCA para la siguiente instruccion
    PCA = PCA + 3; // 3 = 1 + 2;

    //Asignacion de los nuevos valores
    setPC(Proc, PCA);
    setPA(Proc, PAA);

  }//if(Longitud >= Variable)
  else
  {
    //printf("PUSHV Error");
    int *Finish;
    Finish = (int *)malloc(sizeof(int));
    *Finish = OK;

    argv = setAtVblePlugIn(argv,Finish,0);
  }

  //Se guardan las variables en la lista de vbles de los PlugIn's
  argv = setAtVblePlugIn(argv,Proc,1);
    
  //printf("End PUSHV\n");
  
  //Retorno de los argumentos
  return argv;

}//PUSHV


/**
 * PUSHM
 */
Parameters PUSHM(Parameters argv)
{
  //Registro que se necesita de MAPiCO
  int    PCA;                      //Puntero a Codigo Actual
  NodeList PVA;                    //Puntero a Variables Actual
  Auxiliar PAA;                    //Puntero a Argumentos
  NodeArg FPAUX;                   //Puntero auxiliar

  //Vbles para definir procesos
  Proceso Proc;

  //Vble para el Program Byte
  Program Data;

  //Vble para guardar el parametro
  NodeArg NodeTempArg;

  //Otras Variables
  int *Metodo;

  //printf("Begin PUSHM.\n");

  //Recuperacion del primer parametro (Proceso)
  Proc = getAtVblePlugIn(argv,1);

  //Recuperacion del tercer parametro (Data)
  Data = getAtVblePlugIn(argv,3); 

  //Se recuperan los valores de los registros
  PCA = getPC(Proc);
  PVA = getPV(Proc);
  PAA = getPA(Proc);
  
  Metodo = (int *)malloc(sizeof(int));
  
  *Metodo = get16(Data, PCA+1);
  //printf("Metodo [%d]\n", *Metodo);
  
   //Creacion del nuevo argumento de tipo METODO
   NODEARG(NodeTempArg, Metodo, METH);
      
   if(GETTYPE(PAA)==NOT_TYPE)
   {
      //printf("GETTYPE(PAA)!=NOT_TYPE\n");               
      
      //Salvar los argumentos en PAA
      SETNODEARG(PAA, NodeTempArg);         
      SETTYPE(PAA, NODEARGM);
   }//if(GETTYPE(PAA)!=NOT_TYPE)
   else
   {
      //printf("else GETTYPE(PAA)!=NOT_TYPE\n");               
      //Concatener el nuevo argumentos con los ya existentes
      FPAUX = GETNODEARG(PAA);
               
      SETNEXT_ARG(NodeTempArg, FPAUX);         
      
      SETNODEARG(PAA, NodeTempArg);
      SETTYPE(PAA, NODEARGM);
   }//End::else::if(PAA==NULL)
   
   //PRINT_NODE_ARG(GETNODEARG(PAA));
   
   //Incrementar el PCA para la siguiente instruccion
   PCA = PCA + 3; // 3 = 1 + 2;
   
   //Asignacion de los nuevos valores
   setPC(Proc, PCA);
   setPA(Proc, PAA);

  //Se guardan las variables en la lista de vbles de los PlugIn's
  argv = setAtVblePlugIn(argv,Proc,1);
  //printf("End PUSHM\n");

  //Retorno de los argumentos
  return argv;

}//PUSHM 

/**
 * RET
 */
Parameters RET(Parameters argv)
{
  //Registro que se necesita de MAPiCO
  int    PCA;                      //Puntero a Codigo Actual
  NodeList PVA;              //Puntero a Variables Actual
  NodeList PMA;             //Puntero a Metodos Actual
  Auxiliar PAA;                //Puntero Auxiliar Actual
  NodeList POA;              //Puntero a Objetos Actual
  void *PAUX;                 //Puntero Auxiliar
  void *PTEMP;               //Puntero Temporal

  //Declaracion de colas
  List RunQ;            //Cola de Ejecucion
  List MsgQ;            //Cola de Mensajes  
  List AskQ;           //Cola de Preguntas

  //Vbles para definir procesos
  Proceso Proc;
  Proceso FirstProcRunQ = initProceso();
  
  StoreMA sMA;      
  
  //Vble para elemento de RunQ
  NodeList RunQ_First_Element;
  //printf("Begin RET.\n");

  //Recuperacion del primer parametro (Proceso)
  Proc = getAtVblePlugIn(argv,1);

  //Recuperacion de la cola de ejecucion (RunQ)
  RunQ = getAtVblePlugIn(argv,4);
  
  //Recuperacion de la cola de Mensajes (MsgQ)
  MsgQ = getAtVblePlugIn(argv,6);
  
   //Recuperacion de la cola de preguntas
   AskQ = getAtVblePlugIn(argv,7);
   
   //Recuperacion del storeMA
   sMA = getStoreMA(argv);
   
   //printf("LENGTH_LIST antes de hacer RET (RunQ)=[%d]\n", LENGTH_LIST(RunQ));
   //PRINT_LIST(RunQ);
  
   //Se reactivan los mensajes
   if( LENGTH_LIST(RunQ)>0 )
   {
      //Se captura el primer elemento de la cola de Ejecucion
      FirstProcRunQ = GETDATA(FIRST_NODE(RunQ));         
          
      //De RunQ se elimina el primer elemento
      DEL_FIRST_NODE(RunQ);
      
      //Se guardan las variables en la lista de vbles de los PlugIn's
      argv = setAtVblePlugIn(argv,FirstProcRunQ,1);
      argv = setAtVblePlugIn(argv,RunQ,4);           
   }
   else
   {
         //printf("else de if LENGTH_LIST(RunQ)>0\n");
   
         if( LENGTH_LIST(MsgQ)>0 )
         {
            //printf("if LENGTH_LIST(MsgQ)>0\n");
            ADD_AT_END(RunQ,MsgQ); 
            FREE_LIST(MsgQ);     
         }
         else
         {
            //printf("else de if LENGTH_LIST(MsgQ)>0\n");
            if( LENGTH_LIST(AskQ)>0 )
            {
               //printf("if LENGTH_LIST(AskQ)>0\n");
               ADD_AT_END(RunQ,AskQ);      
               FREE_LIST(AskQ);
            }         
            else
            {
               //printf("else de if LENGTH_LIST(AskQ)>0\n");
               //ImprimirStore(sMA->s);   
               int *Finish;  
               Finish = (int *)malloc(sizeof(int));
               *Finish = OK;                 
               argv = setAtVblePlugIn(argv,Finish,0);
            }//End::else::if( LENGTH_LIST(AskQ)>0 )
         }//End::else::if( LENGTH_LIST(MsgQ)>0 )
     }//End::else::if( LENGTH_LIST(RunQ)>0 )
  
  //printf("LENGTH_LIST despues de hacer RET (RunQ)=[%d]\n", LENGTH_LIST(RunQ));
  //PRINT_LIST(RunQ);    
    
  //printf("End RET\n");

  //Retorno de los argumentos
  return argv;

}//RET


/**
 * COBJCC
 */
Parameters COBJCC(Parameters argv)
{
  //Registros que se necesitan de MAPiCO
  int    PCA;           //Program Counter
  NodeList PVA;   //Program Variable
  Auxiliar PAA;
  Auxiliar PAUX;

  //Declaracion de colas
  List RunQ;          //Cola de Ejecucion
  List ObjQ;           //Cola de Objetos
  List MsgQ;         //Cola de Mensajes

  //Vble para el Program Byte
  Program Data;

  //Vble para definir procesos
  Proceso Proc;
  Proceso ProcObjCC;
  
  //Vble para definir la funcion generica
  Parameters (*Instruction)(Parameters); //Funcion de la instruccion

  //printf("Begin COBJCC.\n");

  //Recuperacion del primer parametro (Proceso)
  Proc = getAtVblePlugIn(argv,1);

  //Recuperacion del tercer parametro (Data)
  Data = getAtVblePlugIn(argv,3); 

  //Recuperacion de la cola de ejecucion (RunQ)
  RunQ = getAtVblePlugIn(argv,4);

  //Recuperacion de la cola de Objetos (ObjQ)
  ObjQ = getAtVblePlugIn(argv,5);

  //Recuperacion de la cola de Mensajes (MsgQ)
  MsgQ = getAtVblePlugIn(argv,6);

  //Se recuperan los valores de los registros
  PCA = getPC(Proc);
  PVA = getPV(Proc);
  PAA  = getPA(Proc);
  PAUX = getPAUX(Proc);  
  
  //printf("PCA->[%d]\n",PCA);
  
  ProcObjCC = newProceso(PCA, PVA, NULL, PAA, NULL, PAUX, NULL);
  
  /*
  //printf("1 RunQ ------------------------------\n");
  PRINT_LIST(RunQ);
  //printf(" ObjQ ------------------------------\n");
  PRINT_LIST(ObjQ); 
  //printf(" MsgQ ------------------------------\n");
  PRINT_LIST(MsgQ); 
  //printf("------------------------------\n");    
  */
  
  INSERT_AT_END(ObjQ, ProcObjCC);

  /*
  //printf("2 RunQ ------------------------------\n");
  PRINT_LIST(RunQ);     
  //printf(" ObjQ ------------------------------\n");
  PRINT_LIST(ObjQ);    
  //printf(" MsgQ ------------------------------\n");
  PRINT_LIST(MsgQ); 
  //printf("------------------------------\n");
  */
  
      
  if( LENGTH_LIST(MsgQ)>0 )
  {
      ADD_AT_END(RunQ,MsgQ);
      FREE_LIST(MsgQ);
  }
 
  //Incrementar el PCA para la siguiente instruccion
  PCA = PCA + 10;  // 10 = 1 + 4 + 4 + 1;
  
  //Asignacion de los nuevos valores
  setPC(Proc, PCA);

  //Se guardan las variables en la lista de vbles de los PlugIn's
  argv = setAtVblePlugIn(argv,Proc,1);
  argv = setAtVblePlugIn(argv,RunQ,4);
  argv = setAtVblePlugIn(argv,ObjQ,5);
  argv = setAtVblePlugIn(argv,MsgQ,6);

  //printf("End COBJCC\n");

  //Se busca la instruccion encargada de realizar el schedule
  Instruction = getInstruction(argv, getOpCodeSchedule(argv));

  //Ejecucion de la instruccion
  argv = Instruction(argv);

  //Retorno de los argumentos
  return argv;

}//COBJCC

/**
 * OBJCC
 */
Parameters OBJCC(Parameters argv)
{
  //Registros que se necesitan de MAPiCO
  int    PCA;           //Program Counter
  NodeList PVA;   //Program Variable
  Auxiliar PAA;
  Auxiliar PAUX;

  //Declaracion de colas
  List RunQ;           //Cola de Ejecucion
  List ObjQ;            //Cola de Objetos
  List MsgQ;          //Cola de Mensajes

  //Vble para el Program Byte
  Program Data;

  //VbleS para definir procesos
  Proceso Proc;
  Proceso ProcObjCC;
  
  //Vble para definir la funcion generica
  Parameters (*Instruction)(Parameters); //Funcion de la instruccion

  //printf("Begin OBJCC.\n");

  //Recuperacion del primer parametro (Proceso)
  Proc = getAtVblePlugIn(argv,1);

  //Recuperacion del tercer parametro (Data)
  Data = getAtVblePlugIn(argv,3); 

  //Recuperacion de la cola de ejecucion (RunQ)
  RunQ = getAtVblePlugIn(argv,4);

  //Recuperacion de la cola de Objetos (ObjQ)
  ObjQ = getAtVblePlugIn(argv,5);

  //Recuperacion de la cola de Mensajes (MsgQ)
  MsgQ = getAtVblePlugIn(argv,6);

  //Se recuperan los valores de los registros
  PCA = getPC(Proc);
  PVA = getPV(Proc);
  PAA  = getPA(Proc);
  PAUX = getPAUX(Proc);
  
  ProcObjCC =  newProceso(PCA, PVA, NULL, PAA, NULL, PAUX, NULL);
  INSERT_AT_END(ObjQ, ProcObjCC);

  if( LENGTH_LIST(MsgQ)>0 )
    {
      ADD_AT_END(RunQ,MsgQ);
      FREE_LIST(MsgQ);
    }

  //Incrementar el PCA para la siguiente instruccion
  PCA = PCA + 10;  // 10 = 1 + 4 + 4 + 1;

  //Asignacion de los nuevos valores
  setPC(Proc, PCA);

  //Se guardan las variables en la lista de vbles de los PlugIn's
  argv = setAtVblePlugIn(argv,Proc,1);
  argv = setAtVblePlugIn(argv,RunQ,4);
  argv = setAtVblePlugIn(argv,ObjQ,5);
  argv = setAtVblePlugIn(argv,MsgQ,6);

  //printf("End OBJCC\n");

  //Se busca la instruccion encargada de realizar el schedule
  Instruction = getInstruction(argv, getOpCodeSchedule(argv));

  //Ejecucion de la instruccion
  argv = Instruction(argv);

  //Retorno de los argumentos
  return argv;  

}//OBJCC


/**
 * ValidType_PAA
 */
Parameters ValidType_PAA(Parameters argv, Auxiliar PAA)
{
   if(GETTYPE(PAA)!=NOT_TYPE)
   {      
      
      if(GETTYPE(PAA)!=NODEARGM && GETTYPE(PAA)!=NOT_TYPE)
      {
         int *Finish;
         char MensajeError[100];
         
         sprintf(MensajeError, "Error en el tipo de PAA->[%d]", GETTYPE(PAA));
         argv = setError(argv, MensajeError);      
         Finish = (int *)malloc(sizeof(int));
         *Finish = OK;            
         argv = setAtVblePlugIn(argv,Finish,0);
         argv = setResponse(argv, ERROR);
         return argv;   
      }//if(GETTYPE(PAA)!=NODEARGM && GETTYPE(PAA)!=NOT_TYPE) 
      
   }//if(GETTYPE(PAA)!=NOT_TYPE)
      
   argv = setResponse(argv, OK);
   return argv;
      
}//ValidType_PAA

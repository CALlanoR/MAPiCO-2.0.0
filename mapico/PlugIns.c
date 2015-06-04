#include "PlugIns.h"

Parameters loadInstructions(Parameters argv, char **Functions, char *PathLibrary, void *Handle, int NumPlugIn)
{
   //Variables para agregar las funciones del PlugIn
   int i, Longitud, opCode_int, PosDosPuntos;
   //char *opCode_str, *NameFunction; 
   char opCode_str[10];
   char NameFunction[20];
   i=0;        
            
   //Se agregan cada una de las funciones que tenga esta libreria 
   while(Functions[i]!=NULL)
   {      
      Longitud = strlen(Functions[i]);
   
      //Posicion donde se encuentra el separador ":"
      PosDosPuntos = strcspn(Functions[i],":");
      
      //opCode_str = (char *)malloc(sizeof(char)*PosDosPuntos);
      //NameFunction  = (char *)malloc(sizeof(char)* (Longitud - PosDosPuntos));
      
      //memset(opCode_str, '\0', strlen(opCode_str));
      //memset(NameFunction, '\0', strlen(NameFunction));
      
      //memset(opCode_str, '\0', 10);
      //memset(NameFunction, '\0', 20);      
      
      strncpy(opCode_str, Functions[i], PosDosPuntos);
      strncpy(NameFunction, (Functions[i] + PosDosPuntos + 1), (Longitud - PosDosPuntos));
   
      //printf("opCode_str [%s], NameFunction [%s]\n",opCode_str, NameFunction);
   
      opCode_int = atoi(opCode_str);
   
      //Se verifica que el opCode no este duplicado
      if(isInstruction(argv,opCode_int)==NOEXIST)
      {
         //Guarda la informacion necesaria para el PlugIn
         argv = setNameFunction(argv,NameFunction,NumPlugIn,opCode_int);
         argv = setPathLibrary(argv,PathLibrary,NumPlugIn);
         argv = setHandle(argv,Handle,NumPlugIn);
      }
      else
      {
         argv = setResponse(argv,ERROR);
         argv = setError(argv,INSTRUCTION_DUPLICATE);
      }
   
      //free(opCode_str);
      //free(NameFunction);
      
      i++;
                           
   }//while
   
   return argv;
      
}//loadInstructions

Parameters loadPlugIns(Parameters argv, char *PathPlugInList)
{
   FILE *FileConfig;
   void *Handle;
   char *Error;
   char PathLibrary[MAX_PATH];
   int TamPathLibrary, NumPlugIn;
   
   Parameters (*Catalogue)(Parameters argv, char *PathLibrary, void *Handle, int NumPlugIn);   
   
   NumPlugIn=0;

   //Abrir archivo de configuracion
   if((FileConfig=fopen(PathPlugInList,"r"))==NULL)
   {
     printf("Carga de PlugIns. [ERROR]: No se pudo cargar el abrir el Archivo de PlugIns\n");
     exit(1);      
   }
   
   //printf("PathPlugInList [%s]\n", PathPlugInList);
   
   //printf("Proceso de Carga de PlugIns\n");
   
   while(!feof(FileConfig))
   {
      //Se leen cada uno de los nombres de los PlugIns
      fgets(PathLibrary,MAX_PATH,FileConfig); 
   
      if(PathLibrary[0]!='#')
      {
         //Se Elimina el salto de linea del nombre
         TamPathLibrary = strlen(PathLibrary);
   
         //PathLibrary[TamPathLibrary]='\0';
         if(iscntrl(PathLibrary[TamPathLibrary-1]))
            PathLibrary[TamPathLibrary-1]='\0';
         else
            PathLibrary[TamPathLibrary]='\0';
   
         //Se abre el archivo que contiene el path de cada PlugIn
         Handle = dlopen(PathLibrary, RTLD_LAZY);
   
         //Se chequea si ocurrio algun error
         Error = dlerror();
         
         if(Error)
         {
            argv = setResponse(argv,ERROR);
            argv = setError(argv,NOT_OPEN_LIBRARY);
            
            fclose(FileConfig);
            return argv;
         }
         
         //Se captura la funcion Catalogue de la libreria
         Catalogue = dlsym(Handle,"Catalogue");
            
         //Se chequea si encontro la funcion "Catalogue"
         Error = dlerror ();
         
         if(Error)
         {
            argv = setResponse(argv,ERROR);
            argv = setError(argv,NOT_CATALOGUE);
            fclose(FileConfig);
            return argv;                 
         }
         
         NumPlugIn++;
         
         //printf("Catalogue(%s,%d)\n", PathLibrary, NumPlugIn);
         
         argv = Catalogue(argv,PathLibrary,Handle,NumPlugIn);
         
         /*
         if(getResponse(argv)!=ERROR)
            printf("Cargue de %s [OK]\n", PathLibrary);
         else
            printf("Cargue de %s [FAILED]\n", PathLibrary);
         */
   
      }//if(PathLibrary[0]!='#')
               
   }//End::while(!feof(FileConfig))

   /*
   //Prueba de funcionamiento de los PlugIn's
   for(int i=0;i<MAX_INSTRUCTIONS;i++)
     {
       printf("[Instruction %d]->[IndexPlugIn %d]\n",i,argv.Instructions[i].IndexPlugIn);
       printf("[Instruction %d]->[NameFunction %s]\n\n",i,argv.Instructions[i].NameFunction);       
     }

   for(int i=0;i<MAX_OPEN_PLUGINS;i++)
     {
       printf("[PlugIn %d]->[PathLibrary %s]\n",i,argv.PlugIns[i].PathLibrary);
     }

   printf("\n\nNumPlugInsLoad:[%d]\n",argv.NumPlugInsLoad);
   */

   fclose(FileConfig);

   return argv;

}//loadPlugIns


void* getInstruction(Parameters argv, int NumInstruction)
{
  void (*Instruc)(Parameters argv);
  char *Error;

  Instruction instruccion = searchInstruction(argv, NumInstruction);
  
  //Captura FunctionName de la libreria  
  Instruc = dlsym(getHandle(argv, getIndexPlugInByInstruction(argv, instruccion)), getNameFunctionByInstruction(argv, instruccion)); 
      
  Error = dlerror ();
  //Cheque si hubo error al encontrar la funcion
  if(Error)
    {
      setResponse(argv,ERROR);
      setError(argv,NOT_FUNCTION);
    }
  else
    {
      setResponse(argv,NOERROR);
    }

  return Instruc;

}//getInstruction


void closePlugIns(Parameters argv)
{
  int Resultado, NumPlugInsLoad, i;

  NumPlugInsLoad = getNumPlugInsLoad(argv);

  for(i=1;i<NumPlugInsLoad;i++)
    {
      Resultado = dlclose(getHandle(argv,i));

      if(Resultado!=0)
   {
     setResponse(argv,ERROR);
     setError(argv,CLOSE_ERROR);
   }
      else
   {
     setResponse(argv,NOERROR);
   }
    }//for(i=1;i<NumPlugInsLoad;i++)

  //Libera la memoria ocupada por los PlugIns
  freeParameters(argv);

}//closeLibrary


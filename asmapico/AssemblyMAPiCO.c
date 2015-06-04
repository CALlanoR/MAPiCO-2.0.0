////////////////////////
//// Librerias ////
////////////////////////
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <dlfcn.h>
#include <string.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

/////////////////////////////
////  Constantes ////
/////////////////////////////
#define MAXTAMLINEA    100
#define NUMLINEAS      500
#define TAMOPCODE        1
#define TAMXPATH       100
#define CONSTANTE        1
#define DIRECCION        2
#define PREDICADO        3

//////////////////////////////////////////////////////
//// Prototipos de las funciones /////
//////////////////////////////////////////////////////
int GetSumBytes(char *Instruction, xmlXPathContextPtr xpathCtx, xmlDocPtr doc);
int GetTamBytesParam(char *Instruction, xmlXPathContextPtr xpathCtx, xmlDocPtr doc, int numParam);
int GetOpCodeInstruction(char *Instruction, xmlXPathContextPtr xpathCtx, xmlDocPtr doc);
int GetOpCodePredicate(char *Predicate, xmlXPathContextPtr xpathCtx, xmlDocPtr doc);
int GetTipoParam(char *Instruction, xmlXPathContextPtr xpathCtx, xmlDocPtr doc, int numParam);

//////////////////////////////////////
//// Funcion Principal ////
//////////////////////////////////////GetOpCodeInstruction
int main(int argc, char *argv[])
{   
   //////////////////////////////
   ////// Variables //////
   /////////////////////////////   
   FILE *fileIN;
   FILE *fileOUT;   
   char Linea[MAXTAMLINEA+1];
   char *Instruccion;
   char InstruccionTemp[10];
   int *OpCode;
   int *OpCodePredicate;
   int *Constante;
   int *DireccionXLinea;
   int *direccion;      
   int numLinea = 2;
   int sumParamBytes = 0;
   int numParam = 1;
   int i;
   int TamBytes;
   int ActivarLog = 0;
   xmlDocPtr doc;
   xmlXPathContextPtr xpathCtx; 

    ///////////////////////////////////////////////////////////////////////
    /// Validar numero correcto de parametros ///
   ////////////////////////////////////////////////////////////////////////    
   if(argc!=3)
   {
      printf("Para activar el rastreo usar:  asmapico filename.xml [0/1]   ( default=0 (No rastreo) / 1 (Rastreo completo) )\n");
      ActivarLog = 0;      
      //exit(1);
   }
   else
   {
      //Recupera la opcion de Rastreo del programa
      ActivarLog = atoi(argv[2]);      
   }

   //Abrir archivo de entrada
   if((fileIN=fopen(argv[1],"r"))==NULL)
   {
      printf("[ERROR]: No se pudo abrir el archivo %s\n", argv[1]);
      exit(1);      
   }
   
   //Abrir archivo de salida 
   if((fileOUT=fopen("FileInBytes.mapico","wb+"))==NULL)
   {
      fclose(fileIN);
      printf("[ERROR]: No se pudo abrir el archivo FileInBytes.mapico\n");
      exit(1);      
   }
          
   //////////////////////////////////////////////////////////
   ////// Cargar Configuracion XML //////
   /////////////////////////////////////////////////////////   
    xmlInitParser();  // Init libxml
    LIBXML_TEST_VERSION
                    
    // Load XML document
    doc = xmlParseFile("AssemblyMAPiCO.xml");
    if (doc == NULL) 
    {
      fprintf(stderr, "[ERROR]: No se pudo parsear el archivo AssemblyMAPiCO.xml\n");      
      xmlCleanupParser();  // Shutdown libxml       
      fclose(fileIN);
      fclose(fileOUT);
      exit(1);
    }   

    // Create xpath evaluation context
    xpathCtx = xmlXPathNewContext(doc);
    if(xpathCtx == NULL) 
    {
        fprintf(stderr,"[ERROR]: No se pudo crear el XPath context\n");
        xmlFreeDoc(doc); 
        xmlCleanupParser();  // Shutdown libxml               
        fclose(fileIN);
        fclose(fileOUT);        
        exit(1);
    }    
    
   //////////////////////////////////////////////
   ////// Inicializar Variables //////
   //////////////////////////////////////////////
   DireccionXLinea = (int *)malloc(sizeof(int)*NUMLINEAS); //Numero de lineas iniciales
   direccion = (int *)malloc(sizeof(int));
   OpCode = (int *)malloc(sizeof(int));
   OpCodePredicate = (int *)malloc(sizeof(int));
   Constante = (int *)malloc(sizeof(int)); 
   memset(DireccionXLinea,0,NUMLINEAS);      
   memset(Linea,'\0',MAXTAMLINEA+1);  //Inicializacion de la linea
   
   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /// Primera Pasada del Assembly - Calcular la direccion de cada linea del ProgramBytes - ///
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   printf("Primera Pasada del Assembly - Calculo de las direcciones de cada linea del ProgramBytes-\n");
    while(!feof(fileIN))    
    {
       fgets(Linea,MAXTAMLINEA,fileIN);
              
       Instruccion = strtok(Linea, " ");       
              
       if(iscntrl(Instruccion[strlen(Instruccion) -1]))
          Instruccion[strlen(Instruccion)-1]='\0';      
       
       if(ActivarLog)
          printf("[%s]\n", Instruccion);                   
              
       //Se calcula la suma de bytes de cada uno de los parametros de la instruccion - Si los tiene -
       sumParamBytes = GetSumBytes(Instruccion, xpathCtx, doc);
       
       if(ActivarLog)
          printf("sumParamBytes [%d]\n", sumParamBytes); //<-
       
       if(sumParamBytes==0)
       {
           fprintf(stderr,"[ERROR]: No se puedo evaluar el tamaño de bytes de la instruccion [%s]\n", Instruccion);
           xmlFreeDoc(doc); 
           fclose(fileIN);
           fclose(fileOUT);           
           xmlCleanupParser();  // Shutdown libxml
           free(DireccionXLinea);               
           exit(1);          
       }
       
       DireccionXLinea[numLinea] = DireccionXLinea[numLinea-1] + sumParamBytes; 
              
      numLinea++;             
    }//while(!feof
    
    if(ActivarLog)
    {
       for(i=1;i<numLinea;i++)
          printf("Linea[%d]=%d\n", i, DireccionXLinea[i]);    
    }
        
    fseek(fileIN,0,SEEK_SET);
    
   //Inicializacion de la linea
   memset(Linea,'\0',MAXTAMLINEA+1);              
    
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /// Segunda Pasada del Assembly - Cambiar los nombres por sus OpCodes correspondientes - ///
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   printf("Segunda Pasada del Assembly - Cambiar los nombres por sus OpCodes correspondientes-\n");   
    while(!feof(fileIN))    
    {
       //memset(OpCode,'\0', TAMOPCODE);
       fgets(Linea,MAXTAMLINEA,fileIN);
              
       Instruccion = strtok(Linea, " ");       
                     
       if(iscntrl(Instruccion[strlen(Instruccion) -1])) //Instruccion sin parametros
       {             
          Instruccion[strlen(Instruccion)-1]='\0';      
          
          if(ActivarLog)
             printf("Instruccion sin parametros [%s]\n", Instruccion);

          //Consulta el OpCode de la instruccion del XML
          *OpCode = GetOpCodeInstruction(Instruccion, xpathCtx,doc);   
          
          //Escribe la instruccion en bytes                 
          fwrite( OpCode, sizeof(char), 1 , fileOUT );
          
          if(ActivarLog)
             printf("Instruccion %s OpCode [%d]\n", Instruccion, *OpCode);
       }
       else  //Instruccion con parametros
       {
          if(ActivarLog)
             printf("Instruccion con parametros [%s]\t", Instruccion);          
          
          memset(InstruccionTemp, '\0',10);
          memcpy(InstruccionTemp, Instruccion, 10);
          
          //Consulta el OpCode de la instruccion del XML
          *OpCode = GetOpCodeInstruction(Instruccion, xpathCtx,doc);                    
          
          //Escribe la instruccion en bytes          
          fwrite( OpCode, sizeof(char), 1 , fileOUT );
          
          if(ActivarLog)
             printf("Instruccion %s OpCode [%d]\n", InstruccionTemp, *OpCode);          
         
          numParam = 1;
          
          do
          {
             Instruccion = strtok('\0', " ");
                          
             if(Instruccion)
             {
                if(iscntrl(Instruccion[strlen(Instruccion) -1]))
                {
                   Instruccion[strlen(Instruccion)-1]='\0'; 
                }             
             
                if(ActivarLog)
                   printf("Parametro%d : [%s]\n", numParam, Instruccion);                
                
                switch(GetTipoParam(InstruccionTemp, xpathCtx, doc, numParam))
                {
                   case CONSTANTE:
                      
                      if(ActivarLog)
                         printf("entro a CONSTANTE\n");
                      
                      TamBytes = GetTamBytesParam(InstruccionTemp, xpathCtx, doc, numParam);
                       *Constante = atoi(Instruccion);
                       
                       switch(TamBytes)
                       {
                          case 8:
                             fwrite( Constante, sizeof(char), 1 , fileOUT );
                             break;
                          case 16:
                             fwrite( Constante, sizeof(short int), 1 , fileOUT );
                             break;
                          case 32:
                             fwrite( Constante, sizeof(int), 1 , fileOUT );
                             break;                             
                       }                       
                      break;
                      
                   case DIRECCION:
                      
                      if(ActivarLog)
                         printf("entro a DIRECCION\n");
                      
                      TamBytes = GetTamBytesParam(InstruccionTemp, xpathCtx, doc, numParam);
                      
                      if(ActivarLog)
                         printf("TamBytes [%d]\n", TamBytes);
                      *direccion = DireccionXLinea[atoi(Instruccion)];
                      
                      if(ActivarLog)
                         printf("direccion [%d]\n", *direccion);
                      
                       switch(TamBytes)
                       {
                          case 8:
                             fwrite( direccion, sizeof(char), 1 , fileOUT );
                             break;
                          case 16:
                             fwrite( direccion, sizeof(short int), 1 , fileOUT );
                             break;
                          case 32:
                             fwrite( direccion, sizeof(int), 1 , fileOUT );
                             break;                             
                       }                                            
                      break;
                      
                   case PREDICADO:
                      
                      if(ActivarLog)
                         printf("entro a PREDICADO\n");
                      
                      memset(OpCodePredicate,'\0', TAMOPCODE);
                      TamBytes = GetTamBytesParam(InstruccionTemp, xpathCtx, doc, numParam);
                      *OpCodePredicate = GetOpCodePredicate(Instruccion, xpathCtx, doc);                      
                       switch(TamBytes)
                       {
                          case 8:
                             fwrite( OpCodePredicate, sizeof(char), 1 , fileOUT );
                             break;
                          case 16:
                             fwrite( OpCodePredicate, sizeof(short int), 1 , fileOUT );
                             break;
                          case 32:
                             fwrite( OpCodePredicate, sizeof(int), 1 , fileOUT );
                             break;                             
                       }                                              
                      break;
                      
                   default:
                     fprintf(stderr,"[ERROR]: No se puedo evaluar el tamaño de bytes de la instruccion [%s]\n", Instruccion);
                     xmlFreeDoc(doc); 
                     fclose(fileIN);
                     fclose(fileOUT);           
                     xmlCleanupParser();  // Shutdown libxml
                     free(DireccionXLinea);               
                     exit(1);                                                   
                }
                
                numParam++;
             }
          }while(Instruccion);         
       }//else
       //printf("\n");       
    }//while(!feof    
            
    //////////////////////////////////
    /// Liberar recursos ///
    //////////////////////////////////
        
    //Cerrar Archivos
    fclose(fileIN);
    fclose(fileOUT);
    
    //Liberar memoria
    free(DireccionXLinea);
    free(OpCode);
    free(OpCodePredicate);
    free(Constante);
    
    // Shutdown libxml 
    xmlCleanupParser();   
    
    // this is to debug memory for regression tests
    xmlMemoryDump();     
      
}//main

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Funciones para la extraccion de la informacion del archivo de configuracion XML ////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Funcion que se encarga de extraer el tipo del parametro i
int GetTipoParam(char *Instruction, xmlXPathContextPtr xpathCtx, xmlDocPtr doc, int numParam)
{
   xmlXPathObjectPtr xpathObj;   
   xmlNodePtr cur;
   xmlChar *uri; 
   int Tipo=0;   
   char xpathExpr[TAMXPATH];
    
   //Construccion del XPath
   memset(xpathExpr,'\0',TAMXPATH);
   sprintf(xpathExpr, "//Configuration/Instructions/%s/Params/Param%d", Instruction, numParam);
   
   //printf("xpathExpr en GetTipoParam [%s]\n", xpathExpr);
   
   // Evaluar xpath expression
   xpathObj = xmlXPathEvalExpression(xpathExpr, xpathCtx);
   
   cur = xpathObj->nodesetval->nodeTab[0];       
   uri = xmlGetProp(cur, "Tipo");
   
   if(strcmp(uri,"C")==0)
      Tipo =  CONSTANTE;
   else if(strcmp(uri,"D")==0)
      Tipo = DIRECCION;
   else if(strcmp(uri,"P")==0)
      Tipo = PREDICADO;
   
    xmlFree(uri);
    return Tipo;          
   
}//GetTipoParam

//Funcion que se encarga de extraer el tamaño en bytes del parametro i
int GetTamBytesParam(char *Instruction, xmlXPathContextPtr xpathCtx, xmlDocPtr doc, int numParam)
{
   xmlXPathObjectPtr xpathObj;      
   xmlNodePtr cur;
   xmlChar *uri;    
   int TamBytes;
   char xpathExpr[TAMXPATH];
    
   //Construccion del XPath
   memset(xpathExpr,'\0',TAMXPATH);
   sprintf(xpathExpr, "//Configuration/Instructions/%s/Params/Param%d", Instruction, numParam);
   
   //printf("xpathExpr en GetTamBytesParam [%s]\n", xpathExpr);
   
   // Evaluar xpath expression
   xpathObj = xmlXPathEvalExpression(xpathExpr, xpathCtx);
      
   cur = xpathObj->nodesetval->nodeTab[0];       
   uri = xmlGetProp(cur, "TamBytes");
   TamBytes = atoi(uri);
   xmlFree(uri);     
   return TamBytes;                  
   
}//GetTamBytesParam

//Funcion que se encarga de retornar el OpCode de una instruccion
int GetOpCodeInstruction(char *Instruction, xmlXPathContextPtr xpathCtx, xmlDocPtr doc)
{
   xmlXPathObjectPtr xpathObj;   
   xmlNodePtr cur;
   xmlChar *uri;    
   int OpCode;
   char xpathExpr[TAMXPATH];
      
   //Construccion del XPath
   memset(xpathExpr,'\0',TAMXPATH);
   sprintf(xpathExpr, "//Configuration/Instructions/%s", Instruction);
   
   // Evaluar xpath expression
   xpathObj = xmlXPathEvalExpression(xpathExpr, xpathCtx);
    
   cur = xpathObj->nodesetval->nodeTab[0];       
   uri = xmlGetProp(cur, "OpCode");
   //printf("OpCode in char [%s]\n", uri);
   OpCode = atoi(uri);
   //printf("OpCode in int [%d]\n", OpCode);   
   xmlFree(uri);     
   return OpCode;
    
}//GetOpCodeInstruction

//Funcion que se encarga de retornar el Code de un predicado
int GetOpCodePredicate(char *Predicate, xmlXPathContextPtr xpathCtx, xmlDocPtr doc)
{
    xmlXPathObjectPtr xpathObj;   
    xmlNodePtr cur;
    xmlChar *uri;    
    int OpCodePredicate;
    char xpathExpr[TAMXPATH];
    
    //Construccion del XPath
    memset(xpathExpr,'\0',TAMXPATH);
    sprintf(xpathExpr, "//Configuration/Predicates/%s", Predicate);
    
    //printf("xpathExpr en GetOpCodePredicate [%s]\n", xpathExpr);
           
    // Evaluar xpath expression
    xpathObj = xmlXPathEvalExpression(xpathExpr, xpathCtx);
    cur = xpathObj->nodesetval->nodeTab[0];       
    uri = xmlGetProp(cur, "Code");
    OpCodePredicate = atoi(uri);
    //sprintf(OpCodePredicate, "%s", uri);
    xmlFree(uri);     
    return OpCodePredicate;
}//GetOpCodePredicate

//Funcion que se encarga de retornar la suma de bytes de los parametros de una instruccion
int GetSumBytes(char *Instruction, xmlXPathContextPtr xpathCtx, xmlDocPtr doc)
{
    xmlXPathObjectPtr xpathObj;   
    xmlNodePtr cur;
    xmlChar *uri;    
    char xpathExpr[TAMXPATH];
    int size;
    int NumParams;
    int i;
    int sumBytes = TAMOPCODE;
        
    //Construccion del XPath para averiguar el numero de parametros
    memset(xpathExpr,'\0',TAMXPATH);
    sprintf(xpathExpr, "//Configuration/Instructions/%s", Instruction);
    
    //printf("xPath para NumParams [%s]\n", xpathExpr);
   
    // Evaluar xpath expression
    xpathObj = xmlXPathEvalExpression(xpathExpr, xpathCtx);
    
    //printf("pudo evaluar xmlXPathEval\n");       
        
    cur = xpathObj->nodesetval->nodeTab[0];       
    uri = xmlGetProp(cur, "NumParams");
    NumParams = atoi(uri);     
           
    for(i=1;i<=NumParams;i++)
    {
       memset(xpathExpr,'\0',TAMXPATH);
       sprintf(xpathExpr, "//Configuration/Instructions/%s/Params/Param%d", Instruction, i);       

       //printf("xPath [%s]\n", xpathExpr);

      // Evaluar xpath expression
      xpathObj = xmlXPathEvalExpression(xpathExpr, xpathCtx);
 
      //printf("despues de xmlXPathEval\n");
    
      cur = xpathObj->nodesetval->nodeTab[0];       
      uri = xmlGetProp(cur, "TamBytes");
      
      switch(atoi(uri))
      {
         case 8:
            sumBytes = sumBytes + 1;
            break;
         case 16:
            sumBytes = sumBytes + 2;
            break;
         case 32:
            sumBytes = sumBytes + 4;
            break;            
      }      
      xmlFree(uri);              
    }
     
     xpathObj=NULL;
     
     return sumBytes;
     
}//GetSumParamsBytes




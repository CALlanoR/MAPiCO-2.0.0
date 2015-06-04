#include "Loader.h"

Program Loader(char *FileName)
{
  FILE *fileIN;
  Program Data;
  int BytesLeidos=0;

  //Reserva memoria para Data
  Data = (Program)malloc(sizeof(Program));

  //Abrir archivo
  if((fileIN=fopen(FileName,"rb"))==NULL)
    {
      printf("Carga del Program Byte. [ERROR]: No se pudo abrir el archivo %s\n",FileName);
      exit(1); 
    }

  //Calculo del tamaño del archivo en bytes
  fseek(fileIN, 0, SEEK_END);  // Colocar el cursor al final del fichero
  BytesLeidos = ftell(fileIN); // Tamaño en bytes
  
  //printf("despues de leer todo el archivo BytesLeidos [%d]\n", BytesLeidos);

  //Se reserva la memoria exacta para contener el archivo
  Data->File = (char *)malloc(BytesLeidos*sizeof(char)+1);
  //memset(Data->File, '\0', BytesLeidos);
  Data->Size = BytesLeidos;

  //Se rebobina el archivo para que quede al inicio
  rewind(fileIN);
  
  //printf("antes de leerlo todo otra vez\n");

  //Se lee todo el archivo de una sola vez
  fread(Data->File, sizeof(char), BytesLeidos, fileIN);

  //printf("Carga del Program Byte. [OK]\n");
  
  //Cerrar Archivo
  fclose(fileIN);
  
  return Data;

}//Loader


char get8(Program Data, int Pointer)
{
  char TempData;
  
  if (Data->File[Pointer] < 0)
  {
     TempData = (char)((Data->File[Pointer] ^ 255)+ 1);
     TempData *= -1;
  }
  else
     TempData =   (char)Data->File[Pointer];

    return (TempData);
 }//get8


short int get16(Program Data, int Pointer)
{
   short TempData;
   short res;

   if (Data->File[Pointer] < 0)
   {
      TempData = (short)((Data->File[Pointer] ^ 255)+ 1);
      TempData *= -1;
   }
   else
      TempData =   (short)Data->File[Pointer];

   res=(short)(TempData);

   if (Data->File[Pointer+1] < 0)
   {
      TempData = (short)((Data->File[Pointer+1] ^ 255)+ 1);
      TempData *= -1;
   }
   else
      TempData =   (short)Data->File[Pointer+1];

   res += (TempData*256);
     
   return res;

}//get16


int get32(Program Data, int Pointer)
{
   int TempData;
   int res;

   if (Data->File[Pointer] < 0)
   {
      TempData = (int)((Data->File[Pointer] ^ 255)+ 1);
      TempData *= -1;
   }
   else
      TempData = (int)Data->File[Pointer];

   res= (TempData);
   
   if (Data->File[Pointer+1] < 0)
   {
      TempData = (int)((Data->File[Pointer+1] ^ 255)+ 1);
      TempData *= -1;
   }
   else
      TempData =   (int)Data->File[Pointer+1];

   res += (TempData*256);

   if (Data->File[Pointer+2] < 0)
   {
      TempData = (int)((Data->File[Pointer+2] ^ 255)+ 1);
      TempData *= -1;
   }
   else
      TempData =   (int)Data->File[Pointer+2];

   res += (TempData*256*256);

   if (Data->File[Pointer+3] < 0)
   {
      TempData = (int)((Data->File[Pointer+3] ^ 255)+ 1);
      TempData *= -1;
   }
   else
      TempData =   (int)Data->File[Pointer+3];

   res += (TempData*256*256*256);
   
   return res;
  
}//get32


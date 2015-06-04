#include "HeapSort.h"


void HeapSort(int A[], int Length)
{
  int heapSize;
  
  /*
  printf("Antes Length [%d]\n", Length);
     for(int i=1;i<=Length;i++)
      printf("PC[%d]=[%d]\t",i, A[i]); 
  */

  Build_Heap(A,Length);

  heapSize = Length;
  while(heapSize>=2)
    {
      Exchange(A,1,heapSize);
      heapSize = heapSize - 1;
      Heapify(A,1,heapSize);
    }

    /*
      printf("Despues\n");    
         for(int i=1;i<=Length;i++)
      printf("PC[%d]=[%d]\t",i, A[i]); 
    */
         
}//HeapSort

void Build_Heap(int A[], int Length)
{
  int i, heapSize;
  heapSize = Length;
  for(i=Length/2;i>=1;i--)
      Heapify(A,i,heapSize);
}//Build_Heap

void Heapify(int A[],int i, int heapSize)
{
  int l,r,largest;

  l = Left(i);
  r = Right(i);

  if(l<=heapSize && A[l]>A[i])
    largest = l;
  else
    largest = i;

  if(r<=heapSize && A[r]>A[largest])
    largest = r;
  
  if(largest != i)
    {
      Exchange(A,i,largest);
      Heapify(A,largest,heapSize);
    }

}//Heapify

void Exchange(int A[],int i,int j)
{
  int temp;
  temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}//Exchange

int Left(int i)
{
  return 2*i;
}//Left

int Right(int i)
{
  return 2*i + 1;
}//Right

int searchBinary(int A[], int Length, int Element)
{
  int bajo, alto, medio;
  bajo = 1;
  alto = Length;
 
  /*
  printf("********ENTRO A searchBinary *****************************************\n"); 
    printf("Length [%d]\n", Length);
    printf("Element [%d]\n", Element);
     for(int i=1;i<=Length;i++)
      printf("PC[%d]=[%d]\t",i, A[i]); 
  */

  while(bajo<=alto)
  {
      medio = (bajo+alto)/2;
      if(Element < A[medio]) alto = medio - 1;
      else if(Element>A[medio]) bajo = medio + 1;
      else 
      {
         //printf("Lo encontro\n");
         return medio;
      }
  }

  //printf("No Lo encontro\n");
  
  return -1;  
}

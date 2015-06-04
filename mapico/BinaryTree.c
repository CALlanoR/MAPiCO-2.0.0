#include "BinaryTree.h"

/**
* newNode
*/
NodeTree newNode(int key, void *Value)
{
   NodeTree node;
   node = (NodeTree)malloc(sizeof(NodeTree));
   
   node->key = key;
   node->Value = Value;
   node->Left = NULL;
   node->Right = NULL;
   
   return node;
}//newNode

/**
* insertNode
*/

NodeTree insertNode(NodeTree Tree, int key, void *Value)
{
   NodeTree y,x;
   
   x = Tree;
   y = NULL;
   
   while(x!=NULL)
   {
      y = x;
      if(key < x->key)
         x = x->Left;
      else
         x = x->Right;      
   }//while
      
   if(y==NULL)
   {
      y = newNode(key, Value);
      return y;
   }
   else
   {
      if(key < y->key)
         y->Left = newNode(key, Value);
      else
         y->Right = newNode(key, Value);
   }//while
   
   return Tree;   
}//insertNode

/**
* Left
*/
NodeTree LeftNode(NodeTree Tree)
{
   return Tree->Left;
}//Left

/**
* Right
*/
NodeTree RightNode(NodeTree Tree)
{
   return Tree->Right;
}//Right

/**
* searchNode
*/
void *searchNode(NodeTree Tree, int key)
{
   NodeTree x;
   x = Tree;
   while(x!=NULL && key!=x->key)
   {
      if(key<x->key)
         x = LeftNode(x);
      else
         x = RightNode(x);
   }//while
   
   if(x!=NULL)   
      return x->Value;
   else
      return NULL;
   
}//searchNode

/**
* inorden
*/
void inorden(NodeTree Tree)
{
   char *Value;
   if(Tree==NULL)
      return;
   
   inorden(Tree->Left);
   Value = Tree->Value;
   printf("%d %s\n", Tree->key, Value);
   inorden(Tree->Right);         
}//inorden


#define WeightType int
#include "SqStack.h"
typedef struct{
	char c;
	WeightType weight;
	int parent,lchild,rchild;
}HTNode,*HuffTree;
void HuffmanTree(HuffTree &HT,WeightType *w,int n);
void HuffmanCoding(HuffTree HT,char **&HC,int n);
void Coding(HuffTree HT,int root,char**HC,SqStack &S);
void Select(HuffTree HT,int n,int i,int &s1,int &s2); 


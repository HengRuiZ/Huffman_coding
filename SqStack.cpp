#include"SqStack.h"
#include<stdio.h>
void InitStack_sq(SqStack &S,int msize)
{
	S.elem=new ElemType[msize];
	S.stacksize=msize;
	S.top=-1;
}
void Increment(SqStack &L)
{
	int i,inc_size=5;
	ElemType*a;
	a=new ElemType[L.stacksize+inc_size];
	if(!a){printf("∑÷≈‰ƒ⁄¥Ê¥ÌŒÛ£°");return;}
	for(i=0;i<L.stacksize;i++)a[i]=L.elem[i];
	delete []L.elem;
	L.elem=a;
	L.stacksize+=inc_size;
}
void Push_sq(SqStack &S,ElemType e)
{
	if(S.top==S.stacksize-1)Increment(S);
	S.elem[++S.top]=e;
}
bool Pop_sq1(SqStack &S,int i,ElemType &e)
{
	if(S.top==-1)return 1;
	e=S.elem[i];
	for(;i<S.top;i++)S.elem[i]=S.elem[i+1];
	S.top--;
	return 0;
}
bool Pop_sq(SqStack &S,ElemType &e)
{
	if(S.top==-1)return 1;
	e=S.elem[S.top];
	S.top--;
	return 0;
}



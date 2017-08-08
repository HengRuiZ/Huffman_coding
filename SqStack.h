#define STACK_INIT_SIZE 100
typedef char ElemType;
typedef struct{
	ElemType *elem;
	int stacksize;
	int top;
}SqStack;
void InitStack_sq(SqStack &S,int msize);
void Increment(SqStack &L);
void Push_sq(SqStack &S,ElemType e);
bool Pop_sq(SqStack &S,ElemType &e);
bool Pop_sq1(SqStack &S,int i,ElemType &e);

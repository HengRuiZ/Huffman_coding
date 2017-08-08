#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"iostream"
#include"HuffmanTree.h"
using namespace std;
FILE *fp1,*fp2,*fp3,*fp4,*fp5;
void Select(HuffTree HT,int n,int i,int &s1,int &s2)
{
	int j,k,b,weight1,weight2;
	for(j=1,k=0;j<i;j++)
	if(HT[j].parent==0)
	if(k==0)
	{
		weight1=HT[j].weight;
		k++;
		s1=j;
	}
	else if(k==1)
	{
		weight2=HT[j].weight;
		k++;
		s2=j;
		if(weight2<weight1)
		{
			b=weight1;
			weight1=weight2;
			weight2=b;
			b=s2;
			s2=s1;
			s1=b;
		}
	}
	else{
		if(HT[j].weight<weight1)
		{
			weight2=weight1;
			weight1=HT[j].weight;
			s2=s1;
			s1=j;
		}
		else if(HT[j].weight<weight2)
		{
			weight2=HT[j].weight;
			s2=j;
		}
	}
}
void HuffmanTree(HuffTree &HT,int n)
{
	int i,m,s1,s2;
	m=n*2-1;
	for(i=0;i<m+1;i++)
	{
		HT[i].parent=0;
		HT[i].lchild=0;
		HT[i].rchild=0;
	}
	for(i=n+1;i<=m;i++){
		Select(HT,n,i,s1,s2);
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
		HT[s1].parent=HT[s2].parent=i;
	}
}
void HuffmanCoding(HuffTree HT,char **&HC,int n)
{
	if(HC!=NULL)
	{
		cout<<"密码本已存在"<<endl;
		return;
	}
	SqStack S;
	InitStack_sq(S,100);
	HC=(char**)malloc(sizeof(char*)*(n+1));
	Coding(HT,2*n-1,HC,S);
}
void Coding(HuffTree HT,int root,char**HC,SqStack &S)
{
	char c;
	if(root!=0)
	{
		if(HT[root].lchild==0)
		{
			Push_sq(S,'\0');
			HC[root]=(char*)malloc(S.stacksize);
			//cout<<S.elem<<endl;
			strcpy(HC[root],S.elem);
			Pop_sq(S,c);
		}
		Push_sq(S,'0');
		Coding(HT,HT[root].lchild,HC,S);
		Pop_sq(S,c);
		Push_sq(S,'1');
		Coding(HT,HT[root].rchild,HC,S);
		Pop_sq(S,c);
	}
}
void InitHT(HuffTree &HT,int &n)
{
	int i;
	if((fp1=fopen("hfmTree.txt","wb"))==NULL){
		cout<<"无法打开文件\"hfmTree.txt\""<<endl;
		system("pause");
		exit(0);
	}
	cout<<"请输入字符集大小"<<endl;
	cin>>n;
	HT=(HuffTree)malloc(sizeof(HTNode)*(n*2));
	for(i=1;i<n+1;i++)
	{
		cout<<"请输入字符"<<endl;
		getchar();
		gets(&(HT[i].c));
		cout<<"请输入频度"<<endl;
		cin>>HT[i].weight;
	}
	HuffmanTree(HT,n);
	fwrite(&n,sizeof(int),1,fp1);
	for(i=1;i<n*2;i++)
	fwrite(&(HT[i]),sizeof(HTNode),1,fp1);
	fclose(fp1);
}
void InitHT_F(HuffTree &HT,int &n)
{
	int i;
	if((fp1=fopen("hfmTree.txt","rb"))==NULL){
		cout<<"无法打开文件\"hfmTree.txt\""<<endl;
		system("pause");
		exit(0);
	}
	fread(&n,sizeof(int),1,fp1);
	HT=(HuffTree)malloc(sizeof(HTNode)*(n*2));
	for(i=1;i<n*2;i++)
	fread(&(HT[i]),sizeof(HTNode),1,fp1);
	fclose(fp1);
}
void Encoding(HuffTree &HT,char**HC,int n)
{
	char c;
	int i;
	if((fp2=fopen("ToBeTran.txt","r"))==NULL)
	{
		cout<<"无法打开文件\"ToBeTran.txt\""<<endl;
		system("pause");
		exit(0);
	}
	if((fp3=fopen("CodeFile.txt","w"))==NULL)
	{
		cout<<"无法打开文件\"CodeFile.txt\""<<endl;
		system("pause");
		exit(0);
	}
	while((c=fgetc(fp2))!=EOF)
	for(i=1;i<n+1;i++)
	{
		if(c==HT[i].c)
		fputs(HC[i],fp3);
	}
	fclose(fp2);
	fclose(fp3);
}
void Decoding(HuffTree &HT,char**HC,int n)
{
	SqStack S;
	char c;
	int i;
	InitStack_sq(S,20);
	if((fp3=fopen("CodeFile.txt","r"))==NULL){
		cout<<"无法打开文件\"hfmTree.txt\""<<endl;
		system("pause");
		exit(0);
	}
	if((fp4=fopen("TextFile.txt","w"))==NULL){
		cout<<"无法打开文件\"hfmTree.txt\""<<endl;
		system("pause");
		exit(0);
	}
	while((c=fgetc(fp3))!=EOF)
	{
		Push_sq(S,c);
		Push_sq(S,'\0');
		for(i=1;i<n+1;i++)
		{
			if(strcmp(S.elem,HC[i])==0)
			{
				fputc(HT[i].c,fp4);
				S.top=-1;
				break;
			}
		}
		Pop_sq(S,c);
	}
}
void PrintHT(HuffTree &HT,int n)
{
	printf("***********************************************************\n过于密集可能无法打印\n*********************************************************\n");
	int i=1,j,k;
	int layer[n*2][2];
	int lay=1,pos=32;
	for(i=1;i<n*2;i++)layer[i][0]=0;
	layer[n*2-1][0]=1;layer[n*2-1][1]=64;
	while(i)
	{
		i=0;
		for(j=1;j<n*2;j++)
		{
			if(layer[j][0]==lay)
			{
				i=1;
				layer[HT[j].lchild][0]=lay+1;
				layer[HT[j].lchild][1]=layer[j][1]-pos;
				layer[HT[j].rchild][0]=lay+1;
				layer[HT[j].rchild][1]=layer[j][1]+pos;
			}
		}
		lay++;
		pos/=2;
	}
	//for(j=1;j<n*2;j++)
	//printf("%d	%d\n",layer[j][0],layer[j][1]);
	for(i=1;i<lay;i++)
	{
		for(j=0;j<128;j++)
		{pos=0;
		for(k=1;k<n*2;k++)
		if(layer[k][0]==i&&layer[k][1]==j)
		{
			pos=1;
			if(k<n+1)
			printf("%c",HT[k].c);
			else printf("#");
			break;
		}
		if(pos==0)printf(" ");
		}
		printf("\n");
	}
}
void PrintCode()
{
	char c;
	if((fp3=fopen("CodeFile.txt","r"))==NULL){
		cout<<"无法打开文件\"hfmTree.txt\""<<endl;
		system("pause");
		exit(0);
	}
	if((fp5=fopen("CodePrint.txt","w"))==NULL){
		cout<<"无法打开文件\"hfmTree.txt\""<<endl;
		system("pause");
		exit(0);
	}
	while((c=fgetc(fp3))!=EOF)
	{
		cout<<c;
		fputc(c,fp5);
	}
}
main()
{
	int i,n;
	HuffTree HT=NULL;
	SqStack S;
	char **HC=NULL,c;
	while(1)
	{
		printf("哈夫曼编码解码系统\n===============================\n0.退出\n1.初始化\n2.编码\n3.解码\n4.打印代码文件\n5.打印哈夫曼树\n");
		cin>>i;
		switch(i){
			case 0:return 0;
			case 1:{
				cout<<"请选择：1.手动输入	2.从文件导入"<<endl;
				cin>>i;
				if(i==1)
				InitHT(HT,n);
				else if(i==2)
				InitHT_F(HT,n);
				HuffmanTree(HT,n);
				break;
			}
			case 2:{
				HuffmanCoding(HT,HC,n);
				//for(i=1;i<n+1;i++)
				//printf("%3d	%s\n",HT[i].weight,HC[i]);
				Encoding(HT,HC,n);
				break;
			}
			case 3:{
				Decoding(HT,HC,n);
				break;
			}
			case 4:{
				PrintCode();
				break;
			}
			case 5:{
				PrintHT(HT,n);
				break;
			}
		}
	}
	return 0;
}

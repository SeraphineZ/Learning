#include<stdio.h>

#include<stdlib.h>

//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXSIZE 100

//Status 是函数的类型，其值是函数结果状态代码
typedef int Status;
typedef char Elemtype;

typedef struct {
	Elemtype* elem;
	int length;
}SqList;
SqList L;

Status InitList_Sq(SqList& L) {
	L.elem = (Elemtype*)malloc(sizeof(Elemtype) * MAXSIZE);
	if (!L.elem)	exit(OVERFLOW);
	L.length = 0;
	return OK;
}

void DestroyList(SqList& L)
{
	if (L.elem)	free(L.elem);	//释放存储空间
}

void ClearList(SqList& L)
{
	L.length = 0;	//将线性表的长度置0
}

Status GetLength(SqList& L)
{
	return (L.length);
}

Status IsEmpty(SqList& L)
{
	if (L.length == 0)	return 1;
	else return 0;
}

Status GetElem(SqList L, int i, Elemtype& e)
{
	if (i<1 || i>L.length)	return ERROR;
	//判断i值是否合理
	e = L.elem[i - 1];	//第i-1的单元存储着第i个数据
	return OK;
}

Status LocateElem(SqList L, Elemtype& e)
{
	for (int i = 0; i < L.length; i++) 
		if (L.elem[i] == e)	return i + 1;	//查找成功，返回序号
	return 0;	//查找失败，返回0
}

Status ListInsert_Sq(SqList L, int i, int j, Elemtype& e)
{
	if (i<1 || i>L.length)	return ERROR;
	if (L.length == MAXSIZE)	return ERROR;
	for (j = L.length + 1; j >= i - 1; j++)
		L.elem[j + 1] = L.elem[j];
	L.elem[i - 1] = e;
	L.length++;
	return OK;
}

Status ListDelete_Sq(SqList L, int i)
{
	if (i<1 || i>L.length)	return ERROR;
	for (int j = i; j <= L.length - 1; j++)
		L.elem[j - 1] = L.elem[j];
	L.length--;
	return OK;
}
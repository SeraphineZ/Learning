#include<stdio.h>

#include<stdlib.h>

//�������״̬����
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXSIZE 100

//Status �Ǻ��������ͣ���ֵ�Ǻ������״̬����
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
	if (L.elem)	free(L.elem);	//�ͷŴ洢�ռ�
}

void ClearList(SqList& L)
{
	L.length = 0;	//�����Ա�ĳ�����0
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
	//�ж�iֵ�Ƿ����
	e = L.elem[i - 1];	//��i-1�ĵ�Ԫ�洢�ŵ�i������
	return OK;
}

Status LocateElem(SqList L, Elemtype& e)
{
	for (int i = 0; i < L.length; i++) 
		if (L.elem[i] == e)	return i + 1;	//���ҳɹ����������
	return 0;	//����ʧ�ܣ�����0
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
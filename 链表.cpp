#include<stdio.h>

#include<stdlib.h>

#include <iostream>

#define _CRT_SECURE_NO_WARNINGS

//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define MAXSIZE 100

//Status 是函数的类型，其值是函数结果状态代码
typedef int Status;
typedef char Elemtype;

typedef struct LNode {	//声明结点的类型和指向结点的指针类型
	Elemtype data;		//结点的数据域
	struct LNode* next;	//结点的指针域
}LNode, * LinkList;		//LinkList为指向结构体LNode的指针类型
LinkList L;

typedef struct DuLNode {
	Elemtype data;
	struct DuLNode* prior, * next;
}DuLNode,*DuLinkList;

Status InitList_L(LinkList& L) {
	L = (LinkList)malloc(sizeof(LNode));//L=new LNode;
	if (L != NULL) {
		L->next = NULL;
	}
	
	return OK;
}

Status ListEmpty(LinkList& L) {
	if (L->next)
		return 0;
	else
		return 1;
}

Status DestroyList_L(LinkList& L) {
	LNode* p;
	while (L) {
		p = L;
		L = L->next;
		free(p);
	}
	return OK;
}

Status ClearList(LinkList& L) {
	LNode* p, * q;
	p = L->next;
	while (p) {		//没到表尾
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;	//头结点指针域为空
	return OK;
}

Status ListLength_L(LinkList L) {
	LNode* p;
	p = L->next;
	int i = 0;
	while (p) {
		i++;
		p = p->next;
	}
	return i;
}

Status GetElem_L(LinkList L, int i, Elemtype& e) {	//获取线性表L中第i个元素的内容，通过e返回
	LNode* p;
	p = L->next;
	int j = 1;
	while (p && j < i) {
		p = p->next;
		++j;
	}
	if (!p || j > i) {
		return ERROR;
	}
	e = p->data;
	return OK;
}

LNode* LocateElem_L1(LinkList L, Elemtype e) {	//在线性表L中查找值为e的数据元素
	LNode* p;
	p = L->next;
	while (p && p->data != e) {
		p = p->next;
	}
	return p;
}

Status LocateElem_L2(LinkList L, Elemtype e) {	//在线性表L中查找值为e的数据元素的位置序号
	LNode* p;
	p = L->next;
	int i = 1;
	while (p && p->data != e) {
		p = p->next;
		i++;
	}
	if (p)	return i;
	else return 0;
}

Status ListInsert_L(LinkList& L, int i, Elemtype e) {
	LNode* p,* s;
	p = L;
	int j = 0;
	while (p && j < i - 1) {
		p = p->next;
		j++;
	}
	if (!p || j > i - 1) {
		return ERROR;
	}
	s = new LNode;
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}

Status ListDelete_L(LinkList& L, int i, Elemtype& e) {
	LNode* p, * q;
	p = L;
	int j = 0;
	while (p->next && j < i - 1) {
		p = p->next;
		j++;
	}
	if (!p->next || j > i - 1) {
		return ERROR;
	}
	q = p->next;
	p->next = q->next;
	e = q->data;
	free(q);
	return OK;
}

void CreateList_H(LinkList& L, int n) {
	L = new LNode;
	L->next = NULL;			//先建立一个带头结点的单链表
	LNode* p;
	int i;
	for (i = n; i > 0; --i) {
		p = new LNode;
		std::cin >> p->data;
		p->next = L->next;	//插入到表头
		L->next = p;
	}
}

void CreateList_R(LinkList& L, int n) {
	L = new LNode;
	L->next = NULL;
	LNode* p, * r;
	r = L;	//尾指针r指向头结点
	int i;
	for (i = 0; i < n; ++i) {
		p = new LNode;
		std::cin >> p->data;	//生成新结点，输入元素值
		p->next = NULL;
		r->next = p;	//插入到表尾
		r = p;	//r指向新的尾结点
	}
}

LinkList Connect(LinkList Ta, LinkList Tb) {
									//假设Ta、Tb都是非空的单循环链表
	LNode* p;
	p = Ta->next;				//p存表头结点
	Ta->next = Tb->next->next;	//Tb表头连结Ta表尾
	delete Tb->next;			//释放Tb表头结点
	Tb->next = p;				//修改指针
	return Tb;
}

Status InitDuList(DuLinkList &L,int i,int n) {
	L = (DuLinkList)malloc(sizeof(DuLNode));
	if (L != NULL) {
		L->prior = NULL;
		L->next = NULL;
	}
	return OK;
}

DuLNode* GetElem_DuL(DuLinkList L, int i)
{
	DuLNode* p = L->next;
	int j = 1;
	while (p && j < i)
	{
		p = p->next;
		j++;
	}
	if (!p || j > i)
		return NULL;
	else
		return p;
}

Status ListInsert_DuL(DuLinkList& L, int i, Elemtype e) {
	//在带头结点的双向循环链表L中第i个位置之前插入元素e
	DuLNode* p, * s;
	if (!(p = GetElem_DuL(L,i)))	return ERROR;
	s = new DuLNode;
	s->data = e;
	s->prior = p->prior;
	p->prior->next = s;
	s->next = p;
	p->prior = s;
	return OK;
}

Status ListDelete_DuL(DuLinkList& L, int i, Elemtype& e) {
	//删除带头结点的双向循环链表L的第i个元素，并用e返回
	DuLNode* p;
	if (!(p = GetElem_DuL(L, i)))	return ERROR;
	e = p->data;
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	return OK;
}

int main()
{
	printf("hello world!");
	return 0;
}


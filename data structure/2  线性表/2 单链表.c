#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LNode
{
	double			data;
	struct LNode	*next;
}LNode, *LinkList;

bool compare(double a, double b)
{
	return a == b;
}

double GetElem_L(LinkList L, int i)
{
	LinkList p = L->next;
	int j = 0;
	for(; p && j < i; ++j, p = p->next);
	if(p)
		return p->data;
	printf("错误：下标访问越界！\n");
	exit(0);
}

void ListInsert_L(LinkList *L, int i, double e)
{
	LinkList p = *L;
	int j = -1;
	for(; p && j < i - 1; ++j, p = p->next);
	if(p)
	{
		LinkList s = (LinkList)malloc(sizeof(LNode));
		s->data = e;
		s->next = p->next;
		p->next = s;
		return;
	}
	printf("错误：下标访问越界！\n");
}

void ListDelete_L(LinkList *L, int i)
{
	LinkList p = *L;
	int j = -1;
	for(; p && j < i - 1; ++j, p = p->next);
	if(p)
	{
		LinkList q = p->next;
		p->next = q->next;
		free(q);
		return;
	}
	printf("错误：下标访问越界！\n");
}

void CreateList_L(LinkList *L, int n)
{
	*L = (LinkList)malloc(sizeof(LNode));
	(*L)->next = NULL;
	int i;
	LinkList q = *L;
	for(i = 0; i < n; ++i, q = q->next)
	{
		LinkList p = (LinkList)malloc(sizeof(LNode));
		scanf("%lf", &(p->data));
		q->next = p;
		p->next = NULL;
	}
}

void ListTraverse_L(LinkList L)
{
	LinkList p = L->next;
	if(!p || !L)
	{
		printf("错误：链表为空！\n");
		return;
	}
	for(; p; p = p->next)
		printf("%lf\t", p->data);
	printf("\n");
}

void InitList(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(LNode));
	(*L)->next = NULL;
}

void DestroyList_L(LinkList *L)
{
	LinkList p = (*L)->next;
	for(; p; p = p->next)
	{
		(*L)->next = p->next;
		free(p);
	}
	free(*L);
}

void ClearList_L(LinkList *L)
{
	if(!((*L)->next))
	{
		printf("错误：链表为空！\n");
		return;
	}
	LinkList p = (*L)->next;
	for(; p; p = p->next)
	{
		(*L)->next = p->next;
		free(p);
	}
}

bool ListEmpty_L(LinkList L)
{
	return L->next;
}

int LocateElem_L(LinkList L, double e, bool (*comparep)(double, double))
{
	LinkList p = L->next;
	int i = 0;
	for(; p && !(*comparep)(p->data, e); ++i, p = p->next);
	if(p) return i;
	return -1;
}

double PriorElem_L(LinkList L, double cur_e)
{
	LinkList p = L->next, q = L;
	for(; p && p->data != cur_e; p = p->next, q = q->next);
	if(!p)
	{
		printf("错误：%lf不在链表中！\n", cur_e);
		exit(0);
	}
	if(p == L->next)
	{
		printf("错误：%lf前没有元素！\n", cur_e);
		exit(0);
	}
	return q->data;
}

double NextElem_L(LinkList L, double cur_e)
{
	LinkList p = L->next;
	for(; p && p->data != cur_e; p = p->next);
	if(!p)
	{
		printf("错误：%lf不在链表中！\n", cur_e);
		exit(0);
	}
	if(!(p->next))
	{
		printf("错误：%lf后没有元素！\n", cur_e);
		exit(0);
	}
	return p->next->data;
}


void MergeList_L(LinkList La, LinkList Lb, LinkList *Lc)
{
	InitList(Lc);
	LinkList pa = La->next, pb = Lb->next;
	bool (*comparep)(double, double) = &compare;
	int i = 0;
	for(; pa; pa = pa->next)
			ListInsert_L(Lc, i++, pa->data);
	for(; pb; pb = pb->next)
		if(LocateElem_L(La, pb->data, comparep) == -1)
			ListInsert_L(Lc, i++, pb->data);
}

int main()
{
	LinkList l, l2, l3;
	LinkList *lp = &l, *lp2 = &l2, *lp3 = &l3;


	CreateList_L(lp, 3);
	CreateList_L(lp2, 5);
	ListTraverse_L(l);
	ListTraverse_L(l2);
	MergeList_L(l, l2, lp3);
	ListTraverse_L(l3);
	/*
	ListTraverse_L(l);

	printf("%lf\n", GetElem_L(l, 1));

	ListInsert_L(lp, 1, 2.5);
	ListTraverse_L(l);

	ListDelete_L(lp, 2);
	ListTraverse_L(l);

	bool (*comparep)(double, double) = &compare;
	printf("%d\n", LocateElem_L(l, 1, comparep));*/

	//printf("%lf\n", PriorElem_L(l, 3));
	//printf("%lf\n", NextElem_L(l, 3));

	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct DuLNode
{
	double			data;
	struct DuLNode	*prior;
	struct DuLNode	*next;
}DuLNode, *DuLinkList;

DuLinkList GetElemP_DuL(DuLinkList L, int i)
{
	DuLinkList p = L->next;
	int j = 0;
	for(; p && j < i; ++j, p = p->next);
	return p;
}

void ListInsert_DuL(DuLinkList *L, int i, double e)
{
	DuLinkList p = GetElemP_DuL(*L, i);
	if(!p)
	{
		printf("错误：第%d个元素不存在！\n", i);
		exit(0);
	}
	DuLinkList s = (DuLinkList)malloc(sizeof(DuLNode));
	if(!s)
	{
		printf("错误：内存分配失败！\n");
		exit(0);
	}
	s->data = e;
	s->prior = p->prior;
	p->prior->next = s;
	s->next = p;
	p->prior = s;
}


void ListDelete_DuL(DuLinkList *L, int i)
{
	DuLinkList p = GetElemP_DuL(*L, i);
	if(!p)
	{
		printf("错误：第%d个元素不存在！\n", i);
		exit(0);
	}
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
}

void ListTraverse_DuL(DuLinkList L)
{
	DuLinkList p = L->next;
	if(!p || !L)
	{
		printf("错误：链表为空！\n");
		return;
	}
	for(; p; p = p->next)
		printf("%lf\t", p->data);
	printf("\n");
}

void InitList_DuL(DuLinkList *L)
{
	*L = (DuLinkList)malloc(sizeof(DuLNode));
	(*L)->prior = NULL;
	(*L)->next = NULL;
}

int main()
{
	DuLinkList l, *lp = &l;
	InitList_DuL(lp);
	DuLinkList s = (DuLinkList)malloc(sizeof(DuLNode));
	if(!s)
	{
		printf("错误：内存分配失败！\n");
		exit(0);
	}
	s->data = 100;
	s->prior = *lp;
	s->next = NULL;
	(*lp)->next = s;

	ListInsert_DuL(lp, 0, 3);
	ListInsert_DuL(lp, 0, 2);
	ListInsert_DuL(lp, 0, 1);

	ListTraverse_DuL(l);

	ListDelete_DuL(lp, 1);
	ListTraverse_DuL(l);

	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LIST_INIT_SIZE		100
#define LISTINCREASEMENT	10

typedef struct
{
	double	*elem;
	int 	length;
	int 	listsize;
}SqList;

bool compare(double a, double b)
{
	return a == b;
}

void InitList_Sq(SqList* L)
{
	(*L).elem = (double*)malloc(LIST_INIT_SIZE * sizeof(double));
	if(!(*L).elem)
	{
		printf("错误：内存分配失败！\n");
		exit(0);
	}

	(*L).length = 0;
	(*L).listsize = LIST_INIT_SIZE;
}

void ListInsert_Sq(SqList* L, int i, double e)
{
	if(i < 0 || i > (*L).length)
	{
		printf("错误：下标访问越界！\n");
		return;
	}

	if(i == (*L).length && (*L).length == (*L).listsize)
	{
		double* newbase = (double*)realloc((*L).elem, ((*L).listsize + LISTINCREASEMENT) * sizeof(double));
		if(!newbase)
		{
			printf("错误：内存分配失败！\n");
			exit(0);
		}
		(*L).elem = newbase;
		(*L).listsize += LISTINCREASEMENT;
	}


	int j = (*L).length;
	for(; j > i; --j)
		(*L).elem[j] = (*L).elem[j - 1];
	(*L).elem[i] = e;
	++(*L).length;
}

void ListDelete_Sq(SqList* L, int i)
{
	if(i < 0 || i > (*L).length - 1)
		printf("错误：下标访问越界！\n");

	int j = i;
	for( ; j < (*L).length - 1; ++j)
		(*L).elem[j] = (*L).elem[j + 1];	
	--(*L).length;

	if((*L).length == (*L).listsize - LISTINCREASEMENT)
	{
		double* newbase = (double*)realloc((*L).elem, ((*L).listsize - LISTINCREASEMENT) * sizeof(double));
		if(!newbase)
		{
			printf("错误：内存分配失败！\n");
			exit(0);
		}
		(*L).elem = newbase;
		(*L).listsize -= LISTINCREASEMENT;
	}
}

int LocateElem_Sq(SqList L, double e, bool (*comparep)(double, double))
{
	int i = 0;
	for(; i < L.length; ++i)
		if(L.elem[i] == e)
			return i;
	return L.length;
}

void MergeList_Sq(SqList La, SqList Lb, SqList *Lc)
{
	(*Lc).listsize = La.listsize;
	double* newbase = (double*)realloc((*Lc).elem, La.listsize * sizeof(double));
	(*Lc).length = La.length;
	int i;
	for(i = 0; i < La.length; ++i)
		(*Lc).elem[i] = La.elem[i];
	
	bool (*funp)(double, double) = &compare;
	for(i = 0; i < Lb.length; ++i)
	{
		int location = LocateElem_Sq(La, Lb.elem[i], funp);
		if(location == La.length)
		{
			++(*Lc).length;
			if((*Lc).length > (*Lc).listsize)
			{
				double* newbase = (double*)realloc((*Lc).elem, ((*Lc).listsize + LISTINCREASEMENT) * sizeof(double));
				if(!newbase)
				{
					printf("错误：内存分配失败！\n");
					exit(0);
				}
				(*Lc).elem = newbase;
				(*Lc).listsize += LISTINCREASEMENT;
			}
			(*Lc).elem[(*Lc).length - 1] = Lb.elem[i];
		}
	}
}

int main()
{

	SqList l;
	SqList *lp = &l;

	InitList_Sq(lp);


	ListInsert_Sq(lp, 0, 1);
	ListInsert_Sq(lp, 0, 2);
	ListInsert_Sq(lp, 0, 3);
	ListInsert_Sq(lp, 0, 4);
	ListInsert_Sq(lp, 0, 5);

	printf("%lf\t", l.elem[0]);
	printf("%lf\t", l.elem[1]);
	printf("%lf\t", l.elem[2]);
	printf("%lf\t", l.elem[3]);
	printf("%lf\t", l.elem[4]);
	printf("\n");

	SqList l2;
	SqList *lp2 = &l2;

	InitList_Sq(lp2);


	ListInsert_Sq(lp2, 0, 1);
	ListInsert_Sq(lp2, 0, 2);
	ListInsert_Sq(lp2, 0, 33);
	ListInsert_Sq(lp2, 0, 44);
	ListInsert_Sq(lp2, 0, 5);

	printf("%lf\t", l2.elem[0]);
	printf("%lf\t", l2.elem[1]);
	printf("%lf\t", l2.elem[2]);
	printf("%lf\t", l2.elem[3]);
	printf("%lf\t", l2.elem[4]);
	printf("\n");

	SqList l3;
	SqList *lp3 = &l3;

	InitList_Sq(lp3);

	MergeList_Sq(l, l2, lp3);
	printf("%lf\t", l3.elem[0]);
	printf("%lf\t", l3.elem[1]);
	printf("%lf\t", l3.elem[2]);
	printf("%lf\t", l3.elem[3]);
	printf("%lf\t", l3.elem[4]);
	printf("%lf\t", l3.elem[5]);
	printf("%lf\t", l3.elem[6]);
	printf("\n");


	/*
	ListDelete_Sq(lp, 1);
	printf("%f\t", l.elem[0]);
	printf("%f\t", l.elem[1]);
	printf("%f\t", l.elem[2]);
	printf("%f\t", l.elem[3]);
	*/

	/*
	bool (*funp)(double, double) = &compare;
	printf("%d\n", LocateElem_Sq(l, 4, funp));
	*/

	return 0;
}
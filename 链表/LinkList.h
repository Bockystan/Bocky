#pragma once
#include<stdio.h>
#include<stdlib.h>

//线性表的单链表存储结构
struct LNode {
	int data;
	LNode *next;
};
typedef LNode* LinkList;
//查找
int GetElem_L(LinkList &L, int i, int &e) {
	//L为带头结点的单链表头指针
	//当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR
	LNode *p =L->next;
	int j = 1;				//j为计数器
	while (p && j < i) {
		p = p->next;
		++j;
	}
	if (!p || j > i) {		//第i个元素不存在
		return 0;
	}
	e = p->data;			//取第i个元素
	return 1;
}


//算法2.8
//在带头结点的单链线性表L中第i个位置之前插入元素e
int ListInsert_L(LinkList &L, int i, int e) {
	LNode *p = L;
	int j = 0;
	while (p && j < i - 1) {		//寻找第i-1个结点
		p = p->next;
		++j;
	}
	if (!p) {
		printf("ERROR\n");		//i值不合法
		return 1;
	}
	LNode *s = (LNode*)malloc(sizeof(LNode));
	s->data = e;					//生成新结点
	s->next = p->next;
	p->next = s;					//插入新结点
	return 0;
}//ListInsert_L

 //算法2.9
 //在带头结点的单链线性表L中，删除第i个元素，并由e返回其值
int ListDelete_L(LinkList &L, int i, int &e) {
	LNode *p = L;
	int j = 0;
	while (p->next && j < i - 1) {		//寻找第i-1个结点，并使p指向它的前驱
		p = p->next;
		++j;
	}
	if (!p->next) {
		printf("ERROR\n");			//i值不合法
		return 1;
	}
	LNode *q = p->next;
	p->next = q->next;
	e = q->data;
	free(q);							//删除并释放结点
	return 0;
}//ListDelete_L

 //算法2.10
 //逆位序输入n个元素的值， 建立带表头节点的单链线性表L
void CreateList_L(LinkList &L, int n) {
	L = (LNode*)malloc(sizeof(LNode));		//生成头结点
	L->next = NULL;
	LNode *p;
	for (int i = n; i > 0; --i) {
		p = (LNode*)malloc(sizeof(LNode));	//生成新节点
		scanf("%d", &p->data);
		p->next = L->next;
		L->next = p;						//插入到表头
	}
}//CreateList_L

void CreateList_L1(LinkList &L, int n)//顺位序创建
{
	L = (LinkList)malloc(sizeof(LNode));//为头结点申请空间

	LinkList tail;//头结点要保存起来，使用tail替代；
	tail = (LinkList)malloc(sizeof(LNode));//为tail申请空间；
	tail = L;//开始L即为tail；
	LinkList p;
	for (int i = 0; i<n; i++)
	{
		p = (LinkList)malloc(sizeof(LNode));//为新结点申请空间并输入数据以初始化
	//	printf("请输入第%d个数据：\n", (i + 1));
		scanf("%d", &p->data);

		tail->next = p;//插入操作
		tail = tail->next;
	}
	tail->next = NULL;//最后tail->next指向NULL；
}
 //算法2.11
 //已知单链线性表La和Lb的元素按值非递减排列
 //归并La和Lb得到新的单链线性表Lc，Lc的元素也按值非递减排列
void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc) {
	LNode *pa = La->next;
	LNode *pb = Lb->next;
	LNode *pc = Lc = La;			//用La的头结点作为Lc的头结点
	while (pa && pb) {
		if (pa->data <= pb->data) {
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else {
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	if (pa) pc->next = pa;		//插入La的剩余元素
	if (pb) pc->next = pb;		//插入Lb的剩余元素
	free(Lb);					//释放Lb的头结点
}//MergeList_L

 //打印链表中的元素
void OutputList_L(LinkList L) {
	LNode *p = L->next;
	while (p) {
		printf("%d ", p->data);
		p = p->next;
	}
}
#pragma once
#include<stdio.h>
#include<stdlib.h>

//���Ա�ĵ�����洢�ṹ
struct LNode {
	int data;
	LNode *next;
};
typedef LNode* LinkList;
//����
int GetElem_L(LinkList &L, int i, int &e) {
	//LΪ��ͷ���ĵ�����ͷָ��
	//����i��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR
	LNode *p =L->next;
	int j = 1;				//jΪ������
	while (p && j < i) {
		p = p->next;
		++j;
	}
	if (!p || j > i) {		//��i��Ԫ�ز�����
		return 0;
	}
	e = p->data;			//ȡ��i��Ԫ��
	return 1;
}


//�㷨2.8
//�ڴ�ͷ���ĵ������Ա�L�е�i��λ��֮ǰ����Ԫ��e
int ListInsert_L(LinkList &L, int i, int e) {
	LNode *p = L;
	int j = 0;
	while (p && j < i - 1) {		//Ѱ�ҵ�i-1�����
		p = p->next;
		++j;
	}
	if (!p) {
		printf("ERROR\n");		//iֵ���Ϸ�
		return 1;
	}
	LNode *s = (LNode*)malloc(sizeof(LNode));
	s->data = e;					//�����½��
	s->next = p->next;
	p->next = s;					//�����½��
	return 0;
}//ListInsert_L

 //�㷨2.9
 //�ڴ�ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ�أ�����e������ֵ
int ListDelete_L(LinkList &L, int i, int &e) {
	LNode *p = L;
	int j = 0;
	while (p->next && j < i - 1) {		//Ѱ�ҵ�i-1����㣬��ʹpָ������ǰ��
		p = p->next;
		++j;
	}
	if (!p->next) {
		printf("ERROR\n");			//iֵ���Ϸ�
		return 1;
	}
	LNode *q = p->next;
	p->next = q->next;
	e = q->data;
	free(q);							//ɾ�����ͷŽ��
	return 0;
}//ListDelete_L

 //�㷨2.10
 //��λ������n��Ԫ�ص�ֵ�� ��������ͷ�ڵ�ĵ������Ա�L
void CreateList_L(LinkList &L, int n) {
	L = (LNode*)malloc(sizeof(LNode));		//����ͷ���
	L->next = NULL;
	LNode *p;
	for (int i = n; i > 0; --i) {
		p = (LNode*)malloc(sizeof(LNode));	//�����½ڵ�
		scanf("%d", &p->data);
		p->next = L->next;
		L->next = p;						//���뵽��ͷ
	}
}//CreateList_L

void CreateList_L1(LinkList &L, int n)//˳λ�򴴽�
{
	L = (LinkList)malloc(sizeof(LNode));//Ϊͷ�������ռ�

	LinkList tail;//ͷ���Ҫ����������ʹ��tail�����
	tail = (LinkList)malloc(sizeof(LNode));//Ϊtail����ռ䣻
	tail = L;//��ʼL��Ϊtail��
	LinkList p;
	for (int i = 0; i<n; i++)
	{
		p = (LinkList)malloc(sizeof(LNode));//Ϊ�½������ռ䲢���������Գ�ʼ��
	//	printf("�������%d�����ݣ�\n", (i + 1));
		scanf("%d", &p->data);

		tail->next = p;//�������
		tail = tail->next;
	}
	tail->next = NULL;//���tail->nextָ��NULL��
}
 //�㷨2.11
 //��֪�������Ա�La��Lb��Ԫ�ذ�ֵ�ǵݼ�����
 //�鲢La��Lb�õ��µĵ������Ա�Lc��Lc��Ԫ��Ҳ��ֵ�ǵݼ�����
void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc) {
	LNode *pa = La->next;
	LNode *pb = Lb->next;
	LNode *pc = Lc = La;			//��La��ͷ�����ΪLc��ͷ���
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
	if (pa) pc->next = pa;		//����La��ʣ��Ԫ��
	if (pb) pc->next = pb;		//����Lb��ʣ��Ԫ��
	free(Lb);					//�ͷ�Lb��ͷ���
}//MergeList_L

 //��ӡ�����е�Ԫ��
void OutputList_L(LinkList L) {
	LNode *p = L->next;
	while (p) {
		printf("%d ", p->data);
		p = p->next;
	}
}
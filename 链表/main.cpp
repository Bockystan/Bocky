#include"LinkList.h"

int main() {

	//��������
	LinkList L;
	printf("������9������:\n");

	CreateList_L(L, 9);
	OutputList_L(L);
	printf("\n\n");
	
	//����
	int i,e;				//iΪλ��  eΪԪ��
	printf("������Ҫ�ڵڼ���Ԫ�غ�������֣�");
	scanf("%d",&i);
	printf("�����������������֣�");
	scanf("%d",&e);
	printf("�ڵ�%d��Ԫ��ǰ����%d\n", i, e);
	ListInsert_L(L, i, e);
	OutputList_L(L);
	printf("\n\n");

	//ɾ��
	printf("������Ҫɾ���ڼ������֣�");
	scanf("%d", &i);
	ListDelete_L(L, i, e);
	OutputList_L(L);

	printf("\n\n");

	//����
	int res;

	printf("��������Ҫ���ҵ�����:");
	scanf("%d", &e);
	res = GetElem_L(L, i, e);
	printf("����ҵ�����Ϊ��%d��\n",res);
	

	//�ϲ�
	LinkList La;
	LinkList Lb;
	LinkList Lc;
	printf("������5������:\n");
	CreateList_L1(La, 5);				//�������
	printf("������5������:\n");			
	CreateList_L1(Lb, 5);				//�������
	MergeList_L(La, Lb, Lc);
	printf("�ϲ���");
	OutputList_L(Lc);
	printf("\n\n");


}
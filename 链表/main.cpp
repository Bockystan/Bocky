#include"LinkList.h"

int main() {

	//输入逆序
	LinkList L;
	printf("请输入9个整数:\n");

	CreateList_L(L, 9);
	OutputList_L(L);
	printf("\n\n");
	
	//插入
	int i,e;				//i为位置  e为元素
	printf("请问你要在第几个元素后插入数字：");
	scanf("%d",&i);
	printf("请输入你想插入的数字：");
	scanf("%d",&e);
	printf("在第%d个元素前插入%d\n", i, e);
	ListInsert_L(L, i, e);
	OutputList_L(L);
	printf("\n\n");

	//删除
	printf("请问你要删除第几个数字：");
	scanf("%d", &i);
	ListDelete_L(L, i, e);
	OutputList_L(L);

	printf("\n\n");

	//查找
	int res;

	printf("请输入你要查找的数字:");
	scanf("%d", &e);
	res = GetElem_L(L, i, e);
	printf("你查找的数字为第%d个\n",res);
	

	//合并
	LinkList La;
	LinkList Lb;
	LinkList Lc;
	printf("请输入5个整数:\n");
	CreateList_L1(La, 5);				//正序输出
	printf("请输入5个整数:\n");			
	CreateList_L1(Lb, 5);				//正序输出
	MergeList_L(La, Lb, Lc);
	printf("合并后");
	OutputList_L(Lc);
	printf("\n\n");


}
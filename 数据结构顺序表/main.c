#include <stdio.h>
#include "List.h"

int main() {
	SqList L;
	int i;
	InitList_Sq(&L);
	printf( "请输入待输入的数字个数:");
	scanf("%d", &L.length);
	printf( "请输入数字\n");
	for(i = 0;i <L.length;i++) {
		scanf("%d",&L.elem[i]);
	}
	printf("\n");
	printf("你输入的数字是:");
	for (i = 0; i <L.length; i++) {
		printf("%d ", L.elem[i]);
	}
	printf("\n");
	int e ;
	int a;
	printf("你想把数字放到第几号:");
	scanf("%d", &a);
	printf("你想插入哪个数字：");
	scanf("%d", &e);
	ListInsert_Sq(&L, a, e);
	for (int i = 0; i<L.length; i++) {
		printf("%d ", L.elem[i]);
	}
	printf("\n");

	

	/*--------------------------------*/

	int b;
	printf("你想删除几号数字:");
	scanf("%d",&b);
	DeleteList_Sq(&L, b, &e);
	for (int i = 0; i<L.length; i++) {
		printf("%d ", L.elem[i]);
	}
	printf("\n");


	/*--------------------------------*/


	
	
	int res;
	printf("你想查哪个数字的位置:");
	scanf("%d",&res);

	res = LocateElem_Sq(&L, res, compare);
	if (res != 0) {

		printf("这个数字在第%d号", res);
	}
	else {
		printf("没有找到.");
	}
	printf("\n");

	/*--------------------------------*/
	SqList La, Lb, Lc;
	InitList_Sq(&La);
	printf("请输入待输入的数字个数:");
	scanf("%d", &La.length);
	printf("请输入数字\n");
	for (i = 0; i <La.length; i++) {
		scanf("%d", &La.elem[i]);
	}
	printf("\n");
	/*ListInsert_Sq(&La, 1, 8);
	ListInsert_Sq(&La, 2, 7);
	ListInsert_Sq(&La, 3, 5);
	ListInsert_Sq(&La, 4, 3);
	ListInsert_Sq(&La, 5, 0);*/
	InitList_Sq(&Lb);
	printf("链表a:\n");
	printf("请输入待输入的数字个数:");
	scanf("%d", &Lb.length);
	printf("请输入数字\n");
	for (i = 0; i <Lb.length; i++) {
		scanf("%d", &Lb.elem[i]);
	}
	printf("\n");
	printf("链表b:\n");
	/*ListInsert_Sq(&Lb, 1, 6);
	ListInsert_Sq(&Lb, 2, 4);
	ListInsert_Sq(&Lb, 3, 2);
	ListInsert_Sq(&Lb, 4, 1);
	ListInsert_Sq(&Lb, 5, 0);*/
	
	MergeList_Sq(La, Lb, &Lc);
	printf("合并前\n");
	printf("链表a:");
	for (int i = 0; i < La.length; i++) printf("%d ", (La.elem[i]));
	printf("\n");
	printf("链表b:");
	for (int i = 0; i < Lb.length; i++) printf("%d ", (Lb.elem[i]));
	printf("\n");
	printf("合并后\n");
	for (int i = 0; i < Lc.length; i++) printf("%d ", (Lc.elem[i]));

}
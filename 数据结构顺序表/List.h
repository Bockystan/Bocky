#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 100
#define LISTINCREATMENT 10

typedef struct {
	int *elem;
	int length;
	int listsize;
}SqList;

int InitList_Sq(SqList *L){								//构造顺序表
	L->elem = (int *)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L->elem) {
		exit(0);
	}
	L->length = 0;
	L->listsize = LIST_INIT_SIZE;
	return 0;
}

int ListInsert_Sq(SqList *L, int i, int e) {					//	增
	int *p, *q;													//定义指针变量
	if (i < 1 || i > L->length + 1) {							//异常处理
		return -1;
	}

	if (L->length >= L->listsize) {
		int *newbase;
		newbase = (int *)realloc(L->elem, (L->listsize + LISTINCREATMENT) * sizeof(int));

		if (!newbase) {
			printf("Error");
			exit(0);
		}

		L->elem = newbase;
		L->listsize += LISTINCREATMENT;
	}


	q = &(L->elem[i - 1]);

	for (p = &(L->elem[L->length - 1]); p >= q; p--) {
		*(p + 1) = *p;
	}

	*q = e;
	L->length++;
	return 0;
}




int DeleteList_Sq(SqList *L, int i, int *e) {			//删
	int *p, *q;
	if ((i < 1) || (i > L->length)) {
		return -1;
	}
	//i 不合法

	p = &(L->elem[i - 1]);                           //P为删除元素的位置
	*e = *p;                                         //被删除的元素赋值给e
	q = L->elem + L->length - 1;                     //表尾元素位置
	for (++p; p <= q; ++p) {
		*(p - 1) = *p;                               //被删除元素之后的元素左移
	}
	--L->length;                                     //表长减1
	return 0;
}


int compare(int a, int b) {
	if (a == b)
		return 1;
	else
		return 0;
}


int LocateElem_Sq(SqList *L, int e, int(*compare)(int, int)) {        //查找
	int i, *p;
	i = 1;								//i的初值为第一个元素的位序
	p = L->elem;                        //p的初值为第一个元素的存储位置

	while (i <= L->length && !compare(*p++, e)) {
		++i;
	}
	if (i <= L->length) {
		return i;
	}
	else {
		return 0;
	}
}



void MergeList_Sq(SqList La, SqList Lb, SqList *Lc) {
	//手动输入La,Lb顺序表中的元素，将这两个顺序表进行合并，通过Lc顺序表input。
	Lc->listsize = Lc->length = La.length + Lb.length;		//Lc的长度 = La的长度 + Lb的长度
	int *pc = Lc->elem = (int*)malloc(Lc->listsize * sizeof(int));
	if (!pc) {
		printf("OVERFLOW\n");		//存储分配失败
		return;
	}
	int *pa = La.elem;			//pa指向La第一个元素的存储位置
	int *pb = Lb.elem;			//pb指向Lb第一个元素的存储位置
	int *pa_last = La.elem + La.length - 1;		//pa_last指向La最后一个元素的存储位置
	int *pb_last = Lb.elem + Lb.length - 1;		//pa_last指向La最后一个元素的存储位置
	while (pa <= pa_last && pb <= pb_last) {
		if (*pa <= *pb) *pc++ = *pa++;			//合并
		else *pc++ = *pb++;					//把符合顺序的La和Lb中的元素逐个放入Lc中
	}
	while (pa <= pa_last) *pc++ = *pa++;		//插入La的剩余元素
	while (pb <= pb_last) *pc++ = *pb++;		//插入Lb的剩余元素
}//MergeList_Sq


#pragma once
#include<stdio.h>
#include "stdlib.h"
#include<string.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OVERFLOW -2
#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0  //异常抛出  

/*定义栈结构体*/
typedef struct {
	char * base;//栈的基址 在栈构造之前和销毁之后，base的值为NULL
	char * top;//栈顶指针 
	int size;//栈容量（当前已分配的存储空间，以元素为单位）
}Stack;


/*函数声明*/
int init(Stack *);//构造空栈
char getTop(Stack *);//若栈不空，则用e返回的栈顶元素，并返回OK，否则返回ERROR
int push(Stack *, char);//插入元素e为新的栈顶元素
int pop(Stack *, char *);//若栈不空，则删除stack的栈顶元素，
						 //用e返回其值并返回OK，否则返回ERROR
						 /*
						 * 初始化栈
						 */

int init(Stack *stack) {
	stack->base = (char *)malloc(STACK_INIT_SIZE * sizeof(char));
	if (stack->base == NULL) {
		printf("空间分配失败！\n");
		exit(OVERFLOW);
	}
	stack->top = stack->base;
	stack->size = STACK_INIT_SIZE;
	//printf("初始化完毕！\n");

	return 0;
}//init

char getTop(Stack *stack) {
	//若栈不空，则用e返回stack的栈顶元素，并返回OK，否则返回ERROR
	if (stack->base == stack->top) {
		return ERROR;
	}

	return *(stack->top - 1);
}//getTop


int push(Stack *stack, char e) {			//入栈
	if ((stack->top) - (stack->base) >= stack->size) {//栈满，追加空间
		stack->base = (char *)realloc(stack->base,
			(stack->size + STACKINCREMENT) * sizeof(char));

		if (!stack->base)  exit(OVERFLOW);
		stack->top = (stack->base) + (stack->size);
		stack->size += STACKINCREMENT;
	}
	*(stack->top)++ = e;//先把e压入栈顶，stack.top再增加1指向栈顶元素e的下一个位置  
	return OK;
}//push


int pop(Stack *stack, char *e) {				//出栈
	//若栈不空，则删除stack的栈顶元素，用e返回其值，并返回OK，否则返回ERROR

	if (stack->top == stack->base) {
		printf("栈中无元素可出！\n");
		return ERROR;
	}

	*e = *(stack->top - 1); //stack.top先减1指向栈顶元素，再取值，交给e带回
	stack->top--;
	return 0;

}

 





int main() {
	Stack stack;//声明栈
	char element = ' ';//声明一个元素(空格)用来存放从栈顶取出来的元素
	char *str = (char *)malloc(STACK_INIT_SIZE * sizeof(char));//声明一个用来存储输入的字符串的数组的指针
	int length;//字符串中实际有的元素个数
	int i;//循环变量


	init(&stack);
	printf("输入一串100位以内的字符：\n");
	scanf("%s", str);
	length = strlen(str);
	for (i = 0; i < length; i++) {
		push(&stack, str[i]);

	}
	


	printf("从栈顶读字符：\n");

	while (getTop(&stack)) {
		pop(&stack, &element);
		printf("%c", element);
	}
	
	printf("\n");
  	//int asd; 
	//scanf("%d", &asd);
	system("pause");
	return 0;
}


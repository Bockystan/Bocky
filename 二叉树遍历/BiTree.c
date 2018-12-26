#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10

//定义二叉树的结点
typedef struct Node {
	char data;                  // 结点数据
	struct Node *lChild;        // 左孩子
	struct Node *rChild;        // 右孩子
} Node, *BiTree;

typedef struct Node{
	char data;
	struct Node *rChild;
	struct Node *lChild;
}Node, *;
//定义栈
typedef struct {
	BiTree *base;
	BiTree *top;
	int stacksize;
} Stack;

//栈声明
int initStack(Stack *stack);		//创建栈

int destroyStack(Stack *stack);		//销毁栈

int isStackEmpty(Stack stack);		//判断栈是否为空

int getTop(Stack stack, BiTree *node);//获得栈顶元素

int push(Stack *stack, BiTree node);//入栈

int pop(Stack *stack, BiTree *node);//出栈

//二叉树声明
BiTree createBinaryTree(BiTree T);//创造一棵二叉叉叉叉叉树

int preOrderTraverse(BiTree tree);//先序遍历递归算法

int inOrderTraverse(BiTree tree);//中序遍历递归算法

int postOrderTraverse(BiTree tree);//后序遍历递归算法

int preOrderStackTraverse(BiTree tree);//先序遍历非递归算法

int inOrderStackTraverse(BiTree tree);//中序遍历非递归算法

int postOrderStackTraverse(BiTree tree);//后序遍历非递归算法

int visit(char e);//输出访问元素e 传递二叉树中对结点的操作方式



BiTree createBinaryTree(BiTree T) {
	//按照先序次序输入二叉树中结点的值(!)，‘!’表示空树
	//构造二叉链表表示的二叉树T
	char e;
	scanf("%c", &e);
	if (e == '!') {
		T = NULL;
	}
	else {
		if (!(T = (Node *)malloc(sizeof(Node)))) {
			exit(OVERFLOW);
		}
		T->data = e;                                   // 生成根节点
		T->lChild = createBinaryTree(T->lChild);    // 构造左子树
		T->rChild = createBinaryTree(T->rChild);    // 构造右子树
	}
	return T;
	
}//createBinaryTree

 
 //先序递归
int preOrderTraverse(BiTree tree) {
	if (tree) {
		if (!visit(tree->data)) { 
			return ERROR; 
		};
		preOrderTraverse(tree->lChild);
		preOrderTraverse(tree->rChild);
	}
	return OK;
}

//中序递归
int inOrderTraverse(BiTree tree) {
	if (tree) {
		inOrderTraverse(tree->lChild);
		if (!visit(tree->data)) { 
			return ERROR; 
		};
		inOrderTraverse(tree->rChild);
	}
	return OK;

}


//后序递归
int postOrderTraverse(BiTree tree) {
	if (tree) {
		postOrderTraverse(tree->lChild);
		postOrderTraverse(tree->rChild);
		if (!visit(tree->data)) { 
			return ERROR; 
		};
	}
	return OK;
}

//先序遍历非递归算法
//首先访问当前树的根结点数据，接下来应该依次遍历其左子树和右子树，
//然而程序的控制流只能处理其一，所以考虑将右子树的根保存在栈里面
//若当前指针指向的树为空，说明当前树为空树，
//不需要做任何处理，直接弹出栈顶的子树，为下次循环做准备
int preOrderStackTraverse(BiTree tree) {
	Stack stack;
	BiTree p;//从栈顶弹出的节点
	initStack(&stack);
	push(&stack, tree); // 根指针入栈
	while (!isStackEmpty(stack)) {
		pop(&stack, &p);    //访问根节点
		if (!visit(p->data)) { 
			return ERROR;
		}

		if (p->rChild) { 
			push(&stack, p->rChild);
		}

		if (p->lChild) {
			push(&stack, p->lChild);
		}
		
	}
	destroyStack(&stack);
	return OK;
}//preOrderStack

//中序遍历非递归算法
/*访问其根结点之前应先访问其左子树，因而先将当前根节点入栈，然后考虑其左子树
不断将非空的根节点入栈，直到左子树为一空树；
当左子树为空时，不需要做任何处理，弹出并访问栈顶结点，然后遍历其右子树*/
int inOrderStackTraverse(BiTree tree) {
	Stack stack;
	BiTree p;
	initStack(&stack);
	p = tree;
	while (p || !isStackEmpty(stack)) {
		if (p) {
			push(&stack, p);
			p = p->lChild;    //根指针进栈，遍历左子树
		}
		else {//根指针退栈，访问根节点，遍历右子树
			pop(&stack, &p);
			if (!visit(p->data)) { return ERROR; }
			p = p->rChild;
		}
	}
	destroyStack(&stack);
	return OK;
}//inOrderStack

//*后序遍历非递归算法
int postOrderStackTraverse(BiTree tree) {
	Stack S;
	BiTree p, q;
	initStack(&S);
	push(&S, tree); // 根指针入栈
	while (!isStackEmpty(S)) {
		while (getTop(S, &p) && p && (p->lChild || p->rChild)) {
			push(&S, p->rChild);        // 右子树入栈
			push(&S, p->lChild);        // 左子树入栈
		}//注意栈中存在空指针，表示某个结点的右子树为空
		////若栈顶不为空，说明栈顶对应的树的右子树未处理，则弹出栈顶
		if (!isStackEmpty(S)) {
			pop(&S, &p);
			if (p) {
				if (!visit(p->data)) { return ERROR; }
			}
			else {// 存在右子树为空的结点，继续向上返回
				pop(&S, &p);
				if (!visit(p->data)) { return ERROR; }
			}
			while (getTop(S, &q) && q && p == q->rChild) {//若当前为右子树，则继续出栈
				pop(&S, &p);
				if (!visit(p->data)) { return ERROR; }
				getTop(S, &q);
			}
		}
	}
	destroyStack(&S);
	return OK;
}


int initStack(Stack *stack) {
	stack->base = (BiTree *)malloc(STACK_INIT_SIZE * sizeof(BiTree));
	if (stack->base == NULL) {
		printf("空间分配失败！\n");
		exit(OVERFLOW);
	}
	stack->top = stack->base;
	stack->stacksize = STACK_INIT_SIZE;
	//printf("初始化完毕！\n");

	return 0;
}//init

int isStackEmpty(Stack stack) {
	if (stack.top == stack.base) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}//isStackEmpty

int destroyStack(Stack *stack) {
	if (!stack) {
		printf("指针为空，释放失败.\n");
		exit(0);
	}
	free(stack->base);
	return OK;
}//dest

int getTop(Stack stack, BiTree *node) {
	//若栈不空，则用e返回stack的栈顶元素，并返回OK，否则返回ERROR
	if (stack.base == stack.top) {
		return ERROR;
	}
	*node = *(stack.top - 1);
        return OK;
}//getTop


int push(Stack *stack, BiTree node) {			//入栈
	if ((stack->top) - (stack->base) >= stack->stacksize) {//栈满，追加空间
		stack->base = (BiTree *)realloc(stack->base,
			(stack->stacksize + STACK_INCREMENT) * sizeof(char));

		if (!stack->base)  exit(OVERFLOW);
		stack->top = (stack->base) + (stack->stacksize);
		stack->stacksize += STACK_INCREMENT;
	}
	*(stack->top)++ = node;//先把e压入栈顶，stack.top再增加1指向栈顶元素e的下一个位置  
	return OK;
}//push


int pop(Stack *stack, BiTree *node) {				//出栈
												//若栈不空，则删除stack的栈顶元素，用e返回其值，并返回OK，否则返回ERROR

	if (stack->top == stack->base) {
		printf("栈中无元素可出！\n");
		return ERROR;
	}

	*node = *(stack->top - 1); //stack.top先减1指向栈顶元素，再取值，交给e带回
	stack->top--;
	return 0;

}

int visit(char e) {
	if (e == '\0') {
		return ERROR;
	}
	else {
		printf("%c", e);
	}
	return OK;
}


int main() {
	BiTree tree = NULL;
	printf("请按先序遍历的顺序输入一个二叉树，!代表空结点（如：124!!6!!37!!8!!）：\n");
	tree = createBinaryTree(tree);//把创建好的树的根节点指针赋给tree
	printf("\n递归先序遍历：\n");
	preOrderTraverse(tree);
	printf("\n递归中序遍历：\n");
	inOrderTraverse(tree);
	printf("\n递归后序遍历：\n");
	postOrderTraverse(tree);
	printf("\n非递归先序遍历：\n");
	preOrderStackTraverse(tree);
	printf("\n非递归中序遍历：\n");
	inOrderStackTraverse(tree);
	printf("\n非递归后序遍历：\n");
	postOrderStackTraverse(tree);

	printf("\n");
	return 0;
}
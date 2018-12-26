#include <stdio.h>    
#include<stdlib.h>    
#include<string.h>   
int s2;
int s1;
int m;
typedef struct {
	//char ch;
	int data;
	int parent, lchild, rchild; //parent用于标记是否为没有父节点的树
}Htree, *Hufftree;	//动态分配数组 以便于存储该哈夫曼树
typedef char* Huffcode;//动态分配数组 存储哈弗曼编码表
	 
void select(Hufftree &Ht, int n){//构建哈夫曼树

		char *cd;
		int m1, m2;//最小值与次小值
		m1 = m2 = 100;
		s1 = s2 = 0;//用s1和s2保存  数组中权值最小的两个节点下标
		int i;
		for (i = 1; i <= n; i++)
		{
			if (!Ht[i].parent){
				if (Ht[i].data<m1){//如果比最小值小
					m2 = m1;
					s2 = s1;
					m1 = Ht[i].data;
					s1 = i;
				}

				else if (Ht[i].data < m2) {// 如果小于次小值
					s2 = i;
					m2 = Ht[i].data;
				}
				else
				{//如果大于次小值，则什么都不做  
					;
				}
			}
		}
}

void Huffman(Hufftree &Ht, Huffcode Hc[], int *w, int n) {
	int start;
	char *cd;//暂存
	int i, c, f;
	if (n < 1) {
		return;
	}
	m = 2 * n - 1;//n个叶子节点 总共有m=2*n-1个节点
	Ht = (Htree*)malloc((m + 1) * sizeof(Htree));//0号单元未用
	for (i = 1; i <= n; i++)//初始化前n个节点
	{
		Ht[i].data = w[i - 1];
		Ht[i].parent = 0;
		Ht[i].lchild = -1;
		Ht[i].rchild = -1;
	}
	for (i = n + 1; i <= m; i++) //初始化后n-1个节点  
	{
		Ht[i].data = 0;
		Ht[i].parent = 0;
		Ht[i].lchild = -1;
		Ht[i].rchild = -1;
	}
	for (i = n + 1; i <= m; ++i) //建哈夫曼树
							//Ht[1..i-1]选择parent为0且权值最小的两个节点，用s1 s2存。
	{
		select(Ht, i - 1);
		Ht[s1].parent = i;
		Ht[s2].parent = i;
		Ht[i].lchild = s1;
		Ht[i].rchild = s2;
		Ht[i].data = Ht[s1].data + Ht[s2].data;
	}

	cd = (char *)malloc(n * sizeof(char));//分配求编码的工作空间
	start = 0;
	cd[n - 1] = '\0';					//编码结束符
	for (i = 1; i <= n; i++)			//逐个求哈弗曼编码	
	{
		start = n - 1;					//编码结束符位置
		for (c = i, f = Ht[i].parent; f != 0; c = f, f = Ht[f].parent)//从叶子到根逆向求编码，
																	 //Ht前n个分量表示叶子结点，最后一个根结点
		{
			if (Ht[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		Hc[i] = (char*)malloc((n - start) * sizeof(char));//分配空间
		strcpy(Hc[i], &cd[start]);						  //从cd复制编码到Hc
	}

}
void decode(Hufftree &Ht)//译码
{
	int i, j = 0;
	i = m;
	//printf("%d",m);
	char b[20];
	printf("输入编码 以'#'结束:\n");
	scanf("%s", b);
	printf("译码后的字符为:\n");
	while (b[j] != '#')
	{ 
		if (b[j] == '0')
			i = Ht[i].lchild;
		else
			i = Ht[i].rchild;
		if (Ht[i].lchild == -1)
		{
			printf("%d", Ht[i].data);
			i = m;              //每次译码从头开始  
		}
		j++;
	}
	printf("\n");
}
int main()
{
	Hufftree Ht;
	Huffcode *Hc;
	int w[20];
	int i, n;
	printf("输入要编码字符个数:\n");
	scanf("%d", &n);
	Hc = (Huffcode*)malloc(n * sizeof(Huffcode));
	printf("输入要编码的字符的权值:\n");
	for (i = 0; i<n; i++)
		scanf("%d", &w[i]);
	Huffman(Ht, Hc, w, n);
	printf("字符编码为:\n");
	for (i = 1; i <= n; i++)
	{
		printf("%d  %s\n", w[i - 1], Hc[i]);
	}
	printf(" 译码: \n");
	decode(Ht);
	int abc;
	scanf("%d", &abc); 
	return 0;
	
}
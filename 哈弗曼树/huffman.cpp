#include <stdio.h>    
#include<stdlib.h>    
#include<string.h>   
int s2;
int s1;
int m;
typedef struct {
	//char ch;
	int data;
	int parent, lchild, rchild; //parent���ڱ���Ƿ�Ϊû�и��ڵ����
}Htree, *Hufftree;	//��̬�������� �Ա��ڴ洢�ù�������
typedef char* Huffcode;//��̬�������� �洢�����������
	 
void select(Hufftree &Ht, int n){//������������

		char *cd;
		int m1, m2;//��Сֵ���Сֵ
		m1 = m2 = 100;
		s1 = s2 = 0;//��s1��s2����  ������Ȩֵ��С�������ڵ��±�
		int i;
		for (i = 1; i <= n; i++)
		{
			if (!Ht[i].parent){
				if (Ht[i].data<m1){//�������СֵС
					m2 = m1;
					s2 = s1;
					m1 = Ht[i].data;
					s1 = i;
				}

				else if (Ht[i].data < m2) {// ���С�ڴ�Сֵ
					s2 = i;
					m2 = Ht[i].data;
				}
				else
				{//������ڴ�Сֵ����ʲô������  
					;
				}
			}
		}
}

void Huffman(Hufftree &Ht, Huffcode Hc[], int *w, int n) {
	int start;
	char *cd;//�ݴ�
	int i, c, f;
	if (n < 1) {
		return;
	}
	m = 2 * n - 1;//n��Ҷ�ӽڵ� �ܹ���m=2*n-1���ڵ�
	Ht = (Htree*)malloc((m + 1) * sizeof(Htree));//0�ŵ�Ԫδ��
	for (i = 1; i <= n; i++)//��ʼ��ǰn���ڵ�
	{
		Ht[i].data = w[i - 1];
		Ht[i].parent = 0;
		Ht[i].lchild = -1;
		Ht[i].rchild = -1;
	}
	for (i = n + 1; i <= m; i++) //��ʼ����n-1���ڵ�  
	{
		Ht[i].data = 0;
		Ht[i].parent = 0;
		Ht[i].lchild = -1;
		Ht[i].rchild = -1;
	}
	for (i = n + 1; i <= m; ++i) //����������
							//Ht[1..i-1]ѡ��parentΪ0��Ȩֵ��С�������ڵ㣬��s1 s2�档
	{
		select(Ht, i - 1);
		Ht[s1].parent = i;
		Ht[s2].parent = i;
		Ht[i].lchild = s1;
		Ht[i].rchild = s2;
		Ht[i].data = Ht[s1].data + Ht[s2].data;
	}

	cd = (char *)malloc(n * sizeof(char));//���������Ĺ����ռ�
	start = 0;
	cd[n - 1] = '\0';					//���������
	for (i = 1; i <= n; i++)			//��������������	
	{
		start = n - 1;					//���������λ��
		for (c = i, f = Ht[i].parent; f != 0; c = f, f = Ht[f].parent)//��Ҷ�ӵ�����������룬
																	 //Htǰn��������ʾҶ�ӽ�㣬���һ�������
		{
			if (Ht[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		Hc[i] = (char*)malloc((n - start) * sizeof(char));//����ռ�
		strcpy(Hc[i], &cd[start]);						  //��cd���Ʊ��뵽Hc
	}

}
void decode(Hufftree &Ht)//����
{
	int i, j = 0;
	i = m;
	//printf("%d",m);
	char b[20];
	printf("������� ��'#'����:\n");
	scanf("%s", b);
	printf("�������ַ�Ϊ:\n");
	while (b[j] != '#')
	{ 
		if (b[j] == '0')
			i = Ht[i].lchild;
		else
			i = Ht[i].rchild;
		if (Ht[i].lchild == -1)
		{
			printf("%d", Ht[i].data);
			i = m;              //ÿ�������ͷ��ʼ  
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
	printf("����Ҫ�����ַ�����:\n");
	scanf("%d", &n);
	Hc = (Huffcode*)malloc(n * sizeof(Huffcode));
	printf("����Ҫ������ַ���Ȩֵ:\n");
	for (i = 0; i<n; i++)
		scanf("%d", &w[i]);
	Huffman(Ht, Hc, w, n);
	printf("�ַ�����Ϊ:\n");
	for (i = 1; i <= n; i++)
	{
		printf("%d  %s\n", w[i - 1], Hc[i]);
	}
	printf(" ����: \n");
	decode(Ht);
	int abc;
	scanf("%d", &abc); 
	return 0;
	
}
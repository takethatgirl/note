#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<io.h>
typedef int Status; 
#define ok 1
#define false 0
#define ok 1
#define error 0 
typedef struct
{
	unsigned int weight;
	unsigned int parents;
	unsigned int lchild;
	unsigned int rchild;
}HTNode,*HuffmanTree;
//选出权值最小的两个结点 
void Select(HuffmanTree *HT,int n,int *s1,int *s2)
{
    int i,tmp;
	for(i=1;i<=n;++i)
	{
		if((*HT)[i].parents==0)
		{
			*s1 = i;break;
		}
	}//s1,第一个符合要求的任意权值的结点 
	for(i++;i<=n;++i)
	{
		if((*HT)[i].parents==0)
		{
			*s2 = i;break;
		}
	}//s1,第二个符合要求的任意权值的结点
	if((*HT)[*s1].weight>(*HT)[*s2].weight)
	{
		tmp = *s1;
		*s1 = *s2;
		*s2 = tmp;
	}//保证s1存储的是最小权值的元素的索引 
	for(i++;i<=n;++i)
	{
		if((*HT)[i].weight<=(*HT)[*s1].weight&&(*HT)[i].parents==0)
		{
			*s2 = *s1;
		    *s1 = i;
		}
	}
}//遍历寻找 
//搭建哈夫曼树并生成哈夫曼码 
Status HuffmanCoding(HuffmanTree *HT,int *w,int n)
{
	int m = 2*n - 1;
	int i,j,s1,s2;
	if(n<=1)
	return error;
	*HT = (HuffmanTree)malloc(sizeof(HTNode)*(m+1));
	if(*HT==NULL)
	exit(-1);
	for(i=1;i<=n;++i)
	{
		(*HT)[i].weight = w[i];
		(*HT)[i].parents = 0;
		(*HT)[i].lchild = 0;
		(*HT)[i].rchild = 0;
	}
	for(;i<=m;++i)
	{
		(*HT)[i].weight = 0;
		(*HT)[i].parents = 0;
		(*HT)[i].lchild = 0;
		(*HT)[i].rchild = 0;
	}
	puts("\n哈夫曼树的构造过程如下：");
	printf("HT初态：\n结点  weight  parents  lchild  rchild\n");
	for(i=1;i<=n;++i)
	{
		printf("%2d%8d%8d%8d%8d\n",i,(*HT)[i].weight,(*HT)[i].parents,(*HT)[i].lchild,(*HT)[i].rchild);
	}
	for(i=n+1;i<=m;++i)
	{
		Select(HT,i-1,&s1,&s2);
	    (*HT)[s1].parents = i;
	    (*HT)[s2].parents = i;
	    (*HT)[i].weight = (*HT)[s1].weight+(*HT)[s2].weight;
	    (*HT)[i].lchild = s1;(*HT)[i].rchild = s2;
	    printf("Select: s1 = %d s2 = %d 新生成的第%d个结点:\n",s1,s2,i);
	    printf("%d(w)  %d(p)  %d(l)  %d(r)\n",(*HT)[i].weight,(*HT)[i].parents,(*HT)[i].lchild,(*HT)[i].rchild);
	}
	puts("哈夫曼树的最终状态如下：");
	printf("结点  weight  parents  lchild  rchild\n");
	for(i=1;i<=m;++i)
	{
		printf("%2d%8d%8d%8d%8d\n",i,(*HT)[i].weight,(*HT)[i].parents,(*HT)[i].lchild,(*HT)[i].rchild);
	}	
}
int main()
{
	int w[6] = {0,3,4,5,6};//n = 5
	HuffmanTree HT; 
	HuffmanCoding(&HT,w,4);
	return 0;
}

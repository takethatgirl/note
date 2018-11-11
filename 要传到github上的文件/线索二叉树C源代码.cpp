/*
线索二叉树前言：
二叉树有性质，(1)n0=n2+1,一棵有n个结点的二叉树，(2)n = n0+n1+n2,
由（1）（2）得，2n0+n1= n+1，所以空指针数目是n+1.
用这n+1个指针，存放相应结点在某种遍历的前驱和后继，在以后的遍历中，
可以加快遍历速度，而且还未占用额外的空间。
如果一个结点的左指针是空，则放该结点的遍历前驱，如果一个结点的
右指针为空，则放该结点的遍历后继。但是这样有个副作用，无法知晓，
左右指针域放的是孩子，还是某种遍历的前驱后继。所以设置个标志位，
通过标志位，判断放的是谁。
步骤是，先把二叉树创建好，然后，按照某种遍历方法，操作每一个结点，
操作结点的顺序，刚好是遍历顺序，可以设置一个指针变量pre，始终保存，
上一个被处理的结点。--->>看中序线索二叉树的代码。
处理完毕的结果是，遍历序列的最后一个结点的左指针判断了，但是右指针没进行判断。
但是根据二叉树中序遍历的特点，我们可以“明知”右指针一定是个空指针。
把一棵二叉树线索化后，增设一个头结点，头结点的左孩子指向树根，头结点
的右孩子指向遍历序列的最后一个结点。这样可以达到，从任何一个结点都可以快速
的遍历整个二叉树。整体来看，头结点的左右就是找到中序遍历的最后一个结点，
与整个原线索二叉树无关。
如何找中序线索化二叉树某个结点p的后继？
如果右标志是Thread，说明右指针本来是NULL，现存放的是后继，而不是右孩子。
如果右指针存放的不是后继，那么该结点的后继是，以该结点右孩子为根结点的二叉树
中序遍历的第一个结点，即从p->rchild出发最左结点。
注意：最后一个元素没有后继结点！
如何找中序线索化二叉树某个结点p的前驱？
方法同找后继。
如何遍历中序线索化二叉树？
1，找到从树根出发的最左结点，该结点是中序遍历的第一个结点。
2，from 最左结点 to 中序遍历的最后一个结点（p->rchild==NULL）
注释：它是整个二叉树唯一一个空指针域！
3，不断调用求后继函数，以求后继函数做扫描指针。
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef enum { Link, Thread } PointerTag;
typedef struct node {
	char data;
	struct node *lchild, *rchild;
	PointerTag ltag, rtag;
}BiThrNode,*BiThrTree;
BiThrTree pre = NULL;
/*创建二叉树*/
void Create(BiThrTree *T) {
	char ch;
	scanf("%c", &ch);
	if (ch == '#')
		(*T) = NULL;
	else {
		*T = (BiThrTree)malloc(sizeof(BiThrNode));
		if (!*T) exit(-1);
		(*T)->data = ch;
		(*T)->ltag = Link;
		(*T)->rtag = Link;
		Create(&(*T)->lchild);
		Create(&(*T)->rchild);
	}
}
/*中序遍历二叉树*/
void InOrder(BiThrTree T) {
	if (T) {
		InOrder(T->lchild);
		printf("%c ", T->data);
		InOrder(T->rchild);
	}
}
/*中序线索化一棵二叉树*/
void InThread(BiThrTree T) {
	if (T) {
		InThread(T->lchild);
		if (T->lchild == NULL) {
			T->ltag = Thread;
			T->lchild = pre;
		}
		/*下面是一行very 重要的代码*/
		if (pre != NULL && pre->rchild == NULL) {
			pre->rtag = Thread;
			pre->rchild = T;
		}
		pre = T;
		InThread(T->rchild);
	}
}
/*给线索化后的二叉树加上头结点*/
void HeadInThread(BiThrTree *head, BiThrTree T) {
	(*head) = (BiThrTree)malloc(sizeof(BiThrNode));
	if (!*head) exit(-1);
	if (T == NULL) {
		*head = NULL;
		return;
	}
	InThread(T);
	(*head)->lchild = T;//指向根结点
    (*head)->rchild = pre;//指向中序遍历的最后一个结点
}
/*求线索二叉树的中序遍历的后继结点*/
BiThrTree LDRNext(BiThrTree p) {
	if (p == NULL || p->rchild == NULL)
		return NULL;
	if (p->rtag == Thread)
		return p->rchild;
	else {
		p = p->rchild;
		while (p->ltag == Link) {
			p = p->lchild;
		}
		return p;
	}
}
/*求线索二叉树的中序遍历的前驱结点*/
BiThrTree LDRPre(BiThrTree p) {
	if (p == NULL)//其实应该加个p不是中序遍历的第一个结点
		return NULL;
	if (p->ltag == Thread)
		return p->lchild;
	else {
		p = p->lchild;
		while (p->rtag == Link)
			p = p->rchild;
	}
}
/*中序遍历线索二叉树*/
void LDR(BiThrTree head) {
	if (head == NULL)
		return;
	BiThrTree p = head;
	while (p->lchild) {
		p = p->lchild;
	}
	while (p) {
		printf("%c ", p->data);
		p = LDRNext(p);
	}
	printf("\n");
}
int main() {
	BiThrTree T,head;
	Create(&T);
	HeadInThread(&head, T);
	LDR(head);
	system("pause");
	return 0;
}

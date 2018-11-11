/*
����������ǰ�ԣ�
�����������ʣ�(1)n0=n2+1,һ����n�����Ķ�������(2)n = n0+n1+n2,
�ɣ�1����2���ã�2n0+n1= n+1�����Կ�ָ����Ŀ��n+1.
����n+1��ָ�룬�����Ӧ�����ĳ�ֱ�����ǰ���ͺ�̣����Ժ�ı����У�
���Լӿ�����ٶȣ����һ�δռ�ö���Ŀռ䡣
���һ��������ָ���ǿգ���Ÿý��ı���ǰ�������һ������
��ָ��Ϊ�գ���Ÿý��ı�����̡����������и������ã��޷�֪����
����ָ����ŵ��Ǻ��ӣ�����ĳ�ֱ�����ǰ����̡��������ø���־λ��
ͨ����־λ���жϷŵ���˭��
�����ǣ��ȰѶ����������ã�Ȼ�󣬰���ĳ�ֱ�������������ÿһ����㣬
��������˳�򣬸պ��Ǳ���˳�򣬿�������һ��ָ�����pre��ʼ�ձ��棬
��һ��������Ľ�㡣--->>�����������������Ĵ��롣
������ϵĽ���ǣ��������е����һ��������ָ���ж��ˣ�������ָ��û�����жϡ�
���Ǹ��ݶ���������������ص㣬���ǿ��ԡ���֪����ָ��һ���Ǹ���ָ�롣
��һ�ö�����������������һ��ͷ��㣬ͷ��������ָ��������ͷ���
���Һ���ָ��������е����һ����㡣�������Դﵽ�����κ�һ����㶼���Կ���
�ı�������������������������ͷ�������Ҿ����ҵ�������������һ����㣬
������ԭ�����������޹ء�
���������������������ĳ�����p�ĺ�̣�
����ұ�־��Thread��˵����ָ�뱾����NULL���ִ�ŵ��Ǻ�̣��������Һ��ӡ�
�����ָ���ŵĲ��Ǻ�̣���ô�ý��ĺ���ǣ��Ըý���Һ���Ϊ�����Ķ�����
��������ĵ�һ����㣬����p->rchild���������㡣
ע�⣺���һ��Ԫ��û�к�̽�㣡
���������������������ĳ�����p��ǰ����
����ͬ�Һ�̡�
��α���������������������
1���ҵ������������������㣬�ý������������ĵ�һ����㡣
2��from ������ to ������������һ����㣨p->rchild==NULL��
ע�ͣ���������������Ψһһ����ָ����
3�����ϵ������̺����������̺�����ɨ��ָ�롣
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
/*����������*/
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
/*�������������*/
void InOrder(BiThrTree T) {
	if (T) {
		InOrder(T->lchild);
		printf("%c ", T->data);
		InOrder(T->rchild);
	}
}
/*����������һ�ö�����*/
void InThread(BiThrTree T) {
	if (T) {
		InThread(T->lchild);
		if (T->lchild == NULL) {
			T->ltag = Thread;
			T->lchild = pre;
		}
		/*������һ��very ��Ҫ�Ĵ���*/
		if (pre != NULL && pre->rchild == NULL) {
			pre->rtag = Thread;
			pre->rchild = T;
		}
		pre = T;
		InThread(T->rchild);
	}
}
/*����������Ķ���������ͷ���*/
void HeadInThread(BiThrTree *head, BiThrTree T) {
	(*head) = (BiThrTree)malloc(sizeof(BiThrNode));
	if (!*head) exit(-1);
	if (T == NULL) {
		*head = NULL;
		return;
	}
	InThread(T);
	(*head)->lchild = T;//ָ������
    (*head)->rchild = pre;//ָ��������������һ�����
}
/*����������������������ĺ�̽��*/
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
/*�����������������������ǰ�����*/
BiThrTree LDRPre(BiThrTree p) {
	if (p == NULL)//��ʵӦ�üӸ�p������������ĵ�һ�����
		return NULL;
	if (p->ltag == Thread)
		return p->lchild;
	else {
		p = p->lchild;
		while (p->rtag == Link)
			p = p->rchild;
	}
}
/*�����������������*/
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

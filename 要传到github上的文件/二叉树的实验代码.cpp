#include<stdio.h>
#include<stdlib.h>
typedef struct node {
	struct node *lchild, *rchild;
	char data;
}BiTNode, *BiTree;
void Create(BiTree *T) {
	char ch;
	scanf("%c", &ch);
	if (ch == '#')
		*T = NULL;
	else {
		*T = (BiTree)malloc(sizeof(BiTNode));
		if (*T == NULL) exit(-1);
		(*T)->data = ch;
		Create(&((*T)->lchild));
		Create(&((*T)->rchild));
	}
}

void DLR(BiTree T) {
	if(T) {
		printf("Ç°%c\n",T->data);
		DLR(T->lchild);
		DLR(T->rchild);
		printf("ºó%c\n",T->data);
	}
}

int main() {
	BiTree T;
	Create(&T);
	int i = 3;
    DLR(T);
	return 0;
}

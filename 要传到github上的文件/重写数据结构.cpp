/*�����ɱ�ġ����顱*/ 
#include<stdio.h>
#include<stdlib.h>
#define INIT_SIZE 100
#define INCREMENT 10
typedef struct {
	char *base;//����ַ 
	unsigned count;//����Ԫ�ظ��� 
	unsigned size;//�������� 
}SqList;
/*��ʼ��˳���*/
void InitList(SqList *L) {
	(*L).base = (char*)malloc(sizeof(char)*INIT_SIZE);
	if(!(*L).base) exit(-1);
	(*L).count = 0;
	(*L).size = INIT_SIZE;
}

int main() {
	
	return 0;
}

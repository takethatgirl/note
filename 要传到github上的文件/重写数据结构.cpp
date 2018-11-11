/*容量可变的“数组”*/ 
#include<stdio.h>
#include<stdlib.h>
#define INIT_SIZE 100
#define INCREMENT 10
typedef struct {
	char *base;//基地址 
	unsigned count;//数组元素个数 
	unsigned size;//数组容量 
}SqList;
/*初始化顺序表*/
void InitList(SqList *L) {
	(*L).base = (char*)malloc(sizeof(char)*INIT_SIZE);
	if(!(*L).base) exit(-1);
	(*L).count = 0;
	(*L).size = INIT_SIZE;
}

int main() {
	
	return 0;
}

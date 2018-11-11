#include<stdio.h>
#include<stdlib.h>
 
void f() {
	static int a;
	printf("a = %d\n",a++);
	printf("a = %d\n\n",a);
}
int main() {
int *a = (int*)malloc(sizeof(int)*100);
printf("a[2] = %d\n",a[2]);
int b[100];	
printf("b[3] = %d\n",b[3]);

	f();
	f();
	return 0;
} 

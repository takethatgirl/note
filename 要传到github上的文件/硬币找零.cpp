#include<stdio.h>
int MinOuShu(int *a,int len) {
	int min;
	int flag = 0;
	for(int i = 0;i < len;++i) {
		if(flag == 0) {
			if(a[i] % 2 == 0) {
				min = i;
				flag = 1;
			}
		}
		else {
			if(a[i] % 2 == 0 && a[i] < a[min])
			min = i; 
		}
	}
	return a[min];
}

int main() {
	int a[10] = {1,2,3,4,5,10,6,7,8,9};
	printf("%d\n",MinOuShu(a,10));
}

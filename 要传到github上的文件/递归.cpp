#include<stdio.h>
void reversePrint(int *arr,int len) {
	if(arr == NULL || len <= 0)
	return;
	if(len == 1) {
		printf("%d ",arr[0]);
	}
	else {
		reversePrint(arr+1,len-1);
		printf("%d ",arr[0]);
	}
} 

int main() {
	int arr[7] = {1,22,3,43,8,10,23};
	reversePrint(arr,7);
} 

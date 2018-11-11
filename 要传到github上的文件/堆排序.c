#include<stdio.h>
void swap(int *a,int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
//���µ���
void downAdjust(int *arr,int len,int i) {
	
	while(i <= (len-1) / 2) {
		int min = 2*i;
		if(2*i+1 <= len-1) {
			min = arr[2*i+1] <= arr[min] ? 2*i+1:2*i;  
		}
		if(arr[i] > arr[min]) {
			swap(&arr[i],&arr[min]);
			i = min;
		}
		else
		break;
	}
} 
//���� 
void createDeap(int *arr,int len) {
	int i;
	for(i = (len-1) / 2;i >= 1;--i) {
		downAdjust(arr,len,i);
	}
}
//������ 
void heapSort(int *arr,int len) {
	createDeap(arr,len);
	int i = len-1;
	while(i >= 1) {
		swap(&arr[i],&arr[1]);
		downAdjust(arr,i,1);
		--i;
	}
}
int main() {
	int arr[10] = {0,12,4,6,4,5,83,3444,76,465};
	heapSort(arr,10);
	int i;
	for(i = 0;i < 10;++i) {
		printf("%d ",arr[i]);
	}
	return 0;
}

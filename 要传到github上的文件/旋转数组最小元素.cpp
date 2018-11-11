#include<stdio.h>

int findMax(int *a,unsigned n) {
	if(n <= 0)
	return -1;
	if(n == 1)
	return a[n-1];
	int key = a[n-1];
	int i = 0;
	int j = n - 2;
	int mid;
	while(i < j) {
		mid = i + (j - i) / 2;
		if(a[mid] > key) {
			i = mid + 1;
		}
		else if(a[mid] > key){
			j = mid - 1;
		}
		else {
			
		}
	}
	return a[i] > key ? key : a[i];
}

int main() {
	int a[10] = {3,4,4,0,2,2,2,2,2,2};
	printf("%d\n",findMax(a,10));
	return 0;
}

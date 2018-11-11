#include<stdio.h>
int MoreThanHalfNum(int *a,int start,int end) {
	if(start == end)
	return a[start];
	int i = start;
	int j = end;
	int key = a[i];
	while(i < j) {
		while(i < j && a[j] >= key)
		--j;
		a[i] = a[j];
		while(i < j && a[i] <= key) 
		++i;
		a[j] = a[i];
	}
	a[i] = key;
	if(i = start + (end - start) / 2)
		return key;
		else if(i > start + (end - start) / 2)
		return MoreThanHalfNum(a,start,i-1);
		else
		return MoreThanHalfNum(a,i+1,end);
}
int main() {
	int a[14] = {0,1,2,1,1,2,1,12,1,42,32,1,1,1};
	printf("%d \n",MoreThanHalfNum(a,0,13));
	return 0;
}

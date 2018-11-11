#include<stdio.h>
#include<limits.h>
#include<math.h>
#include<stdlib.h>
#define BUCKETSIZE 10
/*获取数字的位数*/
int GetLoopTimes(int num) {
	int count = 0;
	while (num) {
		num /= 10;
		++count;
	}
	printf("最大数是%d位数\n",count);
	return count;
}
/*查询数组中最大的数*/
int SearchMax(int *a, int n) {
	int k = 0;
	int i;
	for (i = 0; i < n; ++i) {
		if (a[i] > a[k])
			k = i;
	}
	printf("最大数是%d\n",a[k]);
	return a[k];
}
/*针对第loop位入桶排序再取出*/
bool LoopSort(int *a, int n, int loop) {
	int i, j, row_index;
	int buckets[10][BUCKETSIZE] = {0};
	int divisor = (int)(pow(10, loop - 1));
	for (i = 0; i < n; ++i) {
		row_index = (a[i] / divisor) % 10;
		for (j = 0; j < BUCKETSIZE && buckets[row_index][j] != 0; ++j)
			;
		if (j == BUCKETSIZE)
			return false;
			printf("%d入桶%d\n",a[i],row_index);
		buckets[row_index][j] = a[i];
	}
	/*从桶中取出数据恢复*/
	j = 0;
	for (i = 0; i < 10; ++i) {
		while (buckets[i][j] != 0) {
			*a = buckets[i][j];
			a++;
			++j;
		}
		j = 0;
	}
}
void BucketSort(int *a, int n) {
	int looptimes = GetLoopTimes(SearchMax(a, n));
	int i, status;
	for (i = 1; i <= looptimes; ++i) {
	    LoopSort(a, n, i);
	}
}

int main() {
	int arr[5] = {466,200,100,312,566};
	BucketSort(arr,5);
	for(int i = 0;i < 5;++i) {
		printf("%d ",arr[i]);
	}
}

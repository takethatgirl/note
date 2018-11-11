/*输出一个数组的《和最大的连续序列》的和*/
/*算法流程
设置一个变量maxsum始终保存最大sum的值。 
   从第一个元素到最后一个元素不断sum，
   sum是0，放弃，从下一位从心开始sum，
   sum是正数，在sum基础上继续sum 。
   每一个sum都与当前maxsum比较，大于它，变更新maxsum。
   maxsum只会是所有正数sum中的一个。 
   */ 
#include<stdio.h>
int startpos,endpos; 
int Maxsum(int *a,int start,int end) {
	int maxsum = a[start];
	int sum = 0;
	int i;
	for(i = start;i <= end;++i) {
		sum += a[i];
		if(sum > maxsum)
		maxsum = sum;
		endpos = i;
		if(sum < 0)
		sum = 0; 
		startpos = i + 1;
	}
	return maxsum;
}
int main() {
	int a[6] = {-9,-2,-8,7,-1,2};
	printf("maxsum = %d,%d,%d\n",Maxsum(a,0,5),startpos,endpos);
	return 0;
}

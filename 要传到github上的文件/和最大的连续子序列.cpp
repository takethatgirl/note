/*���һ������ġ��������������С��ĺ�*/
/*�㷨����
����һ������maxsumʼ�ձ������sum��ֵ�� 
   �ӵ�һ��Ԫ�ص����һ��Ԫ�ز���sum��
   sum��0������������һλ���Ŀ�ʼsum��
   sum����������sum�����ϼ���sum ��
   ÿһ��sum���뵱ǰmaxsum�Ƚϣ��������������maxsum��
   maxsumֻ������������sum�е�һ���� 
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

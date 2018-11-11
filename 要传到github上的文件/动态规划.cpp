#include<stdio.h>
#define row 100
//maxsum
int MaxSum(int D[][row],int i,int j,int N) {
	if(i == N)
	return D[i][j];
	else {
		int x = MaxSum(D,i+1,j,N) + D[i][j];
		int y = MaxSum(D,i+1,j+1,N) + D[i][j];
		return x > y ? x : y;
	}
}

int main() {
	int D[row][row];
	D[1][1] = 7;
	D[2][1] = 3; D[2][2] = 8;
	D[3][1]=8; D[3][2]=1; D[3][3]=0;
	D[4][1]=2; D[4][2]=7; D[4][3]=4;D[4][4] = 4;
	D[5][1]=4;D[5][2] = 5;D[5][3] = 2;D[5][4] = 6; D[5][5] = 5;
	
	int result = MaxSum(D,1,1,5);
	printf("%d \n",result);
	return 0;
}

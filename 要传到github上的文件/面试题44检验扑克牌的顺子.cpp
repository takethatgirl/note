#include<stdio.h>
#include<string.h>
#define ConsecutiveTimes 5
#define king '$'
/*���5���˿����Ƿ�Ϸ�*/
bool CheckCardIsOK(char *str) {
	if(str == NULL)
	return false;
	if(strlen(str) != ConsecutiveTimes)
	return false;
	int i;
	for(i = 0;i < ConsecutiveTimes;++i) {
		if(!(str[i]>'2'&&str[i]<':')||str[i]=='J'||str[i]=='Q'||str[i]=='K'||str[i]=='A'||str[i]==king)
		return false;
	}
	return true;
} 
/*�ж����ĸ���*/ 
int NumOfKing(char *str) {
	int i,count = 0;
	for(i = 0;i < ConsecutiveTimes;++i) {
		if(str[i] == king)
		{
			++count;
		}
		
	}
	return count;
}
/*�ַ�����ת������������*/
void CharToInt(char *str,int kingnum) {
	int i;
	for(i = 0;i < ConsecutiveTimes - kingnum;++i) {
		if(str[i]>'2'&&str[i]<':')
		str[i] -= '0';
		else if(str[i] == 'J')
		str[i] -= 63;
		else if(str[i] == 'Q')
		str[i] -= 70;
		else if(str[i] == 'K')
		str[i] -= 64;
		else
		str[i] -= 54;
	}
}
/*����*/
void Sort(char *str) 
bool JudgeIsConsecutiveOf5(char *str) {
	;
}
int main() {
	
	return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int flag = 1;//ȫ�ֱ�������Ϊ�����ķ���ֵ
/*
���һ���ַ����ĸ�ʽ�Ƿ���ȷ
����ֵ��-2����ʽ����
����ֵ��-1����ʽ��ȷ���ַ�����ʾ����
����ֵ��0����ʽ��ȷ���ַ�����ʾ0
����ֵ��1����ʽ��ȷ���ַ�����ʾ����
����ֵ��2�����ַ���
*/
int FormIsOk(char *string) {
	/**/
	char *p = string;
	if (p == NULL)
		return 2;/*���ַ�������2*/
	if (*p == '-') {
		++p;
		while (*p != '\0' && *p == '0') {
			++p;
		}
		if (*p == '\0' || *p != *(string + 1))
			return -2;
		while (*p != '\0') {
			if (!(*p >= '0' && *p <= '9'))
				return -2;
			++p;
		}
		return -1;/*��������-1*/
	}
	else if (*p == '0') {
		if (*++p == '\0')
			return 0;/*0����0*/
		return -2;
	}
	else {
		while (*p != '\0') {
			if (!(*p >= '0' && *p <= '9'))
				return -2;
			++p;
		}
		return 1;/*��������1*/
	}
}
/*��һ���ǿ��ַ���ÿλ��char��ת����int����*/
void EveryCharToInt(char *str) {
	while (*str != '\0') {
		*str -= '0';
		++str;
	}
}
/*
����һ����ʾ�������ַ���ת���ɵ�����ֵ
flag = 3 �� ����ֵ��3������Ǵ�������long long��Χ
flag =1��ת�������ȷ������.
*/
long long int PositiveStringToInt(char *str) {
	int length = strlen(str);
	EveryCharToInt(str);
	long long int sum = 0, weight = 1,beforesum,beforeweight;
	int i;
	for (i = length - 1; i >= 0; --i) {
		beforesum = sum;
		sum += str[i] * weight;
		if (sum != str[i] * weight + beforesum) {
			flag = 3;
			return 3;
		}
		beforeweight = weight;
		weight *= 10;
		if (weight / 10 != beforeweight) {
			flag = 3;
			return 3;
		}
	}
	return sum;
}
/*�ַ���ת��������*/
/*
flag = 1���ɹ�ת������������ȷ���
flag = -2�ҷ���ֵ��-2 :�ַ�����ʽ����
flag = 2�ҷ���ֵ��2���ַ����ǿ�
flag = 3������������޷�ת��������
*/
long long int StringToInt(char *string) {
	long long int sum;
	int result = FormIsOk(string);
	if (result == -2) {
		flag = -2;
		return -2;/*�ַ�����ʽ����*/
	}
	else if (result == 2) {
		flag = 2;
		return 2;/*���ַ���*/
	}
	/*��ʼת�����ַ�����0ʱ������0*/
	else if (result == 0) {
		flag = 1;
		return 0;
	}
	else if (result == -1){
		char *p = string + 1;
		sum = PositiveStringToInt(p);
		if (flag != 3)
			return -sum;
		else
			return 0;
	}
	else {
		sum = PositiveStringToInt(string);
		if (flag != 3)
			return sum;
		else
			return 0;
	}
}
int main() {
	char p[100] = "922337203685477580";
	long long int num;
	num = StringToInt(p);
	if (flag == 3)
		printf("flag = %d,���\n",flag);
	else if (flag == 1)
		printf("flag = %d,num = %lld\n", flag,num);
	else if (flag == 2)
		printf("flag = %d,���ַ���\n",flag);
	else
		printf("flag = %d,�ַ�����ʽ����\n",flag);
	system("pause");
	return 0;
}

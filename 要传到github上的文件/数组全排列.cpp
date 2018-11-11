#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int flag = 1;//全局变量，作为函数的返回值
/*
检测一个字符串的格式是否正确
返回值是-2，格式错误
返回值是-1，格式正确且字符串表示负数
返回值是0，格式正确且字符串表示0
返回值是1，格式正确且字符串表示正数
返回值是2，空字符串
*/
int FormIsOk(char *string) {
	/**/
	char *p = string;
	if (p == NULL)
		return 2;/*空字符串返回2*/
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
		return -1;/*负数返回-1*/
	}
	else if (*p == '0') {
		if (*++p == '\0')
			return 0;/*0返回0*/
		return -2;
	}
	else {
		while (*p != '\0') {
			if (!(*p >= '0' && *p <= '9'))
				return -2;
			++p;
		}
		return 1;/*正数返回1*/
	}
}
/*把一个非空字符串每位由char型转换成int类型*/
void EveryCharToInt(char *str) {
	while (*str != '\0') {
		*str -= '0';
		++str;
	}
}
/*
返回一个表示正数的字符串转换成的整型值
flag = 3 且 返回值是3，结果是大数超出long long范围
flag =1，转换结果正确并返回.
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
/*字符串转换成整数*/
/*
flag = 1：成功转换并返回了正确结果
flag = -2且返回值是-2 :字符串格式错误
flag = 2且返回值是2：字符串是空
flag = 3：大数溢出，无法转换成整型
*/
long long int StringToInt(char *string) {
	long long int sum;
	int result = FormIsOk(string);
	if (result == -2) {
		flag = -2;
		return -2;/*字符串格式错误*/
	}
	else if (result == 2) {
		flag = 2;
		return 2;/*空字符串*/
	}
	/*开始转换，字符串是0时，返回0*/
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
		printf("flag = %d,溢出\n",flag);
	else if (flag == 1)
		printf("flag = %d,num = %lld\n", flag,num);
	else if (flag == 2)
		printf("flag = %d,空字符串\n",flag);
	else
		printf("flag = %d,字符串格式错误\n",flag);
	system("pause");
	return 0;
}

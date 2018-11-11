/*改良后的KMP算法*/
/*   http://www.cnblogs.com/tangzhengyue/p/4315393.html
在一段正文中查找特定的字符串，如果采用暴力匹配算法，
  出现不相等时，正文要回退到上次开始匹配的下一个位置，
  子串要回退到1号字符位置，时间效率是 m*n
  ************************************************************
  KMP算法有"记忆功能"，能利用上次匹配的信息，减少下一次匹配的回退长度.
  出现不相等时，分为两种情况：
  1.子串的第一个字符不相等：正文索引i前进一个位置，继续与子串开头匹配.
  2.子串的非第一个字符不相等：正文索引不变，子串索引跳到其next值，再
    继续匹配。
  3.直到正文结束或子串结束
****子串的next至于子串自身有关，与其他皆无关****
引入概念：
next(x) = y的含义：
模式串【1，2，…, y-1】与【x-y+1，x-y+2，…，x-1】完全匹配，那很显然，
next(x+1) = y + 1
一个字符key[i]的next值不止一个！只是不同的next值[1 -- next[j]](j<i),
长度不一，我们要找的是最长的next位。
求next值过程：
根本思想是，from 1 to last -1 根据本位的next值求下一位的next的值.
1，分配一个与子串长度相等的数组
2，预定义0号字符next值是 -1
3，如果本位与next位相等，就得出下一字符的next值【注释：此步可优化】
4，不相等，就找本位的下下一个next值，直到找到与本位相等的next值或
   next值超出数组，即=-1时结束，并填写下一个字符的next值。
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void Next(char *strkey, int* &next) {
	int keylen = strlen(strkey);//获取待匹配串的长度
	next = (int*)malloc(sizeof(int)*keylen);
	if (!next) exit(-1);//分配等长的next数组
	next[0] = -1;//预定义0号字符的next值是-1；
	/*根据本位，推出下一位的next值。从0号字符开始推*/
	int k = -1;//k始终保存当前扫描位的next值，这点十分重要 
	int i = 0;
	while (i < keylen - 1) {//遍历 1--last - 1 
		if (-1 == k || strkey[i] == strkey[k]) {
			/*满足字符和它的next字符相等就填写下一个字符的next值
			不满足，继续找直到找到相等的next值，或者next == -1*/
			++i; ++k;
			if (strkey[i] != strkey[k] || k == 0)//**
				next[i] = k;//**
			else //**   这4行是优化改进的核心代码 
				next[i] = next[k];//**
		}
		else
			k = next[k];//找更短的"回跳比肩next值" 
	}
}
int KMP(char *txt, char *strkey, int *next) {
	int txtlen = strlen(txt);//正文长度
	int keylen = strlen(strkey);//子串长度
	int i = 0, j = 0;//扫描，不能使用for循环
	while (i < txtlen && j < keylen) {
		if (txt[i] == strkey[j]) {
			++i;
			++j;
		}
		else {/*难点就是：不相等时，有两种情况要分别处理！！*/
			if (j == 0) {
				++i;
			}
			else
				j = next[j];
		}
	}
	if (j == keylen && i <= txtlen) {
		return i - keylen + 1;
	}
	else {
		return 0;
	}
}
int main() {
	int *next;//用于接收Next函数传出的next数组的首地址
	char txt[200];
	printf("请输入你的正文：\n");
	gets(txt);
	printf("请输入你要查找的子串:\n");
	char strkey[20];
	//	fflush(stdin);
	gets(strkey);
	Next(strkey, next);
	printf("子串的next求值结果：\n");
	for (unsigned int i = 0; i <= strlen(strkey) - 1; ++i) {
		printf("%5c", strkey[i]);
	}
	printf("\n");
	for (unsigned int i = 0; i <= strlen(strkey) - 1; ++i) {
		printf("%5d", next[i]);
	}
	printf("\n");
	int pos = KMP(txt, strkey, next);
	if (pos)
		printf("字符匹配，匹配点是%d\n", pos);
	else
		printf("字符失配！\n");
	system("pause");
	return 0;
}


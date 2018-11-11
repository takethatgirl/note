/*�������KMP�㷨*/
/*   http://www.cnblogs.com/tangzhengyue/p/4315393.html
��һ�������в����ض����ַ�����������ñ���ƥ���㷨��
  ���ֲ����ʱ������Ҫ���˵��ϴο�ʼƥ�����һ��λ�ã�
  �Ӵ�Ҫ���˵�1���ַ�λ�ã�ʱ��Ч���� m*n
  ************************************************************
  KMP�㷨��"���书��"���������ϴ�ƥ�����Ϣ��������һ��ƥ��Ļ��˳���.
  ���ֲ����ʱ����Ϊ���������
  1.�Ӵ��ĵ�һ���ַ�����ȣ���������iǰ��һ��λ�ã��������Ӵ���ͷƥ��.
  2.�Ӵ��ķǵ�һ���ַ�����ȣ������������䣬�Ӵ�����������nextֵ����
    ����ƥ�䡣
  3.ֱ�����Ľ������Ӵ�����
****�Ӵ���next�����Ӵ������йأ����������޹�****
������
next(x) = y�ĺ��壺
ģʽ����1��2����, y-1���롾x-y+1��x-y+2������x-1����ȫƥ�䣬�Ǻ���Ȼ��
next(x+1) = y + 1
һ���ַ�key[i]��nextֵ��ֹһ����ֻ�ǲ�ͬ��nextֵ[1 -- next[j]](j<i),
���Ȳ�һ������Ҫ�ҵ������nextλ��
��nextֵ���̣�
����˼���ǣ�from 1 to last -1 ���ݱ�λ��nextֵ����һλ��next��ֵ.
1������һ�����Ӵ�������ȵ�����
2��Ԥ����0���ַ�nextֵ�� -1
3�������λ��nextλ��ȣ��͵ó���һ�ַ���nextֵ��ע�ͣ��˲����Ż���
4������ȣ����ұ�λ������һ��nextֵ��ֱ���ҵ��뱾λ��ȵ�nextֵ��
   nextֵ�������飬��=-1ʱ����������д��һ���ַ���nextֵ��
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void Next(char *strkey, int* &next) {
	int keylen = strlen(strkey);//��ȡ��ƥ�䴮�ĳ���
	next = (int*)malloc(sizeof(int)*keylen);
	if (!next) exit(-1);//����ȳ���next����
	next[0] = -1;//Ԥ����0���ַ���nextֵ��-1��
	/*���ݱ�λ���Ƴ���һλ��nextֵ����0���ַ���ʼ��*/
	int k = -1;//kʼ�ձ��浱ǰɨ��λ��nextֵ�����ʮ����Ҫ 
	int i = 0;
	while (i < keylen - 1) {//���� 1--last - 1 
		if (-1 == k || strkey[i] == strkey[k]) {
			/*�����ַ�������next�ַ���Ⱦ���д��һ���ַ���nextֵ
			�����㣬������ֱ���ҵ���ȵ�nextֵ������next == -1*/
			++i; ++k;
			if (strkey[i] != strkey[k] || k == 0)//**
				next[i] = k;//**
			else //**   ��4�����Ż��Ľ��ĺ��Ĵ��� 
				next[i] = next[k];//**
		}
		else
			k = next[k];//�Ҹ��̵�"�����ȼ�nextֵ" 
	}
}
int KMP(char *txt, char *strkey, int *next) {
	int txtlen = strlen(txt);//���ĳ���
	int keylen = strlen(strkey);//�Ӵ�����
	int i = 0, j = 0;//ɨ�裬����ʹ��forѭ��
	while (i < txtlen && j < keylen) {
		if (txt[i] == strkey[j]) {
			++i;
			++j;
		}
		else {/*�ѵ���ǣ������ʱ�����������Ҫ�ֱ�����*/
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
	int *next;//���ڽ���Next����������next������׵�ַ
	char txt[200];
	printf("������������ģ�\n");
	gets(txt);
	printf("��������Ҫ���ҵ��Ӵ�:\n");
	char strkey[20];
	//	fflush(stdin);
	gets(strkey);
	Next(strkey, next);
	printf("�Ӵ���next��ֵ�����\n");
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
		printf("�ַ�ƥ�䣬ƥ�����%d\n", pos);
	else
		printf("�ַ�ʧ�䣡\n");
	system("pause");
	return 0;
}


#define FREQUENT 100//����Ƶ��
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef int Boolean;
#define baseYear 2017 //year standard according to protocol 
#define true 1
#define false 0
#define ok 1
#define error 0
struct tag {
	int number;
	char cityName[20];
};
/*save substrings from splited original string*/
struct splitString {
	char ss[10];
};

//�ͻ����ݴ��ϴη��͵�����֡

//�������ݴ��ϴ��յ�������֡��ʱ��
unsigned char lastTime;
//�ط���־λ
Boolean repeatSendFlag = true;

unsigned char defaultCodeData[10];//�洢��������±���������
int len;//����֡�ֽڳ���

void InitCity(struct tag * CITY);//���챾�ء�����-���롿ӳ���
Boolean ReadBitValue(unsigned char data, int pos);//��ĳ��bit��1����0
Boolean ReadIntBitValue(int data, int pos);//��ĳ��bit��1����0
void setBitValue(unsigned char *data, int pos, Boolean flag);//����ĳ��bitΪ1��0
Boolean NumsOfOneIsOdd8(unsigned char data);//�Ե����ֽڽ�����У��
Boolean OddCheck(unsigned char *codeData, int len);//������֡��У��
Boolean NumsOfOneIsOdd7(unsigned char data);//����һ���ֽ�ǰ7��bit 1�ĸ���
void Pack(unsigned char *data);//��װ�ֽڣ�ʹ�������У��λ
int StringToInt(char* str);//�ַ���ת��������
void Encode(unsigned char* defaultCodeData, int *len);//����
void Decode(unsigned char *defaultCodeData);//����
void Next();//������ͣ

/*��ʼ���洢���д���Ĳ�ѯ����*/
void InitCity(struct tag * CITY) {
	int k = 0;
	for (; k < 10; ++k) {
		CITY[k].number = k;
	}
	strcpy(CITY[0].cityName, "����");
	strcpy(CITY[1].cityName, "����");
	strcpy(CITY[2].cityName, "�Ϻ�");
	strcpy(CITY[3].cityName, "�Ͼ�");
	strcpy(CITY[4].cityName, "����");
	strcpy(CITY[5].cityName, "����");
	strcpy(CITY[6].cityName, "����");
	strcpy(CITY[7].cityName, "����");
	strcpy(CITY[8].cityName, "�ɶ�");
	strcpy(CITY[9].cityName, "���");
}
 
/*
read a signal bit of the byte,if 1,return true;else return fasle
*/
Boolean ReadBitValue(unsigned char data, int pos) {
	return (data >> (pos - 1)) & 1 ? true : false;
}
/*
read a signal bit of the integer,if 1 return true;else return false
*/
Boolean ReadIntBitValue(int data, int pos) {
	return (data >> (pos - 1)) & 1 ? true : false;
}
/*suspended program...*/
void Next() {
	printf("\n-----------------������ͣ----------------\n Next/exit: y/n ? ");
	char ch;
	scanf("%c", &ch);
    fflush(stdin);
	printf("\n");
	if (ch == 'n')
		exit(-1);
}
/*
set pos bit of a byte to 1 or 0
if flag == true, set 1; else,set 0
*/
void setBitValue(unsigned char *data, int pos, Boolean flag) {
	if (pos < 1 || pos > 8) {
		printf("input bit value a byte out of range\n");
		return;
	}
	if (flag == true)
		*data |= (1 << (pos - 1));
	else
		*data &= (~(1 << (pos - 1)));
}
/*����һ��int������ĳ��bit*/
void setBitValueInt(int *data, int pos, Boolean flag) {
	if (pos < 1 || pos > 32) {
		printf("input bit value a byte out of range\n");
		return;
	}
	if (flag == true)
		*data |= (1 << (pos - 1));
	else
		*data &= (~(1 << (pos - 1)));
}
/*
Odd-Check
count numbers of 1 in a byte
if is odd ��return true; if even, return fasle
*/
Boolean NumsOfOneIsOdd8(unsigned char data) {
	int number = 0;
	while (data) {
		if ((data & 1) == 1)
			number++;
		data >>= 1;
	}
	return (number & 1) == 1 ? true : false;
}
/*��������֡*/
Boolean OddCheck(unsigned char *codeData, int len) {
	if (codeData == NULL) {
		printf("error!");
		exit(-1);
	}
	int i = 0;
	for (; i < len; ++i) {
		if (NumsOfOneIsOdd8(codeData[i]))
			printf("����֡�ĵ�%d���ֽ�У����ϣ���ȷ����.\n", i + 1);
		else {
			printf("����֡���͹��̳������룬��������ڵ�%d���ֽ�\n", i + 1);
			return error;
		}
	}
	printf("����֡��żУ����ϣ���ȷ����\n");
	return ok;
}
/*
�ж�һ���ֽڵĵ�7λ1�ĸ���
������1����true��ż����1����false
*/
Boolean NumsOfOneIsOdd7(unsigned char data) {
	Boolean b1 = NumsOfOneIsOdd8(data);
	Boolean b2;
	if ((data & 128))
		b2 = true;
	else
		b2 = false;
	return b1 == b2 ? false : true;
}
/*��װһ���ֽڣ�ʹ֮���λ����У��λ*/
void Pack(unsigned char *data) {
	if (NumsOfOneIsOdd7(*data))
		setBitValue(data, 8, false);
	else
		setBitValue(data, 8, true);
}
/*�ַ���ת�����޷��ŵ�1�ֽ�����*/
int StringToInt(char* str) {
	int len = strlen(str);
	int result = 0;
	int weight = 1;
	while (len) {
		result += (str[len - 1] - '0')*weight;
		len--;
		weight *= 10;
	}
	return result;
}
/*
codeData����������з���ռ�
codeData�Ǳ����Զ���������ֽ�����
len ������ĳ���
*/
void Encode(unsigned char* defaultCodeData,int *len) {
	//���� ��  �� �� ʱ�� PM SO2�������¶� 
	//10 2020 10 26 12 386 50 7 23 100 25
	//10����  1�� 10�� 26�� 12�βɼ� PM2.5 386 SO2 50 ������7 �¶�23 ����������Ŀ100 �ô�������� 25
	printf("������ģ�⴫�����ɼ������ݣ�\n");//0 2020 10 26 12 386 50 7 23 100 25\n
	//printf("3 2017 1 4 18 305 27 11 8 125 66\n");
	//printf("7 2018 8 15 23 199 18 3 32 50 10\n");
	//�洢ģ��Ĵ�������ԭʼ�ַ��� 
	char str[50];
	fgets(str, 50, stdin);
	fflush(stdin);
	//���ԭʼ�ַ������׵�ַ 
	char *p = str;
	//����洢���ַ��������� 
	printf("��������ַ������ա� ���ָ�������ַ���Ƭ��");
	struct splitString substring[11];
	//��ʼ����split�ָ�ԭʼ�ַ���	
	int i = 0;
	char *temp = strtok(p, " ");
	while (temp != NULL) {
		strcpy(substring[i++].ss, temp);
		temp = strtok(NULL, " ");
	}
	printf("��11���ַ���ȫ��ת���ɶ�Ӧ������...\n");
	/*�����зָ�����ַ���ת����int�������洢*/
	int store[11];
	for (i = 0; i < 10; ++i) {
		store[i] = StringToInt(substring[i].ss);
	}
	store[10] = atoi(substring[10].ss);
	printf("�����ʾ����ݡ����Ǹ�����\n");
	//�������: 2018 - baseYear = 1 
	store[1] -= baseYear;
	printf("[store]�������������Ļ����������\n");
	for (i = 0; i < 11; ++i) {
		if (i < 9)
			printf("(0%d) %5d\n", i + 1, store[i]);
		else
			printf("(%d) %5d\n", i + 1, store[i]);
	}
	/*��ʼ���룬ʹ��codeData[10]�������������*/
	unsigned char codeData[10];
	//10����  1�� 10�� 26�� 12�βɼ� PM2.5 386 SO2 50 ������7 �¶�23 ����������Ŀ100 �ô�������� 25
	printf("�������\n");
	codeData[0] = (unsigned char)store[0];
	Pack(&codeData[0]);
	printf("����ǰ�ĳ��� %d\n", store[0]);
	printf("�����ĳ��У�������֡�ĵ�1���ֽ� %d\n", codeData[0]);
	printf("��������\n");
	codeData[1] = (unsigned char)store[1];
	codeData[2] = (unsigned char)store[2];
	codeData[1] <<= 4;
	codeData[1] |= codeData[2];
	Pack(&codeData[1]);
	printf("����ǰ����%d  ��%d\n", store[1], store[2]);
	printf("�������ֽڣ�������֡�ĵ�2���ֽ� %d\n", codeData[1]);
	printf("�����պ�PM2.5\n");
	codeData[2] = store[3];//��
	for (i = 8; i < 10; ++i) {
		if (ReadIntBitValue(store[5], i))
			setBitValue(&codeData[2], i - 2, true);
		else
			setBitValue(&codeData[2], i - 2, false);
	}
	Pack(&codeData[2]);
	codeData[4] = store[5];
	Pack(&codeData[4]);
	printf("����ǰ��%d PM2.5 %d\n", store[3], store[5]);
	printf("�������պ�PM2.5,������֡�ĵ�3���ֽ�%u\n", codeData[2]);
	printf("���������֡�ĵ�5���ֽ�%u\n", codeData[4]);
	printf("�������Ƶ��\n");
	codeData[3] = store[4];
	Pack(&codeData[3]);
	printf("����ǰ�Ĳ���Ƶ��%d\n", store[4]);
	printf("�����Ĳ���Ƶ�ʣ�������֡�ĵ�4���ֽ�%d", codeData[3]);
	printf("SO2,������ָ�����¶ȣ����д�������Ŀ����������Ŵ�������:\n");
	for (i = 6; i < 11; ++i) {
		codeData[i - 1] = store[i];
		Pack(&codeData[i - 1]);
	}
	printf("����ǰSO2,������ָ�����¶ȣ����д�������Ŀ�����������\n");
	for (i = 6; i < 11; ++i) {
		printf("%8d ", store[i]);
	}
	printf("\n");
	printf("�����SO2,������ָ�����¶ȣ����д�������Ŀ�����������\n");
	printf("��������֡�ĵ�6,7,8,9,10���ֽ�\n");
	for (i = 5; i < 10; ++i) {
		printf("%8d ", codeData[i]);
	}
	printf("\n");
	Next();
	printf("��������һ���Դ�ӡ������֡�������ֽ�\n");
	for (i = 0; i < 10; ++i) {
		printf("(%d)%8u\n", i + 1, codeData[i]);
	}
	printf("\n");
	Next();
	printf("���ǵ�Э����õ�����У�飬������֡��ÿ���ֽڵ����λ�����ó�����У��λ\n");
	printf("���ԣ�����֡�ٷ���ǰ��������У�飬��Ȼ����true\n");
	printf("������������֡������У��\n");
	OddCheck(codeData, 10);
	for (i = 0; i < 10; ++i) {
		defaultCodeData[i] = codeData[i];
	}
	*len = 10;
	Next();
	printf("�������ڷ�������֡\n");
}
//���벢д�����ݿ��Թ���ѯʹ��
void Decode(unsigned char *defaultCodeData) {
	int j;
	char string[300] = { 0 };//�ݴ���������ַ���
	struct tag CITY[10];//�洢���д���
	InitCity(CITY);
	printf("����Ԥ��������д������£�\n");
	for (int i = 0; i < 10; ++i) {
		printf("%d %s \n", CITY[i].number,CITY[i].cityName);
	}
	printf("������֡������У��\n");
	OddCheck(defaultCodeData, 10);
	printf("\n��ѯ���ء�����-���롿ӳ����ҵ������Ӧ�ĳ���\n");
	setBitValue(&defaultCodeData[0], 8, false);
	int temp = defaultCodeData[0];
	for (j = 0; j < 10; ++j) {
		if (temp == CITY[j].number) {
			printf("\n����֡���Եĳ�����%s\n", CITY[j].cityName);
			strcat(string, CITY[j].cityName);
			strcat(string, " ");
			break;
		}
	}

	//�����꣬�£��գ�ʱ��
	int year = 0;   int month = 0; int day = 0;
	char Year[10];  char Month[10]; char Day[10];
	for (j = 5; j < 8; ++j) {
		Boolean value = ReadBitValue(defaultCodeData[1], j);
		setBitValueInt(&year, j - 4, value);
	}
	year += baseYear;
	for (j = 1; j < 5; ++j) {
		Boolean value = ReadBitValue(defaultCodeData[1], j);
		setBitValueInt(&month, j, value);
	}
	for (j = 1; j < 6; ++j) {
		Boolean value = ReadBitValue(defaultCodeData[2], j);
		setBitValueInt(&day, j, value);
	}
	_itoa(year, Year, 10); _itoa(month, Month, 10); _itoa(day, Day, 10);
	strcat(string, Year); strcat(string, "�� ");
	strcat(string, Month); strcat(string, "�� ");
	strcat(string, Day); strcat(string, "�� ");

	//�������Ƶ��
	static int lastDataTime = 0;
	int time = 0;  
	int hour = 0;  char Hour[20];
	int min = 0;   char Min[20];
	for (j = 1; j < 8; ++j) {
		Boolean value = ReadBitValue(defaultCodeData[3], j);
		setBitValueInt(&time, j, value);
	}
	hour = 1440 / FREQUENT * time / 60;
	min = (1440 / FREQUENT) * time % 60;
	_itoa(hour, Hour,10);
	_itoa(min, Min, 10);
	strcat(string, Hour); strcat(string, "ʱ ");
	strcat(string, Min);  strcat(string, "�� ");
	
	printf("time == %d\n\n\n\n\n",time);
    //������ǵ�һ�η������ݣ��ͼ������֡ 
    if(lastDataTime != 0) {
    	//�������֡�Ƿ�����
		if(lastDataTime + 1 == time) {
			printf("����֡������,���Խ��գ�\n");
			lastDataTime = time;
		}
		else {
			printf("����֡������Ҫ�ط���\n");
			return;
		}
	}
	else {
		lastDataTime = time;
	}
	//����PM2.5
	int pm = 0;
	char Pm[20];
	for (j = 1; j < 8; ++j) {
		Boolean value = ReadBitValue(defaultCodeData[4], j);
		setBitValueInt(&pm, j, value);
	}
	for (j = 8; j < 10;++j) {
		Boolean value = ReadBitValue(defaultCodeData[2], j-2);
		setBitValueInt(&pm, j, value);
	}
	if(pm < 50) printf("������������\n");
	if(pm < 150) printf("������������\n");
	if(pm < 300) printf("������������\n");
	if(pm < 400) printf("�������������� ;��Ҫ���أ��ظ���������\n"); 
	_itoa(pm, Pm, 10);
	strcat(string, Pm);
	strcat(string, "��g/m3 pm2.5 ");

	//����SO2�������ߣ��¶ȣ��������������������������������
	int temp2 = 0; char Temp[20];
	int r;
	for (r = 5; r < 10; ++r) {
		for (j = 1; j < 8; ++j) {
			Boolean value = ReadBitValue(defaultCodeData[r], j);
			setBitValueInt(&temp2, j, value);
		}
		
		if (r == 5) if(temp2 > 20) printf("SO2���꣬��������,��ҵ����\n"); else printf("SO2Ũ������\n");
		if (r == 6) if(temp2 > 7) printf("�����߳��꣬�������棬ע���ɹ\n");else printf("������ָ������\n");
		if (r == 7) if(temp2 > 30 || temp2 < 5) printf("�¶ȳ��꣬��������,ע�Ᵽů���ɹ\n");else printf("�¶�����\n\n");

		_itoa(temp2, Temp, 10);
		strcat(string, Temp);
		if (r == 5) strcat(string, "mg/m3 SO2 ");
		if (r == 6) strcat(string, "W/m2 ������ָ�� ");
		if (r == 7) strcat(string, "��C �¶� ");
		if (r == 8) strcat(string, " �����������ڴ��������� ");
		if (r == 9) strcat(string, " ����������� ");
	}
	printf("���շ�����Э���������������£�\n\n");
	strcat(string, "\n");
	printf("%s\n", string);
	//����һ���ı�����ģ�����ݿ�
	FILE* fr = fopen("C:/Users/Administrator/Desktop/data.txt", "a");
	if (fr == NULL) {
		printf("���ļ�����\n");
		exit(-1);
	}
	fputs(string, fr);
	fclose(fr);
}
int main() {
	while (true) {
		Encode(defaultCodeData, &len);
		printf("�������ǿ�ʼ����Э�����\n");
		Decode(defaultCodeData);
		system("pause");
	}
	return 0;
}


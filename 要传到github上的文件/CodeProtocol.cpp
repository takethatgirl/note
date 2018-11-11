#define FREQUENT 100//采样频率
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

//客户端暂存上次发送的数据帧

//服务器暂存上次收到的数据帧的时间
unsigned char lastTime;
//重发标志位
Boolean repeatSendFlag = true;

unsigned char defaultCodeData[10];//存储定义的重新编码后的数据
int len;//数据帧字节长度

void InitCity(struct tag * CITY);//构造本地【城市-代码】映射表
Boolean ReadBitValue(unsigned char data, int pos);//读某个bit是1还是0
Boolean ReadIntBitValue(int data, int pos);//读某个bit是1还是0
void setBitValue(unsigned char *data, int pos, Boolean flag);//设置某个bit为1或0
Boolean NumsOfOneIsOdd8(unsigned char data);//对单个字节进行奇校验
Boolean OddCheck(unsigned char *codeData, int len);//对数据帧奇校验
Boolean NumsOfOneIsOdd7(unsigned char data);//检验一个字节前7个bit 1的个数
void Pack(unsigned char *data);//包装字节，使其带有奇校验位
int StringToInt(char* str);//字符串转换成整数
void Encode(unsigned char* defaultCodeData, int *len);//编码
void Decode(unsigned char *defaultCodeData);//解析
void Next();//程序暂停

/*初始化存储城市代码的查询数组*/
void InitCity(struct tag * CITY) {
	int k = 0;
	for (; k < 10; ++k) {
		CITY[k].number = k;
	}
	strcpy(CITY[0].cityName, "西安");
	strcpy(CITY[1].cityName, "北京");
	strcpy(CITY[2].cityName, "上海");
	strcpy(CITY[3].cityName, "南京");
	strcpy(CITY[4].cityName, "杭州");
	strcpy(CITY[5].cityName, "沈阳");
	strcpy(CITY[6].cityName, "广州");
	strcpy(CITY[7].cityName, "重庆");
	strcpy(CITY[8].cityName, "成都");
	strcpy(CITY[9].cityName, "天津");
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
	printf("\n-----------------程序暂停----------------\n Next/exit: y/n ? ");
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
/*设置一个int整数的某个bit*/
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
if is odd ，return true; if even, return fasle
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
/*检验数据帧*/
Boolean OddCheck(unsigned char *codeData, int len) {
	if (codeData == NULL) {
		printf("error!");
		exit(-1);
	}
	int i = 0;
	for (; i < len; ++i) {
		if (NumsOfOneIsOdd8(codeData[i]))
			printf("数据帧的第%d个字节校验完毕，正确接收.\n", i + 1);
		else {
			printf("数据帧传送过程出现误码，误码出现在第%d个字节\n", i + 1);
			return error;
		}
	}
	printf("数据帧奇偶校验完毕，正确传送\n");
	return ok;
}
/*
判断一个字节的低7位1的个数
奇数个1返回true，偶数个1返回false
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
/*封装一个字节，使之最高位是奇校验位*/
void Pack(unsigned char *data) {
	if (NumsOfOneIsOdd7(*data))
		setBitValue(data, 8, false);
	else
		setBitValue(data, 8, true);
}
/*字符串转换成无符号的1字节整数*/
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
codeData数组必须自行分配空间
codeData是保存自定义编码后的字节数组
len 是数组的长度
*/
void Encode(unsigned char* defaultCodeData,int *len) {
	//城市 年  月 日 时间 PM SO2紫外线温度 
	//10 2020 10 26 12 386 50 7 23 100 25
	//10城市  1年 10月 26日 12次采集 PM2.5 386 SO2 50 紫外线7 温度23 传感器总数目100 该传感器编号 25
	printf("请输入模拟传感器采集的数据：\n");//0 2020 10 26 12 386 50 7 23 100 25\n
	//printf("3 2017 1 4 18 305 27 11 8 125 66\n");
	//printf("7 2018 8 15 23 199 18 3 32 50 10\n");
	//存储模拟的传感器的原始字符串 
	char str[50];
	fgets(str, 50, stdin);
	fflush(stdin);
	//获得原始字符串的首地址 
	char *p = str;
	//定义存储子字符串的数组 
	printf("将输入的字符串按照“ ”分割成若干字符串片段");
	struct splitString substring[11];
	//开始进行split分割原始字符串	
	int i = 0;
	char *temp = strtok(p, " ");
	while (temp != NULL) {
		strcpy(substring[i++].ss, temp);
		temp = strtok(NULL, " ");
	}
	printf("将11个字符串全部转换成对应的整数...\n");
	/*把所有分割的子字符串转换成int整数并存储*/
	int store[11];
	for (i = 0; i < 10; ++i) {
		store[i] = StringToInt(substring[i].ss);
	}
	store[10] = atoi(substring[10].ss);
	printf("处理表示【年份】的那个整数\n");
	//调整年份: 2018 - baseYear = 1 
	store[1] -= baseYear;
	printf("[store]遍历初步处理后的环境各项参数\n");
	for (i = 0; i < 11; ++i) {
		if (i < 9)
			printf("(0%d) %5d\n", i + 1, store[i]);
		else
			printf("(%d) %5d\n", i + 1, store[i]);
	}
	/*开始编码，使用codeData[10]保存编码后的数据*/
	unsigned char codeData[10];
	//10城市  1年 10月 26日 12次采集 PM2.5 386 SO2 50 紫外线7 温度23 传感器总数目100 该传感器编号 25
	printf("处理城市\n");
	codeData[0] = (unsigned char)store[0];
	Pack(&codeData[0]);
	printf("处理前的城市 %d\n", store[0]);
	printf("处理后的城市，即数据帧的第1个字节 %d\n", codeData[0]);
	printf("处理年月\n");
	codeData[1] = (unsigned char)store[1];
	codeData[2] = (unsigned char)store[2];
	codeData[1] <<= 4;
	codeData[1] |= codeData[2];
	Pack(&codeData[1]);
	printf("处理前的年%d  月%d\n", store[1], store[2]);
	printf("处理后的字节，即数据帧的第2个字节 %d\n", codeData[1]);
	printf("处理日和PM2.5\n");
	codeData[2] = store[3];//日
	for (i = 8; i < 10; ++i) {
		if (ReadIntBitValue(store[5], i))
			setBitValue(&codeData[2], i - 2, true);
		else
			setBitValue(&codeData[2], i - 2, false);
	}
	Pack(&codeData[2]);
	codeData[4] = store[5];
	Pack(&codeData[4]);
	printf("处理前日%d PM2.5 %d\n", store[3], store[5]);
	printf("处理后的日和PM2.5,即数据帧的第3个字节%u\n", codeData[2]);
	printf("处理后数据帧的第5个字节%u\n", codeData[4]);
	printf("处理采样频率\n");
	codeData[3] = store[4];
	Pack(&codeData[3]);
	printf("处理前的采样频率%d\n", store[4]);
	printf("处理后的采样频率，即数据帧的第4个字节%d", codeData[3]);
	printf("SO2,紫外线指数，温度，本市传感器数目，传感器编号处理如下:\n");
	for (i = 6; i < 11; ++i) {
		codeData[i - 1] = store[i];
		Pack(&codeData[i - 1]);
	}
	printf("处理前SO2,紫外线指数，温度，本市传感器数目，传感器编号\n");
	for (i = 6; i < 11; ++i) {
		printf("%8d ", store[i]);
	}
	printf("\n");
	printf("处理后SO2,紫外线指数，温度，本市传感器数目，传感器编号\n");
	printf("即，数据帧的第6,7,8,9,10个字节\n");
	for (i = 5; i < 10; ++i) {
		printf("%8d ", codeData[i]);
	}
	printf("\n");
	Next();
	printf("现在我们一次性打印出数据帧的所有字节\n");
	for (i = 0; i < 10; ++i) {
		printf("(%d)%8u\n", i + 1, codeData[i]);
	}
	printf("\n");
	Next();
	printf("我们的协议采用的是奇校验，把数据帧的每个字节的最高位都设置成了奇校验位\n");
	printf("所以，数据帧再发送前，进行奇校验，必然返回true\n");
	printf("现在我们数据帧进行奇校验\n");
	OddCheck(codeData, 10);
	for (i = 0; i < 10; ++i) {
		defaultCodeData[i] = codeData[i];
	}
	*len = 10;
	Next();
	printf("我们现在发送数据帧\n");
}
//解码并写入数据库以供查询使用
void Decode(unsigned char *defaultCodeData) {
	int j;
	char string[300] = { 0 };//暂存解析出的字符串
	struct tag CITY[10];//存储城市代码
	InitCity(CITY);
	printf("我们预先浏览城市代码如下：\n");
	for (int i = 0; i < 10; ++i) {
		printf("%d %s \n", CITY[i].number,CITY[i].cityName);
	}
	printf("对数据帧进行奇校验\n");
	OddCheck(defaultCodeData, 10);
	printf("\n查询本地【城市-代码】映射表，找到代码对应的城市\n");
	setBitValue(&defaultCodeData[0], 8, false);
	int temp = defaultCodeData[0];
	for (j = 0; j < 10; ++j) {
		if (temp == CITY[j].number) {
			printf("\n数据帧来自的城市是%s\n", CITY[j].cityName);
			strcat(string, CITY[j].cityName);
			strcat(string, " ");
			break;
		}
	}

	//解析年，月，日，时间
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
	strcat(string, Year); strcat(string, "年 ");
	strcat(string, Month); strcat(string, "月 ");
	strcat(string, Day); strcat(string, "日 ");

	//解码采样频率
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
	strcat(string, Hour); strcat(string, "时 ");
	strcat(string, Min);  strcat(string, "分 ");
	
	printf("time == %d\n\n\n\n\n",time);
    //如果不是第一次发送数据，就检查数据帧 
    if(lastDataTime != 0) {
    	//检查数据帧是否乱序
		if(lastDataTime + 1 == time) {
			printf("数据帧不乱序,可以接收！\n");
			lastDataTime = time;
		}
		else {
			printf("数据帧乱序，需要重发！\n");
			return;
		}
	}
	else {
		lastDataTime = time;
	}
	//解码PM2.5
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
	if(pm < 50) printf("空气质量：优\n");
	if(pm < 150) printf("空气质量：良\n");
	if(pm < 300) printf("空气质量：差\n");
	if(pm < 400) printf("空气质量：极差 ;需要调控，回复调控数据\n"); 
	_itoa(pm, Pm, 10);
	strcat(string, Pm);
	strcat(string, "μg/m3 pm2.5 ");

	//处理SO2，紫外线，温度，传感器网传感器总量，本传感器编号
	int temp2 = 0; char Temp[20];
	int r;
	for (r = 5; r < 10; ++r) {
		for (j = 1; j < 8; ++j) {
			Boolean value = ReadBitValue(defaultCodeData[r], j);
			setBitValueInt(&temp2, j, value);
		}
		
		if (r == 5) if(temp2 > 20) printf("SO2超标，发出警告,工业酸雨\n"); else printf("SO2浓度正常\n");
		if (r == 6) if(temp2 > 7) printf("紫外线超标，发出警告，注意防晒\n");else printf("紫外线指数正常\n");
		if (r == 7) if(temp2 > 30 || temp2 < 5) printf("温度超标，发出警告,注意保暖或防晒\n");else printf("温度正常\n\n");

		_itoa(temp2, Temp, 10);
		strcat(string, Temp);
		if (r == 5) strcat(string, "mg/m3 SO2 ");
		if (r == 6) strcat(string, "W/m2 紫外线指数 ");
		if (r == 7) strcat(string, "°C 温度 ");
		if (r == 8) strcat(string, " 所属传感网内传感器总量 ");
		if (r == 9) strcat(string, " 本传感器编号 ");
	}
	printf("接收方根据协议解析后的数据如下：\n\n");
	strcat(string, "\n");
	printf("%s\n", string);
	//定义一个文本，来模拟数据库
	FILE* fr = fopen("C:/Users/Administrator/Desktop/data.txt", "a");
	if (fr == NULL) {
		printf("打开文件出错！\n");
		exit(-1);
	}
	fputs(string, fr);
	fclose(fr);
}
int main() {
	while (true) {
		Encode(defaultCodeData, &len);
		printf("现在我们开始根据协议解码\n");
		Decode(defaultCodeData);
		system("pause");
	}
	return 0;
}


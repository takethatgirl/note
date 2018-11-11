#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
struct node{
	long weight;  //Ȩֵ
	unsigned char ch;//�ַ�
	int parent,lchild,rchild;
	char code[256];//�����λ�����Ϊ256λ
    int CodeLength;//���볤��
}hfmnode[512];
void compress();
void uncompress(); 
//������
int main()
{
	int choice;
	 printf("��ѡ��1~3��\n");
	 printf("1.ѹ���ļ�\n");
	 printf("2.��ѹ�ļ�\n");
	 printf("3.�˳���\n");
		scanf("%d",&choice);
		if(choice==1)compress();
		else if(choice==2)uncompress();
		     else if(choice==3) return 0;
	              else printf("�������");
    
}

//ѹ������
void compress()
{
	void encode(struct node *nodep,int n);//���뺯��
	int select(struct node *nodep,int pose);//���ڽ�����������ѡ��Ȩֵ��С�Ľ��ĺ���
	int i,j;
	char infile[20],outfile[20];
	FILE  *ifp,*ofp; 
	unsigned char c;//
	long FileLength,filelength=0;
	int n,m;//Ҷ�����ͽ����
	int s1,s2; //Ȩֵ��С���������ı��
	char codes[256];
	long sumlength=0;
	float rate,speed;
	int count=0;
	clock_t start1, start2,finish1,finish2;
	double  duration1,duration2;
	    printf("�������ѹ�����ļ���:");
	    scanf("%s",infile);
	    ifp=fopen(infile,"rb");
		if(ifp==NULL)
		{
            printf("�ļ�����������ļ�������!\n");
            return;
		}
	    printf("������ѹ���ļ���:");
	      scanf("%s",outfile);
	    ofp=fopen(outfile,"wb");
		if(ofp==NULL)
		{
           printf("�ļ�����������ļ�������!\n");
            return;
		}

start1=clock() ;//��ʼ��ʱ1

	//ͳ���ļ����ַ��������Լ������ַ��ĸ���
	//�����ַ���ASCII��ֵ�������±�
		FileLength=0;
	    while(!feof(ifp)) 
		{
		 fread(&c,1,1,ifp);
		 hfmnode[c].weight++; 
		 FileLength++;
		}
		FileLength--; //�ļ������һ���ַ��ĸ������ͳ��һ�Σ�����Ҫ��һ
		hfmnode[c].weight--;
		//�ٽ�ASCIIת��Ϊ�ַ����뵽����ch��Ա�ͬʱ��˫�ס����Ӹ���ֵ-1
		    n=0;
	        for(i=0;i<256;i++)
				if(hfmnode[i].weight!=0)
				{
					hfmnode[i].ch=(unsigned char)i;
		      	    n++;//Ҷ����
			    hfmnode[i].lchild=hfmnode[i].rchild=hfmnode[i].parent=-1;    	
				} 
m=2*n-1;//���������������
 j=0;
 for(i=0;i<256;i++)//ȥ��ȨֵΪ0�Ľ��
     if(hfmnode[i].weight!=0)
	 {
        hfmnode[j]=hfmnode[i];
        j++;
	 }

for(i=n;i<m;i++)//��ʼ�������
{
		hfmnode[i].lchild=hfmnode[i].rchild=-1;
		hfmnode[i].parent=-1;
}
//������������
   for(i=n;i<m;i++)
   {
	      s1=select(hfmnode,i-1);
	    hfmnode[i].lchild=s1;
	    hfmnode[s1].parent=i;
	  	   s2=select(hfmnode,i-1);
	    hfmnode[i].rchild=s2;
	    hfmnode[s2].parent=i;
	  hfmnode[i].weight=hfmnode[s1].weight+hfmnode[s2].weight;
   }
//����
encode(hfmnode,n);

 finish1=clock();
duration1=(double)(finish1- start1) / CLOCKS_PER_SEC;
 /*printf( "��������������ʱΪ��%f seconds\n", duration1 );*/
  printf("������ɣ��Ƿ�鿴������Ϣ: y or n?\n");
	    c=getch();
	    if(c=='y')
		{	printf("\n");
            printf("Ҷ����Ϊ%d,�����Ϊ%d\n",n,m); 
			for(i=0;i<n;i++)
			printf("%d��Ҷ�ӽ���ȨֵΪ��%ld,˫��Ϊ��%d,���Һ��ӣ�%d,����Ϊ��%s\n",
				i,hfmnode[i].weight,hfmnode[i].parent,hfmnode[i].lchild,hfmnode[i].code);
		}	
start2=clock() ;//��ʼ��ʱ2
	 fseek(ifp,0,SEEK_SET);//��ifpָ���Ƶ��ļ���ͷλ��
	 fwrite(&FileLength,4,1,ofp);//��FileLengthд��Ŀ���ļ���ǰ4���ֽڵ�λ��
	 fseek(ofp,8,SEEK_SET);//�ٽ�Ŀ���ļ�ָ��ofp�Ƶ����ļ���ͷ8���ֽ�λ��
   codes[0]=0;
	//��������Ϣд��Ŀ���ļ�
	 while(!feof(ifp))
	 {
		 fread(&c,1,1,ifp);
		 filelength++;
		 for(i=0;i<n;i++)
		   if(c==hfmnode[i].ch) break;	//ch����ҲΪunsigned ��
		 strcat(codes,hfmnode[i].code);
		  while(strlen(codes)>=8)
		  {
         	 for(i=0;i<8;i++)//��codes��ǰ8λ01�����ʾ���ַ�����c
			  {
	              if(codes[i]=='1')
					  c=(c<<1)|1;
	              else c=c<<1;
			 }
	        fwrite(&c,1,1,ofp); //���µ��ַ�д��Ŀ���ļ�
			sumlength++;
            strcpy(codes,codes+8);//����codes��ֵ
		  }
       if(filelength==FileLength) break;
	 }

	   //�ٽ�ʣ��Ĳ���8λ��01���벹ȫ8λ������д��
	   if(strlen(codes)>0)
	   {
	       strcat(codes,"00000000");
	       for(i=0;i<8;i++)
		   {
	          if(codes[i]=='1') 
				  c=(c<<1)|1;
	          else c=c<<1;
		   }
	       fwrite(&c,1,1,ofp);
	       sumlength++;
	   }
	 
	   sumlength+=8;
printf("�������ܳ�Ϊ��%ld���ֽ�\n",sumlength-8);
	 //��sumlength��n��ֵд��Ŀ���ļ���Ϊ���Ƿ����ѹ
	    fseek(ofp,4,SEEK_SET);
	    fwrite(&sumlength,4,1,ofp);//��sumlengthд��Ŀ���ļ��ĵ�5-8���ֽ���         
	    fseek(ofp,sumlength,SEEK_SET);
	    fwrite(&n,4,1,ofp);//��Ҷ����nд������κ����4���ֽڵ�λ��
	//Ϊ�����ѹ���ѱ�����Ϣ����n�����λ��
	//�洢��ʽΪ��n*���ַ�ֵ��1���ֽڣ�+���ַ���01�����λ����1���ֽڣ�+���루�ֽ�����ȷ������count��������ֵ����
	    for(i=0;i<n;i++)
		{
	       fwrite(&(hfmnode[i].ch),1,1,ofp);
           c=hfmnode[i].CodeLength;//�����Ϊ256λ�����ֻ����һ���ֽڴ洢
	       fwrite(&c,1,1,ofp);
	       //д���ַ��ı���
	       if(hfmnode[i].CodeLength%8!=0) 
	          for(j=hfmnode[i].CodeLength%8;j<8;j++)//�ѱ��벻��8λ���ڵ�λ��0,��ֵ��C���ٰ�Cд��
	          strcat(hfmnode[i].code,"0");
	       while(hfmnode[i].code[0]!=0)//��ʼ������룬ÿ8λ������������һ���ֽ�
		   {
	           c=0;
	           for(j=0;j<8;j++)
			   {
	               if(hfmnode[i].code[j]=='1')
	 				   c=(c<<1)|1;
	               else c=c<<1;
			   }
	           strcpy(hfmnode[i].code,hfmnode[i].code+8);//����ǰ��8λ�������������
			   count++; //����ռ���ֽ�������ֵ
	           fwrite(&c,1,1,ofp);
		   }
		}
		printf("\n");
         finish2=clock();
	     duration2=(double)(finish2- start2) / CLOCKS_PER_SEC;
	     /*printf( "д��Ŀ���ļ���ʱΪ��%f seconds\n", duration2);*/
		 printf( "ѹ����ʱΪ��%f seconds\n", duration1+duration2);
		   speed=(float)FileLength/(duration1+duration2)/1000;
		   printf("\nѹ������Ϊ��%5.2f KB/S\n",speed);
		printf("\n");
	    printf("Դ�ļ�����Ϊ��%ld���ֽ�\n",FileLength);
		sumlength=sumlength+4+n*2+count; //����ѹ�����ļ��ĳ���
		printf("ѹ�����ļ�����Ϊ��%ld���ֽ�\n",sumlength);
		rate=(float)sumlength/(float)FileLength;
		printf("ѹ����(�ٷֱ�)Ϊ��%4.2f%%%\n",rate*100);
	    fclose(ifp);
	    fclose(ofp);  
		return;	
}
//������ǩ

//������������������ѡ����СȨֵ���ĺ���
int select(struct node *nodep,int pose)
{ 
	int i;
	int s1;
	long min=2147483647;//s��ֵΪlong�͵����ֵ
	for(i=0;i<=pose;i++)
	{
		if(nodep[i].parent!=-1)continue;
		if(nodep[i].weight<min)
		{
			min=nodep[i].weight;  
			s1=i;
		}
	}
	return s1;
}
//������ǩ

//���������뺯��
void encode(struct node *nodep,int n)
{   //��Ҷ�������ÿ���ַ��Ĺ���������
	int start;
	int i,f,c;
	char codes[256];
	codes[n-1]='\0';  //���������
	for(i=0;i<n;i++) //����ַ������������
	{
       start=n-1;
	   for(c=i,f=nodep[i].parent;f!=-1;c=f,f=nodep[f].parent)
	   {
		   start--;
		   if(nodep[f].lchild==c)
			   codes[start]='0';
		   else codes[start]='1';
           
	   }
	   strcpy(nodep[i].code,&codes[start]);
	   nodep[i].CodeLength=strlen(nodep[i].code);  
	}
}
//������ǩ

//��ѹ����
void uncompress() //��ѹ�ļ�

{ 
	clock_t start, finish;
    double  duration;
	FILE *ifp,*ofp;  
	char infile[20],outfile[20];
    long FileLength,sumlength,filelength;
	int n,m;  
	int i,j,k;
	char buf[256],codes[256];
    unsigned char c;
	int maxlength;
	float speed;
     printf("������Ҫ��ѹ���ļ���:");
	    scanf("%s",infile);
	    ifp=fopen(infile,"rb");
		if(ifp==NULL)
		{
        printf("�ļ�����������ļ�������!\n");
        return;
		}
	 printf("������Ŀ���ļ���:");
	      scanf("%s",outfile);
	    ofp=fopen(outfile,"wb");
		if(ofp==NULL)
		{
        printf("�ļ�����������ļ�������!\n");
        return;
		}
start=clock() ;//��ʼ��ʱ
    fread(&FileLength,4,1,ifp);//��ѹ���ļ�����FileLength��sumlength
    fread(&sumlength,4,1,ifp);
    fseek(ifp,sumlength,SEEK_SET);    //����sumlength����n��ֵ
    fread(&n,4,1,ifp);
    printf("\n������Ϣ:Դ�ļ�����Ϊ%d���ֽ�,�ַ�����n=%d\n",FileLength,n);
    for(i=0;i<n;i++)//�������Ϣ
	{
       fread(&hfmnode[i].ch,1,1,ifp);//�ַ�
       fread(&c,1,1,ifp);//���볤��
	   hfmnode[i].CodeLength=c;
       hfmnode[i].code[0]=0;
       if(hfmnode[i].CodeLength%8>0) m=hfmnode[i].CodeLength/8+1;//mΪ����ռ���ֽ���
       else m=hfmnode[i].CodeLength/8;
       for(j=0;j<m;j++)//�����ֽڳ���m��������
	   {
           fread(&c,1,1,ifp);//�˴�cΪ01����ת���ɵ��ַ�
           itoa(c,buf,2);//�ַ��ͱ���ת���ɶ������ͣ���λΪ1��
          //������벻��8λ����˵��ȱ����8-kλ0�����Ӧ����ǰ���ȱλд0
           for(k=8;k>strlen(buf);k--)
		   {
               strcat(hfmnode[i].code,"0");
		   }
           //�ٰѶ����Ʊ�����hfmnode.code��
            strcat(hfmnode[i].code,buf);
	   }
       hfmnode[i].code[hfmnode[i].CodeLength]=0;//ȥ�������ж����0  
	}
 //�ҳ����볤�ȵ����ֵ
 maxlength=0;
 for(i=0;i<n;i++)
     if(hfmnode[i].CodeLength>maxlength)
		 maxlength=hfmnode[i].CodeLength;
//��ʼд��Ŀ���ļ�
 fseek(ifp,8,SEEK_SET); //ָ��ָ�����������ʼ����
 filelength=0;
 codes[0]=0;
 buf[0]=0;
 while(1)
 {
    while(strlen(codes)<maxlength)//codesС�ڱ��볤�ȵ����ֵʱ����������
	{
        fread(&c,1,1,ifp);
        itoa(c,buf,2);//��ԭ����
        for(k=8;k>strlen(buf);k--)
		{
           strcat(codes,"0");//��ȱ����0����
		}
        strcat(codes,buf);//codes�д�ʱ���Ϊһ��01����
	}
    for(i=0;i<n;i++)
	{  //��codes�в�����ʹ��ǰweightλ��hfmnode.code��ͬ��iֵ��weight��Ϊcodelength
      if(memcmp(hfmnode[i].code,codes,(unsigned int)hfmnode[i].CodeLength)==0) break;
	}
    strcpy(codes,codes+hfmnode[i].CodeLength);//����codes��ֵ
    c=hfmnode[i].ch;
    fwrite(&c,1,1,ofp);

    filelength++;
    if(filelength==FileLength) break;//д�����
 }
     finish = clock();
     duration = (double)(finish - start) / CLOCKS_PER_SEC;
     printf( "\n��ѹ��ɣ���ѹ��ʱΪ��%f seconds\n", duration );
       
	 fseek(ifp,0,SEEK_SET);  
	 FileLength=0;
	    while(!feof(ifp)) 
		{
	      fread(&c,1,1,ifp);
		  FileLength++;
		}
		FileLength--; 
	speed=(float)FileLength/duration/1000;
	/*printf("���ļ�����Ϊ��%ld���ֽ�\n",FileLength);*/
	printf("\n��ѹ�ٶ�Ϊ��%5.2fKB/S\n",speed);

   fclose(ifp);
   fclose(ofp);
   return;
}


#include "stdio.h"   
#include <stdlib.h>  
int main() {   
    FILE *fp;   
    char ch; 
	 FILE *wp;
	 wp = fopen("C:\\Users\\well\\Desktop\\1234.txt","wb");
    if((fp=fopen("C:\\Users\\well\\Desktop\\123.txt","rb"))==NULL) {  
        printf("file cannot be opened/n");   
        exit(1);   
    }   
    while((ch=fgetc(fp))!=EOF)   
        fputc(ch,wp);   
    fclose(fp); 
	
	
	unsigned char hh = 140;
	printf("%c",hh);  
}  

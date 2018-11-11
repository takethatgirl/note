#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<sys/socket.h>  
#include<sys/types.h>  
#include<unistd.h>  
#include<netinet/in.h>  
#define PORT 6666  
#define true 1
#define fasle 0
#define ok 1
#define error 0
int main(int argc,char **argv) {  
    int err,n;  
    char sendline[20],recvline[20];  
    int sockfd;
    if(sockfd=socket(AF_INET,SOCK_STREAM,0 == -1)) { 
        printf("socket error\n");  
        return -1;  
    } 
	struct sockaddr_in addr_ser; 
    memset(&addr_ser,0,sizeof(addr_ser));  
    addr_ser.sin_family=AF_INET;  
    addr_ser.sin_addr.s_addr=htonl(INADDR_ANY);  
    addr_ser.sin_port=htons(PORT);  
    err=connect(sockfd,(struct sockaddr *)&addr_ser,sizeof(addr_ser));  
    if(err==-1) {  
        printf("connect error\n");  
        return -1;  
    }    
    printf("connect with server...\n");    
    while(true) {  
        printf("Input your words:");  
        scanf("%s",&sendline);      
        send(sockfd,sendline,strlen(sendline),0);  
        printf("waiting for server...\n");  
        n=recv(sockfd,recvline,100,0);  
        recvline[n]='\0';   
        printf("recv data is:%s\n",recvline);  
    }   
    return 0;  
}  

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<stdio.h>
int main()
{
	struct sockaddr_in addr,cliaddr;
	addr.sin_family=AF_INET;
	addr.sin_port=5050;
	addr.sin_addr.s_addr=INADDR_ANY;
	char buf[] = "hello";
	char buf1[50];
	int s = socket(AF_INET,SOCK_DGRAM,0);
	int len;
	sendto(s,buf,sizeof(buf),0,(struct sockaddr *)&addr,sizeof(addr));
	int n = recvfrom(s,buf1,sizeof(buf1),0,(struct sockaddr *)&addr,&len);
	buf1[n]='\0';
	printf("%s",buf1);
}

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
	char buf[50];
	int s = socket(AF_INET,SOCK_DGRAM,0);
	bind(s,(struct sockaddr*)&addr,sizeof(struct sockaddr));
	int len = sizeof(cliaddr);
	int i = 1;
	while (i <= 2)
	{
		int n = recvfrom(s,buf,sizeof(buf),0,(struct sockaddr *)&cliaddr,&len);
		buf[n]='\0';
		printf("%s\n",buf);
		i++;
	}
}

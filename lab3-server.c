#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT 8080
#define MAXLINE 1024
int main()
{
    int sockfd;
    char buffer[MAXLINE];
    char msgServer[MAXLINE];
    struct sockaddr_in servaddr, cliaddr;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
    bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    int len, n;
    len = sizeof(cliaddr);
    while(1)
    {
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0';
        printf("%s\n", buffer);
        if (strcmp(buffer, "exit") == 0)
        {
            sendto(sockfd, "exit", strlen("exit"), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
            return 0;
        }
        scanf("%s", msgServer);
        sendto(sockfd, msgServer, strlen(msgServer), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#define PORT 8080
#define MAXLINE 1024
int main()
{
    int sockfd;
    char buffer[MAXLINE];
    char msgClient[MAXLINE];
    struct sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
    int n, len;
    while(1)
    {
        scanf("%s", msgClient);
        sendto(sockfd, msgClient, strlen(msgClient), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
        buffer[n] = '\0';
        printf("%s\n", buffer);
        if (strcmp(buffer, "exit") == 0)
        {
            sendto(sockfd, "exit", strlen("exit"), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
            close(sockfd);
            return 0;
        }
    }
    close(sockfd);
    return 0;
}

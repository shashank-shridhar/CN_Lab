#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
int main()
{
    int sockfd;
    struct sockaddr_in server_addr;
    char server_message[2000], client_message[2000];
    memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket created successfully\n");
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5050);
    server_addr.sin_addr.s_addr = INADDR_ANY;;
    connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    printf("Connection with server processed successfully !!\n");
    printf("Enter message to be sent to the server: ");
    gets(client_message);
    send(sockfd, client_message, strlen(client_message), 0);
    recv(sockfd, server_message, sizeof(server_message), 0);
    printf("Response from the Server: %s\n",server_message);
    recv(sockfd, server_message, sizeof(server_message), 0);
    printf("Message from the Server: %s\n",server_message);
    close(sockfd);
    return 0;
}
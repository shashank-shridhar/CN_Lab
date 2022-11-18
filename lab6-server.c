#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
int main()
{

    int sockfd, client_sock[2], client_size;
    struct sockaddr_in servaddr, cliaddr;
    char server_message[2000], client_message1[2000], client_message2[2000];
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message1, '\0', sizeof(client_message1));
    memset(client_message2, '\0', sizeof(client_message2));   
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket created successfully\n");
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5050);
    servaddr.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(sockfd, 2);
    client_size = sizeof(cliaddr);

    client_sock[0] = accept(sockfd, (struct sockaddr*)&cliaddr, &client_size);
    printf("Connection establishment successful with client 1.\n");
    send(client_sock[0],"Hello from server",strlen("Hello from server"),0);
    recv(client_sock[0], client_message1, sizeof(client_message1), 0);
    printf("Message from client 1: %s\n", client_message1);
    printf("\n");

    client_sock[1] = accept(sockfd, (struct sockaddr*)&cliaddr, &client_size);
    printf("Connection establishment successful with client 2.\n");
    send(client_sock[1],"Hello from server",strlen("Hello from server"),0);
    recv(client_sock[1], client_message2, sizeof(client_message2), 0);
    printf("Message from client 2: %s\n", client_message2);
    printf("\n");

    printf("After swapping the values: \n");
    send(client_sock[0],client_message2,strlen(client_message2),0);
    send(client_sock[1],client_message1,strlen(client_message1),0);

    close(client_sock[0]);
    close(client_sock[1]);
    close(sockfd);
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(){
    //client side
    printf("Client side\n");
    int socketFD = socket(AF_INET, SOCK_STREAM,0);
   
    const char *ip = "142.251.111.27";
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(80);
    inet_pton(AF_INET,ip, &address.sin_addr.s_addr);
   
    int result = connect(socketFD, (struct sockaddr *)&address, sizeof(address));

    if(result == 0){
        printf("Connection successful\n");
    }else{
        perror("Connection failed\n");
    }

    const char *message = "GET / HTTP/1.1\r\nHost: google.com\r\n\r\n";
    send(socketFD, message, strlen(message), 0);

    char buffer[1024];
    recv(socketFD, buffer, 1024, 0);
    printf("Data received: %s\n", buffer);


    close(socketFD);
    return 0;
}
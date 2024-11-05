#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

int createTCPIpv4socket();
struct sockaddr_in* createIPv4Address(const char *ip, int port);

int main(){
    // Client side
    printf("Client side\n");
    int socketFD = createTCPIpv4socket();

    struct sockaddr_in *address = createIPv4Address("93.184.216.34", 80);

    int result = connect(socketFD, (struct sockaddr *)address, sizeof(*address));

    if(result == 0){
        printf("Connection successful\n");
    }else{
        perror("Connection failed\n");
        return 1;
    }

    const char *message = "GET / HTTP/1.1\r\nHost: example.com\r\n\r\n";
    send(socketFD, message, strlen(message), 0);

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    int bytes_received = recv(socketFD, buffer, sizeof(buffer) - 1, 0);
    if(bytes_received > 0){
        printf("Data received:\n%s\n", buffer);
    }else if(bytes_received == 0){
        printf("Connection closed by the server.\n");
    }else{
        perror("recv failed");
    }

    close(socketFD);
    free(address);
    return 0;
}

int createTCPIpv4socket(){
    int socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0) {
        perror("Socket creation failed");
        exit(1);
    }
    return socketFD;
}

struct sockaddr_in* createIPv4Address(const char *ip, int port){
    struct sockaddr_in *address = malloc(sizeof(struct sockaddr_in));
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    inet_pton(AF_INET, ip, &address->sin_addr.s_addr);
    return address;
}
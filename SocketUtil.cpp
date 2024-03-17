#include "SocketUtil.hpp"

int createTCPIpv4Socket() {
    int socketFD = socket(AF_INET, SOCK_STREAM, 0);
    return socketFD;
}

sockaddr_in* createIPv4Address(char *ip, int port) {

    struct sockaddr_in* address = new sockaddr_in;
    address->sin_port = htons(80);
    address->sin_family = AF_INET;
    if(strlen(ip) == 0)
        address->sin_addr.s_addr = htonl(INADDR_ANY);
    else 
        inet_pton(AF_INET, ip, &address->sin_addr.s_addr);
    return address;
}
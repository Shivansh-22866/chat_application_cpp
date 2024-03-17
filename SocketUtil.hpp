#ifndef SOCKET_UTIL_HPP
#define SOCKET_UTIL_HPP

#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

using namespace std;

class AcceptedSocket {
    public:
        int acceptedSocketFD;
        struct sockaddr_in address;
        int error;
        bool accepted;

        AcceptedSocket() {
            acceptedSocketFD = -1;
            accepted = false;
        }

        AcceptedSocket(int acceptedSocketFD, struct sockaddr_in address) {
            this->acceptedSocketFD = acceptedSocketFD;
            this->address = address;
            this->accepted = acceptedSocketFD > 0;
            if(!this->accepted) {
                this->error = acceptedSocketFD;
            }
        }
};

int createTCPIpv4Socket();

struct sockaddr_in* createIPv4Address(char* ip, int port);

AcceptedSocket* acceptIncomingConnection(int serverSocketFD);

#endif
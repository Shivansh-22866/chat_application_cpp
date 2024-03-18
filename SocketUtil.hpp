#ifndef SOCKET_UTIL_HPP
#define SOCKET_UTIL_HPP

#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include <vector>

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

struct sockaddr_in* createIPv4Address(char* , int);

AcceptedSocket* acceptIncomingConnection(int);

void* listenAndDisplay(void *arg);

void startListeningAndDisplay(int );

#endif
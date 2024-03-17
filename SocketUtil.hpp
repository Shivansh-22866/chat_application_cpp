#ifndef SOCKET_UTIL_HPP
#define SOCKET_UTIL_HPP

#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

using namespace std;

int createTCPIpv4Socket();

struct sockaddr_in* createIPv4Address(char* ip, int port);

#endif
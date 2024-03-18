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

AcceptedSocket* acceptIncomingConnection(int serverSocketFD) {
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen = sizeof(struct sockaddr_in);
    int clientSocketFD = accept(serverSocketFD, reinterpret_cast<struct sockaddr*>(&clientAddress), &clientAddressLen);

    AcceptedSocket* acceptedSocket = new AcceptedSocket(clientSocketFD, clientAddress);

    return acceptedSocket;
}

void* listenAndDisplay(void *arg) {
    int* socketFDPtr = (int*)arg;
    int socketFD = *socketFDPtr;
    char buffer[1024];

    while (true) {
        ssize_t amountReceived = recv(socketFD, buffer, 1024, 0);

        if (amountReceived > 0) {
            buffer[amountReceived] = '\0';
            cout << buffer << endl;
        }

        if (amountReceived <= 0) {
            cerr << "recv failed: " << strerror(errno) << endl;
            break;
        }
    }

    close(socketFD);
    return NULL;
}

void startListeningAndDisplay(int socketFD) {
    int* socketFDPtr = new int(socketFD);
    pthread_t id;
    pthread_create(&id, NULL, listenAndDisplay, (void*)socketFDPtr);
}
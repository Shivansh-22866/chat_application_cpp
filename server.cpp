#include "SocketUtil.cpp"

AcceptedSocket acceptedSockets[10];
int acceptedSocketCount = 0;

void broadcastReceivedMessage(char* buffer, int socketFD) {
    for(int i=0;i<acceptedSocketCount;i++) {
        if(acceptedSockets[i].acceptedSocketFD != socketFD) {
            send(acceptedSockets[i].acceptedSocketFD, buffer, strlen(buffer), 0);
        }
    }
}


void* receiveAndDisplay(void* arg) {
    int socketFD = *((int*)arg);

    char buffer[1024];
    while (true) {
        ssize_t amountReceived = recv(socketFD, buffer, 1024, 0);

        if (amountReceived > 0) {
            buffer[amountReceived] = '\0';
            cout << "Response received: " << endl;
            cout << buffer << endl;

            broadcastReceivedMessage(buffer, socketFD);
        }

        if (amountReceived <= 0) {
            cerr << "recv failed: " << strerror(errno) << endl;
            break;
        }
    }

    close(socketFD);
    return NULL;
}

void* startAcceptingNewIncomingConnection(void* arg) {
    int serverSocketFD = *((int*)arg);

    while (true) {
        AcceptedSocket* clientSocket = acceptIncomingConnection(serverSocketFD);
        acceptedSockets[acceptedSocketCount++] = *clientSocket;
        if (clientSocket != nullptr) {
            int* clientSocketFDPtr = new int(clientSocket->acceptedSocketFD);
            pthread_t displayThread;
            pthread_create(&displayThread, NULL, receiveAndDisplay, clientSocketFDPtr);
        }
    }

    return NULL;
}


int main() {
    int serverSocketFD = createTCPIpv4Socket();
    struct sockaddr_in *serverAddress = createIPv4Address((char *)"", 7000);

    int opt = 1;
    setsockopt(serverSocketFD, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    int res = bind(serverSocketFD, reinterpret_cast<struct sockaddr*>(serverAddress), sizeof(*serverAddress));

    if (res == 0) {
        std::cout << "Server is listening on port 7000" << std::endl;
    }

    if (res == -1) {
        std::cerr << "Bind failed: " << strerror(errno) << std::endl;
        return 1;
    }

    int listenResult = listen(serverSocketFD, 10);

    pthread_t acceptThread;
    pthread_create(&acceptThread, NULL, startAcceptingNewIncomingConnection, &serverSocketFD);

    pthread_join(acceptThread, NULL);

    shutdown(serverSocketFD, SHUT_RDWR);

    return 0;
}

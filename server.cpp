#include "SocketUtil.cpp"
#include <pthread.h> // Include pthread.h for pthread functions

void* receiveAndDisplay(void* arg) {
    int socketFD = *((int*)arg); // Cast the argument back to int and dereference it

    char buffer[1024];
    while (true) {
        ssize_t amountReceived = recv(socketFD, buffer, 1024, 0);

        if (amountReceived > 0) {
            buffer[amountReceived] = '\0'; // Null-terminate the received data
            std::cout << "Response received: " << std::endl;
            std::cout << buffer << std::endl;
        }

        if (amountReceived <= 0) {
            std::cerr << "recv failed: " << strerror(errno) << std::endl;
            break;
        }
    }

    close(socketFD);
    return NULL;
}

void* startAcceptingNewIncomingConnection(void* arg) {
    int serverSocketFD = *((int*)arg); // Cast the argument back to int and dereference it

    while (true) {
        AcceptedSocket* clientSocket = acceptIncomingConnection(serverSocketFD);
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

    // Main thread can do other tasks here while accepting connections in a separate thread

    // Join the accept thread to wait for it to finish
    pthread_join(acceptThread, NULL);

    shutdown(serverSocketFD, SHUT_RDWR);

    return 0;
}

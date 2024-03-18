#include "SocketUtil.cpp"

void* listenAndDisplay(void *arg) {
    int* socketFDPtr = (int*)arg;
    int socketFD = *socketFDPtr;
    char buffer[1024];

    while (true) {
        ssize_t amountReceived = recv(socketFD, buffer, 1024, 0);

        if (amountReceived > 0) {
            buffer[amountReceived] = '\0';
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

void startListeningAndDisplay(int socketFD) {
    int* socketFDPtr = new int(socketFD);
    pthread_t id;
    pthread_create(&id, NULL, listenAndDisplay, (void*)socketFDPtr);
}

int main() {
    int socketFD = createTCPIpv4Socket();

    char *ip = (char *)"127.0.0.1";
    struct sockaddr_in* address = createIPv4Address(ip, 7000);

    int res = connect(socketFD, reinterpret_cast<struct sockaddr*>(address), sizeof(*address));
    if(res == 0) {
        std::cout << "Successful Connection!!" << std::endl;
    } else {
        std::cout << "Unsuccessful Connection" << std::endl;
        return 1;
    }

    char* line = NULL;
    size_t len = 0;
    std::cout << "Write some message to send" << std::endl;

    startListeningAndDisplay(socketFD);

    while(true) {
        ssize_t charCount = getline(&line, &len, stdin);
        if(charCount > 0) {
            if(strcmp(line, "exit\n") == 0) {
                break;
            }
            ssize_t amountSent = send(socketFD, line, charCount, 0);
        }
    }

    close(socketFD);

    return 0;
}

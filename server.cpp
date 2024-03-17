#include "SocketUtil.cpp"

void receiveAndDisplay(AcceptedSocket* clientSocket) {
        char buffer[1024];

    while(true) {
        ssize_t amountReceived = recv(clientSocket->acceptedSocketFD, buffer, 1024, 0);

        if(amountReceived>0) {
            buffer[amountReceived] = 0;
            std::cout<<"Response received: "<<std::endl;
            std::cout<<buffer<<std::endl;
        }

        if(amountReceived==0) {
            std::cerr << "recv failed: " << strerror(errno) << std::endl;
            break;
        }
    }
}



int main() {

    int serverSocketFD = createTCPIpv4Socket();
    struct sockaddr_in *serverAddress = createIPv4Address((char *)"", 7000);

    int opt = 1;
    setsockopt(serverSocketFD, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));


    int res = bind(serverSocketFD, reinterpret_cast<struct sockaddr*>(serverAddress), (socklen_t)sizeof(*serverAddress));

    std::cout << res << std::endl;

    if(res == 0) {
        std::cout << "Server is listening on port 2000" << std::endl;
    }

    if (res == -1) {
        std::cerr << "Bind failed: " << strerror(errno) << std::endl;
        return 1;
    }

    int listenResult = listen(serverSocketFD, 10);

    AcceptedSocket* clientSocket = acceptIncomingConnection(serverSocketFD);

    receiveAndDisplay(clientSocket);

    close(clientSocket->acceptedSocketFD);
    shutdown(serverSocketFD, SHUT_RDWR);

    return 0;
}


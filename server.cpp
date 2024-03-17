#include "SocketUtil.cpp"

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

    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen = sizeof(struct sockaddr_in);
    int clientSocketFD = accept(serverSocketFD, reinterpret_cast<struct sockaddr*>(&clientAddress), &clientAddressLen);

    char buffer[1024];
    recv(clientSocketFD, buffer, 1024, 0);

    std::cout<<"Response received: "<<std::endl;
    std::cout<<buffer<<std::endl;

    return 0;
}
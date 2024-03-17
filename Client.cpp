#include "SocketUtil.cpp"

int main() {
    int socketFD = createTCPIpv4Socket();

    char *ip = (char *)"127.0.0.1";
    struct sockaddr_in* address = createIPv4Address(ip, 7000);


    int res = connect(socketFD, reinterpret_cast<struct sockaddr*>(address), sizeof(*address));

    if(res == 0) {
        cout<<"Successful Connection!!"<<endl;
    }

    else if(res < 0) {
        cout<<"Unsuccessful Connection"<<endl;
    }

    char* line = NULL;
    size_t len = 0;
    cout<<"Write some message to send\n"<<endl;

    while(true) {
        ssize_t charCount =  getline(&line, &len, stdin);
        if(charCount > 0) {
            if(line == "exit\n") {
                break;
            }
            ssize_t amountSent = send(socketFD, line, charCount, 0);
        }
    }

    close(socketFD);

    return 0;
}

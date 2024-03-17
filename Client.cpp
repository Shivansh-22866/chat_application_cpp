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
    

    char* message;
    message = (char *)"GET \\ HTTP/1.1\r\nHost:google.com\r\n\r\n";
    send(socketFD, message, strlen(message), 0);

    char buffer[1024];
    recv(socketFD, buffer, 1024, 0);
    cout<<"The message was: \n"<<buffer<<endl;

    return 0;
}

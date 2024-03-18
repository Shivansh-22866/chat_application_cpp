#include "SocketUtil.cpp"

int main() {
    int socketFD = createTCPIpv4Socket();

    char *ip = (char *)"127.0.0.1";
    struct sockaddr_in* address = createIPv4Address(ip, 7000);

    int res = connect(socketFD, reinterpret_cast<struct sockaddr*>(address), sizeof(*address));
    if (res == 0) {
        cout << "Successful Connection!!" << endl;
    } else {
        cout << "Unsuccessful Connection" << endl;
        return 1;
    }

    cout << "Enter your username: ";
    char username[1024];
    cin.getline(username, 1024);

    startListeningAndDisplay(socketFD);

    char* line = NULL;
    size_t len = 0;
    cout << "Write some message to send" << endl;

    while(true) {
        ssize_t charCount = getline(&line, &len, stdin);
        if(charCount > 0) {
            if(strcmp(line, "exit\n") == 0) {
                break;
            }

            string messageToSend = string(username) + ": " + string(line);
            ssize_t amountSent = send(socketFD, messageToSend.c_str(), messageToSend.length(), 0);
        }
    }

    close(socketFD);

    return 0;
}

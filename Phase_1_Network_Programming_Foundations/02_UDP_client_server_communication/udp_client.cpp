#include <iostream>
#include <cstring>

#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

int main()
{
    int clientSocket;

    clientSocket = socket(AF_INET, SOCK_DGRAM,0);

    if(clientSocket<0)
    {
        perror("Socket Creation Faild");
        return 1;
    }

    sockaddr_in serverAddr{};

    serverAddr.sin_family = AF_INET;

    serverAddr.sin_port = htons(8080);

    inet_pton(AF_INET,"127.0.0.1", &serverAddr.sin_addr);

    char message[1024];

    cout<<"Enter message: ";
    cin.getline(message, 1024);

    sendto(clientSocket, message, strlen(message),0, (sockaddr*)&serverAddr, sizeof(serverAddr));

    char buffer[1024];

    socklen_t len = sizeof(serverAddr);

    int bytesReceived = recvfrom(clientSocket, buffer, sizeof(buffer), 0, (sockaddr*)&serverAddr, &len);

    buffer[bytesReceived]= '\0';

    cout<<"Server: "<< buffer<<endl;

    close(clientSocket);

    return 0;
}
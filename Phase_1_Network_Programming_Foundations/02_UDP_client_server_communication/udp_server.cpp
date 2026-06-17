#include <iostream>
#include<cstring>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

int main()
{
    int serverSocket;

    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if(serverSocket<0)
    {
        perror("Socket creation failed");
        return 1;
    }

    sockaddr_in serverAddr{}, clientAddr{};

    serverAddr.sin_family = AF_INET; 

    serverAddr.sin_addr.s_addr = INADDR_ANY;

    serverAddr.sin_port = htons(8080);

    if(bind(serverSocket, (sockaddr*)&serverAddr,sizeof(serverAddr))<0)
    {
        perror("bind failed");
        return 1;
    }

    char buffer[1024];

    socklen_t clientLen = sizeof(clientAddr);

    cout<<"UDP server running...\n";

    while(true)
    {
        int bytesReceived = recvfrom(serverSocket, buffer, sizeof(buffer),0, (sockaddr*)&clientAddr, &clientLen);

        buffer[bytesReceived] = '\0';

        cout<<"Client:"<<buffer<<endl;

        sendto(serverSocket, "packet recieved", 15,0, (sockaddr*)&clientAddr, clientLen);
    }

    close(serverSocket);
    return 0;
}
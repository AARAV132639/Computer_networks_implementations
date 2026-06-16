#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

int main()
{
    int clientSocket;

    sockaddr_in serverAddr{};

    //Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(clientSocket<0)
    {
        cerr<< "Socket creation failed \n";
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);

    inet_pton(AF_INET,"127.0.0.1", &serverAddr.sin_addr);

    //connect to server
    if(connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr))<0)
    {
        cerr << "Connection failed \n";
        return 1;
    }

    string msg = "Hello from client";

    send(clientSocket, msg.c_str(), msg.size(),0);

    char buffer [1024] ={0};

    recv(clientSocket, buffer, sizeof(buffer),0);

    cout<<"Server says:"<<buffer<<endl;

    close(clientSocket);

    return 0;
}
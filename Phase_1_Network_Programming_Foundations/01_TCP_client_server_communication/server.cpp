#include <iostream>
#include <cstring>
#include <unistd.h>
# include <arpa/inet.h>

using namespace std;

int main()
{
    int serverSocket, clientSocket;

    sockaddr_in serverAddr{}, clientAddr{};

    socklen_t clientLen = sizeof(clientAddr);

    //create socket

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(serverSocket<0)
    {
        cerr << "Socket creating failed \n";
        return 1;
    }

    //configure server address
    serverAddr.sin_family = AF_INET;

    serverAddr.sin_addr.s_addr = INADDR_ANY;

    serverAddr.sin_port = htons(8080);

    //bind sockt
    if(bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr))<0)
    {
        cerr << "Bind failed /n";
        return 1;
    }

    //listen for connections
    listen(serverSocket, 5);

    cout<<"Server listening on port 8080...\n";

    //Accept client
    clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientLen);

    if (clientSocket<0)
    {
        cerr<< "Accept failed\n";
        return 1;
    }

    cout<< "Client connected \n";

    char buffer[1024] = {0};

    recv(clientSocket, buffer, sizeof(buffer), 0);

    cout<< "Client says: "<<buffer<<endl;

    string reply = "Hello from server";

    send(clientSocket, reply.c_str(), reply.size(),0);

    close(clientSocket);
    close(serverSocket);

    return 0;

}
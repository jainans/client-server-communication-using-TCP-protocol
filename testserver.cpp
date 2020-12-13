#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/time.h>
#include<bits/stdc++.h>

using namespace std;

int main (int argc, char * argv[])
{

    //get the arguments
    if(argc!=2){
        cout<<"Missing port name"<<endl;
        exit(0);
    }
    int port  = atoi(argv[1]);
    char message[1500];

    //create a socket using sockaddr_in for listening purpose

    sockaddr_in serverSocket;
    serverSocket.sin_family = AF_INET;
    serverSocket.sin_port = htons(port);
    serverSocket.sin_addr.s_addr = htonl(INADDR_ANY);

    //get the socket descriptor using socket() function

    int serverSocketID = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocketId < 0){
        cout<<"not successful"<<endl;
        exit(0);
    }
    // bind() the socket to the server

    int bindStatus = bind(serverSocketId, (struct sockaddr *)&serverSocket, sizeof(serverSocket));
    if(bindStatus < 0){
        cout<<"not successfully bind"<<endl;
        exit(0);
    }
    cout<<"Waiting for a client to connect...."<<endl;

    // listen the socket on a port using listen function

    listen(serverSocketID, 1);

    // create a new dedicate socket using sockaddr_in function for receiving and sending messages

    sockaddr_in newSocket;
    socklen_t newSocketLen =  sizeof(newSocket);

    // accept the connection using accept() function

    int newSocketId = accept(serverSocketID, (struct sockaddr* )&newSocket, newSocketLen);
    if(newSocketId<0){
        cout<<"not successful accept()"<<endl;
        exit(0);
    }
    cout<<"Client connected successfully.."<<endl;

    //start sending and receiving messages using send() and recv() functions

    while(1)
    {
        cout<<"Waiting for a message from the client.."<<endl;
        recv(newSocketID, (char* )&message, sizeof(message), 0);
        if(!strcmp(message, "exit"))
        {
            cout<<"connection terminated"<<endl;
            break;
        }
        cout<<"Client : "<<endl;
        cout<<message<<endl;
        string data;
        getline(cin, data);
        strcpy(message, data.c_str());
        if(data=="exit"){
            cout<<"session terminated"<<endl;
            break;
        }
        send(newSocketID, (char*)&message, sizeof(message), 0);

    }

    //close the sockets using close function

    close(serverSocketID);
    close(newSocketId);
}

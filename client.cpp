#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
#iinclude<sys/time.h>
#include<bits/stdc++.h>

using namespace std;

int main (int argc, char* argv[])
{
  // get the arguments

  if(argc!=3)
  {
      cout<<"Missing hostname or port number"<<endl;
      exit(0);
  }
  char* serverName = argv[1];
  int port = atoi(argv[2]);
  char message[1500];

  // get the details of the server using servername by using gethostbyname() function

  struct hostent* host = gethostbyname(serverName);

  // declare a clientSocket using sockaddr_in

  sockaddr_in clientSocket;
  clientSocket.sin_family  = AF_INET;
  clientSocket.sin_port = htons(port);
  clientSocket.sin_addr = **(struct in_addr**)host->h_addr_list;

  // socket() call to get a descriptor for the client socket

  int clientSocketID = socket(AF_INET, SOCK_STREAM, 0);

  // connect() call to connect to server

  int status = connect(clientSocketID, (sockaddr*)&clientSocket, sizeof(clientSocket));
  if(status<0)
  {
    cout<<"Error connecting"<<endl;
    exit(0);
  }
  cout<<"successful connection !"<<endl;

  // start sending and receiving messages

  while(1)
  {
    string data;
    cout<<"Client :";
    getline(cin, data);
    strcpy(message, data.c_str());
    if(data=="exit")
    {
    cout<<"session terminated"<<endl;
    break;
    }
    send(clientSocketID, message, sizeof(message), 0);
    cout<<"Server :";
    recv(clientSocketID, message, sizeof(message), 0);
    if(!strcmp(message, "exit"))
    {
        cout<<"session terminate"<<endl;
        break;
    }
    cout<<message<<endl;
  }

  //close to close the socketID
  close(clientSocketID);
}

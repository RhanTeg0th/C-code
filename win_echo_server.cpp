#include "stdafx.h"
#include <iostream>
#include <string>
#include <string.h>


#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>






#pragma comment(lib, "ws2_32.lib")

using namespace std;


static int MAXPENDING = 5;


int main(int argc, char *argv[])
{
	
	WSADATA wsaData;
	int iResult;
	int optv = 0;
	bool connected = false;
	char *optval = (char*)&optv;
	int optlen = sizeof(optval);
	string Q = "quit";
	const char *exit =Q.c_str();

    


    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup function failed with error: %d\n", iResult);
        return 1;
    }


	if(argc!=2){
		printf("Error: incorrect number of arguments.  ");
		return 1;
	}


	SOCKET servSock;
	servSock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(servSock==INVALID_SOCKET){
		printf("Socket function failed with error: %d\n",GetLastError());
		return 1;
	}
	

	u_int servPort = atoi(argv[1]);

	sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(servPort);

	int opt = setsockopt(servSock,SOL_SOCKET,SO_REUSEADDR,optval,sizeof(optval));
		
	
	if(bind(servSock,(sockaddr*)&servAddr,sizeof(servAddr))<0){
		printf("Bind function failed with error: %d\n", GetLastError());
		return 1;
	}

	

	for(;;){


		if(listen(servSock,MAXPENDING) < 0){
		printf("Listen function failed with error: %d/n",GetLastError());
		return 1;
		}else{
			char *str = new char[5];
			
			printf("Server listening on port %d\n",servPort);
		}

		SOCKET clientSock;
		sockaddr_in clientAddr;
		socklen_t caddrlen = sizeof(clientAddr);
		
		

		clientSock = accept(servSock,(sockaddr*)&clientAddr,&caddrlen);
		
		if(clientSock < 0){
		   printf("Accept() function failed with error: %d/n", GetLastError());
		   goto QUIT;

		}else if(clientSock >=0){
			connected = true;
		}
		
		

		char cName[INET_ADDRSTRLEN];

		if(inet_ntop(AF_INET,&clientAddr.sin_addr,cName,sizeof(cName))!=NULL){
			printf("Handling client %s/%d\n", cName,ntohs(clientAddr.sin_port));
		}else{
			printf("Error: Unable to get client address");
		}

		
		char buffer[256];
		

		while(connected==true){

			

			long nbytesrcvd = recv(clientSock,buffer,sizeof(buffer),0);
				
			
				

			if(nbytesrcvd==0){
				connected = false;
				cout << endl;
				cout << cName << ": client disconnected" << endl;					
				cout << endl;
				break;
			}

			

			if(nbytesrcvd < 0){
				printf("Error: recv() failed");
				cout << endl;
				goto QUIT;
			}
		           					

			 if(nbytesrcvd > 0){
			 	   		
				long nbytessent = send(clientSock,buffer,sizeof(buffer),0);
				if(nbytessent < 0){
					cout << "Error: send() failed" << endl;
					cout << endl;
					goto QUIT;			
					
				}else if(nbytessent > sizeof(buffer)){
					cout << "send() error: sent unexpected # of bytes" << endl;
					cout << endl;
					goto QUIT;
							
				}  						
			 }

		}

		    
		
		QUIT:
					    
			int iResult = closesocket(clientSock);
			if (iResult == SOCKET_ERROR) {
				printf("closesocket function failed with error: %d\n",GetLastError());
			}
			
	   
	
		}




}


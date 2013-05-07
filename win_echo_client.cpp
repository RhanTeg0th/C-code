#include "stdafx.h"
#include <iostream>
#include <string>
#include <string.h>


#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>



#pragma comment(lib, "ws2_32.lib")

using namespace std;


int main(int argc,char* argv[])
{
	

	WSADATA wsaData;
	int result;
	bool connected = false;
	hostent *rhost;
	char buffer[256];
	string exit = "quit";

	

	

    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != NO_ERROR) {
        printf("WSAStartup function failed with error: %d\n", result);
        return 1;
    }

	 
	
   
    SOCKET connector;
    connector = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (connector == INVALID_SOCKET) {
        wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

	string hname;
	cout << "Enter host name(URL): ";
	cin >> hname;
	cout << endl;
	
	string portnum;
	cout << "Enter the port number you wish to connect on: " ;
	cin >> portnum;
	cout << endl;
    
	char *hostname = const_cast<char*>(hname.c_str());
	char *hostPort = const_cast<char*>(portnum.c_str());


	
	rhost = gethostbyname(hostname);
	in_addr addr;
	addr.s_addr = *(u_long *)rhost->h_addr_list[0];

	

	sockaddr_in clientserv;
	clientserv.sin_family = AF_INET;
	clientserv.sin_addr.s_addr = addr.s_addr;
	clientserv.sin_port = htons(atoi(hostPort));

	if(connect(connector,(sockaddr*)&clientserv,sizeof(clientserv))==SOCKET_ERROR){
		printf("connect function failed with error: %d\n", GetLastError());
        if(closesocket(connector)<0){
			printf("closesocket function failed %d\n", GetLastError());
		}
        return 1;
	}else{
		connected = true;
		cout << "Connected to host " << hname << " on port " << portnum << endl;
		cout << "Type 'quit' to exit the program " << endl;
	}


	while(connected==true){

       int nbr = 0;
	   
	   
	   cout << endl;
	   cout << ">";
       scanf("%s",buffer);
	   cout << endl;
	      
	   string str(buffer);

	   if(str==exit){
		   
		   connected = false;
		   goto quit;
	   }

	   
	   

	   long nbs = send(connector,buffer,sizeof(buffer),0);
	   if(nbs < 0){
			printf("send() failed", GetLastError());
			return 1;
	   }

	   while(nbr < nbs){
			nbr = recv(connector,buffer,sizeof(buffer),0);
			if(nbr < 0){
				printf("recv() failed", GetLastError());
				return 1;

			}else if(nbr==0){
				printf("recv() failed: connection closed prematurely", GetLastError());
				return 1;				
			}else if(nbr > 0){
				cout << endl;
				cout << ">> ";
				printf(buffer);
				cout << endl;
			}
					
	   }

	   

	}

	quit:
   		
		if (closesocket(connector) == SOCKET_ERROR) {
			printf("closesocket function failed with error: %ld\n", GetLastError());
			WSACleanup();
			return 1;
		}

	
	WSACleanup();

	return 0;
	


}


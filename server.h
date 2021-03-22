#pragma once

#include <iostream>
#include <WinSock2.h>
#include <thread>
#include <chrono>
#include <string>
#include <stdexcept>

namespace server{
	WORD        wVersionRequested;
	WSADATA     wsaData;
	SOCKADDR_IN servAddr, cliAddr;
	SOCKET      s, s2;
	int         err;
	int         bytesSent;
	char        buf[999];
	
	#define showError(s,e) std::cout<<"[X] "<<(s)<<" : "<<(e)<<"\n";
	int makeConnection(const int PORT=12345){
		wVersionRequested = MAKEWORD(1,1);
		err = WSAStartup(wVersionRequested, &wsaData);
		if(err!=0){
			showError("WSAStartup Error",WSAGetLastError());
			WSACleanup();
			return 0;
		}
		servAddr.sin_family = AF_INET;
		servAddr.sin_port = htons(PORT);
		servAddr.sin_addr.s_addr = inet_addr("0.0.0.0");
		
		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(s==INVALID_SOCKET){
			showError("Socket Error",WSAGetLastError());
			WSACleanup();
			return 0;
		}
		int x = bind(s,reinterpret_cast<SOCKADDR *>(&servAddr),sizeof(servAddr));
		if(x==SOCKET_ERROR){
			showError("Binding Failed"<<WSAGetLastError());
			WSACleanup();
			return 0;
		}
		
		listen(s,5);
		int xx=sizeof(cliAddr);
		s2 = accept(s,reinterpret_cast<SOCKADDR*>(&cliAddr),&xx);
		
		return 1;
	}
	
	string recvTxt(){
		int n = recv(s2,buf,999,0);
		if(n<=0){
			return "";
		}
		buf[n]=0;
		return string(buf);
	}
	
	int sendTxt(string str){
		return send(s2,str.c_str(),str.size(),0);
	}
	#undef showError
}
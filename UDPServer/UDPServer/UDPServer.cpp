// UDPServer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <WinSock2.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>

#pragma comment(lib,"WS2_32.lib")

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA data;	

	WORD w = MAKEWORD(2,0);
	char sztext[] ="欢迎你\r\n";
	::WSAStartup(w,&data);
	SOCKET s;
	s = ::socket(AF_INET,SOCK_DGRAM,0);
	sockaddr_in addr, addr2;
	int n = sizeof(addr2);
	char buff[] = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(75);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	if(::bind(s,(sockaddr*)&addr,sizeof(addr)) == SOCKET_ERROR){
		cout<<"Failed bind()"<<endl;
		return 0;
	}

	cout<<"UDP服务器已启动"<<endl;
	char buf[1024];
	while(TRUE){
		int nRecv = ::recvfrom(s,buf,1024,0,(sockaddr*)&addr2,&n);
		if (nRecv > 0){
			buf[nRecv] = '\n';
			printf("接收到数据(%s):%s",::inet_ntoa(addr2.sin_addr),buf);
		}
	}
	::closesocket(s);
	/*
	while(true){
	if(::recvfrom(s,buff,10,0,(sockaddr*)&addr2,&n) != -1){
		cout<<inet_ntoa(addr2.sin_addr)<<"已经连接上"<<endl;
		cout<<buff<<endl;
		::sendto(s,sztext,sizeof(sztext),0,(sockaddr*)&addr2,n);
		::closesocket(s);
		::WSACleanup();

	}
	}*/

	cin.get();
	return 0;
}


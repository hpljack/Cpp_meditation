// TCPServer.cpp : 定义控制台应用程序的入口点。
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
	SOCKET s, s1;
	s = ::socket(AF_INET,SOCK_STREAM,0);
	sockaddr_in addr, addr2;
	int n = sizeof(addr2);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(75);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	::bind(s,(sockaddr*)&addr,sizeof(addr));
	::listen(s,5);
	cout<<"服务器已启动"<<endl;

	while(true){
		s1 = ::accept(s,(sockaddr*)&addr2,&n);
		if(s1 != NULL){
			cout<<inet_ntoa(addr2.sin_addr)<<"已经连接上"<<endl;
			::send(s1,sztext,sizeof(sztext),0); //向客户端发送字符数组
		}
		::closesocket(s);
		::closesocket(s1);
		::WSACleanup();
	}

	cin.get();
	return 0;
}


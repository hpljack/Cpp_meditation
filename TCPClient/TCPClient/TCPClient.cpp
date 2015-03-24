// TCPClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>
#include <iostream>

#pragma comment(lib,"WS2_32.lib")

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA data;
	WORD w = MAKEWORD(2,0);
	::WSAStartup(w,&data);
	SOCKET s;
	char sztext[10] = {0};

	s = ::socket(AF_INET,SOCK_STREAM,0);
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(75);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	cout<<"客户端已启动"<<endl;
	::connect(s,(sockaddr*)&addr,sizeof(addr));
	::recv(s,sztext,sizeof(sztext),0);
	cout<<sztext<<endl;
	::closesocket(s);
	::WSACleanup();


	cin.get();
	return 0;
}


// UDPClient.cpp : �������̨Ӧ�ó������ڵ㡣
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
	::WSAStartup(w,&data);
	SOCKET s;
	char sztext[] = "�ͻ���˵ ���";
	s = ::socket(AF_INET,SOCK_DGRAM,0);
	sockaddr_in addr,addr2;
	int n = sizeof(addr2);
	char buff[10] ={0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(75);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	cout<<"UDP�ͻ���������"<<endl;

	if(::sendto(s,sztext,sizeof(sztext),0,(sockaddr*)&addr,n) != 0){
		::recvfrom(s,buff,10,0,(sockaddr*)&addr2,&n);
		cout<<"������˵�� "<<buff<<endl;
		::closesocket(s);
		::WSACleanup();
	}

	cin.get();
	return 0;
}


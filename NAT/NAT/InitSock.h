#ifndef CINITSOCK_H
#define CINITSOCK_H

#include <winsock2.h>
#pragma comment(lib,"WS2_32")

class CInitSock{
public:
	CInitSock(BYTE minorVer = 2, BYTE majorVer = 2){
		WSADATA wsData;
		WORD sockVersion = MAKEWORD(minorVer,majorVer);
		if(::WSAStartup(sockVersion,&wsData) != 0){
			exit(0);
		}
	}
	~CInitSock(){
		::WSACleanup();
	}
};
#endif // !CINITSOCK_H

#ifndef GETIPADDR_H
#define GETIPADDR_H

#include "InitSock.h"
#include <stdio.h>

CInitSock initSock;

void GetIpAddress(){

	printf("GetIpAddress function demo\n");

	char szHost[256];
	//get local host name
	::gethostname(szHost,256);
	//get addressinfo by hostname
	HOSTENT* pHost = ::gethostbyname(szHost);
	in_addr addr;
	for(int i = 0; ;++i){
		char* p = pHost->h_addr_list[i];
		if(p == NULL)
			break;

		memcpy(&addr.S_un.S_addr,p,pHost->h_length);
		char* szIp = ::inet_ntoa(addr);
		printf("±¾»úIPµØÖ·£º%s\n",szIp);
	}
}

#endif // !GETIPADDR_H

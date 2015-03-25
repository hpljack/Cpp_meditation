#include "..\..\NAT\NAT\InitSock.h"
#include <stdio.h>

CInitSock initsock;

int main(){
	//创建套接字
	SOCKET sListen = ::socket(AF_INET,SOCK_STREAM,IPPORT_TCPMUX);
	if(sListen == INVALID_SOCKET){
		printf("Failed socket()\n");
		return 0;
	}

	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(4567);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;

	//绑定套接字
	if(::bind(sListen,(LPSOCKADDR)&sin,sizeof(sin)) == SOCKET_ERROR){
		printf("Failed bind()\n");
		return 0;
	}

	//进入监听模式
	if(::listen(sListen,2) == SOCKET_ERROR){
		printf("Failed Listen()\n");
		return 0;
	}

	//循环接收客户的连接请求
	sockaddr_in remoteAddr;
	int nAddrLen = sizeof(remoteAddr);
	SOCKET sClient;
	char szText[] = "TcpSvr Demo!\n";
	while ()
	{
	}

	return 0;
}
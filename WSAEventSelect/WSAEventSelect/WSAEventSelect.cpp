#include <stdio.h>
#include "..\..\common\InitSock.h"

CInitSock initsock;


int main(){

	WSAEVENT eventArray[WSA_MAXIMUM_WAIT_EVENTS];
	SOCKET sockArray[WSA_MAXIMUM_WAIT_EVENTS];

	int nEventTotal = 0;
	USHORT nPort = 4567;

	SOCKET sListen = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(nPort);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;

	if(::bind(sListen,(sockaddr*)&sin,sizeof(sin)) == SOCKET_ERROR){
		printf("Failed bind()\n");
		return -1;
	}

	::listen(sListen,5);
	//创建事件对象，并关联到新的套接字
	WSAEVENT event = ::WSACreateEvent();
	::WSAEventSelect(sListen,event,FD_ACCEPT|FD_CLOSE);
	//添加到表中
	eventArray[nEventTotal] = event;
	sockArray[nEventTotal] = sListen;
	nEventTotal++;

	//处理网络事件
	while (TRUE)
	{
		//在所有事件对象上等待
		int nIndex = ::WSAWaitForMultipleEvents(nEventTotal,eventArray,FALSE,WSA_INFINITE,FALSE);
		//对每个事件调用WSAWaitForMultipleEvents函数，以确定它的状态
		nIndex = nIndex - WSA_WAIT_EVENT_0;
		for (int i = nIndex; i != nEventTotal; ++i)
		{
			nIndex = ::WSAWaitForMultipleEvents(1,&eventArray[i],TRUE,1000,FALSE);
			if(nIndex == WSA_WAIT_FAILED|| nIndex == WSA_WAIT_TIMEOUT)
				continue;
			else{
				//获取到来的消息通知，WSA
			}
		}


	}



	return 0;
}
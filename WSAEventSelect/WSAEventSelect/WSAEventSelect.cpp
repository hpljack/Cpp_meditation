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
	//�����¼����󣬲��������µ��׽���
	WSAEVENT event = ::WSACreateEvent();
	::WSAEventSelect(sListen,event,FD_ACCEPT|FD_CLOSE);
	//��ӵ�����
	eventArray[nEventTotal] = event;
	sockArray[nEventTotal] = sListen;
	nEventTotal++;

	//���������¼�
	while (TRUE)
	{
		//�������¼������ϵȴ�
		int nIndex = ::WSAWaitForMultipleEvents(nEventTotal,eventArray,FALSE,WSA_INFINITE,FALSE);
		//��ÿ���¼�����WSAWaitForMultipleEvents��������ȷ������״̬
		nIndex = nIndex - WSA_WAIT_EVENT_0;
		for (int i = nIndex; i != nEventTotal; ++i)
		{
			nIndex = ::WSAWaitForMultipleEvents(1,&eventArray[i],TRUE,1000,FALSE);
			if(nIndex == WSA_WAIT_FAILED|| nIndex == WSA_WAIT_TIMEOUT)
				continue;
			else{
				//��ȡ��������Ϣ֪ͨ��WSA
			}
		}


	}



	return 0;
}
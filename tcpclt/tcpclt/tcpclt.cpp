#include <stdio.h>
#include "..\..\NAT\NAT\InitSock.h"

CInitSock initsock;

int main(){

	//�����׽���
	SOCKET s = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(s == INVALID_SOCKET){
		printf("Failed socket()\n");
		return 0;
	}

	//��дԶ�˵�ַ��Ϣ
	sockaddr_in srvAddr;
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(4567);
	srvAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if(::connect(s,(sockaddr*)&srvAddr,sizeof(srvAddr)) == -1){
		printf("Failed connect()\nt");
		return 0;
	}

	char buff[256];
	int nRecv = ::recv(s,buff,256,0);
	if (nRecv > 0){
		buff[nRecv] = '\n';
		printf("���յ������ݣ�%s",buff);
	}
	::closesocket(s);

	system("pause");
	return 0;
}
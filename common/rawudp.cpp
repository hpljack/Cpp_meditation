#include "rawudp.h"
#include "InitSock.h"
#include <WS2tcpip.h>
#include "ipheaderinfo.h"
#include <stdio.h>

CInitSock initsock;

void SendUDPPacketTest(){

	//���������Ϣ
	char szDestIp[] = "10.16.115.88";
	char szSourceIP[] = "127.0.0.1";
	USHORT nDestPort = 4567;
	USHORT nSourcePort = 8888;
	char szMsg[] = "This is a test\n";
	int nMsgLen = strlen(szMsg);
	SOCKET sRaw = ::socket(AF_INET,SOCK_RAW,IPPROTO_UDP);//����UDPԭʼ�׽���
	//��ЧIPͷ����ѡ��
	BOOL bIncl = TRUE;
	::setsockopt(sRaw,IPPROTO_IP,IP_HDRINCL,(char*)&bIncl,sizeof(bIncl));
	char buff[1024] = {0};
	//IPͷ����ѡ��
	IPHeader* pIphdr = (IPHeader*)buff;
	pIphdr->ihpVerLen = (4<<4 | (sizeof(IPHeader)/sizeof(ULONG)));
	pIphdr->ipLength = ::htons(sizeof(IPHeader) + sizeof(UDPHeader) + nMsgLen);
	pIphdr->ipTTL = 128;
	pIphdr->ipProtocol = IPPROTO_UDP;
	pIphdr->ipSource = ::inet_addr(szSourceIP);
	pIphdr->ipDestination = ::inet_addr(szDestIp);
	pIphdr->ipChecksum = checksum((USHORT*)pIphdr,sizeof(IPHeader));
	//UDPͷ
	UDPHeader* pUdphdr = (UDPHeader*)&buff[sizeof(IPHeader)];
	pUdphdr->sourcePort = ::htons(8888);
	pUdphdr->destinationPort = ::htons(nDestPort);
	pUdphdr->len = ::htons(sizeof(UDPHeader) + nMsgLen);
	pUdphdr->checksum = 0;
	char* pData = &buff[sizeof(IPHeader) + sizeof(UDPHeader)];
	memcpy(pData,szMsg,nMsgLen);
	ComputeUdpPseudoHeaderChecksum(pIphdr,pUdphdr,pData,nMsgLen);
	//����Ŀ�ĵ�ַ
	SOCKADDR_IN destAddr = {0};
	destAddr.sin_family = AF_INET;
	destAddr.sin_port = ::htons(nDestPort);
	destAddr.sin_addr.S_un.S_addr = ::inet_addr(szDestIp);

	//����ԭʼUDP���
	int nRet;
	for(int i = 0; i != 5; ++i){
		nRet = ::sendto(sRaw,buff,sizeof(IPHeader) + sizeof(UDPHeader) + nMsgLen,0,(SOCKADDR*)&destAddr,sizeof(destAddr));
		if(nRet == SOCKET_ERROR){
			printf("sendto() failed %d\n",::WSAGetLastError());
			break;
		}else
		{
			printf("send %d bytes\n",nRet);
		}
	}
	::closesocket(sRaw);
	return;
}
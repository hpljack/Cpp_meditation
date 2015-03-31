#include <stdio.h>
#include <WS2tcpip.h>
#include "..\..\Common\InitSock.h"
#include <WinSock2.h>
#include <windows.h>
#include <iostream>

using namespace std;

CInitSock initsock;
typedef struct _iphdr
{
	unsigned int h_len: 4;//头长度
	unsigned int   version:4;//IP版本  
	unsigned char  tos;      //服务类型  
	unsigned short total_len;//包的总长度  
	unsigned short ident;    //包标识身份  
	unsigned short frag_and_flags;//标志  
	unsigned char  ttl;       //包生命周期  
	unsigned char  proto;     //协议类型  
	unsigned short checksum;  //IP校验  
	unsigned int   sourceIP;  //源IP  
	unsigned int   destIP;    //目标IP  
}IPHeader,*PIPHeader;
typedef struct icmp_hdr 
{
	unsigned char icmp_type; //消息类型
	unsigned char icmp_code;//代码
	unsigned short icmp_checksum;//校验和
	//回显
	unsigned short icmp_id; //唯一标识次请求的ID号，通常设置为进程号
	unsigned short  icmp_sequence;//序列号
	unsigned long icmp_timestamp;//时间戳
}ICMP_HDR,*PICMP_HDR;

BOOL SetTimeOut(SOCKET s,int nTime, BOOL boRecv){
	int ret = ::setsockopt(s,SOL_SOCKET,boRecv ? SO_RCVTIMEO:SO_SNDTIMEO,(char*)&nTime,sizeof(nTime));
	return ret != SOCKET_ERROR;
}

USHORT checksum(USHORT* buff,int size){
	unsigned long chksum = 0;
	//将数据以字为单位累加到chksum中
	while (size > 1)
	{
		chksum += *buff++;
		size -= sizeof(USHORT);
	}
	//如果为奇数，将最后一个字扩展到双字  在累加
	if (size)
		chksum += *(UCHAR*)buff;

	//将chksum的高16位和低16位相加 取反后得到检验和
	chksum = (chksum>>16) + (chksum&0xffff);
	chksum += (chksum>>16);
	return (USHORT)(~chksum);
}

int main(){
	char szDestIP[] = "127.0.0.1";   //目的地址
	SOCKET sRaw = ::socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);//创建原始套接字
	SetTimeOut(sRaw,1000,TRUE); //设置连接超时
	//设置目的地址
	SOCKADDR_IN dest;
	dest.sin_family = AF_INET;
	dest.sin_port = htons(0);
	dest.sin_addr.S_un.S_addr = inet_addr(szDestIP);
	//创建ICMP封包
	char buff[sizeof(ICMP_HDR) + 32];
	ICMP_HDR* pIcmp = (ICMP_HDR*)buff;
	//填写icmp封包数据
	pIcmp->icmp_type = 8; //请求一个icmp回显
	pIcmp->icmp_code = 0;
	pIcmp->icmp_id = (USHORT)::GetCurrentProcessId();
	pIcmp->icmp_checksum = 0;
	pIcmp->icmp_sequence = 0;
	//填充数据部分可以为任意
	memset(&buff[sizeof(ICMP_HDR)],'E',32);
	//开始发送和接收ICMP封包
	USHORT nSeq = 0;
	char recvBuf[1024];
	SOCKADDR_IN from;
	int nLen = sizeof(from);
	while (TRUE)
	{
		static int nCount = 0;
		int nRet = 0;
		if(nCount++ == 4)
			break;

		pIcmp->icmp_checksum = 0;
		pIcmp->icmp_timestamp = ::GetTickCount();
		pIcmp->icmp_sequence = nSeq++;
		pIcmp->icmp_checksum = checksum((USHORT*)buff,sizeof(ICMP_HDR) + 32);
		nRet = ::sendto(sRaw,buff,sizeof(ICMP_HDR) + 32,0,(SOCKADDR*)&dest,sizeof(dest));
		if (nRet == SOCKET_ERROR)
		{
			printf("sendto() failed:%d\n",::WSAGetLastError());
			system("pause");
			return -1;
		}

		nRet = ::recvfrom(sRaw,recvBuf,1024,0,(SOCKADDR*)&from,&nLen);
		if (nRet == SOCKET_ERROR){
			if(::WSAGetLastError() == WSAETIMEDOUT){
				printf("timed out\n");
				continue;
			}
			printf("recvfrom() failed: %d\n",::WSAGetLastError());
			return -1;
		}
		//开始解析接收到的icmp包
		int nTick = ::GetTickCount();
		if(nRet <sizeof(IPHeader) + sizeof(ICMP_HDR)){
			printf("Too few bytes from %s\n",::inet_ntoa(from.sin_addr));
			system("pause");
		}

		//ICMP_HDR* pRecvIcmp = (ICMP_HDR*)(recvBuf + sizeof(IPHeader));
		ICMP_HDR* pRecvIcmp = (ICMP_HDR*)(recvBuf + 20);// (ICMP_HDR*)(recvBuf + sizeof(IPHeader)); sizeof(IPheader) = 24
		if (pRecvIcmp->icmp_type != 0){//回显
			printf("nonecho type %d recved\n",pRecvIcmp->icmp_type);
			system("pause");
			return -1;
		}
		if(pRecvIcmp->icmp_id != ::GetCurrentProcessId()){
			printf("someone else's packet!\n");
			system("pause");
			return -1;
		}

		printf("%d bytes from %s",nRet,inet_ntoa(from.sin_addr));
		printf(" icmp_seq=%d",pRecvIcmp->icmp_sequence);
		printf(" time: %d ms",nTick-pRecvIcmp->icmp_timestamp);
		printf("\n");
		::Sleep(1000);
	}

	cin.get();	
	return 0;
}
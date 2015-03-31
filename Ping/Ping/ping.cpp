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
	unsigned int h_len: 4;//ͷ����
	unsigned int   version:4;//IP�汾  
	unsigned char  tos;      //��������  
	unsigned short total_len;//�����ܳ���  
	unsigned short ident;    //����ʶ���  
	unsigned short frag_and_flags;//��־  
	unsigned char  ttl;       //����������  
	unsigned char  proto;     //Э������  
	unsigned short checksum;  //IPУ��  
	unsigned int   sourceIP;  //ԴIP  
	unsigned int   destIP;    //Ŀ��IP  
}IPHeader,*PIPHeader;
typedef struct icmp_hdr 
{
	unsigned char icmp_type; //��Ϣ����
	unsigned char icmp_code;//����
	unsigned short icmp_checksum;//У���
	//����
	unsigned short icmp_id; //Ψһ��ʶ�������ID�ţ�ͨ������Ϊ���̺�
	unsigned short  icmp_sequence;//���к�
	unsigned long icmp_timestamp;//ʱ���
}ICMP_HDR,*PICMP_HDR;

BOOL SetTimeOut(SOCKET s,int nTime, BOOL boRecv){
	int ret = ::setsockopt(s,SOL_SOCKET,boRecv ? SO_RCVTIMEO:SO_SNDTIMEO,(char*)&nTime,sizeof(nTime));
	return ret != SOCKET_ERROR;
}

USHORT checksum(USHORT* buff,int size){
	unsigned long chksum = 0;
	//����������Ϊ��λ�ۼӵ�chksum��
	while (size > 1)
	{
		chksum += *buff++;
		size -= sizeof(USHORT);
	}
	//���Ϊ�����������һ������չ��˫��  ���ۼ�
	if (size)
		chksum += *(UCHAR*)buff;

	//��chksum�ĸ�16λ�͵�16λ��� ȡ����õ������
	chksum = (chksum>>16) + (chksum&0xffff);
	chksum += (chksum>>16);
	return (USHORT)(~chksum);
}

int main(){
	char szDestIP[] = "127.0.0.1";   //Ŀ�ĵ�ַ
	SOCKET sRaw = ::socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);//����ԭʼ�׽���
	SetTimeOut(sRaw,1000,TRUE); //�������ӳ�ʱ
	//����Ŀ�ĵ�ַ
	SOCKADDR_IN dest;
	dest.sin_family = AF_INET;
	dest.sin_port = htons(0);
	dest.sin_addr.S_un.S_addr = inet_addr(szDestIP);
	//����ICMP���
	char buff[sizeof(ICMP_HDR) + 32];
	ICMP_HDR* pIcmp = (ICMP_HDR*)buff;
	//��дicmp�������
	pIcmp->icmp_type = 8; //����һ��icmp����
	pIcmp->icmp_code = 0;
	pIcmp->icmp_id = (USHORT)::GetCurrentProcessId();
	pIcmp->icmp_checksum = 0;
	pIcmp->icmp_sequence = 0;
	//������ݲ��ֿ���Ϊ����
	memset(&buff[sizeof(ICMP_HDR)],'E',32);
	//��ʼ���ͺͽ���ICMP���
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
		//��ʼ�������յ���icmp��
		int nTick = ::GetTickCount();
		if(nRet <sizeof(IPHeader) + sizeof(ICMP_HDR)){
			printf("Too few bytes from %s\n",::inet_ntoa(from.sin_addr));
			system("pause");
		}

		//ICMP_HDR* pRecvIcmp = (ICMP_HDR*)(recvBuf + sizeof(IPHeader));
		ICMP_HDR* pRecvIcmp = (ICMP_HDR*)(recvBuf + 20);// (ICMP_HDR*)(recvBuf + sizeof(IPHeader)); sizeof(IPheader) = 24
		if (pRecvIcmp->icmp_type != 0){//����
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
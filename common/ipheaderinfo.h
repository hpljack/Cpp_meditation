#ifndef IPHEADER_INFO_H
#define IPHEADER_INFO_H
#include "InitSock.h"

typedef struct _IPHeader
{
	UCHAR ihpVerLen;
	UCHAR ipTOS;
	USHORT ipLength;
	USHORT ipID;
	USHORT ipFlags;
	UCHAR ipTTL;
	UCHAR ipProtocol;
	USHORT ipChecksum;
	ULONG ipSource;
	ULONG ipDestination;
}IPHeader,*PIPHeader;

typedef struct _UDPHeader
{
	USHORT sourcePort;
	USHORT destinationPort;
	USHORT len;
	USHORT checksum;
}UDPHeader,*PUDPHeader;

typedef struct  _TCPHeader
{
	USHORT sourcePort;
	USHORT destinationPort;
	ULONG sequenceNumber;
	ULONG acknowledgeNumber;
	UCHAR dataoffset;
	UCHAR flags;
	USHORT windows;
	USHORT checksum;
	USHORT urgentPointer;
}TCPHeader,*PTCPHeader;

USHORT checksum(USHORT* buff,int size);

void ComputeUdpPseudoHeaderChecksum(IPHeader* pIphdr,	UDPHeader* pUdphdr,	char* payload,	int payloadlen);

#endif
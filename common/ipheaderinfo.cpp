#include "ipheaderinfo.h"

USHORT checksum(USHORT* buff,int size){
	unsigned long chksum = 0;
	while(size > 1){
		chksum += *buff++;
		size -= sizeof(USHORT);
	}
	if(size){
		chksum += *(UCHAR*)buff;
	}
	chksum = (chksum>>16) + (chksum&0xffff);
	chksum += (chksum>>16);
	return (USHORT)(~chksum);
}

void ComputeUdpPseudoHeaderChecksum(IPHeader* pIphdr,	UDPHeader* pUdphdr,	char* payload,	int payloadlen){

	char buff[1024];
	char* ptr = buff;
	int chksumlen = 0;
	ULONG zero = 0;
	//����ԴIP��Ŀ��IP
	memcpy(ptr,&pIphdr->ipSource,sizeof(pIphdr->ipSource));
	ptr += sizeof(pIphdr->ipSource);
	chksumlen += sizeof(pIphdr->ipSource);
	memcpy(ptr,&pIphdr->ipDestination,sizeof(pIphdr->ipDestination));
	ptr += sizeof(pIphdr->ipDestination);
	chksumlen += sizeof(pIphdr->ipDestination);
	//����8λ0��
	memcpy(ptr,&zero,1);
	ptr += 1;
	chksumlen += 1;
	//Э��
	memcpy(ptr,&pIphdr->ipProtocol,sizeof(pIphdr->ipProtocol));
	ptr += sizeof(pIphdr->ipProtocol);
	chksumlen += sizeof(pIphdr->ipProtocol);
	//UDP����
	memcpy(ptr,&pUdphdr->len,sizeof(pUdphdr->len));
	ptr += sizeof(pUdphdr->len);
	chksumlen += sizeof(pUdphdr->len);
	//UDPԴ�˿�
	memcpy(ptr,&pUdphdr->sourcePort,sizeof(pUdphdr->sourcePort));
	ptr += sizeof(pUdphdr->sourcePort);
	chksumlen += sizeof(pUdphdr->sourcePort);
	//UDPĿ�Ķ˿ں�
	memcpy(ptr,&pUdphdr->destinationPort,sizeof(pUdphdr->destinationPort));
	ptr += sizeof(pUdphdr->destinationPort);
	chksumlen += sizeof(pUdphdr->destinationPort);
	//����UDP����
	memcpy(ptr,&pUdphdr->len,sizeof(pUdphdr->len));
	ptr += sizeof(pUdphdr->len);
	chksumlen += sizeof(pUdphdr->len);
	//16λ��UDPУ�����Ϊ0
	memcpy(ptr,&zero,sizeof(USHORT));
	ptr += sizeof(USHORT);
	chksumlen += sizeof(USHORT);
	//����
	memcpy(ptr,payload,payloadlen);
	ptr += payloadlen;
	chksumlen += payloadlen;

	//���뵽��һ��16λ�߽�
	for(int i = 0; i < payloadlen % 2; i++){
		*ptr = 0;
		ptr++;
		chksumlen++;
	}
	pUdphdr->checksum = checksum((USHORT*)buff,chksumlen);
}
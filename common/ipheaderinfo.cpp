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
	//包含源IP和目的IP
	memcpy(ptr,&pIphdr->ipSource,sizeof(pIphdr->ipSource));
	ptr += sizeof(pIphdr->ipSource);
	chksumlen += sizeof(pIphdr->ipSource);
	memcpy(ptr,&pIphdr->ipDestination,sizeof(pIphdr->ipDestination));
	ptr += sizeof(pIphdr->ipDestination);
	chksumlen += sizeof(pIphdr->ipDestination);
	//包含8位0域
	memcpy(ptr,&zero,1);
	ptr += 1;
	chksumlen += 1;
	//协议
	memcpy(ptr,&pIphdr->ipProtocol,sizeof(pIphdr->ipProtocol));
	ptr += sizeof(pIphdr->ipProtocol);
	chksumlen += sizeof(pIphdr->ipProtocol);
	//UDP长度
	memcpy(ptr,&pUdphdr->len,sizeof(pUdphdr->len));
	ptr += sizeof(pUdphdr->len);
	chksumlen += sizeof(pUdphdr->len);
	//UDP源端口
	memcpy(ptr,&pUdphdr->sourcePort,sizeof(pUdphdr->sourcePort));
	ptr += sizeof(pUdphdr->sourcePort);
	chksumlen += sizeof(pUdphdr->sourcePort);
	//UDP目的端口号
	memcpy(ptr,&pUdphdr->destinationPort,sizeof(pUdphdr->destinationPort));
	ptr += sizeof(pUdphdr->destinationPort);
	chksumlen += sizeof(pUdphdr->destinationPort);
	//又是UDP长度
	memcpy(ptr,&pUdphdr->len,sizeof(pUdphdr->len));
	ptr += sizeof(pUdphdr->len);
	chksumlen += sizeof(pUdphdr->len);
	//16位的UDP校验和置为0
	memcpy(ptr,&zero,sizeof(USHORT));
	ptr += sizeof(USHORT);
	chksumlen += sizeof(USHORT);
	//净荷
	memcpy(ptr,payload,payloadlen);
	ptr += payloadlen;
	chksumlen += payloadlen;

	//补齐到下一个16位边界
	for(int i = 0; i < payloadlen % 2; i++){
		*ptr = 0;
		ptr++;
		chksumlen++;
	}
	pUdphdr->checksum = checksum((USHORT*)buff,chksumlen);
}
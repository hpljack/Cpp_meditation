#ifndef PING_H
#define PING_H
#include <WS2tcpip.h>
#include <WinSock2.h>

#define DEF_PACKET_SIZE 32

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

class CPingDlg;

class CPing{
public:
	void setConfig(char *host,BOOL recordrout=FALSE,int size=DEF_PACKET_SIZE);
	void DecodeIPOptions(char* buf, int bytes);
};
#endif // !PING_H

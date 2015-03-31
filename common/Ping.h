#ifndef PING_H
#define PING_H
#include <WS2tcpip.h>
#include <WinSock2.h>

#define DEF_PACKET_SIZE 32

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

class CPingDlg;

class CPing{
public:
	void setConfig(char *host,BOOL recordrout=FALSE,int size=DEF_PACKET_SIZE);
	void DecodeIPOptions(char* buf, int bytes);
};
#endif // !PING_H

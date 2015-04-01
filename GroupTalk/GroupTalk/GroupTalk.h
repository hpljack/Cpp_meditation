#ifndef GROUP_TALK_H
#pragma once
#include "..\..\common\InitSock.h"
#include <WS2tcpip.h>
#include <stdio.h>

#define BUFFER_SIZE  1024 * 4
#define  GROUP_PORT 4567
#define WM_GROUPTALK  WM_USER + 105

const enum gt_type
{
	MT_JOIN = 1,//�û�����
	MT_LEAVE,   //�û��뿪
	MT_MESG,    //�û�������Ϣ
	MT_MINE     //�����¼�����û����û���Ϣ
};

typedef struct gt_hdr
{
	unsigned char gt_type;  //��Ϣ����
	DWORD dwAddr;          //���ʹ���Ϣ���û���IP��ַ
	char szUser[15];             //���ʹ���Ϣ���û���
	int nDataLength;          //�������ݵĳ���
	char * data(){ return (char*)(this + 1);}
}GT_HDR;

class CGroupTalk
{
public:
	//���캯�� ���������̣߳� ���������
	CGroupTalk(HWND hNotifyWnd,
		    DWORD dwMultiAddr, DWORD dwLocalAddr = INADDR_ANY, int nTTL = 64);
	//�������� ������Դ �뿪������
	~CGroupTalk();
	//��������Ա������Ϣ�� dwRemoteAddrΪĿ���ַ��0��ʾ�����г�Ա����
	BOOL SendText(char* szText,int nLen, DWORD dwRemoteAddr = 0);
protected:
	//��������
	BOOL JoinGroup();
	BOOL LeaveGroup();
	//��ָ����ַ����UDP
	BOOL Send(char *szText, int nLen,DWORD dwRemoteAddr);
protected:
	//�������ķ��
	void DispatchMsg(GT_HDR*, int nLen);
	friend DWORD WINAPI _GroupTalkEntry(LPVOID lpParam);

	HWND m_hNotifyWnd;    //�����ھ��
   DWORD m_dwMultiAddr; //����ʹ�õĶಥ��ַ
   DWORD m_dwLocalAddr; //�û�Ҫʹ�õı��ص�ַ
   int m_nTTL;                        //�ಥ�����TTL
   HANDLE m_hThread;        //�����߳̾��
   HANDLE m_hEvent;          //�¼������ ����ʹ���ص�I/O��������
   SOCKET m_sRead;             //�������ݵ��׽��� ���������ಥ��ַ
   SOCKET m_sSend;              //�������ݵ��׽��� ���ؼ���ಥ��ַ
   BOOL m_bQuit;                  //�û�֪ͨ�����߳��˳�
   char m_szUser[256];          //�û���
};

#define GROUP_TALK_H
#endif // !GROUP_TALK_H
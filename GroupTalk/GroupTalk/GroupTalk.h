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
	MT_JOIN = 1,//用户加入
	MT_LEAVE,   //用户离开
	MT_MESG,    //用户发送消息
	MT_MINE     //告诉新加入的用户的用户信息
};

typedef struct gt_hdr
{
	unsigned char gt_type;  //消息类型
	DWORD dwAddr;          //发送此消息的用户的IP地址
	char szUser[15];             //发送此消息的用户名
	int nDataLength;          //后面数据的长度
	char * data(){ return (char*)(this + 1);}
}GT_HDR;

class CGroupTalk
{
public:
	//构造函数 创建工作线程， 加入会议组
	CGroupTalk(HWND hNotifyWnd,
		    DWORD dwMultiAddr, DWORD dwLocalAddr = INADDR_ANY, int nTTL = 64);
	//析构函数 清理资源 离开会议组
	~CGroupTalk();
	//向其他成员发送消息， dwRemoteAddr为目标地址，0表示向所有成员发送
	BOOL SendText(char* szText,int nLen, DWORD dwRemoteAddr = 0);
protected:
	//帮助函数
	BOOL JoinGroup();
	BOOL LeaveGroup();
	//想指定地址发送UDP
	BOOL Send(char *szText, int nLen,DWORD dwRemoteAddr);
protected:
	//处理到来的封包
	void DispatchMsg(GT_HDR*, int nLen);
	friend DWORD WINAPI _GroupTalkEntry(LPVOID lpParam);

	HWND m_hNotifyWnd;    //主窗口句柄
   DWORD m_dwMultiAddr; //此组使用的多播地址
   DWORD m_dwLocalAddr; //用户要使用的本地地址
   int m_nTTL;                        //多播封包的TTL
   HANDLE m_hThread;        //工作线程句柄
   HANDLE m_hEvent;          //事件句柄， 用来使用重叠I/O接收数据
   SOCKET m_sRead;             //接收数据的套接字 它必须加入多播地址
   SOCKET m_sSend;              //发送数据的套接字 不必加入多播地址
   BOOL m_bQuit;                  //用户通知工作线程退出
   char m_szUser[256];          //用户名
};

#define GROUP_TALK_H
#endif // !GROUP_TALK_H
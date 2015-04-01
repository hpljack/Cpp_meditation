#include "GroupTalk.h"

CGroupTalk::CGroupTalk(HWND hNotifyWnd, DWORD dwMultiAddr, DWORD dwLocalAddr /* = INADDR_ANY */, int nTTL /* = 64 */)
{
	m_hNotifyWnd = hNotifyWnd;
	m_dwMultiAddr = dwMultiAddr;
	m_dwLocalAddr = dwLocalAddr;
	m_nTTL = nTTL;
	m_bQuit = FALSE;
	//ȡ�ñ������û�����Ϊ��ǰ�Ŀͻ��û���
	DWORD dw = 256;
	::gethostname(m_szUser,dw);
	//�����¼������߳�
	m_hEvent = ::WSACreateEvent();
	m_hThread = ::CreateThread(NULL,0,_GroupTalkEntry,this,0,NULL);
}

CGroupTalk::~CGroupTalk()
{
	//֪ͨ�����߳��˳��������˳��� �ͷ���Դ
	m_bQuit = TRUE;
	::SetEvent(m_hEvent);
	::WaitForSingleObject(m_hThread,INFINITE);
	::CloseHandle(m_hThread);
	::CloseHandle(m_hEvent);
}

int CGroupTalk::Send(char *szText, int nLen,DWORD dwRemoteAddr){
	//����UDP���
	SOCKADDR_IN dest;
	dest.sin_family = AF_INET;
	dest.sin_addr.S_un.S_addr = dwRemoteAddr;
	dest.sin_port = ::ntohs(GROUP_PORT);
	return ::sendto(m_sSend,szText,nLen,0,(SOCKADDR*)&dest,sizeof(dest));
}

BOOL CGroupTalk::JoinGroup(){
	//���������
	ip_mreq mcast;
	mcast.imr_interface.S_un.S_addr = INADDR_ANY;
	mcast.imr_multiaddr.S_un.S_addr = m_dwMultiAddr;
	int nRet = ::setsockopt(m_sRead,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char*)&mcast,sizeof(mcast));
	if(nRet != SOCKET_ERROR){
		//���������г�Ա����MT_JOIN��Ϣ�� ���������Լ����û���Ϣ
		char buf[sizeof(GT_HDR)] = {0};
		GT_HDR* pHeader = (GT_HDR*)buf;
		pHeader->gt_type = MT_JOIN;
		strncpy(pHeader->szUser,m_szUser,15);
		Send(buf,sizeof(GT_HDR),m_dwMultiAddr);
		return TRUE;
	}
	return FALSE;
}
BOOL CGroupTalk::LeaveGroup(){
	return TRUE;
}
DWORD WINAPI _GroupTalkEntry(LPVOID lpParam){
	CGroupTalk* pTalk = (CGroupTalk*)lpParam;
	//���������׽��ֺͽ����׽���
	pTalk->m_sSend = ::socket(AF_INET,SOCK_DGRAM,0);
	pTalk->m_sRead = ::WSASocket(AF_INET,SOCK_DGRAM,0,NULL,0,WSA_FLAG_OVERLAPPED);
	//�������������׽���Ҳ���մ��׽����������Ķ˿ڵ�ַ
	BOOL bReuse = TRUE;
	::setsockopt(pTalk->m_sRead,SOL_SOCKET,SO_REUSEADDR,(char*)&bReuse,sizeof(BOOL));
	//���öಥ�����TTLֵ
	::setsockopt(pTalk->m_sSend,IPPROTO_IP,IP_MULTICAST_TTL,(char*)&pTalk->m_nTTL,sizeof(pTalk->m_nTTL));
	//����Ҫʹ�õķ��ͽӿ�
	::setsockopt(pTalk->m_sSend,IPPROTO_IP,IP_MULTICAST_IF,(char*)&pTalk->m_dwLocalAddr,sizeof(pTalk->m_dwLocalAddr));
	//�󶨽����׽��ֵ����ض˿�
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = ::ntohs(GROUP_PORT);
	si.sin_addr.S_un.S_addr = pTalk->m_dwLocalAddr;
	int nRet = ::bind(pTalk->m_sRead,(sockaddr*)&si,sizeof(si));
	if(nRet == SOCKET_ERROR){
		::closesocket(pTalk->m_sSend);
		::closesocket(pTalk->m_sRead);
		//::SendMessage(pTalk->m_hNotifyWnd,WM_GROUPTALK ,-1 ,(long)"bind failded\n");
		return -1;
	}
	//����ಥ��
	WSAOVERLAPPED ol = {0};
	ol.hEvent = pTalk->m_hEvent;
	WSABUF buf;
	buf.buf = new char [BUFFER_SIZE];
	buf.len = BUFFER_SIZE;
	while (TRUE)
	{
		//Ͷ�ݽ���I/O
		DWORD dwRecv;
		DWORD dwFlags = 0;
		sockaddr_in saFrom;
		int nFromLen = sizeof(saFrom);
		int ret = ::WSARecvFrom(pTalk->m_sRead,&buf,1,&dwRecv,&dwFlags,(sockaddr*)&saFrom,&nFromLen,&ol,NULL);
		if(ret == SOCKET_ERROR){
			if(::WSAGetLastError() != WSA_IO_PENDING){
				::SendMessage(pTalk->m_hNotifyWnd,WM_GROUPTALK, - 1,(long)"PostRecv failed\n");
				pTalk->LeaveGroup();
				::closesocket(pTalk->m_sSend);
				::closesocket(pTalk->m_sRead);
				break;
			}
		}
		//�ȴ�I/O��� ������
		::WSAWaitForMultipleEvents(1,&pTalk->m_hEvent,TRUE,WSA_INFINITE,FALSE);
		if (pTalk->m_bQuit)//�Ƿ��˳�
		{
			pTalk->LeaveGroup();
			::closesocket(pTalk->m_sSend);
			::closesocket(pTalk->m_sRead);
			break;
		}

		BOOL b = ::WSAGetOverlappedResult(pTalk->m_sRead,&ol,&dwRecv,FALSE,&dwFlags);
		if(b && dwRecv >= sizeof(GT_HDR)){
			GT_HDR* pHeader = (GT_HDR*)buf.buf;
			//��дԴ��ַ��Ϣ
			pHeader->dwAddr  = saFrom.sin_addr.S_un.S_addr;
			pTalk->DispatchMsg(pHeader,dwRecv);
		}
	}
	delete buf.buf;
	return 0;
}

void CGroupTalk::DispatchMsg(GT_HDR* pHeader, int nLen){
	if(pHeader->gt_type == MT_JOIN) //���û�����
	{
		//�����û������Լ����û���Ϣ
		char buff[sizeof(GT_HDR)] = {0};
		GT_HDR* pSend = (GT_HDR*)buff;
		strncpy(pSend->szUser,m_szUser,15);
		pSend->gt_type = MT_MINE;
		pSend->nDataLength = 0;
		Send(buff,sizeof(GT_HDR),pHeader->dwAddr);
	}else if (pHeader->gt_type = MT_MINE)
	{//�Ƿ������Լ�������� ������
		if(strcmp(pHeader->szUser,m_szUser) == 0)
			return;
		//Ϊ�˼���� �������û��������û�����
		pHeader->gt_type = MT_JOIN;
	}
	::SendMessage(m_hNotifyWnd,WM_GROUPTALK,0,(LPARAM)pHeader);
}
int CGroupTalk::SendText(char* szText,int nLen, DWORD dwRemoteAddr /* = 0 */){
	//������Ϣ���
	char buf[sizeof(GT_HDR) + 1024] = {0};
	GT_HDR* pHeader = (GT_HDR*)buf;
	pHeader->gt_type = MT_MESG;
	//pHeader->nDataLength = nLen < 1024? nLen: 1024;
	pHeader->nDataLength = max(nLen,1024);
	strncpy(pHeader->szUser,m_szUser,15);
	strncpy(pHeader->data(),szText,pHeader->nDataLength);
	//���ʹ˷��
	int nSends = Send(buf,pHeader->nDataLength + sizeof(GT_HDR),dwRemoteAddr = 0? m_dwMultiAddr:dwRemoteAddr);
	return nSends - sizeof(GT_HDR);
}
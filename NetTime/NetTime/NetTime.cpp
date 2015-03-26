#include "..\..\common\InitSock.h"
#include <stdio.h>

void setTimeFromTP(ULONG ulTime){ //����ʱ��Э�鷵�ص�ʱ������ϵͳʱ�� TP time protocol
	//windows�ļ�ʱ����һ��64λ��ֵ�����Ǵ�1601��1��1������12��00�����ڵ�ʱ����
	//��λ��1/1000 000�� ��100���֮һ�루100-nanosecond��
	FILETIME ft;
	SYSTEMTIME st;
	st.wYear = 1900;
	st.wMonth = 1;
	st.wDay = 1;
	st.wHour = 0;
	st.wMinute = 0;
	st.wSecond = 0;
	st.wMilliseconds = 0;
	SystemTimeToFileTime(&st,&ft);
	//Ȼ��TimeProtocolʹ�õĻ�׼ʱ������ѽ���ȥ��ʱ�䣬��ultime
	LONGLONG *pLLong = (LONGLONG*)&ft;
	//ע��  �ļ�ʱ�䵥λ��1/1000000�룬
	*pLLong += (LONGLONG)1000000* ulTime;
	FileTimeToSystemTime(&ft,&st);
	SetSystemTime(&st);
}

CInitSock initsock;
int main(){
	SOCKET s = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(s == INVALID_SOCKET){
		printf("Failed socket()\n");
		return 0;
	}

	//Զ�̵�ַ ʱ�������
	sockaddr_in srvAddr;
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(37);
	srvAddr.sin_addr.S_un.S_addr = inet_addr("202.112.10.60");

	if(::connect(s,(sockaddr*)&srvAddr,sizeof(srvAddr)) == -1){
		printf("Failed connect()\n");
		system("pause");
		return 0;
	}

	ULONG ulTime = 0;
	int nRecv = ::recv(s,(char*)ulTime,sizeof(ulTime),0);
	if(nRecv>0){
		ulTime = ntohl(ulTime);
		setTimeFromTP(ulTime);
		printf("�ɹ����������ʱ��ͬ��!\n");
	}else{
		printf("ʱ�����������ȷ����ǰʱ�䣡\n");
	}
	::closesocket(s);

	system("pause");
	return 0;
}
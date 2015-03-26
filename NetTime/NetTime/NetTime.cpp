#include "..\..\common\InitSock.h"
#include <stdio.h>

void setTimeFromTP(ULONG ulTime){ //根据时间协议返回的时间设置系统时间 TP time protocol
	//windows文件时间是一个64位的值，它是从1601年1月1日中午12：00到现在的时间间隔
	//单位是1/1000 000秒 即100万分之一秒（100-nanosecond）
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
	//然后将TimeProtocol使用的基准时间加上已近逝去的时间，即ultime
	LONGLONG *pLLong = (LONGLONG*)&ft;
	//注意  文件时间单位是1/1000000秒，
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

	//远程地址 时间服务器
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
		printf("成功与服务器的时间同步!\n");
	}else{
		printf("时间服务器不能确定当前时间！\n");
	}
	::closesocket(s);

	system("pause");
	return 0;
}
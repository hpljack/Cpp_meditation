#include "..\..\common\InitSock.h"
#include <stdio.h>

CInitSock initsock;
#define BUFFER_SIZE 1024

typedef struct _PER_HANDLE_DATA{
	SOCKET s;     //对应的套接字句柄
	sockaddr_in addr;//客户端地址
}PER_HANDLE_DATA,*PPER_HANDLE_DATA;

typedef struct _PER_IO_DATA{
	OVERLAPPED ol;     //重叠结构
	char buf[BUFFER_SIZE];//数据缓冲区
	int nOperationType;    //操作类型
#define OP_READ 1
#define OP_WRITE 2
#define OP_ACCEPT 3
}PER_IO_DATA,*PPER_IO_DATA;


int main(){
	int nPort = 4567;
	//创建完成端口对象，创建工作线程处理完成端口对象中事件
	HANDLE hCompletion = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE,0,0,0）;
	::CreateThread(NULL,0,ServerThread,(LPVOID)hCompletion,0,0);

	return 0;
}

DWORD WINAPI ServerThread(LPVOID lpParam){

}

#include "..\..\common\InitSock.h"
#include <stdio.h>

CInitSock initsock;
#define BUFFER_SIZE 1024

typedef struct _PER_HANDLE_DATA{
	SOCKET s;     //��Ӧ���׽��־��
	sockaddr_in addr;//�ͻ��˵�ַ
}PER_HANDLE_DATA,*PPER_HANDLE_DATA;

typedef struct _PER_IO_DATA{
	OVERLAPPED ol;     //�ص��ṹ
	char buf[BUFFER_SIZE];//���ݻ�����
	int nOperationType;    //��������
#define OP_READ 1
#define OP_WRITE 2
#define OP_ACCEPT 3
}PER_IO_DATA,*PPER_IO_DATA;


int main(){
	int nPort = 4567;
	//������ɶ˿ڶ��󣬴��������̴߳�����ɶ˿ڶ������¼�
	HANDLE hCompletion = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE,0,0,0��;
	::CreateThread(NULL,0,ServerThread,(LPVOID)hCompletion,0,0);

	return 0;
}

DWORD WINAPI ServerThread(LPVOID lpParam){

}

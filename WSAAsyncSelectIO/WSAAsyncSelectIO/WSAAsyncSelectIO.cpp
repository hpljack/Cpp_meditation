#include "../../common/InitSock.h"
#include <stdio.h>


//�Զ�����Ϣ
#define  WM_SOCKET = (WM_USER + 101)
#define  MAX_LEN = 1024


//Ϊ��ʹ��WSAAsyncSelectIOģ�ͣ����򴴽�һ�����εĴ��ڣ����ں���WindowProc


LRESULT CALLBACK WindowProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam);

CInitSock initsock;
int main(){
	char szClassName[] ="MainWClass";
	WNDCLASSEX wndClass;

	wndClass.cbSize = sizeof(WNDCLASS);
	wndClass.style = CS_HREDRAW|CS_VREDRAW;
	wndClass.lpfnWndProc = WindowProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = NULL;
	wndClass.hIcon = ::LoadIcon(NULL,IDI_APPLICATION);
	wndClass.hCursor = ::LoadCursor(NULL,IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.hIconSm = NULL;
	wndClass.lpszClassName = szClassName;
	::RegisterClassEx(&wndClass);

	HWND hWnd = ::CreateWindowEx(
					0,
					szClassName,
					"",
					WS_OVERLAPPED,
					CW_USEDEFAULT,
					CW_USEDEFAULT,
					CW_USEDEFAULT,
					CW_USEDEFAULT,
					NULL,
					NULL,
					NULL,
					NULL);
	if(hWnd == NULL){
		::MessageBox(NULL,"�������ڳ���","error",MB_OK);
		return -1;
	}

	USHORT nPort = 4567;
	SOCKET sListen = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(nPort);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;

	if(::bind(sListen,(sockaddr*)&sin,sizeof(sin)) == SOCKET_ERROR){
		printf("Failed bind()\n");
		return -1;
	}

	//���׽�����Ϊ����֪ͨ��Ϣ����
	::WSAAsyncSelect(sListen, hWnd, WM_SOCKET, FD_ACCEPT|FD_CLOSE);
	::listen(sListen,5);//�������ģʽ
	MSG msg;
	while(::GetMessage(&msg,NULL,0,0)){
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
	//��GetMessage����0ʱ�������
	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam){
	switch (uMsg)
	{
	case WM_SOCKET:
		{
			SOCKET s = wParam; //ȥ�����׽��ַ��͵ľ��
			if(WSAGETSELECTERROR(lParam))//����Ƿ��г���
			{
				::closesocket(s);
				return 0;
			}
			switch (WSAGETSELECTEVENT(lParam))
			{
			case FD_ACCEPT: //�����е��׽��ּ�⵽�����ӽ���
				{
					SOCKET sClient = ::accept(s,NULL,NULL);
					::WSAAsyncSelect(sClient,hWnd,WM_SOCKET,FD_READ|FD_WRITE|FD_CLOSE);
				}
				break;
			case FD_WRITE:
				{
				}
				break;
			case FD_READ:
				{
					char szText[1024] = {0};
					if(::recv(s,szText,1024,0) == -1)
						::closesocket(s);
					else
						printf("���յ�������%s\n",szText);
				}
				break;
			case FD_CLOSE:
				{
					::closesocket(s);
				}
				break;
			}

		}
		return 0;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}
	//
	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}
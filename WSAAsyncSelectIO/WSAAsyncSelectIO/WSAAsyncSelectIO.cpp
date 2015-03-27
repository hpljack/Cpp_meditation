#include "../../common/InitSock.h"
#include <stdio.h>


//自定义消息
#define  WM_SOCKET = (WM_USER + 101)
#define  MAX_LEN = 1024


//为了使用WSAAsyncSelectIO模型，程序创建一个隐形的窗口，窗口函数WindowProc


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
		::MessageBox(NULL,"创建窗口出错！","error",MB_OK);
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

	//将套接字设为窗口通知消息类型
	::WSAAsyncSelect(sListen, hWnd, WM_SOCKET, FD_ACCEPT|FD_CLOSE);
	::listen(sListen,5);//进入监听模式
	MSG msg;
	while(::GetMessage(&msg,NULL,0,0)){
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
	//当GetMessage返回0时程序结束
	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam){
	switch (uMsg)
	{
	case WM_SOCKET:
		{
			SOCKET s = wParam; //去的有套接字发送的句柄
			if(WSAGETSELECTERROR(lParam))//检查是否有出错
			{
				::closesocket(s);
				return 0;
			}
			switch (WSAGETSELECTEVENT(lParam))
			{
			case FD_ACCEPT: //监听中的套接字检测到有连接进入
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
						printf("接收到的数据%s\n",szText);
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
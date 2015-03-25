#include <windows.h>
#include <stdio.h>
#include <iostream>
using namespace std;

DWORD WINAPI myfunc1(
	LPVOID lpParameter
);
DWORD WINAPI myfunc2(
	LPVOID lpParameter
);

CRITICAL_SECTION Section;//临界区对象
static int a1 = 0;//全局变量

int main(){
	HANDLE h1,h2;

	InitializeCriticalSection(&Section);
	::Sleep(10000);

	h1 = CreateThread(NULL,0,myfunc1,NULL,0,NULL);
	cout<<"线程1开始运行！"<<endl;
	h2 = CreateThread(NULL,0,myfunc2,NULL,0,NULL);
	cout<<"线程2开始运行！"<<endl;
	::CloseHandle(h1);
	::CloseHandle(h2);

	if (getchar()=='q'){
		DeleteCriticalSection(&Section);
		return 0;
	}else
	{
		::Sleep(100);
		}
}
/*
DWORD WINAPI myfunc1( LPVOID lpParameter ){
	cout<<"线程1正在运行！"<<endl;
	return 0;
}
DWORD WINAPI myfunc2(LPVOID lpParameter){
	cout<<"线程2正在运行！"<<endl;
	return 0;
}
*/

DWORD WINAPI myfunc1( LPVOID lpParameter ){
	while(1){
		EnterCriticalSection(&Section);
		a1++;
		if (a1 < 10000)
		{
			::Sleep(1000);
			cout<<"Thread 1 was counting "<<a1<<endl;
			LeaveCriticalSection(&Section);
		}else{
			LeaveCriticalSection(&Section);
			break;
		}
	}
	return 0;
}

DWORD WINAPI myfunc2( LPVOID lpParameter ){
	while(1){
		EnterCriticalSection(&Section);
		a1++;
		if (a1 < 10000)
		{
			::Sleep(1000);
			cout<<"Thread 2 was counting "<<a1<<endl;
			LeaveCriticalSection(&Section);
		}else{
			LeaveCriticalSection(&Section);
			break;
		}
	}
	return 0;
}
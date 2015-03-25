#include <iostream>
#include "MFC.h"

class CMyWinApp: public CWinApp{
public:
	CMyWinApp(){cout<<"CMyWinApp constructor"<<endl;}
	~CMyWinApp(){cout<<"CMyWinApp destructor"<<endl;}
};

class CMyFrameWnd: public CFrameWnd{
public:
	CMyFrameWnd(){
		cout<<"CMyFrameWnd constructor"<<endl;
	}
	~CMyFrameWnd(){cout<<"CMyFrameWnd destructor"<<endl;}
};


void mfc1Test();
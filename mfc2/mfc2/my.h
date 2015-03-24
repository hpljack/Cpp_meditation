#include <iostream>
#include "mfc.h"

class CMyWinApp: public CWinApp{
public:
	CMyWinApp(){cout<<"CMyWinApp constructor"<<endl;}
	~CMyWinApp(){cout<<"CMyWinApp destructor"<<endl;}

	virtual BOOL InitInstance();
};

class CMyFrameWnd: public CFrameWnd{
public:
	CMyFrameWnd();
	~CMyFrameWnd(){cout<<"CMyFrameWnd destructor"<<endl;}
};


void mfc2Test();
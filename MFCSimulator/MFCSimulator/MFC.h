#pragma once
#include <iostream>

class CObject{
public:
	CObject(){std::cout<<"CObject constructor"<<endl;}
	~CObject(){cout<<"CObject destructor"<<endl;}
};

class CCmdTarget: public CObject{
public:
	CCmdTarget(void){cout<<"CCmdTarget constructor"<<endl;}
	~CCmdTarget(){cout<<"CCmdTarget destructor"<<endl;}
};

class CWinThread: public CCmdTarget{
public:
	CWinThread(){cout<<"CWinThread constructor"<<endl;}
	~CWinThread(){cout<<"CWinThread destructor"<<endl;}
};

class CWinApp: public CWinThread{
public:
	CWinApp* m_pCurrentApp;
public:
	CWinApp(){cout<<"CWinApp constructor"<<endl;}
	~CWinApp(){cout<<"CWinApp destructor"<<endl;}
};

class CDocument: public CCmdTarget{
public:
	CDocument(){cout<<"CDocument constructor"<<endl;}
	~CDocument(){cout<<"CDocument destructor"<<endl;}
};

class CWnd: public CCmdTarget{
public:
	CWnd(){cout<<"CWnd constructor"<<endl;}
	~CWnd(){cout<<"CWnd destructor"<<endl;}
};

class CFrameWnd: public CWnd{
public:
	CFrameWnd(){cout<<"CFrameWnd constructor"<<endl;}
	~CFrameWnd(){cout<<"CFrameWnd destructor"<<endl;}
};

class CView: public CWnd{
public:
	CView(){cout<<"CView costructor"<<endl;}
	~CView(){cout<<"CView destructor"<<endl;}
};

//global function
CWinApp* AfxGetApp();


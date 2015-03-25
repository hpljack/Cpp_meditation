#define BOOL int
#define TRUE 1
#define FALSE 0

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

	virtual BOOL InitInstance(){
		cout<<"CWinThread::InitInstance"<<endl;
		return TRUE;
	}
	virtual int Run(){
		cout<<"CWinThread::Run"<<endl;
		return 1;
	}
};

class CWnd;//Ç°ÖÃ

class CWinApp: public CWinThread{
public:
	CWinApp* m_pCurrentApp;
	CWnd* m_pMaindWnd;
public:
	CWinApp(){
		m_pCurrentApp = this;
	}
	~CWinApp(){}

	virtual BOOL InitApplication(){
		cout<<"CWinApp::InitApplication"<<endl;
		return TRUE;
	}
	virtual BOOL InitInstance(){
		cout<<"CWinApp::InitInstance"<<endl;
		return TRUE;
	}
	virtual int Run(){
		cout<<"CWinApp::Run"<<endl;
		return CWinThread::Run();
	}
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

	virtual BOOL Create();
	BOOL CreateEx();
	virtual BOOL PreCreateWindow();
};

class CFrameWnd: public CWnd{
public:
	CFrameWnd(){cout<<"CFrameWnd constructor"<<endl;}
	~CFrameWnd(){cout<<"CFrameWnd destructor"<<endl;}

	BOOL Create();
	virtual BOOL PreCreateWindow();
};

class CView: public CWnd{
public:
	CView(){cout<<"CView costructor"<<endl;}
	~CView(){cout<<"CView destructor"<<endl;}
};

//global function
CWinApp* AfxGetApp();

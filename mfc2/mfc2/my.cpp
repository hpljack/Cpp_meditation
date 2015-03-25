#include "stdafx.h"
#include "my.h"

CMyWinApp theApp; //global object

BOOL CMyWinApp::InitInstance(){
	cout<<"CMyWinApp::InitInstance"<<endl;
	m_pMaindWnd = new CMyFrameWnd;
	return TRUE;
}
CMyFrameWnd::CMyFrameWnd(){
	cout<<"CMyFrameWnd::CMyFrameWnd"<<endl;
	Create();
}

void mfc2Test(){
	CWinApp* pApp = AfxGetApp();
	pApp->InitApplication();
	pApp->InitInstance();
	pApp->Run();
}
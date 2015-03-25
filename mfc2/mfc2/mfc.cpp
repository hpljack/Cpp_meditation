#include "stdafx.h"
#include "my.h"

extern CMyWinApp theApp; //extern global object

BOOL CWnd::Create(){
	cout<<"Cwnd::Create"<<endl;
	return TRUE;
}

BOOL CWnd::CreateEx(){
	cout<<"CWnd::CreateEX"<<endl;
	PreCreateWindow();
	return TRUE;
}

BOOL CWnd::PreCreateWindow(){
	cout<<"CWnd::PreCreateWindow"<<endl;
	return TRUE;
}

BOOL CFrameWnd::Create(){
	cout<<"CFrameWnd::Create"<<endl;
	CreateEx();
	return TRUE;
}

BOOL CFrameWnd::PreCreateWindow(){
	cout<<"CFrameWnd::PreCreateWindow"<<endl;
	return TRUE;
}

CWinApp* AfxGetApp(){
	return theApp.m_pCurrentApp;
}
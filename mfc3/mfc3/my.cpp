#include "stdafx.h"
#include "my.h"
#include <iostream>
using namespace std;

CMyWinApp theApp;

BOOL CMyWinApp::InitInstance(){
	m_pMainWnd = new CMyFrameWnd;
	return TRUE;
}

CMyFrameWnd::CMyFrameWnd(){
	Create();
}

void PrintAllClasses(){
	CRuntimeClass* pClass;

	//just walk through the simple list of registered classes
	for (pClass = CRuntimeClass::pFirstClass; pClass != NULL;pClass = pClass->m_pNextClass){
		cout<<pClass->m_lpszClassName<<endl;
		cout<<pClass->m_nObjectSize<<endl;
		cout<<pClass->m_wSchema<<endl;
	}
}


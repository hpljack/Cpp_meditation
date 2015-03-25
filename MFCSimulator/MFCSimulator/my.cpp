#include "stdafx.h"
#include "my.h"

CMyWinApp theApp; //global object

void mfc1Test(){
	cout<<"*** mfc1******"<<endl;
	CWinApp* pApp = AfxGetApp();
}
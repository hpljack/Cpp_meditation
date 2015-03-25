#include "stdafx.h"
#include "MyDoc.h"


CMyDoc::CMyDoc(void)
{
}


CMyDoc::~CMyDoc(void)
{
}

void CMyDocTest(){
	CMyDoc mydoc;
	CMyDoc* pmydoc = new CMyDoc();

	cout<<"#1 testing"<<endl;
	mydoc.func();

	cout<<"#2 testing"<<endl;
	((CDocument*)(&mydoc))->func();

	cout<<"#3 testing"<<endl;
	pmydoc->func();

	cout<<"#4 testing"<<endl;
	((CDocument)mydoc).func();
}

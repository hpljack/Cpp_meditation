#include "stdafx.h"
#include "Demo.h"

CDemo::~CDemo(void)
{
	cout<<"Destructor called for "<<name<<endl;
}

CDemo::CDemo(const char* str){
	strncpy(name,str,20);
	cout<<"Constructor called for "<<name<<endl;
}

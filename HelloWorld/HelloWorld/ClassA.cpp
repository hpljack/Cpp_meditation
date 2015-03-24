#include "stdafx.h"
#include "ClassA.h"

#include <iostream>
#include <stdio.h>

using namespace std;

ClassA::ClassA(void)
{
}


ClassA::~ClassA(void)
{
}

void ClassATest(void){
	cout<<"*****************ClassATest*****************"<<endl;

	cout<<sizeof(ClassA)<<endl;
	cout<<sizeof(ClassB)<<endl;
	cout<<sizeof(ClassC)<<endl;

	ClassA  a;
	ClassB  b;
	ClassC  c;

	b.m_data1 = 1;
	b.m_data2 = 2;
	b.m_data3 = 3;
	c.m_data1 = 11;
	c.m_data2 = 12;
	c.m_data3 = 13;
	c.m_data4 = 14;
	c.ClassA::m_data1 = 111;
	
	cout<<b.m_data1<<endl;
	cout<<b.m_data2<<endl;
	cout<<b.m_data3<<endl;
	cout<<c.m_data1<<endl;
	cout<<c.m_data2<<endl;
	cout<<c.m_data3<<endl;
	cout<<c.m_data4<<endl;
	cout<<c.ClassA::m_data1<<endl;

	cout<<&b<<endl;
	cout<<&(b.m_data1)<<endl;
	cout<<&(b.m_data2)<<endl;
	cout<<&(b.m_data3)<<endl;
	cout<<&c<<endl;
	cout<<&(c.m_data1)<<endl;
	cout<<&(c.m_data2)<<endl;
	cout<<&(c.m_data3)<<endl;
	cout<<&(c.m_data4)<<endl;
	cout<<&(c.ClassA::m_data1)<<endl;
}


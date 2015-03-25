#pragma once
class ClassA
{
public:
	ClassA(void);
	~ClassA(void);
public:
	int m_data1;
	int m_data2;
public:
	void func1(){}
	void func2(){}
	virtual void vfunc1(){}
	virtual void vfunc2(){}
};

class ClassB: public ClassA{
public:
	int m_data3;
	void func2(){}
	virtual void vfunc1(){}
};

class ClassC: public ClassB{
public:
	int m_data1;
	int m_data4;
	void func2(){}
	virtual void vfunc1(){}
};


void ClassATest(void);


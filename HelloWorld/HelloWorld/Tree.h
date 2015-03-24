#pragma once
/*
  template class
  include the template class test code
*/
template <class T>
class CTree
{
public:
	CTree(T t1, T t2, T t3);
	T Min();
	T Max();
	~CTree(void);
private:
	T a, b, c;
};


void tempalateClassTest();

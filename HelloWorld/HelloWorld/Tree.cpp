#include "stdafx.h"
#include "Tree.h"

template <class T>
CTree<T>::CTree(T t1, T t2, T t3):a(t1),b(t2),c(t3)
{
	return ;
}

template <class T>
T CTree<T>::Max(){
  T max = a < b? b: a;
  return max < c ? c: max;
}

template <class T>
T CTree<T>::Min(){
	T min = a < b ? a : b;
	return min < c ? min: c;
}

template <class T>
CTree<T>::~CTree(void)
{
}

void tempalateClassTest(){
	cout<<"***tempalateClassTest****"<<endl;
	CTree<int> obj1(2,5,4);
	cout<<obj1.Min()<<endl;
	cout<<obj1.Max()<<endl;

	CTree<float> obj2(3.3,-45.3,4.54);
	cout<<obj2.Min()<<endl;
	cout<<obj2.Max()<<endl;

	CTree<long> obj3(64600L,437847L,364873L);
	cout<<obj3.Min()<<endl;
	cout<<obj3.Max()<<endl;
}

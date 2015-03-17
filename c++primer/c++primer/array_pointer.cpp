#include "stdafx.h"
#include "array_pointer.h"
#include <iostream>

using std::cout;
using std::endl;

void ArrayTest(){
	cout<<"*****ArrayTest***"<<endl;
	const size_t array_size = 10;
	int ia[array_size];
	for (size_t i = 0; i != array_size; ++i){
		ia[i] = i;
		cout<<ia[i]<<endl;
	}
}

void PointerTest(){
	cout<<"*****PointerTest****"<<endl;
	//指针风格
	string* sp1;
	string* sp2;

	int ival = 1024;
	int* pi = &ival;
	cout<<*pi<<endl;

	//void pointer
	double obj = 3.14;
	double* pd =&obj;
	void* pv = &obj; //void pointer can assigned by any type
	pv = pd;
	cout<<*pd<<endl;

	string s = "some value";
	sp1 = &s;//初始化
	cout<<*sp1<<endl;
	*sp1 = "good bye";
	cout<<*sp1<<endl;

	//引用和指针的区别
	int ival2 = 2048;
	int *pi1 = &ival2, *pi2 = &ival2;
	cout<<"pointer"<<endl;
	cout<<"ival="<<ival<<" "<<"ival2="<<ival2<<endl;
	cout<<*pi1<<" "<<*pi2<<endl;
	pi1 = pi2;
	cout<<*pi1<<" "<<*pi2<<endl;
	cout<<"ival="<<ival<<" "<<"ival2="<<ival2<<endl;

	//引用
	int &ri1 = ival, &ri2= ival2;
	cout<<"reference"<<endl;
	cout<<"ival="<<ival<<" "<<"ival2="<<ival2<<endl;
	cout<<ri1<<" "<<ri2<<endl;
	ri1 = ri2;
	cout<<ri1<<" "<<ri2<<endl;
	cout<<"ival="<<ival<<" "<<"ival2="<<ival2<<endl;

	//指向指针的指针 间接操作
	//int *pi = &ival;
	int **ppi = &pi;

	cout<<"The value of ival"<<endl
		<<" Direct value: "<<ival<<endl
		<<" Indirect value : " <<*pi<<endl
		<<" Double indirect value: "<<**ppi<<endl;

	//use pointer acces array

	int ia[] = {0,2,4,8,10};
	int *ip = ia;
	int *last = ia + 4;
	int *last2 = ip + 4;
	cout<<*ip<<endl;
	cout<<*(ip+4)<<endl;
	cout<<*last2<<endl;
	cout<<*last<<endl;

	//指针是数组的迭代器
	const size_t arr_sz = 5;
	int int_arr[arr_sz] = {0,1,2,3,4};
	for(int *pbegin = int_arr, *pend = int_arr + arr_sz; pbegin != pend; ++pbegin){
		cout<<*pbegin<<endl;
	}

	//指向const对象的指针 ****不能修改const对象的值****
	//1、指向const对象的指针不能改变const对象的值 所以该指针也必须是const类型
	//2、指向const对象的指针可以指向非const对象
	//3、指向const对象的指针 指向的是非const对象 可以用其他方法修改非const对象
	const double* cptr;
	const double PI = 3.14;
	cptr = &PI;
	//*cptr = 34; //errror 不能给const指针赋值

	//double *ptr = &PI;//error const对象不能用非const指针
	double dval = 3.14;
	cptr = &dval;
		
	//const指针 ***指针本身的值不能修改***
	int errNumb = 0;
	int* const curErr = &errNumb;
	*curErr = 10;
	cout<<*curErr<<endl;
	//curErr = &ival; //error 不能修改指针

	//指向const对象的const指针 ****既不能修改指针所指向的值 也不能修改指针本身******
	const double * const pi_str = &PI;
	//pi_str = 43.4; //error
	//pi_str = &dval;//error

	//typedef 和指针
}
#include "stdafx.h"
#include "expression.h"
#include "Sales_item.h"

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

void simple_expre(){
	cout<<"****simple_expre****"<<endl;
	short short_value = 32767;
	short ival = 1;
	short_value += ival;
	cout<<"short_value: "<<short_value<<endl;
}

void bitTest(){
	cout<<"****bitTest****"<<endl;
	unsigned char bits = 0227;
	bits = ~bits; //取反
	bits>>1;     //右移
	bits<<2;     //左移

	bits & 0xffff; //与
	bits | 0xffff; //或
	bits ^ 0xffff; //异或
}

void sizeOfTest(){
	cout<<"****sizeOfTest****"<<endl;
	Sales_item  item, *p;
	cout<<"sizeof(Sales_item)="<<sizeof(Sales_item)<<endl; //48
	cout<<"sizeof(item)="<<sizeof item<<endl;//48
	cout<<"sizeof(*p)="<<sizeof *p<<endl;//48
	cout<<"sizeof(p)="<<sizeof p<<endl;//4
}

void newdeleteTest(){
	cout<<"***newdeleteTest***"<<endl;
	int *pi = new int(12);
	string *ps = new string(10,'9');
	cout<<*ps<<endl;
	/*
	for (int i = 0; i != 12; ++i){
		*pi = i;
		cout<<*pi++<<endl;
	}
	*/
	delete pi;
	delete ps;
	//垂悬指针 dangling pointer 指针所指向的对象已经被释放
	//一旦删除了指针所指向的对象，立即将指针置为零

	//const对象的动态分配和回收
	const int *pci = new const int(12);
	const string *pcs = new const string;

	delete pci;
	delete pcs;
}

void conversionTest(){
	cout<<"***conversionTest****"<<endl;
	int ival = 0;
	ival = 3.123 + 3; //隐式转换 implicit type conversion
	cout<<ival<<endl;
	//算术转换 arithmetic conversion
	double dval = 43.0;
	double ddval = dval + ival;
	cout<<ddval<<endl;

	//enum cast
	enum points {point2d = 2, point2w, point3d =3, point3w};
	const size_t array_size = 1024;
	int chunk_size = array_size * point2w;
	int array_3d = array_size * point3d;

	//显示转换 强制转换
	//static_cast dynamic_cast const_cast reinterpret_cast
	double dval1 = 32;
	int ival1 = 323;
	ival1 *= dval1;
	ival1 *= static_cast<int>(dval1); //static_cast  大类型转换为小类型
	cout<<ival1<<endl;
}
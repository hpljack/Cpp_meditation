// c++primer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Sales_item.h"
#include "stlib_test.h"
#include "array_pointer.h"
#include "expression.h"
#include "func.h"
#include "iolib.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	//alarm ring
	cout<<"alarm\a"<<endl; // \a alarm ring 
	std::string titleA = "C++ primer, 4th Ed";
	cout<<titleA<<endl;
	string titileB("C++ primer, 4th Ed");
	cout<<titileB<<endl;

	string all_nine(10,'9');
	cout<<all_nine<<endl;

	string empty;
	
	string* pStr = new string("hello new string");
	cout<<*pStr<<endl;

	//const
	const int bufSize = 512;
	for (int i = 0; i != bufSize; ++i){
		//
	}
	
	//引用
	int ival = 1024;
	int &refVal = ival;
//	int &refVal2; //error
//	int &refVal3 = 10;//error
	refVal += 2;
	cout<<ival<<endl;
	cout<<refVal<<endl;

	//const引用
	const int ival2 = 1023;
	const int &refval2 = ival2;
//	refval2 += 2; //error
//	ival2 += 2;  //error

	//typedef
	typedef double wages;
	typedef int exam_score;
	typedef wages salary;

	wages hourly,weekly;
	exam_score test_result;
	
	//枚举 enum
	enum open_modes {input,ouput,append};
	enum week {sun,mon,tes,wed,thr,sta,fri};
	enum Forms {shape=1, sphere,cylinder,polygon};


	Sales_item item1("323-32323-NDBS",3,8.9);
	Sales_item item2 = item1;


	//StandardLib Test
	stringTest();
	vectorTest();
	iteratorTest();

	//array and pointer
	ArrayTest();
	PointerTest();

	//expression test
	simple_expre();
	sizeOfTest();
	newdeleteTest();
	conversionTest();

	//func test
	func_test();

	//
	InitContainer_test();
	
	cin.get();
	return 0;
}

